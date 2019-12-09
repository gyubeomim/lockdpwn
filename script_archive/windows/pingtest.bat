@echo off
REM batch ==> hosts.txt 파일을 읽어와 ping 명령을 날리는 코드

setLocal EnableDelayedExpansion

for /f "tokens=* delims= " %%a in (hosts.txt) do (
	ping %%a
)
