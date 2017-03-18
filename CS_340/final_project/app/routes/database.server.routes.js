module.exports = function(app) {
    var database = require('../controllers/database.server.controller');
    app.get('/getItems', database.getItems);
    app.get('/getLocations', database.getLocations);
    //app.post('/deleteAllWorkouts', database.deleteAllWorkouts);
};