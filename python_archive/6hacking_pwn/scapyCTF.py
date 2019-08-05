#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> CTF, scapy를 활용해 pcap 파일에서 flag를 얻은 예제 코드
'''
from scapy.all import *

def main():
    packets = rdpcap('D:\\gitrepo\\lockdpwn\\cc_archive\\ctfContestChallange\\book4b_net\\scapy_ex1.pcap')

    flag = ""
    for p  in packets:
        if p['IP'].type == 8:
            flag += chr(p['ICMP'].id)

    print flag


if __name__ == '__main__':
	main()
