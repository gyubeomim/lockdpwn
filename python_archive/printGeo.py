#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pygeoip를 사용해 아이피를 입력하면 GPS위치를 반환하는 예제 코드
               wget http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz 를 다운받아야 한다
'''
import pygeoip
from socket import *
import optparse

gi = pygeoip.GeoIP('.\\GeoLiteCity.dat')

def printRecord(target):
    target = gethostbyname(target)

    rec = gi.record_by_name(target)

    city = rec['city']
    region = rec['region_code']
    country = rec['country_name']
    long = rec['longitude']
    lat = rec['latitude']
    print '[*] Target: ' + target + ' Geo-located. '
    print '[+] '+str(city)+', '+str(region)+', '+str(country)
    print '[+] Latitude: '+str(lat)+ ', Longitude: '+ str(long)


def main():
    parser = optparse.OptionParser('usage%prog "+ " -u <target url>')
    parser.add_option('-u', dest = 'url', type = 'string',\
                                      help = 'specify url address')

    (options, args ) = parser.parse_args()

    url = options.url

    if url == None :
            print parser.usage
            exit(0)
    else:
            printRecord(url)


if __name__ == '__main__':
	main()
