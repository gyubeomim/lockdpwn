#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 소프트융합최신, 기상청에서 기상데이터를 웹크롤링하고 urbaneco 사이트에서 모기포집수를 웹크롤링해서 X, Y의 형태의 데이터로 가공한 후 RandomForest 알고리즘을 사용한 프로젝트
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 
import requests
import re
from bs4 import BeautifulSoup
from datetime import date

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import accuracy_score
from sklearn.metrics import r2_score



#-----------------------------------------------------------------------------------
# DATA PREPROCESSING
#-----------------------------------------------------------------------------------
### 2010년 데이터는 누적치 계산을 위해 준비한다

# 기상청에서 데이터를 가져오기 위해 주소를 입력한다
# 평균기온----------------------------
Tav_2010_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2010'
Tav_2011_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2011'
Tav_2012_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2012'
Tav_2013_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2013'
Tav_2014_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2014'
Tav_2015_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2015'
Tav_2016_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2016'
Tav_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2017'


# 습도---------------------------
Hum_2010_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2010'
Hum_2011_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2011'
Hum_2012_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2012'
Hum_2013_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2013'
Hum_2014_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2014'
Hum_2015_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2015'
Hum_2016_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2016'
Hum_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2017'


# 최저기온  ----------------------------
Tmi_2010_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2010&obs=10'
Tmi_2011_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2011&obs=10'
Tmi_2012_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2012&obs=10'
Tmi_2013_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2013&obs=10'
Tmi_2014_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2014&obs=10'
Tmi_2015_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2015&obs=10'
Tmi_2016_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2016&obs=10'
Tmi_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2017&obs=10'


# 최고기온  ----------------------------
Tmx_2010_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2010&obs=08'
Tmx_2011_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2011&obs=08'
Tmx_2012_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2012&obs=08'
Tmx_2013_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2013&obs=08'
Tmx_2014_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2014&obs=08'
Tmx_2015_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2015&obs=08'
Tmx_2016_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2016&obs=08'
Tmx_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2017&obs=08'



# 강수량----------------------------
Raf_2010_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2010&obs=21'
Raf_2011_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2011&obs=21'
Raf_2012_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2012&obs=21'
Raf_2013_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2013&obs=21'
Raf_2014_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2014&obs=21'
Raf_2015_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2015&obs=21'
Raf_2016_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2016&obs=21'
Raf_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?yy=2017&obs=21'



# List에서 특정 문자를 치환하는 함수
def replace(array, from_, to_):
        while from_ in array:
            idx = array.index(from_)
            array.pop(idx)
            array.insert(idx, to_)



# BeautifulSoup의 데이터를 가공한 후 Numpy 형식으로 반환하는 함수
def getArrayFromBeautyfulSoup(url_name):
    # requests Method를 사용해 데이터를 크롤링한다
    source_code = requests.get(url_name)
    plain_text = source_code.text

    # bs4로 기상데이터들을 가져온다
    soup = BeautifulSoup(plain_text, 'lxml')

    # 한 해의 데이터를 전부 컬럼으로 받기 위해 변수를 추가합니다
    tmp_sum = np.array(np.zeros(15))

    # 매월 1일 ~ 31일 + 평균 데이터들을 tmp에 입력하고 data에 한 컬럼씩 추가합니다
    for i in range(0,32):
        tmp = soup.select('#content_weather > table > tbody > tr')[i].get_text().split("\n")

        # bad char를 삭제해줍니다
        replace(tmp, '\xa0', '')

        tmp = np.array(tmp)
        # 한 컬럼씩 추가합니다
        tmp_sum = np.vstack((tmp_sum, tmp))

    # 맨 앞에 있는 (0,0,0...) 컬럼을 삭제합니다
    tmp_sum = np.delete(tmp_sum, 0, 0)
    return tmp_sum


# 평균온도 2010 ~ 2016 데이터 ---------------------------
Tav_2010_data = getArrayFromBeautyfulSoup(Tav_2010_url)
Tav_2011_data = getArrayFromBeautyfulSoup(Tav_2011_url)
Tav_2012_data = getArrayFromBeautyfulSoup(Tav_2012_url)
Tav_2013_data = getArrayFromBeautyfulSoup(Tav_2013_url)
Tav_2014_data = getArrayFromBeautyfulSoup(Tav_2014_url)
Tav_2015_data = getArrayFromBeautyfulSoup(Tav_2015_url)
Tav_2016_data = getArrayFromBeautyfulSoup(Tav_2016_url)
Tav_2017_data = getArrayFromBeautyfulSoup(Tav_2017_url)


# 최저온도 2010 ~ 2016 데이터 ---------------------------
Tmi_2010_data = getArrayFromBeautyfulSoup(Tmi_2010_url)
Tmi_2011_data = getArrayFromBeautyfulSoup(Tmi_2011_url)
Tmi_2012_data = getArrayFromBeautyfulSoup(Tmi_2012_url)
Tmi_2013_data = getArrayFromBeautyfulSoup(Tmi_2013_url)
Tmi_2014_data = getArrayFromBeautyfulSoup(Tmi_2014_url)
Tmi_2015_data = getArrayFromBeautyfulSoup(Tmi_2015_url)
Tmi_2016_data = getArrayFromBeautyfulSoup(Tmi_2016_url)
Tmi_2017_data = getArrayFromBeautyfulSoup(Tmi_2017_url)


# 최고온도 2010 ~ 2016 데이터 ---------------------------
Tmx_2010_data = getArrayFromBeautyfulSoup(Tmx_2010_url)
Tmx_2011_data = getArrayFromBeautyfulSoup(Tmx_2011_url)
Tmx_2012_data = getArrayFromBeautyfulSoup(Tmx_2012_url)
Tmx_2013_data = getArrayFromBeautyfulSoup(Tmx_2013_url)
Tmx_2014_data = getArrayFromBeautyfulSoup(Tmx_2014_url)
Tmx_2015_data = getArrayFromBeautyfulSoup(Tmx_2015_url)
Tmx_2016_data = getArrayFromBeautyfulSoup(Tmx_2016_url)
Tmx_2017_data = getArrayFromBeautyfulSoup(Tmx_2017_url)


# 강수량 2010 ~ 2016 데이터 ---------------------------
Raf_2010_data = getArrayFromBeautyfulSoup(Raf_2010_url)
Raf_2011_data = getArrayFromBeautyfulSoup(Raf_2011_url)
Raf_2012_data = getArrayFromBeautyfulSoup(Raf_2012_url)
Raf_2013_data = getArrayFromBeautyfulSoup(Raf_2013_url)
Raf_2014_data = getArrayFromBeautyfulSoup(Raf_2014_url)
Raf_2015_data = getArrayFromBeautyfulSoup(Raf_2015_url)
Raf_2016_data = getArrayFromBeautyfulSoup(Raf_2016_url)
Raf_2017_data = getArrayFromBeautyfulSoup(Raf_2017_url)


