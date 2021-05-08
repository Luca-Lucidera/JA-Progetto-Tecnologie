var app = require('http').createServer(handler)
  , io = require('socket.io').listen(app)
  , fs = require('fs')
  , five = require("johnny-five"),
  board,led1,led2,led3,led4,led5,leds,tempsensor,heartsensor,button1,button2,button3,button4,button5;

board = new five.Board({
  port: "COM3"
});

board.on("ready", function() {
    led1 = new five.Led(12);
    led2 = new five.Led(11);
    led3 = new five.Led(10);
    led4 = new five.Led(9);
    led5 = new five.Led(8);
    leds = new five.Leds([led1,led2,led3,led4,led5]);
    button1 = new five.Button(7);
    button2 = new five.Button(6);
    button3 = new five.Button(5);
    button4 = new five.Button(4);
    button5 = new five.Button(3);
    tempsensor = new five.Sensor({
        pin: "A0",
        freq: 1000
    })
    heartsensor = new five.Sensor({
        pin: "A1",
        freq: 1000
    })
    leds.blink();
});

app.listen(80);

function handler (req, res) {
    fs.readFile(__dirname + '/index.html',
    function (err, data) {
      if (err) {
        res.writeHead(500);
        return res.end('Error loading index.html');
      }
  
      res.writeHead(200);
      res.end(data);
    });
}

io.sockets.on('connection', function (socket) {
    button1.on("down", function() {
        socket.emit("button1", {});
    });
    button2.on("down", function() {
        socket.emit("button2", {});
    });
    button3.on("down", function() {
        socket.emit("button3", {});
    });
    button4.on("down", function() {
        socket.emit("button4", {});
    });
    button5.on("down", function() {
        socket.emit("button5", {});
    });

    socket.on('led', function (data) {
        if(board.isReady){
            leds[data].blink();
        } 
    });

    if(board.isReady){
        tempsensor.on("data",function(){
            socket.emit('tempsensor', { raw: this.raw });
        });
        heartsensor.on("data",function(){
            socket.emit('heartsensor', { raw: this.raw });
        });
    };
});