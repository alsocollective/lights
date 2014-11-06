var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io');

app.use(express.static(__dirname));

app.get('/', function(req, res) {
	res.sendfile('index.html');
});

http.listen(3000, function() {
	console.log('listening on *:3000');
});

var io = io.listen(http);

io.on('connection', function(socket) {
	console.log('user connected');

	io.sockets.emit('setup', {
		"red1": red1,
		"green1": green1,
		"blue1": blue1,
		"red2": red2,
		"green2": green2,
		"blue2": blue2,
		"speed": speed
	});

	socket.on('red1', function(msg) {
		console.log('red: ' + msg);
		red1 = msg;
		io.sockets.emit('red1', {
			"value": msg
		});
		writeCue.push({
			"func": 1,
			"r": red1,
			"g": green1,
			"b": blue1
		});
	});
	socket.on('green1', function(msg) {
		console.log('green: ' + msg);
		green1 = msg;
		io.sockets.emit('green1', {
			"value": msg
		});
		writeCue.push({
			"func": 1,
			"r": red1,
			"g": green1,
			"b": blue1
		});
	});
	socket.on('blue1', function(msg) {
		console.log('blue: ' + msg);
		blue1 = msg;
		io.sockets.emit('blue1', {
			"value": msg
		});
		writeCue.push({
			"func": 1,
			"r": red1,
			"g": green1,
			"b": blue1
		});
	});
	socket.on('red2', function(msg) {
		console.log('red: ' + msg);
		red2 = msg;
		io.sockets.emit('red2', {
			"value": msg
		});
		writeCue.push({
			"func": 2,
			"r": red2,
			"g": green2,
			"b": blue2
		});
	});
	socket.on('green2', function(msg) {
		console.log('green: ' + msg);
		green2 = msg;
		io.sockets.emit('green2', {
			"value": msg
		});
		writeCue.push({
			"func": 2,
			"r": red2,
			"g": green2,
			"b": blue2
		});
	});
	socket.on('blue2', function(msg) {
		console.log('blue: ' + msg);
		blue2 = msg;
		io.sockets.emit('blue2', {
			"value": msg
		});
		writeCue.push({
			"func": 2,
			"r": red2,
			"g": green2,
			"b": blue2
		});
	});
	socket.on('fade1', function(msg) {
		console.log("colour change 1");
		writeCue.push({
			"func": 3
		});
	});
	socket.on('fade2', function(msg) {
		console.log("colour change 2");
		writeCue.push({
			"func": 4
		});
	});
	socket.on('fade3', function(msg) {
		console.log("colour change both");
		writeCue.push({
			"func": 5
		});
	});
	socket.on("speed", function(msg) {
		speed = msg;
		io.sockets.emit('speed', {
			"value": msg
		});
		writeCue.push({
			"func": 6,
			"speed": msg
		});
	});

	socket.on('disconnect', function() {
		console.log('user disconnected');
	});
});


var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/cu.usbserial-A4013A6D", {
	baudrate: 9600
});


var red1 = 0,
	green1 = 0,
	blue1 = 0,
	red2 = 0,
	green2 = 0,
	blue2 = 0,
	speed = 50;
var writeCue = [];


var message = new Buffer('aaa');
serialPort.on("open", function() {
	console.log("opend!!! ");
	serialPort.on('data', function(data) {
		var data = data.toString('ascii', 0, data.length)
		if (data.indexOf("READY") > -1) {
			console.log("recived data READY");
			if (writeCue.length > 0) {
				console.log(writeCue[0])
				serialWrite(writeCue[0]);
				writeCue.splice(0, 1);
			}
		} else if (!(data.indexOf("R") > -1 || data.indexOf("E") > -1 || data.indexOf("A") > -1 || data.indexOf("D") > -1 || data.indexOf("Y") > -1) && data.length > 2) {
			console.log(data);
		}
	});
});


function serialWrite(func) {
	if (func["func"] == 3 || func["func"] == 4 || func["func"] == 5) {
		serialPort.write([func["func"]]);
	} else if (func["func"] == 1 || func["func"] == 2) {
		serialPort.write([func["func"], func["r"], func["g"], func["b"]]);
	} else if (func["func"] == 6) {
		serialPort.write([6, func["speed"]]);
	}
}