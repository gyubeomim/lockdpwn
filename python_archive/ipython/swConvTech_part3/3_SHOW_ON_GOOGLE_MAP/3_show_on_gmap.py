#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트웨어융합최신기술, part3_1 Google Static Map에 Query를 보내서 xml 파일을 통해 가져온 Congestion;Coordinates를 시각화해주는 코드
'''
import webbrowser

GOOGLE_APP_KEY = 'AIzaSyCYYJsdrk6AQuzByDXn30-XUIKwHaT_SyQ'
CENTER = '37.60,126.90'

IN_DIR = '../2_PARSE_TMAP/RESULT/'
OUT_DIR = './RESULT/'

for area_index in range(16):
    in_file = open(IN_DIR + "congestion_coor_%02d.txt" % (area_index), 'r')
    out_file = open(OUT_DIR + "gmap_urlstr_%02d.txt" % (area_index), 'w')

    paths = ''
    color = ''

    for line in in_file:
        congestion, linestring = line.split(';')

        #TOOD: Fill in this block to make color string.
        # congestion 1 --> blue
        # congestion 2 --> green
        # congestion 3 --> yellow
        # congestion 4 --> orange
        # congestion 5 --> red

        if(congestion == '0'):  # '0' case added 
            color="black"
        elif(congestion == '1'):
            color="blue"
        elif(congestion == '2'):
            color="green"
        elif(congestion == '3'):
            color="yellow"
        elif(congestion == '4'):
            color="orange"
        elif(congestion == '5'):
            color="red"


        #TOOD: Fill in this block to make (lat, lon) string.  Use the first and the last (lat, lon) only
        coord = linestring.split(' ')
        first_string = coord[0]
        last_string = coord[len(coord)-1]

        # swap (lon,lat) ==> (lat,lon)
        first_string = first_string.split(',')
        first_string = first_string[1] + ',' + first_string[0]

        last_string = last_string.split(',')
        last_string = last_string[1] + ',' + last_string[0]
        last_string = last_string.replace('\n','')  # remove CRLF
    
        paths += '&path=color:'+ color +'|weight:5|' + first_string + '|' + last_string
    
    urlstr = ("https://maps.googleapis.com/maps/api/staticmap?key="+ GOOGLE_APP_KEY + "&center=" + CENTER + "&zoom=12&size=600x600&maptype=roadmap" + paths)

    webbrowser.open(urlstr)

    out_file.write(urlstr)
    out_file.close()

