var mysqlDB = require('../components/db');
var dbPool = new mysqlDB();

exports.getWorkouts = function (req, res) {
    res.json(dbPool.getWorkouts(req));
};

exports.insertWorkout = function (req, res) {
    res.json(dbPool.insertWorkout(req));
};

exports.deleteWorkout = function (req, res) {
    res.json(dbPool.deleteWorkout(req));
};