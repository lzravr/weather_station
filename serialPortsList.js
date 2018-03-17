var SerialPort = require('serialport');

var n = 0;
SerialPort.list(function (err, ports) 
{
  ports.forEach(function(port) 
  {
    console.log(n + ". Port com name: " + port.comName);
    console.log(n + ". Port pnpId: " + port.pnpId);
    console.log(n + ". Port manufacturer: " + port.manufacturer);
	n++;
  });
});