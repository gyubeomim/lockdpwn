#!/usr/bin/ruby
# coding: utf-8
=begin
   ruby ==> 해킹침투코딩 p184, 클래스 데이터에 접근할 수 있는 reader, writer, accessor 속성에 대해 알아본 예제 코드
=end
class Test
  attr_reader :error
  attr_writer :request
  attr_accessor :other

  def test
    @error = "You can't change me"
    print "Request contains #{@request}\n"
    print "Other contains #{@other}\n"
  end
end

mytest = Test.new

## error (read only 테스트)
print "Trying to set error to 'change me'\n"
begin
  mytest.error = "change me"
rescue
  print "...changing error failed\n\n"
end

## request, other (write-only, access-only 변수 테스트)
print "Setting request to 'pretty please' and other to 'we can change this at will'\n\n"
mytest.request = "pretty please"
mytest.other = "we can change this at will"

print "Calling test function...\n"
mytest.test

print "\n"
print "Directly querying data...\n"
print "Error is #{mytest.error}\n"
print "Other is #{mytest.other}\n"

## request (write only 테스트)
begin
  print "Request is #{mytest.request}\n"
rescue
  print "Failed to query mytest.request, it is write only\n"
end
