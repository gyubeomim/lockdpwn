# powershell ==> 해킹침투코딩 p260, 레지스트리에서 값을 읽어와 컴퓨터의 설치된 프로그램을 긁어오는 코드

$file = "./installed_software.txt"
Get-ChildItem HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall `
| ForEach-Object `
{ 
	$property = Get-ItemProperty $_.pspath | Out-File $file -Append 
}
