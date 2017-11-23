#!/usr/bin/perl
=pod
    perl ==> 해킹침투코딩 p128, testfile을 만들어 타임스탬프를 확인해본 코드
=cut
$file = "file";
`touch $file`;

# stat 명령어를 사용해 타임스탬프에 접근한다
$origaccessed = (stat($file))[8];
$origmodified = (stat($file))[9];

print "original accessed = $origaccessed\n";
print "original modified = $origmodified\n";

sleep(5);
`touch $file`;

$newaccessed = (stat($file))[8];
$newmodified = (stat($file))[9];

print "new accessed = $newaccessed\n";
print "new modified = $newmodified\n";

`utime $origaccessed, $origmodified, $file`;


$finalaccessed = (stat($file))[8];
$finalmodified = (stat($file))[9];

print "final accessed = $finalaccessed\n";
print "final modified = $finalmodified\n";
