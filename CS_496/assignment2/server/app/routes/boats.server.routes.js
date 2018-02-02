module.exports = function(app) {
    var index = require('../controllers/boats.server.controller');
    app.get('/boats', index.boat);
    app.get('/boats/:boatid', index.boat);
    app.post('/boats', index.boat);
    app.patch('/boats/:boatid', index.boat);
    app.delete('/boats/:boatid', index.boat);
};