#!/usr/bin/python

# Much of CGIHTTPServer.py has been copied to this.

import os
import sys
import socket
import BaseHTTPServer
import SimpleHTTPServer
import urllib
import re

class MyHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
  def __init__(self, * args):
    self.re_cmd = re.compile("^/([a-zA-Z_][a-zA-Z_0-9]*)(\([^)]*\))(.*)")
    self.Base = self.__class__.__bases__[0]
    apply(self.Base.__init__, [self] + list(args))
  def is_command(self):
    m = self.re_cmd.search(self.path)
    if m:
      self.cmd = urllib.unquote(m.group(1))
      self.args = urllib.unquote(m.group(2))
      self.rest = urllib.unquote(m.group(3))
      print "d0:", self.cmd, self.args, self.rest
      return 1
    return 0
  def do_GET(self):
    if self.is_command():
      output = self.wfile
      self.send_response(200)
      self.send_header("Content-type", "text/html")
      self.end_headers()
      output.write("hoge")
    else:
      return self.Base.do_GET(self)
  def do_POST(self):
    if self.is_cgi():
      self.run_cgi()
    else:
      self.send_error(501, "Can only POST to CGI scripts")
  def send_head(self):
    if self.is_cgi():
      return self.run_cgi()
    else:
      return self.Base.send_head(self)
  cgi_dirs = ["/cgi-bin", "/home/knaka/bin/cgi-bin"]
  def is_cgi(self):
    path = self.path
    for cgi_dir in self.cgi_dirs:
      n = len(cgi_dir)
      if path[:n] == cgi_dir and \
       (not path[n:] or path[n] == "/"):
        rest = path[(n + 1):]
        if rest == "":
          continue
        self.cgi_info = (path[:n], rest,)
        return 1
    return 0
  def is_python(self, path):
    (head, tail,) = os.path.splitext(path)
    return tail.lower() in (".py", ".pyc", ".pyo",)
  def run_cgi(self):
    (dir, rest,) = self.cgi_info
    i = rest.rfind("?")
    if i >= 0:
      (rest, query,) = (rest[:i], rest[(i + 1):],)
    else:
      query = ""
    i = rest.find("/")
    if i >= 0:
      (script, rest,) = (rest[:i], rest[i:],)
    else:
      (script, rest,) = (rest, "",)
    scriptname = dir + "/" + script
    scriptfile = self.translate_path(scriptname)
    if not os.path.exists(scriptfile):
      self.send_error(404, "No such CGI script (%s)" % `scriptname`)
      return
    if not os.path.isfile(scriptfile):
      self.send_error(403, "CGI script is not a plain file (%s)" %
       `scriptname` )
      return
    # Reference: http://hoohoo.ncsa.uiuc.edu/cgi/env.html
    # XXX Much of the following could be prepared ahead of time!
    env = {}
    env["SERVER_SOFTWARE"] = self.version_string()
    env["SERVER_NAME"] = self.server.server_name
    env["GATEWAY_INTERFACE"] = "CGI/1.1"
    env["SERVER_PROTOCOL"] = self.protocol_version
    env["SERVER_PORT"] = str(self.server.server_port)
    env["REQUEST_METHOD"] = self.command
    uqrest = urllib.unquote(rest)
    env["PATH_INFO"] = uqrest
    env["PATH_TRANSLATED"] = self.translate_path(uqrest)
    env["SCRIPT_NAME"] = scriptname
    if query:
      env["QUERY_STRING"] = query
    host = self.address_string()
    if host != self.client_address[0]:
      env["REMOTE_HOST"] = host
    env["REMOTE_ADDR"] = self.client_address[0]
    if self.headers.typeheader is None:
      env["CONTENT_TYPE"] = self.headers.type
    else:
      env["CONTENT_TYPE"] = self.headers.typeheader
    length = self.headers.getheader("content-length")
    if length:
      env["CONTENT_LENGTH"] = length
    accept = []
    for line in self.headers.getallmatchingheaders("accept"):
      if line[:1] in "\t\n\r ":
        accept.append(line.strip())
      else:
        accept = accept + line[7:].split(",")
    env["HTTP_ACCEPT"] = ",".join(accept)
    ua = self.headers.getheader("user-agent")
    if ua:
      env["HTTP_USER_AGENT"] = ua
    co = filter(None, self.headers.getheaders("cookie"))
    if co:
      env["HTTP_COOKIE"] = ", " . join(co)
    self.send_response(200, "Script output follows")
    decoded_query = query.replace("+", " ")
    if self.is_python(scriptname):
      os.environ.update(env)
      save_argv = sys.argv
      save_stdin = sys.stdin
      save_stdout = sys.stdout
      save_stderr = sys.stderr
      try:
        try:
          sys.argv = [scriptfile]
          if "=" not in decoded_query:
            sys.argv.append(decoded_query)
          sys.stdout = self.wfile
          sys.stdin = self.rfile
          execfile(scriptfile, {"__name__": "__main__"})
        finally:
          sys.argv = save_argv
          sys.stdin = save_stdin
          sys.stdout = save_stdout
          sys.stderr = save_stderr
      except SystemExit, sts:
        self.log_error("Python CGI script exit status %s", str(sts))
      else:
        self.log_message("Python CGI script exited OK")
    else:
      args = [script]
      if "=" not in decoded_query:
        args.append(decoded_query)
      self.rfile.flush() # Always flush before forking
      self.wfile.flush() # Always flush before forking
      pid = os.fork()
      if pid != 0:
        (pid, status,) = os.waitpid(pid, 0)
        if status:
          self.log_error("Forked CGI script exit status %#x", status)
        else:
          self.log_error("Forked CGI script exited OK")
        return
      try:
        os.dup2(self.rfile.fileno(), 0)
        os.dup2(self.wfile.fileno(), 1)
        os.execve(scriptfile, args, env)
      except:
        self.server.handle_error(self.request, self.client_address)
        os._exit(127)

class MyServer(BaseHTTPServer.HTTPServer):
  def __init__(self, root, Handler):
    self.Base = self.__class__.__bases__[0]
    self.running = 1
    os.chdir(root)
    ports = range(10000, 10050)
    for port in ports:
      try:
        self.Base.__init__(self, ("", port,), Handler)
        self.port = port
        break
      except socket.error:
        pass
    else:
      sys.stderr.write("No port available from %d to %d.\n" % \
       (ports[0], ports[-1],) )
      raise Exception
  def getPort(self):
    return self.port
  def run(self):
    while httpd.running:
      httpd.handle_request()

import tempfile

class Session:
  def __init__(self):
    old_mask = os.umask(0077)
    tmpdir = tempfile.mktemp(".hoge")
    print "d0", tmpdir
    os.mkdir(tmpdir)
    os.umask(old_mask)

if __name__ == "__main__":
  httpd = MyServer("/home/knaka/bin", MyHandler)
  print "d:", httpd.getPort()
  Session()
  httpd.run()

