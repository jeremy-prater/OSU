module.exports = function(app) {
    var index = require('../controllers/slips.server.controller');
    app.get('/slips', index.slips);
    app.get('/slips/:slipid', index.slips);
    app.post('/slips', index.slips);
    app.delete('/slips/:slipid', index.slips);
};