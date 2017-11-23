#! /usr/local/bin/python3



import cgi
import athletemodel_sqlite3
import yate




form_data = cgi.FieldStorage()
athlete_id = form_data['which_athlete'].value
athlete = athletemodel_sqlite3.get_athlete_from_id(athlete_id)



print(yate.start_response())


print(yate.include_header("Coach Kelly's Timing Data"))


print(yate.header("Athlete: " + athlete['Name'] + " , DOB: " + athlete['DOB'] +"."))


print(yate.para("The top times for this athlete are:"))


print(yate.u_list(athlete['top3']))


print(yate.para("The entire set of timing data is : " +str(athlete['data']) +"(duplicates removed)."))





print(yate.include_footer({"Home": "/index_sqlite3.html", \
                           "Select another athlete": "generate_list_sqlite3.py"}))


