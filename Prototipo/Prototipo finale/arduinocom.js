var app = require('http').createServer(handler)
  , io = require('socket.io')(app)
  , fs = require('fs')
  , SerialPort = require('serialport')
  , Readline = require('@serialport/parser-readline');

app.listen(80);

const port = new SerialPort('COM3', {
    baudRate: 9600
});
const parser = port.pipe(new Readline());

function handler (req, res) {
    fs.readFile(__dirname + '/primo.html',
    function (err, data) {
    if (err) {
        res.writeHead(500);
        return res.end('Error loading index.html');
    }

    res.writeHead(200);
    res.end(data);
    });
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