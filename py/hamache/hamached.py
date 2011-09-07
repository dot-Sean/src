# Much of CGIHTTPServer.py has been copied to this.

import os
import sys
import socket
import BaseHTTPServer
import SimpleHTTPServer
import urllib
import re
import string
import signal
import shutil

version = "0.1"

class HamacheHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
  server_version = "Hamache/%s" % (version,)
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
      return 1
    return 0
  def getAuthId(self):
    return self.server.getAuthId()
  def authorize(self):
    auth_str = self.getAuthId()
    if self.path.find("/%s/" % (auth_str,)) >= 0:
      self.path = self.path.replace("/%s/" % (auth_str,), "/")
      return 1
    return 0
  def do_GET(self):
    self.server.setAlarm()
    os.chdir(self.server.root)
    if not self.authorize():
      return self.send_error(401, "Access denied")
    return self.Base.do_GET(self)
  def do_POST(self):
    self.server.setAlarm()
    os.chdir(self.server.root)
    if not self.authorize():
      return self.send_error(401, "Access denied")
    if self.is_cgi():
      self.run_cgi()
    else:
      self.send_error(501, "Can only POST to CGI scripts")
  def send_head(self):
    if self.is_cgi():
      return self.run_cgi()
    else:
      return self.Base.send_head(self)
  reCgiFile = re.compile("^(.*)/([^/]\\.cgi)$")
  reCgiBinFile = re.compile("^(.*/cgi-bin)/([^/]+)$")
  def is_cgi(self):
    m = self.reCgiFile.search(self.path)
    if not m:
      m = self.reCgiBinFile.search(self.path)
    if m:
      self.cgi_info = (m.group(1), m.group(2),)
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

def genSessionId(len):
  ret = ""
  input = open("/dev/random", "r")
  while len > 0:
    c = input.read(1)
    if c in string.ascii_letters or c in string.digits:
      ret = ret + c
      len = len - 1
  return ret

class TimeoutException(Exception):
  pass

def handleAlarm(signum, frame):
  raise TimeoutException

class HamacheServer(BaseHTTPServer.HTTPServer):
  def __init__(self, root, Handler):
    self.Base = self.__class__.__bases__[0]
    self.running = 1
    self.root = root
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
    self.sesid = genSessionId(64)
  outtime = 10
  def setAlarm(self):
    signal.alarm(self.outtime)
  def getPort(self):
    return self.port
  def putLocal(self, args, tmp_dir = "/tmp"):
    url = "http://127.0.0.1:%d/%s/%s" % \
     (self.getPort(), self.getAuthId(), args[0],)
    if os.fork() == 0:
      self.handle_request()
      sys.exit(0)
    import time
    input = os.popen("cd %s ; LANG= LC_ALL= wget --tries=0 " \
     "--server-response --convert-links %s 2>&1" % (tmp_dir, url,) )
    reContentType = re.compile("Content-type: ([^;]*)")
    reSaved = re.compile("`([^']+)' saved")
    ifile = None
    ofile = None
    for line in input.readlines():
      line = line.strip()
      m = reContentType.search(line)
      if m:
        mtype = m.group(1)
        print "d:", mtype
        if mtype == "text/html":
          ofile = "%s/tmp.html" % (tmp_dir,)
        elif mtype == "text/plain":
          ofile = "%s/tmp.txt" % (tmp_dir,)
        else:
          ofile = "%s/tmp.txt" % (tmp_dir,)
        output = open(ofile, "w")
      m = reSaved.search(line)
      if m:
        ifile = m.group(1)
    if ifile and ofile:
      shutil.copyfile("%s/%s" % (tmp_dir, ifile,), ofile)
    return ofile
  def run(self):
    signal.signal(signal.SIGALRM, handleAlarm)
    try:
      self.setAlarm()
      while self.running:
        self.handle_request()
    except TimeoutException:
      pass
    signal.alarm(0)
  def getAuthId(self):
    return self.sesid

import tempfile

class Session:
  def __init__(self):
    old_mask = os.umask(0077)
    tmpdir = tempfile.mktemp(".hoge")
    print "d0", tmpdir
    os.mkdir(tmpdir)
    os.umask(old_mask)
