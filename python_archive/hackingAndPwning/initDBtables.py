#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 헤드퍼스트파이썬, sqlite3를 사용해 DB에 데이터를 넣어본 예제 코드
'''
import sqlite3
import glob
import athletemodel

connection = sqlite3.connect('coachdata.sqlite')
cursor = connection.cursor()

data_files = glob.glob("../data/*.txt")
athletes = athletemodel.put_to_store(data_files)

for each_ath in athletes:
	name = athletes[each_ath].name
	dob = athletes[each_ath].dob
	cursor.execute("INSERT INTO athletes (name,dob) VALUES (?, ?)",(name,dob))
	connection.commit()

cursor.execute("SELECT id from athletes WHERE name=? AND dob=?",
							 (name,dob))
the_current_id = cursor.fetchone()[0]

for each_time in athletes[each_ath].clean_data:
	cursor.execute("INSERT INTO timing_data (athlete_id,value) VALUES (?,?)",
								 (the_current_id,each_time))

connection.commit()
connection.close()
