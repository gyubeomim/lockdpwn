var express = require('express');
var app = express();

mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'sensor',
    password: 'qwer1234',
    database: 'data'
})

connection.connect();

app.get("/data", function(req, res) {
  console.log("param=" + req.query);

  var qstr = 'select * from sensors where time > date_sub(now(), INTERVAL 1 DAY) ';

  connection.query(qstr, function(err, rows, cols) {
      if (err) {
	        throw err;
	        res.send('query error: '+ qstr);
	        return;
	      }
  
      console.log("Got "+ rows.length +" records");
      var html = "<!doctype html><html><body>";
      html += "<H1> Sensor Data for Last 24 Hours</H1>";
      html += "<table border=1 cellpadding=3 cellspacing=0>";
      html += "<tr><td>Seq#<td>Time Stamp<td>Temperature";

      for (var i=0; i< 15 /*rows.length*/; i++) {
	         html += "<tr><td>Seq#<td>Time Stamp<td>Temperature";
	      }

      html += "</table>";
      html += "</body></html>";
      res.send(html);
    });

});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
})

