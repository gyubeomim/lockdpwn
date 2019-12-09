# powershell ==> 해킹침투코딩, 변수와 함수를 사용해본 예제 코드
function hello
{
    $LOCAL:name = "whoever you are"
    Write-Output "hello there "$name 
}

$name = $args[0]
Write-Output "hello there "$name
hello
Write-Output "hello there "$name 