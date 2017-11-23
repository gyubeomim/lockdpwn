<<<<<<< HEAD
# -*- coding: utf-8 -*-
import scrapy
import sys
from scrapy.spiders import Spider
from scrapy.selector import HtmlXPathSelector
from APT2U.items import APT2UItem
from scrapy.http import Request
from scrapy.selector import Selector
reload(sys)
sys.setdefaultencoding('utf-8')

class APT2U_Spider(scrapy.Spider):
    name = "APT2U"  #spider 이름
    allowed_domains = ["www.apt2you.com"]   #크롤링할 최상위 도메인
    start_urls = ["http://www.apt2you.com/houseSaleSimpleInfo.do"]  #실제 크롤링할 주소

    def parse(self, response):
        hxs = Selector(response)    #지정된 주소에서 전체 소스코드를 가져옴
        selects =[]                 #전체 소스코드 중에서 필요한 영역만 잘라내서 담을 리스트
        selects = hxs.xpath('//tbody[@class="line"]/tr')    #필요한 영역을 잘라서 리스트에 저장
        items = []                                          #데이터를 Item별로 구별해서 담을 리스트
        for sel in selects:
            item = APT2UItem()      #item 객체 선언
            item['aptname'] = sel.xpath('th[@scope="row"]/a[@href="#none"]/text()').extract()   #주택명 추출
            item['link'] = sel.xpath('th[@scope="row"]/a/@onclick').re('\d+')                   #링크 추출
            item['link'][0] = "http://www.apt2you.com/houseSaleDetailInfo.do?manageNo="+item['link'][0] #전체링크주소구성
            item['company'] = sel.xpath('td[1]/text()').extract()                      #건설업체 추출
            item['receiptdate'] = sel.xpath('normalize-space(td[2]/text())').extract() #청약기간 추출
            item['result_date'] = sel.xpath('td[@class="end"]/text()').extract()       #당첨자발표일 추출
            items.append(item)                                                         #Item 1개 세트를 리스트에 담음
        return items
=======
#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==>
'''

import random
from environment import GraphicDisplay, Env

class PolicyIteration:
    def __init__(self, env):
        # 환경에 대한 객체 선언
        self.env = env

        # 가치함수를 2차원 리스트로 초기화
        self.value_table = [[0.00] * env.width for _ in range(env.height)]

        # 상하좌우에 대해 동일한 확률로 정책 초기화
        self.policy_table = [[[0.25, 0.25, 0.25, 0.25]] * env.width for _ in range(env.height)]

        # 마침 상태의 결정
        self.policy_table[2][2] = []

        # 감가율 
        self.discount_factor = 0.9

    def policy_evaluation(self):
        next_value_table = [[0.00] * self.env.width for _ in range(self.env.hegiht)]
        
        for state in self.env.get_all_states():
            value = 0.0

            if state == [2, 2]:
                next_value_table[state[0]][state[1]] = 0.0
                continue

        # 벨만 기대방정식
        for action in self.env.possible_actions:
            next_state = self.env.state_after_action(state, action)
            reward = self.env.get_reward(state, action)
            next_value = self.get_value(next_state)

            value += self.get_policy(state)[action] * (reward + self.discount_factor * next_value)

        next_value_table[state[0]][state[1]] = round(value, 2)


    self.value_table = next_value_table

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
