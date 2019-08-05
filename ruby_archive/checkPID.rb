#!/usr/bin/ruby
#-*- coding: utf-8 -*-
=begin
   ruby ==> 해킹침투코딩 p187, PID와 같이 입력하면 소유자, cwd, command를 출력해주는 예제 코드
=end
require 'etc'

pid = ARGV[0].to_i
cwd = File.readlink("/proc/#{pid}/cwd")
owner = File.stat("/proc/#{pid}/cmdline").uid
file = File.new("/proc/#{pid}/cmdline")

cmdline = file.read.split("\000")
file.close


filename = cmdline.shift

print "Process #{pid} is owned by #{Etc.getpwuid(owner).name}\n"
print "Process #{pid} CWD : #{cwd}\n"
print "Process #{pid} Command: #{filename} #{cmdline.join(' ')}\n"
