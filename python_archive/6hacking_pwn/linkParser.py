#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> violent python, 정규표현과 BeautifulSoup를 사용해 html 코드에서 HREF 링크 구문을 찾아본 예제 코드
'''
from anonBrowser import *
from BeautifulSoup import BeautifulSoup
import os, optparse, re

def printLinks(url):
    ab = anonBrowser()
    ab.anonymize()
    page = ab.open(url)
    html = page.read()

    try:
        print '[+] printing links from regex'
        link_finder = re.compile('href="(.*?)"')
        links = link_finder.findall(html)
        for link in links:
                print link

    except:
        pass

    try:
        print '\n[+] printing links from beautifulsoup'
        
        # 아래 명령어로 html 코드를 긁어온다
        soup = BeautifulSoup(html)
        links = soup.findAll(name = 'a')

        for link in links:
                if link.has_key('href'):
                        print link['href']
    except:
        pass


def main():
    parser = optparse.OptionParser('usage%prog ' + 
                    '-u <target url>')
    parser.add_option('-u', dest = 'tURL', type = 'string', \
                    help = 'specify target url')
    (options, args) = parser.parse_args()

    url = options.tURL

    if url == None:
            print parser.usage
            exit(0)
    else:
            printLinks(url)


if __name__ == '__main__':
	main()




