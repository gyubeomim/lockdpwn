get_data_cgi = '/cgi-bin/generate_data.py'
send_to_server(web_server + get_data_cgi, {'which_athlete':which_athlete})

if resp['which'] in ('positive'):
		selected_athlete = app.dialogGetSelectedItems().result[0]
		which_athlete = athlete_names[selected_athlete]
		athlete =json.loads(send_to_server(web_server + get_data_cgi,\
																			 {'which_athlete':which_athlete}))

		athlete_title = which_athlete + 'top3 times:'

		app.dialogCreateAlert(athlete_title)
		app.dialogSetItems(athlete['Top3'])
		app.dialogSetPositiveButtonTet('OK')
		app.dialogShow()

		resp = app.dialogGetResponse().result
