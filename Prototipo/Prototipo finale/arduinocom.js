var app = require('http').createServer(handler)
  , io = require('socket.io')(app)
  , fs = require('fs')
  , SerialPort = require('serialport')
  , Readline = require('@serialport/parser-readline')
  , url = require('url');

app.listen(80);

const port = new SerialPort('COM3', {
    baudRate: 9600
});
const parser = port.pipe(new Readline());

function handler (req, res) {
    var path = url.parse(req.url).pathname;
    var fsCallback = function(error, data) {
        if(error) throw error;

        res.writeHead(200);
        res.write(data);
        res.end();
    }

    switch(path) {
        case '/login.html':
            fs.readFile(__dirname + '/Login.html', fsCallback);
        break;
        case '/temperatura.html':
            fs.readFile(__dirname + '/temperatura.html', fsCallback);
        break;
        default:
            fs.readFile(__dirname + '/primo.html', fsCallback);
        break;
    }
}

parser.on('error', function(err) {
    console.log('Error: ', err.message);
});

parser.on('data', function (data) {
    io.emit('stuffwithserial', data);
});

//collegamento web -> arduino
io.on("connection", (socket) => {
    socket.on("send", (data) => {
        port.write(data);
    });
});