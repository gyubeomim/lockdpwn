#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> CTF, scapy를 활용해 jpg 코드를 뽑아와 사진파일로 만드는 예제 코드
'''
from scapy.all import *

def main():
	packets = rdpcap('D:\\gitrepo\\lockdpwn\\cc_archive\\ctfContestChallange\\book4b_net\\scapy_ex2.pcap')

	flag = ""
	for p  in packets:
		if p['IP'].src == '10.29.31.155':
			flag += p['Raw'].load

	f = open('flag.jpg', 'wb')
	f.write(flag)
	f.close()
	exit()

if __name__ == '__main__':
	main()
