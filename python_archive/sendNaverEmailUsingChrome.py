#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 네이버에 로그인해서 특정 이메일주소로 메일을 자동으로 보내는 메크로 코드
                황짱이 알려줌
'''
from selenium import webdriver
from bs4 import BeautifulSoup
import time

# 크롬 객체를 생성한다
driver = webdriver.Chrome()
driver.implicitly_wait(3)

# 아이디로 로그인한다
driver.get('https://nid.naver.com/nidlogin.login')
driver.find_element_by_name('id').send_keys('hsy1199')
driver.find_element_by_name('pw').send_keys('32eoeotnthd!')

driver.find_element_by_xpath('//*[@id="frmNIDLogin"]/fieldset/input').click() # 로그인 버튼 클릭
driver.find_element_by_xpath('//*[@id="PM_ID_ct"]/div[1]/div[2]/div[1]/ul[1]/li[1]/a/span[1]').click()  # 메일버튼 클릭
driver.find_element_by_xpath('//*[@id="nav_snb"]/div[1]/a[1]/strong/span').click()  # 메일쓰기 버튼 클릭
time.sleep(3)
driver.find_element_by_id('toInput').send_keys('skendy209@naver.com') # 메일주소 값 입력
driver.find_element_by_xpath('//*[@id="subject"]').click()
driver.find_element_by_id('subject').send_keys('spam')   # 메일 제목 값 입력
driver.find_element_by_xpath('//*[@id="sendBtn"]').click()  # 보내기 버튼 클릭
