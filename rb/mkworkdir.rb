#!/usr/bin/ruby
# -*- coding: utf-8 -*-

def mkworkdir
  chars = ("a" .. "z").to_a
  length = chars.length
  require "tmpdir"
  begin
    dir_name = "#{Dir.tmpdir}/workdir-#{Process.pid}-%s" % \
     [(Array.new(6) { chars[rand(length)] }).join,]
  end while File.exists?(dir_name)
  require "fileutils"
  FileUtils.mkdir_name(dir_name)
  FileUtils.chmod(0700, dir_name)
  yield dir_name
  FileUtils.remove_entry(dir_name)
end

mkworkdir { |dir|
  `touch #{dir}/hoge`
  print `ls -ld #{dir}`
  print `ls -l #{dir}`
}