# 습도 2010 ~ 2016 데이터 ---------------------------
Hum_2010_data = getArrayFromBeautyfulSoup(Hum_2010_url)
Hum_2011_data = getArrayFromBeautyfulSoup(Hum_2011_url)
Hum_2012_data = getArrayFromBeautyfulSoup(Hum_2012_url)
Hum_2013_data = getArrayFromBeautyfulSoup(Hum_2013_url)
Hum_2014_data = getArrayFromBeautyfulSoup(Hum_2014_url)
Hum_2015_data = getArrayFromBeautyfulSoup(Hum_2015_url)
Hum_2016_data = getArrayFromBeautyfulSoup(Hum_2016_url)
Hum_2017_data = getArrayFromBeautyfulSoup(Hum_2017_url)



# pandas 데이터프레임 생성--------------------------------
df_Tav_2010_data = pd.DataFrame(Tav_2010_data)
df_Tav_2011_data = pd.DataFrame(Tav_2011_data)
df_Tav_2012_data = pd.DataFrame(Tav_2012_data)
df_Tav_2013_data = pd.DataFrame(Tav_2013_data)
df_Tav_2014_data = pd.DataFrame(Tav_2014_data)
df_Tav_2015_data = pd.DataFrame(Tav_2015_data)
df_Tav_2016_data = pd.DataFrame(Tav_2016_data)
df_Tav_2017_data = pd.DataFrame(Tav_2017_data)


df_Tmi_2010_data = pd.DataFrame(Tmi_2010_data)
df_Tmi_2011_data = pd.DataFrame(Tmi_2011_data)
df_Tmi_2012_data = pd.DataFrame(Tmi_2012_data)
df_Tmi_2013_data = pd.DataFrame(Tmi_2013_data)
df_Tmi_2014_data = pd.DataFrame(Tmi_2014_data)
df_Tmi_2015_data = pd.DataFrame(Tmi_2015_data)
df_Tmi_2016_data = pd.DataFrame(Tmi_2016_data)
df_Tmi_2017_data = pd.DataFrame(Tmi_2017_data)


df_Tmx_2010_data = pd.DataFrame(Tmx_2010_data)
df_Tmx_2011_data = pd.DataFrame(Tmx_2011_data)
df_Tmx_2012_data = pd.DataFrame(Tmx_2012_data)
df_Tmx_2013_data = pd.DataFrame(Tmx_2013_data)
df_Tmx_2014_data = pd.DataFrame(Tmx_2014_data)
df_Tmx_2015_data = pd.DataFrame(Tmx_2015_data)
df_Tmx_2016_data = pd.DataFrame(Tmx_2016_data)
df_Tmx_2017_data = pd.DataFrame(Tmx_2017_data)


df_Raf_2010_data = pd.DataFrame(Raf_2010_data)
df_Raf_2011_data = pd.DataFrame(Raf_2011_data)
df_Raf_2012_data = pd.DataFrame(Raf_2012_data)
df_Raf_2013_data = pd.DataFrame(Raf_2013_data)
df_Raf_2014_data = pd.DataFrame(Raf_2014_data)
df_Raf_2015_data = pd.DataFrame(Raf_2015_data)
df_Raf_2016_data = pd.DataFrame(Raf_2016_data)
df_Raf_2017_data = pd.DataFrame(Raf_2017_data)


df_Hum_2010_data = pd.DataFrame(Hum_2010_data)
df_Hum_2011_data = pd.DataFrame(Hum_2011_data)
df_Hum_2012_data = pd.DataFrame(Hum_2012_data)
df_Hum_2013_data = pd.DataFrame(Hum_2013_data)
df_Hum_2014_data = pd.DataFrame(Hum_2014_data)
df_Hum_2015_data = pd.DataFrame(Hum_2015_data)
df_Hum_2016_data = pd.DataFrame(Hum_2016_data)
df_Hum_2017_data = pd.DataFrame(Hum_2017_data)



# 강수량 데이터는 공백이 많으므로 공백을 0으로 채운 변수도 따로 설정해줍니다(나머지도 해줘야 하는듯)
df_Raf_2010_data2 = pd.DataFrame(Raf_2010_data)
df_Raf_2011_data2 = pd.DataFrame(Raf_2011_data)
df_Raf_2012_data2 = pd.DataFrame(Raf_2012_data)
df_Raf_2013_data2 = pd.DataFrame(Raf_2013_data)
df_Raf_2014_data2 = pd.DataFrame(Raf_2014_data)
df_Raf_2015_data2 = pd.DataFrame(Raf_2015_data)
df_Raf_2016_data2 = pd.DataFrame(Raf_2016_data)
df_Raf_2017_data2 = pd.DataFrame(Raf_2017_data)


df_Tav_2010_data2 = pd.DataFrame(Tav_2010_data)
df_Tav_2011_data2 = pd.DataFrame(Tav_2011_data)
df_Tav_2012_data2 = pd.DataFrame(Tav_2012_data)
df_Tav_2013_data2 = pd.DataFrame(Tav_2013_data)
df_Tav_2014_data2 = pd.DataFrame(Tav_2014_data)
df_Tav_2015_data2 = pd.DataFrame(Tav_2015_data)
df_Tav_2016_data2 = pd.DataFrame(Tav_2016_data)
df_Tav_2017_data2 = pd.DataFrame(Tav_2017_data)


df_Tmi_2010_data2 = pd.DataFrame(Tmi_2010_data)
df_Tmi_2011_data2 = pd.DataFrame(Tmi_2011_data)
df_Tmi_2012_data2 = pd.DataFrame(Tmi_2012_data)
df_Tmi_2013_data2 = pd.DataFrame(Tmi_2013_data)
df_Tmi_2014_data2 = pd.DataFrame(Tmi_2014_data)
df_Tmi_2015_data2 = pd.DataFrame(Tmi_2015_data)
df_Tmi_2016_data2 = pd.DataFrame(Tmi_2016_data)
df_Tmi_2017_data2 = pd.DataFrame(Tmi_2017_data)


df_Tmx_2010_data2 = pd.DataFrame(Tmx_2010_data)
df_Tmx_2011_data2 = pd.DataFrame(Tmx_2011_data)
df_Tmx_2012_data2 = pd.DataFrame(Tmx_2012_data)
df_Tmx_2013_data2 = pd.DataFrame(Tmx_2013_data)
df_Tmx_2014_data2 = pd.DataFrame(Tmx_2014_data)
df_Tmx_2015_data2 = pd.DataFrame(Tmx_2015_data)
df_Tmx_2016_data2 = pd.DataFrame(Tmx_2016_data)
df_Tmx_2017_data2 = pd.DataFrame(Tmx_2017_data)


df_Hum_2010_data2 = pd.DataFrame(Hum_2010_data)
df_Hum_2011_data2 = pd.DataFrame(Hum_2011_data)
df_Hum_2012_data2 = pd.DataFrame(Hum_2012_data)
df_Hum_2013_data2 = pd.DataFrame(Hum_2013_data)
df_Hum_2014_data2 = pd.DataFrame(Hum_2014_data)
df_Hum_2015_data2 = pd.DataFrame(Hum_2015_data)
df_Hum_2016_data2 = pd.DataFrame(Hum_2016_data)
df_Hum_2017_data2 = pd.DataFrame(Hum_2017_data)


