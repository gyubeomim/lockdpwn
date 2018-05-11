#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> nmap을 사용해 호스트 스캐닝을 하는 예제 코드 

                PortScanner()가 없다면서 현재 작동안된다
'''
import nmap
import optparse
from socket import *

def nmapScan(Host, Port):
	nmScan = nmap.PortScanner()
	Host = gethostbyname(Host)
	nmScan.scan(Host, Port)

	state = nmScan[Host]['tcp'][int(Port)]['state']
	print "[*] " + Host + " tcp/" + Port + " " + state

def main():
	parser = optparse.OptionParser('usage%prog ' + \
			              '-H <target host> -p <target port>')
	parser.add_option('-H', dest='Host', type='string',\
					  help='specify target host')
	parser.add_option('-p', dest='Port', type='string',\
                      help='specify target port[s] separated by comma')

	(options, args) = parser.parse_args()

	Host = options.Host
	Ports = str(options.Port).split(', ')

	if (Host == None) | (Ports[0] == None):
		print parser.usage
		exit(0)

	for Port  in Ports :
		nmapScan(Host, Port)


if __name__ == '__main__':
	main()
