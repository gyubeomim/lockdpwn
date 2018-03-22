#!/usr/bin/ruby
# coding: utf-8
=begin
   ruby ==> 해킹침투코딩 p177, 웹사이트의 헤더를 읽어와 출력하는 코드 (클래스 사용)
=end
require 'net/http'

class MyHead
  def initialize(host, port = nil)
    @host = host
    @port = port.to_i || 80
  end

  def getHeader()
    Net::HTTP.start(@host.to_s, @port) do |http|
      resp = http.head('/')
      return [resp['server'].to_s, resp['x-powered-by'].to_s]
    end
  end

  return [nil, nil]
end

if ARGV.size <= 0 || ARGV.size > 2
  print "Usage: #{$0} Host [Port]\n"
  exit
end

head = MyHead.new(ARGV[0], ARGV[1])
server, mods = head.getHeader()
print "Server #{server} (#{mods})\n"

