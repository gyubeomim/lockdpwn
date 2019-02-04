#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part3_1 
'''
import urllib.request as ur
import codecs
import re

TMAP_APP_KEY = "41e51413-6b35-31ac-86db-9a4d5adf5dbb"

# STEP 1 ------------------------------------------------------------
# variables 
OUT_DIR = "./RESULT/"
VERSION=1
TOLLGATEFAREOPTION=1
ROADTYPE=32
DIRECTIONOPTION=0
ENDX=129.075
ENDY=35.178
ENDRPFLAG="G"
ENDPOIID=14232
STARTX=126.982
STARTY=37.564
ANGLE=180
SPEED=10
UNCETAINTYP=1
UNCETAINTYA=1
UNCETAINTYAP=12
CARTYPE=1
SEARCHOPTION=1
PASSLIST="127.38454163183215,36.35127257501252,1000559889,G,0"
DETAILPOSFLAG=2
REQ_COORD_TYPE="WGS84GEO"
RES_COORD_TYPE="WGS84GEO"
SORT="index"
CALLBACK=""
#GPSTIME=
#STARTNAME="을지로입구역"
#ENDNAME="헤이리"
#GPSINFOLIST=

requestStr = "https://apis.skplanetx.com/tmap/routes?\
appKey="+TMAP_APP_KEY+"\
&callback="+CALLBACK+"\
&version="+str(VERSION)+"\
&tollgateFareOption="+str(TOLLGATEFAREOPTION)+"\
&roadType="+str(ROADTYPE)+"\
&directionOption="+str(DIRECTIONOPTION)+"\
&endX="+str(ENDX)+"\
&endY="+str(ENDY)+"\
&endRpFlag="+str(ENDRPFLAG)+"\
&endPoiId="+str(ENDPOIID)+"\
&reqCoordType="+REQ_COORD_TYPE+"\
&startX="+str(STARTX)+"\
&startY="+str(STARTY)+"\
&angle="+str(ANGLE)+"\
&speed="+str(SPEED)+"\
&uncetaintyP="+str(UNCETAINTYP)+"\
&uncetaintyA="+str(UNCETAINTYA)+"\
&uncetaintyAP="+str(UNCETAINTYAP)+"\
&carType="+str(CARTYPE)+"\
&searchOption="+str(SEARCHOPTION)+"\
&passList="+str(PASSLIST)+"\
&detailPosFlag="+str(DETAILPOSFLAG)+"\
&resCoordType="+RES_COORD_TYPE+"\
&sort="+SORT;


# &gpsTime="+GPSTIME"\&gpsInfoLIst="+GPSINFOLIST+"\
# &startName="+STARTNAME+"\&endName="+ENDNAME+"\

# Header를 추가해줘야 XML 데이터 형식으로 받아온다
q = ur.Request(requestStr)
q.add_header('Accept', 'application/kml')
in_file = ur.urlopen(q)
out_file = open(OUT_DIR+'car_navigation.xml', 'wb')
out_file.write(in_file.read())
out_file.close()


# STEP 2 DATA PARSING---------------------------------------------------

in_file = codecs.open(OUT_DIR+'car_navigation.xml', 'r', 'utf-8')
out_file = open(OUT_DIR+'parsed_car_navigation.txt', 'w')

cont = in_file.read()

# tmap에서 가져온 traffic_0x.xml 데이터는 CRLF가 적용되지 않은 한 줄짜리 xml문서이므로 import xml.etree.ElementTree as ET를 사용할 수 없었습니다 
# 따라서 정규표현식을 사용해 데이터를 추출합니다.

# 정규표현식을 사용해 congestion의 값을 추출합니다
pattern_name = '<name><!\[CDATA\[(.{1,30})\]><\/name>'
r_name = re.compile(pattern_name)
name = r_name.findall(cont)


# 문자열에 ']' 가 포함되어 있는 경우 ']' 문자열을 제거합니다
for i in range(0, len(name)):
    name[i] = name[i].replace(']','')
    if name[i] == '':
        name[i] = "null"


# 정규표현식을 사용해 coordinates의 값을 추출합니다
pattern_coord = '<coordinates>([^ABC]+)<\/coordinates>'
r_coord = re.compile(pattern_coord)
coordinates = r_coord.findall(cont)


for i in range(0, len(name)):
    lines = name[i] + ';' + coordinates[i] + '\n'
    out_file.writelines(lines)

out_file.close()



# STEP 3 -----------------------------------------------------------


