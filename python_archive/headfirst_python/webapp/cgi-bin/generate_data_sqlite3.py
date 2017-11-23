#! /usr/local/bin/python3

import cgi
import json
import athletemodel_sqlite3
import yate



form_data = cgi.FieldStorage()
athlete_id = form_data['which_athlete'].value
athlete = athletemodel_sqlite3.get_athlete_from_id(athlete_id)


print(yate.start_response('application/json'))
print(json.dumps(athlete))
