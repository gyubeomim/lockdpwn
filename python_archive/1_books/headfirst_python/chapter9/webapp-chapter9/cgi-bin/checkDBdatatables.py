
import os
import sqlite3

db_filename = 'coachdata.sqlite'

if not os.path.exists(db_filename):
    print('Whoops - no DB: try running createDBtables.py and initDBtables.py first.')
else:
    which_id = int(input('Provide an id to display: '))

    # Connect to the database in SQLite3.
    connection = sqlite3.connect(db_filename)
    cursor = connection.cursor()

    cursor.execute("SELECT name, dob from athletes WHERE id=?", (which_id,))
    result = cursor.fetchone()
    print(result[0])
    print(result[1])

    # Get the data associated with the athlete.
    cursor.execute("SELECT * from timing_data WHERE athlete_id=?", (which_id,))
    for result_t in cursor.fetchall():
        print(result_t[1], end=' ')
    print()
    
    # Go for it, then close.
    connection.close()
 
