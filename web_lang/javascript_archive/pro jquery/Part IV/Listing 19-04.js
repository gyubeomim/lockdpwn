var http = require('http');
var url = require('url');

http.createServer(function (req, res) {
    console.log("[200 OK] " + req.method + " to " + req.url);
    
    var flowers = ["Astor", "Daffodil", "Rose", "Peony", "Primula", "Snowdrop",
                    "Poppy", "Primrose", "Petuna", "Pansy"];
    
    req.on('end', function() {
        var matches = [];        
        var term = url.parse(req.url, true).query["term"];
        
        if (term) {
            var pattern = new RegExp("^" + term, "i");
            for (var i = 0; i < flowers.length; i++) {                
                if (pattern.test(flowers[i])) {
                    matches.push(flowers[i]);
                }
            }
        } else {
            matches = flowers;
        }
        
        res.writeHead(200, "OK", {
            "Content-Type": "application/json",
            "Access-Control-Allow-Origin": "*"});    
        res.write(JSON.stringify(matches));
        res.end();
    });

}).listen(80);
console.log("Ready on port 80");    
