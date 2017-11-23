#!/usr/bin/perl
=pod
    perl ==> 해킹침투코딩 p143, 쉘 ifconfig 명령어를 사용해 MAC 주소를 가져오는 예제 코드
=cut

$text = `ifconfig | grep HWaddr`;

print "the string is ", "\n", $text, "\n";

$text =~ m/((?:[0-9a-f]{2}[:-]){5}[0-9a-f]{2})/i;

# $& is the previous successful match 라고 한다
print "the mac is ", $&, "\n";
