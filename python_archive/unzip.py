#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> zip 파일을 푸는 예제 코드
                Permission Denied로 윈도우에선 잘 안풀린다
'''
import zipfile
import optparse
from threading import Thread

def extractall(zFile, password ):
    try:
        zFile.extractall(pwd = password)
        print '[+] Fount password ' + password + '\n'
    except:
        pass


def main():
    parser = optparse.OptionParser("usage%prog " + "-f <zipfile> -d <dictionary>")
    parser.add_option('-f', dest = 'zname', type='string', help = 'specify zip file')
    parser.add_option('-d', dest='dname', type='string', help = 'specify dictionary file')
    (option, args) = parser.parse_args()

    if (option.zname == None) | (option.dname == None):
        print parser.usage
        exit(0)

    else:
        zname = option.zname
        dname = option.dname

    zFile = zipfile.ZipFile(zname)
    passFile = open(dname)
    for line in passFile.strip('\n'):
        t = Thread(target = extractFile, args = (zFile, password))
        t.start()


if __name__ == '__main__':
    main()
