var express = require('express');
module.exports = function() {
    var app = express();
    app.use(express.static('./public'));
    app.set('views', './app/views');
    app.set('view engine', 'pug');
    require('../app/routes/index.server.routes.js')(app);
    return app;
};
