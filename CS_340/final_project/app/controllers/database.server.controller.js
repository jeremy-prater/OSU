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

exports.getProductions = function (req, res) {
    dbPool.getProductions(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getItemsByLocation = function (req, res) {
    dbPool.getItemsByLocation(req, res, function (payload) {
        res.json(payload);
    });
};

exports.createItem = function (req, res) {
    dbPool.createItem(req, res, function (payload) {
        res.json(payload);
    });
};

/*exports.updateWorkout = function (req, res) {
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