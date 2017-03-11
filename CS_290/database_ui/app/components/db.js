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
                console.log(err);
                return;
            }
            context.results = JSON.stringify(rows);
            res.json(context);
        });

    };


    this.insertWorkout = function () {
        console.log('[MYSQL] /database.insertWorkout');
        console.log(req.query);
        var context = {};
        mysql.pool.query("INSERT INTO workouts (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?)", [req.query.name, req.query.reps, req.query.date, req.query.lbs],
            function (err, result) {
                if (err) {
                    next(err);
                    return;
                }
                context.results = "Inserted id " + result.workoutID;
                res.render('home', context);
            });
    };

    this.deleteWorkout = function () {
        console.log('[MYSQL] /database.deleteWorkout');
    };

    this.createTable = function () {
        console.log('[MYSQL] Create Table');
        var context = this;
        this.pool.query("DROP TABLE IF EXISTS workouts", function (err) {
            var createString = "CREATE TABLE workouts(" +
                "workoutID INT PRIMARY KEY AUTO_INCREMENT," +
                "name VARCHAR(255) NOT NULL," +
                "reps int NOT NULL," +
                "weight int NOT NULL," +
                "date DATETIME NOT NULL," +
                "lbs BOOLEAN);";
            context.pool.query(createString, function (err) {
                context.results = "Table reset";
                res.json(context);
            })
        });
    };

    // Functions are defined. Do any initialization needed.

    this.createTable();
}