#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p96, 웹사이트에서 robots.txt 파일을 읽어오는 코드
'''
import robotparser

sites = ['www.google.com' , 'www.offensive-security.com'
		,'www.yahoo.com','www.naver.com','www.daum.net','www.ppomppu.co.kr'
		,'www.dcinside.com','koradb.ddns.net']

def getDenies(site):
    paths = []

    # Create a robot parser instance and read the site's robots file
    robot = robotparser.RobotFileParser()
    robot.set_url("http://"+site+"/robots.txt")
    robot.read()

    # For each entry, look at the rule lines and add the path to paths if
    # disallowed
    for entry in robot.entries:
        for line in entry.rulelines:
            not line.allowance and paths.append(line.path)

    return set(paths)


for site in sites:
    print "Denies for " + site
    print "\t" + " \n\t".join(getDenies(site))

    
