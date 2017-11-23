# 시스템최신기술 과제 제출
모든 코드는 systemNewTechnology 폴더 안에 있습니다

Mission #4, #5를 하나의 60초 데모 비디오로 구성.  한 화면에 소스코드 2가지 각각 (온도를 ThingSpeak로도 쏘고, 이어서 여러분 서버로도 쏘는 것) (웹서버인데 화일에도 저장하고, 데이타베이스에도 저장) 화면에 ssh를 여러개 띄워놓고 한번에 비디오 찍도록 함.

- Youtube URL (Mission 4,5) :    [https://youtu.be/xgScrkX3Ohw]
- thingspeak URL :             [https://thingspeak.com/channels/248481]

# Mission 4 :
 node.js 설치 및 간단웹서버 구축, http로 온도 데이타 받아서 화일에 포맷팅하여 저장하는 프로그램 작성, github에 올림
# Mission 5 :
 Mission 4의 연장으로, mysql을 설치하고 온도 데이타를 database에 저장시킴, 프로그램을 github에 올림.

파이썬 코드입니다
```python
import os
import time
import urllib
import json
import httplib
import requests

# 5초의 데이터 업데이트 시간을 설정하고 API 값을 저장합니다
sleep = 5
key = 'PC45B10F37HRMZ0P'

# 라즈베리파이가 센서데이터를 받는 경로를 설정합니다.
temp_sensor='/sys/bus/w1/devices/28-0416935fd1ff/w1_slave'

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

# 파일의 내용을 읽어오는 함수
def temp_raw():
    f = open(temp_sensor,'r')
    lines = f.readlines()
    f.close()
    return lines

# 읽어온 파일의 구문을 분석해 온도부분만 반환하는 함수
def read_temp():
    lines = temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = temp_raw()

    temp_output = lines[1].find('t=')

    if temp_output != -1:
        temp_string = lines[1].strip()[temp_output+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0/5.0 + 32.0
        return temp_c, temp_f

# ThingSpeak에 데이터를 전송하는 함수
# 또한 nodejs에 GET 방식으로 온도 파라미터를 전달하는 역할도 합니다
def thermometer():
    while True:
        temp = read_temp()[0]
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        params = urllib.urlencode({'field1': temp, 'key':key })
        conn = httplib.HTTPConnection("api.thingspeak.com:80")

        try:
            print(" ")
            print "[+] ThingSpeak"
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print temp
            print response.status, response.reason
            data = response.read()
            conn.close()

            print "[+] Node.js"
            r = requests.get('http://192.168.137.74:3000/logone', params={'temp':temp})
            print r.status_code

        except:
            print "connection failed"
        break



if __name__ == "__main__":
    while True:
        thermometer()
        time.sleep(sleep)
```

Node.js 코드입니다
```javascript
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
```


