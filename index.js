var express = require('express');
var app = new express();
var http = require('http');
var server = http.createServer(app);
var io = require('socket.io').listen(server);
var file = "./data/Measurements.db";
var sqlite = require('sqlite3').verbose();
var fs = require('fs');
var bodyParser = require('body-parser');
var urlencodedParser = bodyParser.urlencoded({ extended: false })

var db;

connectDb = function() {
    db = new sqlite.Database(file);
};


app.use(express.static(__dirname + "/public"));


const SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;

var events = require('events');
var eventEmitter = new events.EventEmitter();

var USBtoArduino = new SerialPort( "COM3",{ baudRate: 9600 },function (error) { 

    if(error)
    {
        console.log("greska pri konekciji na arduino");
    }
});

const parser = USBtoArduino.pipe(new Readline({ delimiter: '\n'}));

USBtoArduino.on("error", function (error) { 
    console.log("arduino error : " + error);
});

parser.on("data", function (data) { 
    console.log("data from arduino : " + data);
    if(data[0] == "A")
    {
        connectDb();

        var time = Date.now();
        var tmp = data.split(",");
        tmp[0] = tmp[0].substr(1);

        db.run("INSERT INTO Measurements VALUES (?, ?, ?, ?, ?, ?, ?)", [time, tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5] ], function(err, succ) {
            if(err) {
                console.log("Greska pri upisivanju");
            }
            
        });
    }

    var res = { "message" : data};
    arduino.emit("arduinoResponse", res);
});

var interval;

var arduino = io.of("/arduinoUno").on("connection",function (socket) 
{ 
    console.log("User connected");
    socket.emit("serverConnect", {});

    socket.on("temperature", function (data) { 
        USBtoArduino.write("T");
     });

     socket.on("temperatureOutdoors", function (data) { 
        USBtoArduino.write("t");
     });

    socket.on("humidity", function (data) { 
        USBtoArduino.write("V");
     });

     socket.on("humidityOutdoors", function (data) { 
        USBtoArduino.write("v");
     });

    socket.on("lighting1", function (data) { 
        USBtoArduino.write("S");
     });

    socket.on("lighting2", function (data) { 
        USBtoArduino.write("s");
     });

    socket.on("refresh", function (data) {
        clearInterval(interval);
        interval = setInterval(function()
		{
            USBtoArduino.write("A");
        }, data);
    });

 });




app.get('/day', function (req, res) 
{ 
    var response = [];
    var now = Date.now(); 

    connectDb();

    db.all("SELECT * FROM Measurements WHERE ((? - Time) / (1000 * 60 * 60)) <= 24", [now], function(err, rows) {
        if(!err) {
            console.log(rows);
            res.send(rows);
        }
    });
  
 });

app.get('/month', function (req, res) 
{ 
    var response = [];
    var now = Date.now(); 

    connectDb();

    db.all("SELECT * FROM Measurements WHERE ((? - Time) / (1000 * 60 * 60 * 24)) <= 30", [now], function(err, rows) {
        if(!err) {
            console.log(rows);
            res.send(rows);
        }
    });
 });


 server.listen(3001, function () { 
    console.log("web server port : 3001 ");
 })
