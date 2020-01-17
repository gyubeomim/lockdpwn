#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p78, python webCheck.py [hostname] [port] 로 호스트를 스캔하는 코드 
'''
import httplib, sys
from optparse import OptionParser

def main():
	usageString = "Usage: %prog [options] hostname"
	parser = OptionParser(usage=usageString)
	parser.add_option("-p","--port",dest = "port", metavar = "PORT", default=80,\
					  type ="int" , help = "Port to connect")

	(opts,args) = parser.parse_args()

	if len(args) < 1:
		parser.error("Hostname is required")

	host = args[0]
	host = sys.argv[1]
	port = sys.argv[2]

	client = httplib.HTTPConnection(host, port)

	client.request("GET","/")
	resp = client.getresponse()
	client.close()

	if resp.status == 200:
		print host + " : OK"
		sys.exit()
		
	print host + " : DOWN! (" + resp.status + " , " + resp.reason + ")"

if __name__ == '__main__':
	main()
