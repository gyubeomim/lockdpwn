#! /usr/local/bin/python3

# Step 2: write a new CGI script to handle the new data request.
import json

import athletemodel
import yate

names = athletemodel.get_names_from_store()

print(yate.start_response('application/json'))
print(json.dumps(sorted(names)))