# 강수일 RaD 데이터를 만들기 위해서 변수를 선언해줘야 합니다
df_RaD_2010_data = pd.DataFrame(Raf_2010_data)
df_RaD_2011_data = pd.DataFrame(Raf_2011_data)
df_RaD_2012_data = pd.DataFrame(Raf_2012_data)
df_RaD_2013_data = pd.DataFrame(Raf_2013_data)
df_RaD_2014_data = pd.DataFrame(Raf_2014_data)
df_RaD_2015_data = pd.DataFrame(Raf_2015_data)
df_RaD_2016_data = pd.DataFrame(Raf_2016_data)
df_RaD_2017_data = pd.DataFrame(Raf_2017_data)



# Tav, Tmi, Tmx, Hum, Raf 데이터를 Series로 묶어줍니다
df_Tav = pd.Series((df_Tav_2012_data, df_Tav_2011_data, df_Tav_2012_data, df_Tav_2013_data, df_Tav_2014_data, df_Tav_2015_data, df_Tav_2016_data, df_Tav_2017_data))
df_Tmi = pd.Series((df_Tmi_2010_data, df_Tmi_2011_data, df_Tmi_2012_data, df_Tmi_2013_data, df_Tmi_2014_data, df_Tmi_2015_data, df_Tmi_2016_data, df_Tmi_2017_data))
df_Tmx = pd.Series((df_Tmx_2010_data, df_Tmx_2011_data, df_Tmx_2012_data, df_Tmx_2013_data, df_Tmx_2014_data, df_Tmx_2015_data, df_Tmx_2016_data, df_Tmx_2017_data))
df_Hum = pd.Series((df_Hum_2010_data, df_Hum_2011_data, df_Hum_2012_data, df_Hum_2013_data, df_Hum_2014_data, df_Hum_2015_data, df_Hum_2016_data, df_Hum_2017_data))
df_Raf = pd.Series((df_Raf_2010_data, df_Raf_2011_data, df_Raf_2012_data, df_Raf_2013_data, df_Raf_2014_data, df_Raf_2015_data, df_Raf_2016_data, df_Raf_2017_data))
# 강수일 RaD 데이터
df_RaD = pd.Series((df_RaD_2010_data, df_RaD_2011_data, df_RaD_2012_data, df_RaD_2013_data, df_RaD_2014_data, df_RaD_2015_data, df_RaD_2016_data, df_RaD_2017_data))



# 강수량 정보는 공백란이 많으므로 0으로 채워줘야 합니다
df_Raf_filled_value = pd.Series((df_Raf_2010_data2, df_Raf_2011_data2, df_Raf_2012_data2, df_Raf_2013_data2, df_Raf_2014_data2, df_Raf_2015_data2,df_Raf_2016_data2, df_Raf_2017_data2))
df_Tav_filled_value = pd.Series((df_Tav_2010_data2, df_Tav_2011_data2, df_Tav_2012_data2, df_Tav_2013_data2, df_Tav_2014_data2, df_Tav_2015_data2,df_Tav_2016_data2, df_Tav_2017_data2))
df_Tmi_filled_value = pd.Series((df_Tmi_2010_data2, df_Tmi_2011_data2, df_Tmi_2012_data2, df_Tmi_2013_data2, df_Tmi_2014_data2, df_Tmi_2015_data2,df_Tmi_2016_data2, df_Tmi_2017_data2))
df_Tmx_filled_value = pd.Series((df_Tmx_2010_data2, df_Tmx_2011_data2, df_Tmx_2012_data2, df_Tmx_2013_data2, df_Tmx_2014_data2, df_Tmx_2015_data2,df_Tmx_2016_data2, df_Tmx_2017_data2))
df_Hum_filled_value = pd.Series((df_Hum_2010_data2, df_Hum_2011_data2, df_Hum_2012_data2, df_Hum_2013_data2, df_Hum_2014_data2, df_Hum_2015_data2,df_Hum_2016_data2, df_Hum_2017_data2))




