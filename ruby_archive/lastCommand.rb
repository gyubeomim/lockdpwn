#!/usr/bin/ruby
# coding: utf-8
=begin
   ruby ==> 해킹침투코딩 p173, last 명령어를 사용해 user,host 정보를 얻어와 보기좋게 뿌려주는 코드
=end
data = `last`.split("\n");

users = []
hosts = []

data.each do |l|
  if l == ""
    next
  elsif l.start_with? "reboot"
    next
  elsif l.start_with? "wtmp"
    next
  else
    l.rstrip!
    users << l[0,8].rstrip
    hosts << l[17,16].rstrip.lstrip
  end
end

users.uniq!
hosts.uniq!

until users.empty?
  print "User: %s\n" % users.pop
end

while not hosts.empty?
  print "Hosts: %s\n" % hosts.pop
end
