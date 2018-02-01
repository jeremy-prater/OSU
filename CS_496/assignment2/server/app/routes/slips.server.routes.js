module.exports = function(app) {
    var index = require('../controllers/slips.server.controller');
    app.get('/slips', index.render);
    app.get('/slips/:slipid', index.render);
    app.post('/slips', index.render);
};