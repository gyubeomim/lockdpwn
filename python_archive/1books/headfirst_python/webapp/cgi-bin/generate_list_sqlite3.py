#! /usr/local/bin/python3

import athletemodel_sqlite3
import yate

athletes = athletemodel_sqlite3.get_namesID_from_store()


print(yate.start_response())
print(yate.include_header("Coach Kelly's List of Athletes"))
print(yate.start_form("generate_timing_data_sqlite3.py"))
print(yate.para("Select an athlete from the list to work with:"))
for each_athlete in sorted(athletes):
    print(yate.radio_button_id("which_athlete", each_athlete[0],each_athlete[1]))
    
print(yate.end_form("Select"))
print(yate.include_footer({"Home": "/index_sqlite3.html"}))
