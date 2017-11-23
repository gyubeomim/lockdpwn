#!/usr/bin/ruby
# coding: utf-8
=begin
   ruby ==> 해킹침투코딩 p181, 클래스 상속을 사용해 16진수값을 변환해본 예제 코드
=end
class HexMaker
  def str_to_h(str)
    str.unpack("H*").first
  end
end

class MyHexMaker < HexMaker
  def h_to_s(hex)
    i = 0
    [hex].pack("H*")
  end
end

tst = HexMaker.new.str_to_h("AAAA")
print "Converted string #{tst}\n"

tst = MyHexMaker.new.str_to_h("AAAA")
print "Original String #{MyHexMaker.new.h_to_s(tst)}\n"
