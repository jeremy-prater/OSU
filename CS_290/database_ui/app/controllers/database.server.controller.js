var mysqlDB = require('../components/db');
var dbPool = new mysqlDB();

exports.getWorkouts = function (req, res) {
    dbPool.getWorkouts();
};

exports.insertWorkout = function (req, res) {
    dbPool.insertWorkout();
};

exports.deleteWorkout = function (req, res) {
    dbPool.deleteWorkout();
};