var Avrgirl = require('avrgirl-arduino');
 
var avrgirl = new Avrgirl({
  board: 'uno'
});

avrgirl.flash('/ino/weather_station/weather_station.hex', function (error) {
  if (error) {
    console.error(error);
  } else {
    console.info('done.');
  }
});