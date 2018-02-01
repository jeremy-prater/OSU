module.exports = function(app) {
    var index = require('../controllers/boats.server.controller');
    app.get('/boats', index.render);
    app.get('/boats/:boatid', index.render);
    app.post('/boats', index.render);
};