#! /usr/local/bin/python3

# Step 2: write a new CGI script to handle the new data request.
import json

import athletemodel_sqlite3
import yate

names = athletemodel_sqlite3.get_namesID_from_store()


print(yate.start_response('application/json'))
print(json.dumps(sorted(names)))

