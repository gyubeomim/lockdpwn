#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 크롬의 History 파일을 sqlite3를 사용해 키워드를 분석해본 예제 코드
'''
import os
import sys
import sqlite3

NUM = 10

def getPid(s):
    im = '"IMAGENAME eq %s"' % s
    cmd = "tasklist /V /FI %s"  %  im
    s = os.popen(cmd).read()
    return s

print "======== Chrome Histroy Viewer ============"

def main():
    if "chrome.exe" in getPid("Chrome.exe"):
        os.system("taskkill /f /im chrome.exe")

    con = sqlite3.connect('C:\\Users\\vdl\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\History')
    cursor = con.cursor()
    cursor.execute("SELECT * FROM keyword_search_terms ORDER BY url_id DESC")

    count = 0

    while count < NUM:
        count += 1
        data = cursor.fetchone()
        covdata = "".join(str(data))

        list1 = covdata.split(',')[3]
        list1 = list1.replace('u','')
        list1 = list1.replace('\'','')
        list1 = list1.replace(')','')
        print "\n", list1

    if True:
        print ""
        print "========= Complete Histroy DB load - ",count ," Search keywords =============="

if __name__ == '__main__':
    main()
