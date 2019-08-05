# powershell ==> 해킹침투코딩 p254, 웹상에서 파일을 다운로드 받아오는 코드 
$src = "http://nmap.org/dist/nmap-5.51-setup.exe"
$dest = ".\nmap-5.51-setup.exe"
$web = New-Object System.Net.WebClient
$web.DownloadFile($src, $dest)

$src = "ftp://ftp.fr.netbsd.org/pub/pkgsrc/distfiles/Ouch-0.0402.tar.gz"
$dest = ".\ouch.tar.gz"
$ftp = New-Object System.Net.WebClient
$ftp.DownloadFile($src,$dest)

#$ftp.UploadFile(($src,$dest)