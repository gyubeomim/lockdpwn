#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part3_1 
'''
import urllib.request as ur

TMAP_APP_KEY = "41e51413-6b35-31ac-86db-9a4d5adf5dbb"
REQ_COORD_TYPE = "WGS84GEO"
RES_COORD_TYPE = "WGS84GEO"
SORT = "index"
# centerLat = 37.565
# centerLon = 126.884

OUT_DIR = "./RESULT/"

NUM = 4
OFFSET = MAX_LAT - MIN_LAT

TOLLGATEFAREOPTION=
ROADTYPE=
DIRECTIONOPTION=
ENDX=
ENDY=
ENDRPFLAG=
ENDPOIID=
STARTX=
STARTY=
GPSTIME=
ANGLE=
SPEED=
UNCETAINTYP=
uncetaintyA=
UNCETAINTYAP=
CARTYPE=
STARTNAME=
ENDNAME=
SEARCHOPTION=
PASSLIST=
GPSINFOLIST=
DETAILPOSFLAG=

requestStr = "https://apis.skplanetx.com/tmap/traffic?\
appKey="+ TMAP_APP_KEY +"\
&tollgateFareOption="+TOLLGATEFAREOPTION+"\
&roadType="+ROADTYPE+"\
&directionOption="+DIRECTIONOPTION+"\
&endX="+ENDX+"\
&endY="+ENDY+"\
&endRpFlag="+ENDRPFLAG+"\
&endPoiId="+ENDPOIID+"\
&reqCoordType="+REQ_COORD_TYPE+"\
&startX="+STARTX+"\
&startY="+STARTY+"\
&gpsTime="+GPSTIME"\
&angle="+ANGLE+"\
&speed="+SPEED+"\
&uncetaintyP="+UNCETAINTYP+"\
&uncetaintyA="+UNCETAINTYA+"\
&uncetaintyAP="+UNCETAINTYAP+"\
&carType="+CARTYPE"\
&startName="+STARTNAME+"\
&endName="+ENDNAME+"\
&searchOption="+SEARCHOPTION+"\
&passList="+PASSLIST+"\
&gpsInfoLIst="+GPSINFOLIST+"\
&detailPosFlag="+DETAILPOSFLAG+"\
&resCoordType="+RES_COORD_TYPE+"\
&sort="+SORT+"";

print("%d, %d" %(i,j))

# Header를 추가해줘야 XML 데이터 형식으로 받아온다
q = ur.Request(requestStr)
q.add_header('Accept', 'application/xml')

in_file = ur.urlopen(q)
out_file = open(OUT_DIR+'traffic_%02d.xml' % (AREA_INDEX), 'wb')
out_file.write(in_file.read())
out_file.close()


