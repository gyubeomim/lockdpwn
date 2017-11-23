var express = require('express')
var app = express()

app.get('/', function(req,res)
{
	res.send('Hello world')
})

app.get('/update', function(req,res)
{
	console.log("[*] visited /update url!")
	console.log(req.query)
	console.log(typeof req.query)
	console.log(typeof JSON.stringify(req.query))
	console.log(typeof JSON.parse(JSON.stringify(req.query)))
	console.log(typeof req.query.api_key)
	res.send('Hello world')

	var a ={}
	a = 7
	a.p = 8
	console.log(a)
	console.log(a.p)
})

app.listen(3000, function()
{
	console.log('example app listening on port 3000')
})


























