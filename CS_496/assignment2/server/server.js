var port = 1337;
var express = require('./config/express');
var app = express();

app.listen(port);
module.exports = app;

console.log('Boats and Slips http://localhost:' + port);
