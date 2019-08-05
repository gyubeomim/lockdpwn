#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sqlite3를 이용해 coachdata.sqlite 파일에서 데이터를 가져오는 코드
'''
import sqlite3

db_name = 'coachdata.sqlite'


def get_names_from_store():
    connection = sqlite3.connect(db_name)
    cursor = connection.cursor()
    results = cursor.execute("""SELECT name FROM athletes""")
    response = [row[0] for row in results.fetchall()]
    connection.close()
    return(response)



def get_athlete_from_id(athlete_id):
    connection - sqlite.connect(db_name)
    cursor = connection.cursor()


    results = cursor.execute("""SELECT name, dob FROM athletes WHERE id=?""",
                             (athlete_id,))

    (name,dob) = results.fetchone()


    results = cursor.execute("""SELECT value FROM timing_data WHERE athlete_id=?
ORDER BY value""", (athlete_id,))

    data = [row[0] for row in results.fetctall()]

    response = {  'Name':  name,
                  'DOB':    dob,
                  'data':   data,
                  'top3':   data[0:3]}

    connection.close()

    return(response)


def get_namesID_from_store():
    connection = sqlite3.connect(db_name)
    cursor = connection.cursor()
    results = cursor.execute("""SELECT name, id FROM athletes""")
    response = results.fetchall()
    connection.close()
    return(response)









