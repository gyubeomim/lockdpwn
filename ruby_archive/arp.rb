# -*- coding: utf-8 -*-
=begin
	ruby ==> 해킹침투코딩 p166, arp 파일에서 데이터를 읽어와 현재 존재하는 호스트를 출력하는 코드
=end
require 'socket'

s = UDPSocket.new
254.times do |i|
	next if i ==0
	s.send("test", 0, "192.168.184." + i.to_s, 53)
end

f = File.open("/proc/net/arp",'r')
data = f.read.split("\n")
up_hosts = []

data.each do |line|
	entry = line.split(/\s+/)
	print "entry : ", entry, "\n"
	next if entry[3] == "00:00:00:00:00:00"
	next if entry[0] == "IP"
	up_hosts << {:ip => entry[0], :mac => entry[3]}
end

print "\nActive network hosts\n"
print "%-12s\t%s\n" % ["IP Addr", "MAC Address"]
up_hosts.each do |host|
	print "%-12s\t%s\n" % [host[:ip], host[:mac]]
end


