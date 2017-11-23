
import sqlite3

connection = sqlite3.connect('coachdata.sqlite')
cursor = connection.cursor()

import glob
import athletemodel

data_files = glob.glob("../data/*.txt")
athletes = athletemodel.put_to_store(data_files)

for each_ath in athletes:
    name = athletes[each_ath].name
    dob = athletes[each_ath].dob
    cursor.execute("SELECT id from athletes WHERE name=? AND dob=?", (name, dob))
    the_current_id = cursor.fetchone()[0]
    for each_time in athletes[each_ath].clean_data:
        cursor.execute("INSERT INTO timing_data (athlete_id, value) VALUES (?, ?)", (the_current_id, each_time))
    connection.commit()

connection.close()
 
