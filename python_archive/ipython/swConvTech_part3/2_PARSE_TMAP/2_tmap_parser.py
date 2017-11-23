#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part3_1 tmap으로부터 받은 xml 데이터를 
                                        congestion;coordinates 로 데이터가공 후 저장하는 코드
'''
import codecs
import re

IN_DIR = "../1_GET_TMAP/RESULT/"
OUT_DIR = "./RESULT/"

for area_index in range(16):
    in_file = codecs.open(IN_DIR+'traffic_%02d.xml' % (area_index), 'r', 'utf-8')
    out_file = open(OUT_DIR+'congestion_coor_%02d.txt' % (area_index), 'w')

    cont = in_file.read()
    
    # tmap에서 가져온 traffic_0x.xml 데이터는 CRLF가 적용되지 않은 한 줄짜리 xml문서이므로 import xml.etree.ElementTree as ET를 사용할 수 없었습니다 
    # 따라서 정규표현식을 사용해 데이터를 추출합니다.

    # 정규표현식을 사용해 congestion의 값을 추출합니다
    pattern_cong = '<tmap:congestion>(\d+)<\/tmap:congestion>'
    r_cong = re.compile(pattern_cong)
    congestion = r_cong.findall(cont)

    # 정규표현식을 사용해 coordinates의 값을 추출합니다
    pattern_coord = '<coordinates>([^ABC]+)<\/coordinates>'
    r_coord = re.compile(pattern_coord)
    coordinates = r_coord.findall(cont)

    for i in range(0, len(congestion)):
        lines = congestion[i] + ';' + coordinates[i] + '\n'
        out_file.writelines(lines)

    out_file.close()
