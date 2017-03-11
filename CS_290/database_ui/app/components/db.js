const mysql = require('mysql');

module.exports = function () {
    this.pool = mysql.createPool({
        host: 'mysql.cs.orst.edu',
        user: 'cs340_praterj',
        password: '7221',
        database: 'cs340_praterj'
    });
    console.log('[MYSQL] Created Database object.');

    this.getWorkouts = function (context, callback) {
        console.log('[MYSQL] /database.getWorkouts');
        var context = {};
        this.pool.query('SELECT * FROM workouts', function (err, rows, fields) {
            if (err) {
                next(err);
                return;
            }
            context.results = JSON.stringify(rows);
            res.json(context);
        });

    };
    

    this.insertWorkout = function (context, callback) {
        console.log('[MYSQL] /database.insertWorkout');
    };

    this.deleteWorkout = function (context, callback) {
        console.log('[MYSQL] /database.deleteWorkout');
    };

    this.createTable = function (context, callback) {
        console.log('[MYSQL] Create Table');
        var context = {};
        this.pool.query("DROP TABLE IF EXISTS workouts", function (err) {
            var createString = "CREATE TABLE workouts(" +
                "workoutID INT PRIMARY KEY AUTO_INCREMENT," +
                "name VARCHAR(255) NOT NULL," +
                "reps int NOT NULL," +
                "weight int NOT NULL," +
                "date DATETIME NOT NULL," +
                "lbs BOOLEAN);";
            this.pool.query(createString, function (err) {
                context.results = "Table reset";
                res.json(context);
            })
        });
    };
}