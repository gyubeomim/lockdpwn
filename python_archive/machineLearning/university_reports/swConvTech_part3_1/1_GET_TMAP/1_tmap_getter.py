#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part3_1 tmap에 Request를 해서 특정 위도 경도의 교통상황 데이터를 받아 xml로 저장하는 코드
'''
import urllib.request as ur

TMAP_APP_KEY = "41e51413-6b35-31ac-86db-9a4d5adf5dbb"
MIN_LAT = 37.56
MIN_LON = 126.88
MAX_LAT = 37.57
MAX_LON = 126.89
ZOOM_LEVEL = 19
VERSION = 1
REQ_COORD_TYPE = "WGS84GEO"
RES_COORD_TYPE = "WGS84GEO"
TRAFFIC_TYPE = ""
RADIUS = 1
SORT = "index"
# centerLat = 37.565
# centerLon = 126.884

OUT_DIR = "./RESULT/"

NUM = 4
OFFSET = MAX_LAT - MIN_LAT

for i in range(NUM):
    for j in range(NUM):
        AREA_INDEX = NUM*i + j

        requestStr = "https://apis.skplanetx.com/tmap/traffic?\
appKey="+ TMAP_APP_KEY +"\
&version="+str(VERSION)+"\
&minLat="+str(MIN_LAT + OFFSET*j)+"\
&minLon="+str(MIN_LON + OFFSET*i)+"\
&maxLat="+str(MAX_LAT + OFFSET*j)+"\
&maxLon="+str(MAX_LON + OFFSET*i)+"\
&centerLat="+ str((MIN_LAT + MAX_LAT + OFFSET*j) * 0.5) +"\
&centerLon="+ str((MIN_LON + MAX_LON + OFFSET*i) * 0.5) +"\
&reqCoordType="+ REQ_COORD_TYPE +"\
&resCoordType="+ RES_COORD_TYPE +"\
&trafficType="+ TRAFFIC_TYPE +"\
&radius="+ str(RADIUS) +"\
&zoomLevel="+ str(ZOOM_LEVEL) +"\
&sort="+SORT+""

        print("%d, %d" %(i,j))
        
        # Header를 추가해줘야 XML 데이터 형식으로 받아온다
        q = ur.Request(requestStr)
        q.add_header('Accept', 'application/xml')

        in_file = ur.urlopen(q)
        out_file = open(OUT_DIR+'traffic_%02d.xml' % (AREA_INDEX), 'wb')
        out_file.write(in_file.read())
        out_file.close()


