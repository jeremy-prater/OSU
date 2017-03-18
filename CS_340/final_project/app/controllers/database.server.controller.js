var mysqlDB = require('../components/db');
var dbPool = new mysqlDB();

exports.getItems = function (req, res) {
    dbPool.getItems(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getLocations = function (req, res) {
    dbPool.getLocations(req, res, function (payload) {
        res.json(payload);
    });
};

/*exports.insertWorkout = function (req, res) {
    dbPool.insertWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.updateWorkout = function (req, res) {
    dbPool.updateWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteWorkout = function (req, res) {
    dbPool.deleteWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteAllWorkouts = function (req, res) {
    dbPool.deleteAllWorkouts(req, res, function (payload) {
        res.json(payload);
    });
};*/