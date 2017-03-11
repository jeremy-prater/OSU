module.exports = function(app) {
    var database = require('../controllers/database.server.controller');
    app.get('/getWorkouts', database.getWorkouts);
    app.post('/insertWorkout', database.insertWorkout);
    app.post('/deleteWorkout', database.deleteWorkout);
};