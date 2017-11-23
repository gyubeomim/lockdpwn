// 
// nodejs ==> 시스템최신기술, nodejs로 ds18b20의 센서데이터를 읽어오는 코드
//

// express 패키지를 사용합니다
var express = require('express');
var app = express();

bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({extended: false}));

// 파일을 저장하기 위해 fs, df 패키지를 사용합니다
var fs = require("fs");
var df = require('dataformat');

// mysql에 데이터를 저장하기 위해 mysql 패키지를 사용합니다
mysql = require('mysql');
var connection = mysql.createConnection({
	host:'localhost',
	user:'sensor',
	password:'qwer1234',
	database:'data'
})
connection.connect(); // mysql에 접속합니다

function insert_sensor(user, type, value, user2, serial, ip)
{
	obj = {};
	obj.user = user;
	obj.type = type;
	obj.value = value;
	obj.user2 = user2;
	obj.serial = serial;
	obj.ip = ip
	obj.date = df(new Date(), "yyyy-mm-dd HH:MM:ss");

	var d = JSON.stringify(obj);
	ret = " "+ type + user2 +"="+ value;

	//console.log("RET "+ ret);
	//
	fs.appendFile("Data.txt", d+'\n', function(err) {
		if(err) console.log("File Write Err: %j", r);
	});
	return(ret);
}


function do_get_post(cmd, r, req, res)
{
	console.log(cmd +" %j", r);
	ret_msg = "{serial:"+ r.serial +",user:"+ r.user;

	if (r.format == '2') {
		//console.log("got format 2");
		var items = r.items.split(',');

		for (var i=0; i< items.length; i++) {
			if (items[i].length < 3) continue;
			var v = items[i].split('-');
			ret_msg += insert_sensor(r.user, v[1], v[2], v[0], r.serial, req.connection.remoteAddress);
		}
	}

	ret_msg += "}";
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('X-ACK:' + ret_msg);
}

// server:3000/data 경로에 접속하면 mysql에서 데이터를 읽어와 뿌려줍니다
app.get("/data", function(req, res){
	console.log("params=" + req.query);

	// 데이터를 얼마나 받아올 지 설정할 수 있습니다
	var qstr = 'select * from sensors where time > date_sub(now(), INTERVAL 1 DAY)';

	connection.query(qstr, function(err, rows, cols){
		if(err){
			throw err;
			res.send('query error: ' +qstr);
			return;
		}

		// html 형식으로 뿌려줍니다
		console.log("Got " + rows.length +" records");
		var html = "<!doctype html><html><body>";
		html += "<H1> Sensor Data for Last 24 Hours </H1>";
		html += "<table border=1 cellpadding=3 cellspacing=0>";
		html += "<tr><td>Seq#<td>Time Stamp<td>Temperature";

		for(var i =0; i < rows.length ; i++)
		{
			html += "<tr><td>"+ JSON.stringify(rows[i]['seq'])+"<td>"+ JSON.stringify(rows[i]['time'])+"<td>"+ JSON.stringify(rows[i]['value']);
		}
		html += "</table>";
		html += "</body></html>";
		res.send(html);
	});
});

// server:3000/logone 에 GET 방식으로 접속하면 파라미터 값을 받아서 mysql에 넣는 작업을 수행하고
// log.txt 파일에 데이터를 저장하는 작업 또한 수행합니다
app.get('/logone', function(req, res){
	var i = 0;
	i++;

	r = {};
	r.seq = i;
	r.type = 'T';
	r.device = '102';
	r.unit = '0';
	r.ip = req.ip;
	r.value = req.query.temp;

	var query = connection.query('insert into sensors set ?', r, function(err, rows,cols){
		if(err)
		{
			throw err;
		}
		console.log("[+]SQL injection is done!");
	});
	
	var date = new Date();
	fs.appendFile("log.txt",JSON.stringify(req.query) +", "+req.ip+", "+ date +"\n" ,function(err){
	if(err){
			return console.log(err);
		}
	})
	r = req.query;
	do_get_post("GET", r, req, res);
});



// server:3000/logone 에 POST 방식으로 접속하면 파라미터 값을 받아서 mysql에 넣는 작업을 수행하고
// log.txt 파일에 데이터를 저장하는 작업 또한 수행합니다
app.post('/logone', function(req, res){
	r = {};
	r.seq = 1;
	r.type = 'T';
	r.device = '102';
	r.unit = '0';
	r.ip = req.ip;
	r.value = req.query.temp;

	var query = connection.query('insert into sensors set ?', r, function(err, rows,cols){
		if(err)
		{
			throw err;
		}
		console.log("done");
	});

	var date = new Date();

	fs.appendFile("log.txt",JSON.stringify(req.query) +", "+req.ip+", "+ date +"\n" ,function(err){
		if(err){
			return console.log(err);
		}
	})

	r = req.body;
	do_get_post("POST", r, req, res);
});

// 3000번 포트를 사용합니다
var server = app.listen(3000, function(){
	var host = server.address().address
	var port = server.address().port
	console.log('listening at http://%s:%s',host,port)
});
		