# 강수량의 빈칸을 0으로 채워주는 코드 (나머지 코드도 빈칸 없애줘야 할듯)
for j in range(0,8):
    for i in df_Raf_filled_value[j].columns:
        df_Raf_filled_value[j][i][df_Raf_filled_value[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for j in range(0,8):
    for i in df_Tav_filled_value[j].columns:
        df_Tav_filled_value[j][i][df_Tav_filled_value[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for j in range(0,8):
    for i in df_Tmi_filled_value[j].columns:
        df_Tmi_filled_value[j][i][df_Tmi_filled_value[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for j in range(0,8):
    for i in df_Tmx_filled_value[j].columns:
        df_Tmx_filled_value[j][i][df_Tmx_filled_value[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for j in range(0,8):
    for i in df_Hum_filled_value[j].columns:
        df_Hum_filled_value[j][i][df_Hum_filled_value[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0




# RaD (강수일)을 계산하는 코드
# Raf 데이터중 0.0 ==> Null('')로 바꿔야 RaD를 1로 계산하지 않습니다
for j in range(0,8):
    for i in df_RaD[j].columns:
        if i > 1:
            df_RaD[j][i][df_RaD[j][i].apply(lambda i: True if re.search('0\.0', str(i)) else False)] = ''  
# 강수일 RaD 데이터를 가공하는 코드. 강수량의 값이 존재하면 1로 바꿉니다
for j in range(0,8):
    for i in df_RaD[j].columns:
        if i > 1:
            df_RaD[j][i][df_RaD[j][i].apply(lambda i: False if re.search('^\s*$', str(i)) else True)] = 1  
for j in range(0,8):
    for i in df_RaD[j].columns:
        df_RaD[j][i][df_RaD[j][i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0





#------------------------------------------------------------
# csv의 모기포집수 데이터(Y)와 웹크롤링을 한 기상데이터(X)를 합쳐주는 함수
def makeDataTo_X_Y(csv_file_name, year, location_name):
    # 날짜 포맷을 설정해주기 위한 코드
    dateparse = lambda x: pd.datetime.strptime(x, '%Y-%m-%d %H:%M:%S')
    tmp = pd.read_csv(csv_file_name, names = ["Date", "Mosq"], parse_dates=['Date'], date_parser=dateparse)
    length = len(tmp['Date'])

    # return할 DataFrame 변수 생성 
    tmp_df = pd.DataFrame(np.zeros((length,9)), columns = ["Location", "Date", "Hum", "Raf", "Tmx", "Tav", "Tmi","landUse", "Mosq"])

    # 비수변 : 1, 샛강 : 2, 수변 : 3을 설정하는 코드
    if location_name == "대림동유수지" or location_name == "문래동빗물펌프장" or location_name == "양평동생태공원" or location_name == "양평1동유수지" or location_name == "양평빗물펌프장":
        landUse = 3
    elif location_name == "국회의원회관" or location_name == "당산중학교" or location_name == "KBS":
        landUse = 2
    else:
        landUse = 1

    print("\n[*] Processing... It takes a while... ")
    print(csv_file_name,"\n")

    # Mosquito CSV 데이터 가공 코드
    for leng in range(0, length):
        for month in range(0, 13):
            for day in range(0, 32):
                # 루프를 돌면서 csv 파일에 존재하는 날짜에 데이터가 있는 경우
                if tmp['Date'][leng].date().month == month and tmp['Date'][leng].date().day == day:
                    # 모기가 2000마리가 넘어가면 너무 많다고 생각되어 최대값을 2000으로 제한합니다
                    if tmp['Mosq'][leng] > 2000: 
                        tmp['Mosq'][leng] = 2000


    # Mosquito 모기포집수의 평균(정수로 반올림)을 구합니다
    mosq_mean = tmp['Mosq'].mean().round()
    i = 0
    is_found = False

    for month in range(5, 13):
        for day in range(1, 32):
            for leng in range(0, length):
                # 루프를 돌면서 csv 파일에 존재하는 날짜에 데이터를 추가합니다
                if tmp['Date'][leng].date().month == month and tmp['Date'][leng].date().day == day:
                    print("i : %d, month : %d, day : %d" % (i, month, day))

                    tmp_df['Location'].loc[i] = location_name
                    tmp_df['Date'].loc[i]     = tmp['Date'][leng]
                    tmp_df['Tav'].loc[i]      = df_Tav_filled_value[year-2010][month + 1][day - 1]
                    tmp_df['Tmi'].loc[i]      = df_Tmi_filled_value[year-2010][month + 1][day - 1]
                    tmp_df['Tmx'].loc[i]      = df_Tmx_filled_value[year-2010][month + 1][day - 1]
                    tmp_df['Raf'].loc[i]      = df_Raf_filled_value[year-2010][month + 1][day - 1]
                    tmp_df['Hum'].loc[i]      = df_Hum_filled_value[year-2010][month + 1][day - 1]
                    tmp_df['landUse'].loc[i]  = int(landUse)
                    tmp_df['Mosq'].loc[i]     = int(tmp['Mosq'][leng])
                    is_found = True
            
            # csv 파일에 날짜, Mosquito 값이 있다면 continue로 다음 루프로 넘어갑니다
            if is_found == True:
                is_found = False
                i += 1
                continue

            # csv 파일에 날짜가 없는 경우 없는 날짜를 date로 가공해서 만들어준다
            date = str(day) + '/' + str(month) + '/' + str(year)
            date = pd.to_datetime([date], format='%d/%m/%Y', errors = 'coerce')[0]

            # 2011/6/31 같은 존재하지 않는 날짜는 skip한다
            if pd.isnull(date):
                continue

            print("i : %d, month : %d, day : %d  [csv EMPTY!]" % (i, month, day))

            tmp_df['Location'].loc[i] = location_name
            tmp_df['Date'].loc[i]     = date           # 날짜 삽입
            tmp_df['Tav'].loc[i]      = df_Tav_filled_value[year-2010][month + 1][day - 1]
            tmp_df['Tmi'].loc[i]      = df_Tmi_filled_value[year-2010][month + 1][day - 1]
            tmp_df['Tmx'].loc[i]      = df_Tmx_filled_value[year-2010][month + 1][day - 1]
            tmp_df['Raf'].loc[i]      = df_Raf_filled_value[year-2010][month + 1][day - 1]
            tmp_df['Hum'].loc[i]      = df_Hum_filled_value[year-2010][month + 1][day - 1]
            tmp_df['landUse'].loc[i]  = int(landUse)
            tmp_df['Mosq'].loc[i]     = mosq_mean      # 평균 삽입
            i += 1

    return tmp_df





result = makeDataTo_X_Y(".\\swConvTech_part1_data\\양평빗물펌프장_2011.csv", 2011, "양평빗물펌프장")
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평빗물펌프장_2012.csv", 2012, "양평빗물펌프장"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평빗물펌프장_2013.csv", 2013, "양평빗물펌프장"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평빗물펌프장_2014.csv", 2014, "양평빗물펌프장"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\KBS_모기_포집수_2012.csv", 2012, "KBS"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\KBS_모기_포집수_2013.csv", 2013, "KBS"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\KBS_모기_포집수_2014.csv", 2014, "KBS"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\국회의원회관_모기_포집수_2012.csv", 2012, "국회의원회관"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\국회의원회관_모기_포집수_2014.csv", 2014, "국회의원회관"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\김안과_병원_모기_포집수_2013.csv", 2013, "김안과병원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\김안과_병원_모기_포집수_2014.csv", 2014, "김안과병원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\당산중학교_후문_공원_모기_포집수_2013.csv", 2013, "당산중학교"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\당산중학교_후문_공원_모기_포집수_2014.csv", 2014, "당산중학교"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\대림동_유수지_모기_포집수_2013.csv", 2013, "대림동유수지"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\대림동_유수지_모기_포집수_2014.csv", 2014, "대림동유수지"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\동아에코빌_아파트_모기_포집수_2011.csv", 2011, "동아에코빌아파트"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\동아에코빌_아파트_모기_포집수_2012.csv", 2012, "동아에코빌아파트"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\동아에코빌_아파트_모기_포집수_2013.csv", 2013, "동아에코빌아파트"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\동아에코빌_아파트_모기_포집수_2014.csv", 2014, "동아에코빌아파트"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\두암어린이공원_모기_포집수_2013.csv", 2013, "두암어린이공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\두암어린이공원_모기_포집수_2014.csv", 2014, "두암어린이공원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\문래근린공원_모기_포집수_2013.csv", 2013, "문래근린공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\문래근린공원_모기_포집수_2014.csv", 2014, "문래근린공원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\문래동빗물펌프장_모기포집수_2014.csv", 2014, "문래동빗물펌프장"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\문래동빗물펌프장_모기포집수_2015.csv", 2015, "문래동빗물펌프장"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\살레시오_모기_포집수_2011.csv", 2011, "살레시오"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\살레시오_모기_포집수_2012.csv", 2012, "살레시오"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\살레시오_모기_포집수_2013.csv", 2013, "살레시오"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\살레시오_모기_포집수_2014.csv", 2014, "살레시오"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신길근린공원_모기_포집수_2013.csv", 2013, "신길근린공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신길근린공원_모기_포집수_2014.csv", 2014, "신길근린공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신길근린공원_모기_포집수_2015.csv", 2015, "신길근린공원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신일어린이집_2011.csv", 2011, "신일어린이집"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신일어린이집_2012.csv", 2012, "신일어린이집"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신일어린이집_2013.csv", 2013, "신일어린이집"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\신일어린이집_2014.csv", 2014, "신일어린이집"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평1동유수지_모기_포집수_2012.csv", 2012, "양평1동유수지"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평1동유수지_모기_포집수_2013.csv", 2013, "양평1동유수지"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평1동유수지_모기_포집수_2014.csv", 2014, "양평1동유수지"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동_생태공원_모기_포집수_2012.csv", 2012, "양평동생태공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동_생태공원_모기_포집수_2013.csv", 2013, "양평동생태공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동_생태공원_모기_포집수_2014.csv", 2014, "양평동생태공원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동노인복지회관_모기_포집수_2011.csv", 2011, "양평동노인복지회관"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동노인복지회관_모기_포집수_2012.csv", 2012, "양평동노인복지회관"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동노인복지회관_모기_포집수_2013.csv", 2013, "양평동노인복지회관"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\양평동노인복지회관_모기_포집수_2014.csv", 2014, "양평동노인복지회관"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\여의도고등학교_모기_2014.csv", 2014, "여의도고등학교"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\여의도고등학교_모기_2015.csv", 2015, "여의도고등학교"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\영등포공원_모기_포집수_2011.csv", 2011, "영등포공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\영등포공원_모기_포집수_2012.csv", 2012, "영등포공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\영등포공원_모기_포집수_2013.csv", 2013, "영등포공원"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\영등포공원_모기_포집수_2014.csv", 2014, "영등포공원"))

result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\윤중초등학교_모기_포집수_2014.csv", 2014, "윤중초등학교"))
result = result.append(makeDataTo_X_Y(".\\swConvTech_part1_data\\윤중초등학교_모기_포집수_2015.csv", 2015, "윤중초등학교"))

result = result.reset_index(drop=True)

result.to_csv("part1_data.csv", index=False, encoding='utf-8')
result.to_csv("part1_data_with_index.csv", encoding='utf-8')







# 기상정보의 누적치를 계산해주는 함수
def accumulate_Data(dataset, column_name, day, month, year):
    # day, month, year로 date format의 변수를 만든다
    date = str(day) + '/' + str(month) + '/' + str(year)
    date = pd.to_datetime([date], format='%d/%m/%Y', errors = 'coerce')[0]


    # return할 누적 변수 생성 
    accum_data = pd.DataFrame(np.zeros((1,33)), columns = ["Date", column_name, column_name + "1", column_name + "2", column_name + "3", column_name + "4", column_name + "5", column_name + "6", column_name + "7", column_name + "8", column_name + "9", column_name + "10", column_name + "11", column_name + "12", column_name + "13", column_name + "14", column_name + "15", column_name + "16", column_name + "17", column_name + "18", column_name + "19", column_name + "20", column_name + "21", column_name + "22", column_name + "23", column_name + "24", column_name + "25", column_name + "26", column_name + "27", column_name + "28", column_name + "29", column_name + "30", column_name + "31"])


    # 2월 31일 같은 유효하지 않은 날짜는 skip 하기 위한 코드
    if pd.isnull(date):
        return

    # 처음 누적치 ex) Hum1을 우선 저장한다
    accum_data['Date'].loc[0] = date
    accum_data[column_name].loc[0] = float(dataset[year-2010][month+1][day-1])

    # 3일,2일,1일... 처럼 일수 때문에 저번달로 넘어가야 하는지 결정하는 플래그
    before_month_flag = False

    # 이전 Loop의 누적치를 저장하기 위한 변수
    accum_before = accum_data[column_name+"1"].loc[0]

    # i값이 i -= j로 인해 0이 되더라도 column_name+str(k)는 계속 증가해야 하므로 아래와 같이 k 변수를 추가한다
    k = 1
    
    print("[*] Data Accumulating...")
    print("                        ", date, column_name)

    for i in range(1, 32):
        # 누적값을 구하는 도중 3일, 2일, 1일... 순으로 작아지면 저번달 30일로 넘어간다
        if (day-i-1) < 0:
            # 31일이 있는 달과 아닌 달을 구분합니다
            if month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12:
                day = 31
            else:
                day = 30

            # 1월이 아닌 경우만 -1달씩 감소시킨다
            if month != 1:
               month -= 1
            # 1월이면 전년도 12월달로 간다
            elif month == 1:
                year -= 1
                month = 12

            before_month_flag = True
            j = i
        
        # 저번달 30일로 넘어가면 다시 30일, 29, 28, 27... 순이 되어야 하므로 아래와 같은 코드를 추가한다
        if before_month_flag:
            i -= j 

        # 누적치를 계산해서 아래 넣는다. ex) Raf29 = Raf28 + Raf[day-29] 
        accum_data[column_name+str(k)].loc[0] = accum_before + float(dataset[year-2010][month+1][day-i-1])

        # 이전 Loop의 누적치를 저장한다
        accum_before = accum_data[column_name+str(k)].loc[0]
        k += 1

    return accum_data






# 2011 ~2017년까지 누적데이터를 구한다
for year in range(2011, 2018):
    for month in range(1, 13):
        for day in range(1, 32):
            if year == 2011 and month == 1 and day == 1:
                accum_Hum_result = accumulate_Data(df_Hum_filled_value, "Hum", day, month, year)
                accum_Tav_result = accumulate_Data(df_Tav_filled_value, "Tav", day, month, year)
                accum_Tmi_result = accumulate_Data(df_Tmi_filled_value, "Tmi", day, month, year)
                accum_Tmx_result = accumulate_Data(df_Tmx_filled_value, "Tmx", day, month, year)
                accum_Raf_result = accumulate_Data(df_Raf_filled_value, "Raf", day, month, year)
                accum_RaD_result = accumulate_Data(df_RaD, "RaD", day, month, year)
            else:
                accum_Hum_result = accum_Hum_result.append(accumulate_Data(df_Hum_filled_value, "Hum", day, month, year))
                accum_Tav_result = accum_Tav_result.append(accumulate_Data(df_Tav_filled_value, "Tav", day, month, year))
                accum_Tmi_result = accum_Tmi_result.append(accumulate_Data(df_Tmi_filled_value, "Tmi", day, month, year))
                accum_Tmx_result = accum_Tmx_result.append(accumulate_Data(df_Tmx_filled_value, "Tmx", day, month, year))
                accum_Raf_result = accum_Raf_result.append(accumulate_Data(df_Raf_filled_value, "Raf", day, month, year))
                accum_RaD_result = accum_RaD_result.append(accumulate_Data(df_RaD, "RaD", day, month, year))



# 누적데이터들의 index를 수정하고
accum_Hum_result = accum_Hum_result.reset_index(drop=True)
accum_Tav_result = accum_Tav_result.reset_index(drop=True)
accum_Tmi_result = accum_Tmi_result.reset_index(drop=True)
accum_Tmx_result = accum_Tmx_result.reset_index(drop=True)
accum_Raf_result = accum_Raf_result.reset_index(drop=True)
accum_RaD_result = accum_RaD_result.reset_index(drop=True)


# csv 파일로 저장한다 (하나는 index 있는 버전, 다른 하나는 없는 버전이다)
accum_Hum_result.to_csv("accum_Hum_data.csv", index=False, encoding='utf-8')
accum_Tav_result.to_csv("accum_Tav_data.csv", index=False, encoding='utf-8')
accum_Tmi_result.to_csv("accum_Tmi_data.csv", index=False, encoding='utf-8')
accum_Tmx_result.to_csv("accum_Tmx_data.csv", index=False, encoding='utf-8')
accum_Raf_result.to_csv("accum_Raf_data.csv", index=False, encoding='utf-8')
accum_RaD_result.to_csv("accum_RaD_data.csv", index=False, encoding='utf-8')

#accum_Hum_result.to_csv("accum_Hum_data_with_index.csv", encoding='utf-8')
#accum_Tav_result.to_csv("accum_Tav_data_with_index.csv", encoding='utf-8')
#accum_Tmi_result.to_csv("accum_Tmi_data_with_index.csv", encoding='utf-8')
#accum_Tmx_result.to_csv("accum_Tmx_data_with_index.csv", encoding='utf-8')
#accum_Raf_result.to_csv("accum_Raf_data_with_index.csv", encoding='utf-8')
#accum_RaD_result.to_csv("accum_RaD_data_with_index.csv", encoding='utf-8')

# ipython qtconsole을 재시작해서 변수가 사라진 경우에 사용했습니다
# 데이터 읽어오기 -----------------------------------------------------------
result =  pd.read_csv(".\\part1_data.csv")
accum_Hum_result = pd.read_csv(".\\accum_Hum_data.csv")
accum_Tav_result = pd.read_csv(".\\accum_Tav_data.csv")
accum_Tmi_result = pd.read_csv(".\\accum_Tmi_data.csv")
accum_Tmx_result = pd.read_csv(".\\accum_Tmx_data.csv")
accum_Raf_result = pd.read_csv(".\\accum_Raf_data.csv")
accum_RaD_result = pd.read_csv(".\\accum_RaD_data.csv")



# 위에서 불러온 모든 데이터들을 합쳐줍니다
accum_result = pd.Series((result, accum_Hum_result, accum_Tav_result, accum_Tmi_result, accum_Tmx_result, accum_Raf_result, accum_RaD_result))


    
# result와 accum... csv 데이터들의 컬럼을 합쳐주는 함수
def makeAccumDataTo_X_Y(csv_file, Hum_, Raf_, RaD_, Tav_, Tmi_, Tmx_):
    # result 변수에 있는 데이터 row의 크기를 가져옵니다
    length = len(csv_file[0])

    # return할 DataFrame 변수 생성 
    semi_final_result = pd.DataFrame(np.zeros((length,10)), columns = ["Date", "Location", Hum_, Raf_, RaD_, Tav_, Tmi_,Tmx_, "landUse", "Mosq"])

    # csv 파일의 초기 날짜 (2011/01/01)을 date format으로 수정한다
    init_date = str(1) + '/' + str(1) + '/' + str(2011)
    init_date = pd.to_datetime([init_date], format='%d/%m/%Y', errors = 'coerce')[0]
    
    for leng in range(0, length):
        print ("[*] Processing... %d" % leng)
        for year in range(2011, 2018):
            for month in range(5, 13):
                for day in range(1, 32):

                    if month < 10 and day < 10:
                        string_date = str(year) + '-0' + str(month) + '-0' + str(day)+ ' 00:00:00'
                    elif month < 10:
                        string_date = str(year) + '-0' + str(month) + '-' +  str(day)+ ' 00:00:00'
                    elif day < 10:
                        string_date = str(year) + '-' +  str(month) + '-0' + str(day)+ ' 00:00:00'
                    else:
                        string_date = str(year) + '-' +  str(month) + '-' +  str(day)+ ' 00:00:00'


                    # Date가 일치하는 데이터만 추출해야하므로 날짜가 안맞으면 다음 루프로 넘어간다
                    if csv_file[0]['Date'][leng] != string_date:
                        continue


                    # 현재 날짜를 date format으로 만들고 초기날짜와의 날짜 수를 계산한다
                    date = str(day) + '/' + str(month) + '/' + str(year)
                    date = pd.to_datetime([date], format='%d/%m/%Y', errors = 'coerce')[0]
                    
                    # date 값이 유효하지않으면 skip
                    if pd.isnull(date):
                        continue
                    
                    # 두 날짜의 차이 계산 (yyyy/mm/dd - 2011/01/01)
                    delta = date - init_date
                    gap_between = delta.days

                    print(date, gap_between)

                    semi_final_result['Date'].loc[leng]     =   csv_file[0]['Date'][leng]
                    semi_final_result['Location'].loc[leng] =   csv_file[0]['Location'][leng]
                    semi_final_result['landUse'].loc[leng]  =   csv_file[0]['landUse'][leng]
                    semi_final_result['Mosq'].loc[leng]     =   csv_file[0]['Mosq'][leng]
                    semi_final_result[Hum_].loc[leng]       =   csv_file[1][Hum_][gap_between]
                    semi_final_result[Raf_].loc[leng]       =   csv_file[5][Raf_][gap_between]
                    semi_final_result[RaD_].loc[leng]       =   csv_file[6][RaD_][gap_between]
                    semi_final_result[Tav_].loc[leng]       =   csv_file[2][Tav_][gap_between]
                    semi_final_result[Tmi_].loc[leng]       =   csv_file[3][Tmi_][gap_between]

                    # Tmx는 왜그런지 1825 (2015-12-31)가 없다 
                    if gap_between != 1825:
                        semi_final_result[Tmx_].loc[leng]       =   csv_file[4][Tmx_][gap_between]

    return semi_final_result


# 특정 누적데이터를 설정하는 코드
hum_ = "Hum5"
raf_ = "Raf6"
rad_ = "RaD29"
tav_ = "Tav16"
tmi_ = "Tmi2"
tmx_ = "Tmx19"


# 컬럼:['Date', 'Location', 'Hum20', 'Raf30', 'RaD30', 'Tav5', 'Tmi30', 'Tmx5', 'landUse', 'Mosq'] 같이 누적된 데이터가 있는 DataFrame을 생성합니다
semi_final_result = makeAccumDataTo_X_Y(accum_result, hum_, raf_, rad_, tav_, tmi_, tmx_)
semi_final_result.to_csv("semi_final_result_2.csv", index=False, encoding='utf-8')



# csv 데이터 불러오는 코드----------------------------------------------------------
semi_final_result = pd.read_csv(".\\semi_final_result_2.csv")


# Mosquito (모기 포집수)의 데이터를 1~8 단계 Level로 등급을 매기는 함수
def change_Mosquito_To_Level(f_result):
    length = len(f_result['Mosq'])

    for i in range(0, length):
        print(i, '/', length)
        mosq_num = f_result['Mosq'][i]
        if mosq_num > 1280:
            f_result['Mosq'][i] = 8
        elif mosq_num <= 1280 and mosq_num > 640:
            f_result['Mosq'][i] = 7
        elif mosq_num <= 640 and mosq_num > 320:
            f_result['Mosq'][i] = 6
        elif mosq_num <= 320 and mosq_num > 160:
            f_result['Mosq'][i] = 5
        elif mosq_num <= 160 and mosq_num > 80:
            f_result['Mosq'][i] = 4
        elif mosq_num <= 80 and mosq_num > 40:
            f_result['Mosq'][i] = 3
        elif mosq_num <= 40 and mosq_num > 20:
            f_result['Mosq'][i] = 2
        else:
            f_result['Mosq'][i] = 1

    f_result = f_result.rename(columns={'Mosq':'Level'})
    return f_result



# ['Mosq'] 헤더를 ['Level']로 바꾸고 모기포집수를 레벨로 바꿉니다
final_result = change_Mosquito_To_Level(semi_final_result)


# RF에 사용하지 않을 컬럼을 삭제합니다
del final_result['Location']

final_result.to_csv("final_result_2.csv", index=False, encoding='utf-8')






# csv 데이터 불러오는 코드----------------------------------------------------------
final_result = pd.read_csv(".\\final_result_2.csv")





#-----------------------------------------------------------------------------------
# DO RANDOMFOREST
#-----------------------------------------------------------------------------------
# File Paths & Headers
HEADERS = ["Date", hum_, raf_, rad_, tav_, tmi_, tmx_, 'landUse', "Level"]


# 데이터를 일정비율로 나눠주는 함수
def split_dataset(dataset, train_percentage, feature_headers, target_header, std_border):

    while True:
        # Split dataset into train and test dataset
        train_x, test_x, train_y, test_y = train_test_split(dataset[feature_headers], dataset[target_header], train_size=train_percentage)
        
        # 데이터의 표준편차를 구해서 표준편차의 차이가 일정량이상 작아질때까지 데이터셋을 나눠줍니다
        train_std = np.std(train_x, axis=0)
        test_std = np.std(test_x, axis=0)

        print ("\n[TRAIN STD] \n\n", train_std)
        print ("\n\n[TEST STD] \n\n", test_std)
    
        # 루프를 돌면서 표준편차의 차이가 심하면 계속 루프를 돌면서 데이터를 섞습니다
        for i in range(1, len(feature_headers)):
            if (train_std[i] - test_std[i]) > std_border:
                continue
        break

    return train_x, test_x, train_y, test_y




# Random Forest를 수행하는 함수
def random_forest_classifier(features, target):
    clf = RandomForestClassifier(n_estimators=1000, n_jobs=1, random_state=1) 
    clf.fit(features, target)
    return clf



# Test, Train 데이터를 30 : 70 으로 나눈다
train_x, test_x, train_y, test_y =  split_dataset(final_result, 0.7, HEADERS[1:-1], HEADERS[-1], 5)

# RandomForest를 수행한다
trained_model = random_forest_classifier(train_x, train_y)

# 수행한 후 결과를 예측하기 위해 predictions 변수를 설정한다
predictions = trained_model.predict(test_x)


# 정답률을 알아보는 코드 
print("Train Accuracy :: ", accuracy_score(train_y, trained_model.predict(train_x)))
print("Test Accuracy  :: ", accuracy_score(test_y, predictions))


# 실제 정답을 맞춰보는 코드
for i in range(0, 10):
    print("Actual, Predicted outcome {}, {}".format(list(test_y)[i], predictions[i]))




# 각 변수들의 기여도를 평가하고 그려주는 함수
def getImportanceValue_and_plot(t_model, X):

    # 각각 Feature들의 기여도를 보고 정규화시킵니다
    importances = t_model.feature_importances_
    std = np.std([tree.feature_importances_ for tree in trained_model.estimators_], axis=0)

    # 크기가 큰 순서로 정렬합니다
    indices = np.argsort(importances)[::-1]

    # 랭킹 순위를 매깁니다
    print("Feature ranking:")
    for f in range(X.shape[1]):
        print("%d. feature %d, %s    (%f)" % (f + 1, indices[f], X.columns[indices[f]] , importances[indices[f]])) 

    
    # 그래프를 그립니다
    plt.figure()
    plt.title("Feature importances")
    plt.bar(range(X.shape[1]), importances[indices], color="g", yerr=std[indices], align="center")
    plt.xticks(range(X.shape[1]), X.columns[indices])
    plt.xlim([-1, X.shape[1]])
    plt.show()



# Importance Value를 구합니다
getImportanceValue_and_plot(trained_model, train_x)




# 모델 성능 평가 (결정계수 r2)--------------------------------------------
rforest_regressor = RandomForestRegressor(n_estimators=1000, criterion='mse', n_jobs=1, random_state=1)
rforest_regressor.fit(train_x, train_y)

train_y_pred = rforest_regressor.predict(train_x)
test_y_pred = rforest_regressor.predict(test_x)

# 결정계수를 계산합니다
r2_train = r2_score(train_y, train_y_pred)
r2_test = r2_score(test_y, test_y_pred)

print('R2 - Train: %.3f, Test: %.3f' %(r2_train, r2_test))



# 그래프를 그리기 위해 idx를 정렬하고 각각의 파라미터별로 그래프를 그립니다
train_x = train_x.reset_index(drop=True)
train_y = train_y.reset_index(drop=True)
test_x = test_x.reset_index(drop=True)
test_y = test_y.reset_index(drop=True)

sort_idx = train_x['Hum5'].values.ravel().argsort()

plt.plot(train_x[hum_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'r.', lw=1, label='Random Forest')
plt.title(hum_, fontsize=16)
plt.xlabel(hum_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()


plt.plot(train_x[raf_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'g.', lw=1, label='Random Forest')
plt.title(raf_, fontsize=16)
plt.xlabel(raf_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()

plt.plot(train_x[rad_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'b.', lw=1, label='Random Forest')
plt.title(rad_, fontsize=16)
plt.xlabel(rad_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()


plt.plot(train_x[tav_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'c.', lw=1, label='Random Forest')
plt.title(tav_, fontsize=16)
plt.xlabel(tav_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()


plt.plot(train_x[tmi_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'y.', lw=1, label='Random Forest')
plt.title(tmi_, fontsize=16)
plt.xlabel(tmi_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()


plt.plot(train_x[tmx_][sort_idx], rforest_regressor.predict(train_x.values[sort_idx]), 'k.', lw=1, label='Random Forest')
plt.title(tmx_, fontsize=16)
plt.xlabel(tmx_, fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()




#--------------------------------------------------------------------
# FORECAST 2017.08 Mosquito using RANDOMFOREST
# 데이터를 처음에는 2016년도까지만 저장했기 떄문에 아래처럼 새로 작성했다
#--------------------------------------------------------------------

# 기상청에서 데이터를 가져오기 위해 주소를 입력한다
# 평균기온----------------------------
Tav_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=07&yy=2017'

# 습도---------------------------
Hum_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=12&yy=2017'

# 최저기온  ----------------------------
Tmi_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=10yy=2017'

# 최고기온  ----------------------------
Tmx_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=08yy=2017'

# 강수량----------------------------
Raf_2017_url = 'http://www.kma.go.kr/weather/climate/past_table.jsp?obs=21yy=2017'


# 평균온도 2017 데이터 ---------------------------
Tav_2017_data = getArrayFromBeautyfulSoup(Tav_2017_url)

# 최저온도 2017 데이터 ---------------------------
Tmi_2017_data = getArrayFromBeautyfulSoup(Tmi_2017_url)

# 최고온도 2017 데이터 ---------------------------
Tmx_2017_data = getArrayFromBeautyfulSoup(Tmx_2017_url)

# 강수량 2017 데이터 ---------------------------
Raf_2017_data = getArrayFromBeautyfulSoup(Raf_2017_url)

# 습도 2017 데이터 ---------------------------
Hum_2017_data = getArrayFromBeautyfulSoup(Hum_2017_url)



# pandas 데이터프레임 생성--------------------------------
df_Tav_2017_data = pd.DataFrame(Tav_2017_data)
df_Tmi_2017_data = pd.DataFrame(Tmi_2017_data)
df_Tmx_2017_data = pd.DataFrame(Tmx_2017_data)
df_Raf_2017_data = pd.DataFrame(Raf_2017_data)
df_Hum_2017_data = pd.DataFrame(Hum_2017_data)

# 강수량 데이터는 공백이 많으므로 공백을 0으로 채운 변수도 따로 설정해줍니다(나머지도 해줘야 하는듯)
df_Raf_2017_data2 = pd.DataFrame(Raf_2017_data)
df_Tav_2017_data2 = pd.DataFrame(Tav_2017_data)
df_Tmi_2017_data2 = pd.DataFrame(Tmi_2017_data)
df_Tmx_2017_data2 = pd.DataFrame(Tmx_2017_data)
df_Hum_2017_data2 = pd.DataFrame(Hum_2017_data)
# 강수일 RaD 데이터를 만들기 위해서 변수를 선언해줘야 합니다
df_RaD_2017_data = pd.DataFrame(Raf_2017_data)


# 강수량의 빈칸을 0으로 채워주는 코드 (나머지 코드도 빈칸 없애줘야 할듯)
for i in df_Raf_2017_data2.columns:
    df_Raf_2017_data2[i][df_Raf_2017_data2[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for i in df_Tav_2017_data2.columns:
    df_Tav_2017_data2[i][df_Tav_2017_data2[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for i in df_Tmi_2017_data2.columns:
    df_Tmi_2017_data2[i][df_Tmi_2017_data2[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for i in df_Tmx_2017_data2.columns:
    df_Tmx_2017_data2[i][df_Tmx_2017_data2[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0
for i in df_Hum_2017_data2.columns:
    df_Hum_2017_data2[i][df_Hum_2017_data2[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0


# RaD (강수일)을 계산하는 코드
# Raf 데이터중 0.0 ==> Null('')로 바꿔야 RaD를 1로 계산하지 않습니다
for i in df_RaD_2017_data.columns:
    if i > 1:
        df_RaD_2017_data[i][df_RaD_2017_data[i].apply(lambda i: True if re.search('0\.0', str(i)) else False)] = ''  

# 강수일 RaD 데이터를 가공하는 코드. 강수량의 값이 존재하면 1로 바꿉니다
for i in df_RaD_2017_data.columns:
    if i > 1:
        df_RaD_2017_data[i][df_RaD_2017_data[i].apply(lambda i: False if re.search('^\s*$', str(i)) else True)] = 1  

for i in df_RaD_2017_data.columns:
    df_RaD_2017_data[i][df_RaD_2017_data[i].apply(lambda i: True if re.search('^\s*$', str(i)) else False)] = 0



# 2017년 누적데이터를 구한다
year = 2017
for month in range(1, 13):
    for day in range(1, 32):
        if month == 1 and day == 1:
            accum_Hum_result_2017 = accumulate_Data(df_Hum_2017_data2, "Hum", day, month, year)
            accum_Tav_result_2017 = accumulate_Data(df_Tav_2017_data2, "Tav", day, month, year)
            accum_Tmi_result_2017 = accumulate_Data(df_Tmi_2017_data2, "Tmi", day, month, year)
            accum_Tmx_result_2017 = accumulate_Data(df_Tmx_2017_data2, "Tmx", day, month, year)
            accum_Raf_result_2017 = accumulate_Data(df_Raf_2017_data2, "Raf", day, month, year)
            accum_RaD_result_2017 = accumulate_Data(df_RaD_2017_data, "RaD", day, month, year)
        else:
            accum_Hum_result_2017 = accum_Hum_result_2017.append(accumulate_Data(df_Hum_2017_data2, "Hum", day, month, year))
            accum_Tav_result_2017 = accum_Tav_result_2017.append(accumulate_Data(df_Tav_2017_data2, "Tav", day, month, year))
            accum_Tmi_result_2017 = accum_Tmi_result_2017.append(accumulate_Data(df_Tmi_2017_data2, "Tmi", day, month, year))
            accum_Tmx_result_2017 = accum_Tmx_result_2017.append(accumulate_Data(df_Tmx_2017_data2, "Tmx", day, month, year))
            accum_Raf_result_2017 = accum_Raf_result_2017.append(accumulate_Data(df_Raf_2017_data2, "Raf", day, month, year))
            accum_RaD_result_2017 = accum_RaD_result_2017.append(accumulate_Data(df_RaD_2017_data, "RaD", day, month, year))


# 누적데이터들의 index를 수정하고
accum_Hum_result_2017 = accum_Hum_result_2017.reset_index(drop=True)
accum_Tav_result_2017 = accum_Tav_result_2017.reset_index(drop=True)
accum_Tmi_result_2017 = accum_Tmi_result_2017.reset_index(drop=True)
accum_Tmx_result_2017 = accum_Tmx_result_2017.reset_index(drop=True)
accum_Raf_result_2017 = accum_Raf_result_2017.reset_index(drop=True)
accum_RaD_result_2017 = accum_RaD_result_2017.reset_index(drop=True)


# csv 파일로 저장한다 (하나는 index 있는 버전, 다른 하나는 없는 버전이다)
accum_Hum_result_2017.to_csv("accum_Hum_data_2017.csv", index=False, encoding='utf-8')
accum_Tav_result_2017.to_csv("accum_Tav_data_2017.csv", index=False, encoding='utf-8')
accum_Tmi_result_2017.to_csv("accum_Tmi_data_2017.csv", index=False, encoding='utf-8')
accum_Tmx_result_2017.to_csv("accum_Tmx_data_2017.csv", index=False, encoding='utf-8')
accum_Raf_result_2017.to_csv("accum_Raf_data_2017.csv", index=False, encoding='utf-8')
accum_RaD_result_2017.to_csv("accum_RaD_data_2017.csv", index=False, encoding='utf-8')


# 위에서 불러온 모든 데이터들을 합쳐줍니다
accum_result_2017 = pd.Series((accum_Hum_result_2017, accum_Tav_result_2017, accum_Tmi_result_2017, accum_Tmx_result_2017, accum_Raf_result_2017, accum_RaD_result_2017))


# 특정 누적데이터를 설정하는 코드
hum_ = "Hum5"
raf_ = "Raf6"
rad_ = "RaD29"
tav_ = "Tav16"
tmi_ = "Tmi2"
tmx_ = "Tmx19"


# 2017년용 result와 accum... csv 데이터들의 컬럼을 합쳐주는 함수
def makeAccumDataTo_X_Y_2017(csv_file, Hum_, Raf_, RaD_, Tav_, Tmi_, Tmx_):
    # return할 DataFrame 변수 생성 
    result_2017 = pd.DataFrame(np.zeros((31,7)), columns = ["Date", Hum_, Raf_, RaD_, Tav_, Tmi_,Tmx_])

    for day in range(0, 31):
        print(day)

        result_2017['Date'].loc[day]     =   csv_file[0]['Date'][day+212]
        result_2017[Hum_].loc[day]       =   csv_file[0][Hum_][day+212]
        result_2017[Tav_].loc[day]       =   csv_file[1][Tav_][day+212]
        result_2017[Tmi_].loc[day]       =   csv_file[2][Tmi_][day+212]
        result_2017[Tmx_].loc[day]       =   csv_file[3][Tmx_][day+212]
        result_2017[Raf_].loc[day]       =   csv_file[4][Raf_][day+212]
        result_2017[RaD_].loc[day]       =   csv_file[5][RaD_][day+212]

    return result_2017


result_2017 = makeAccumDataTo_X_Y_2017(accum_result_2017, hum_, raf_, rad_, tav_, tmi_, tmx_)
del result_2017['Date']


result_2017.to_csv("result_2017.csv", index=False, encoding='utf-8')



# result_2017을 불러오는 코드----------------------------------------
result_2017 = pd.read_csv(".\\result_2017.csv")

# landUse를 3(수변)으로 가정합니다
result_2017['landUse'] = 3

# 수행한 후 결과를 예측하기 위해 predictions 변수를 설정한다
predictions = trained_model.predict(result_2017)


# 예측한 결과를 plot을 통해 확인합니다
plt.plot(predictions, 'gx')
plt.grid()
plt.title("Prediction of Mosquito Level in 2017.08", fontsize=16)
plt.xlabel("Date", fontsize=16)
plt.ylabel("Mosquito Level", fontsize=16)
plt.show()


