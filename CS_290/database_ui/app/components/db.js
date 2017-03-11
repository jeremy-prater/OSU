const mysql = require('mysql');

module.exports = function () {
    var context = this;


    this.pool = mysql.createPool({
        host: 'mysql.cs.orst.edu',
        user: 'cs340_praterj',
        password: '7221',
        database: 'cs340_praterj'
    });
    console.log('[MYSQL] Created Database object.');

    this.getWorkouts = function (req, res, callback) {
        console.log('[MYSQL] /database.getWorkouts');
        context.pool.query('SELECT * FROM workouts', function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };


    this.insertWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.insertWorkout');
        var payload = {};
        var dataSet = [
            req.body.name,
            req.body.reps,
            req.body.weight,
            req.body.date,
            req.body.lbs
        ];
        context.pool.query("INSERT INTO workouts (name, reps, weight, date, lbs) VALUES (?, ?, ?, ?, ?)", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": true,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.deleteWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.deleteWorkout');
        var payload = {};
        var dataSet = [
            req.body.workoutID,
        ];
        context.pool.query("DELETE FROM workouts WHERE workoutID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload.error = err;
                    callback(payload);
                    return;
                }
                payload = {
                    "deleted": req.body.workoutID
                };
                callback(payload);
            });
    };

    this.createTable = function () {
        console.log('[MYSQL] Create Table');
        var createString =
            "CREATE TABLE IF NOT EXISTS workouts(" +
            "workoutID INT PRIMARY KEY AUTO_INCREMENT," +
            "name VARCHAR(255) NOT NULL," +
            "reps int NOT NULL," +
            "weight int NOT NULL," +
            "date DATETIME NOT NULL," +
            "lbs BOOLEAN NOT NULL) ENGINE=InnoDB;";
        context.pool.query(createString, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            }
        });
    };

    // Functions are defined. Do any initialization needed.

    this.createTable();
}