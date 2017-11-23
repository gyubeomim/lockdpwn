//
// nodejs ==> 시스템최신기술, localhost:3000/graph 에 접속하면 mysql로부터 데이터를 읽어와 Google Chart를 그려주는 코드
//
var express = require('express');
var app = express();
var fs = require('fs');
var df = require('dataformat');

mysql = require('mysql');
var connection = mysql.createConnection({
	host: 'localhost',
	user: 'sensor',
	password: 'qwer1234',
	database: 'data'
})
connection.connect();

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


// localhost:3000/graph에 접속하면 googleChartSample.html에서 구글차트 템플릿을 읽어와 mysql의 데이터를 입력받아 뿌려줍니다
app.get('/graph', function(req, res){
	// 해당 템플릿 파일을 읽어온다
	var html = fs.readFile("/home/pi/gitrepo/lockdpwn/systemNewTechnology/mission6/googleChartSample.html", function (err, html) {
		html = " "+ html

		// mysql로부터 데이터를 읽어온다
		var qstr = 'select * from sensors';
		connection.query(qstr, function(err, rows, cols) {
			if (err) throw err;

			var data = "data.addRows([";
			var comma = "";
			var date = new Date;

			// 데이터를 날짜/숫자 형식에 맞게 넣어준다
			for (var i=0; i< rows.length; i++) {
				r = rows[i];
				data += comma + "[new Date(" + r.time.getFullYear() +"," +r.time.getMonth() +","+ r.time.getDate()+"," + r.time.getHours() +"," +r.time.getMinutes() + "," + r.time.getSeconds() + ")"  + ","+ r.value +"]";
				comma = ",";
			}

			// google chart 형식에 맞게 데이터를 설정한다
			var header = "data.addColumn('date', 'Date/Time');"
			header += "data.addColumn('number', 'Temp');"
			data += "]);";
			// sample.html의 <%HEADER%>와 <%DATA%> 부분을 데이터로 교체한다
			html = html.replace("<%HEADER%>", header);
			html = html.replace("<%DATA%>", data);

			res.writeHeader(200, {"Content-Type": "text/html"});
			res.write(html);
			res.end();
			console.log('[+] graph plot is complete!');
		});
	});
})

// 3000번 포트를 사용합니다
var server = app.listen(3000, function(){
	var host = server.address().address
	var port = server.address().port
	console.log('listening at http://%s:%s',host,port)
});
