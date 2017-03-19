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

    this.insertData = function (table, names, data, callback) {
        var itemData =
            "INSERT INTO " + table + " (" + names + ") VALUES (" + data + ");"
        context.pool.query(itemData, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            } else {
                if (callback) {
                    callback();
                }
            }
        });
    };

    this.insertCodex = function (codexType) {
        switch (codexType) {
            case 'items':
                {
                    console.log("[MYSQL] Adding items...");
                    // Raw materials
                    // Semiconductor stuff
                    this.insertData('space_items', 'itemID, name', '1, "Silicon"');
                    this.insertData('space_items', 'itemID, name', '2, "Germanium"');
                    this.insertData('space_items', 'itemID, name', '3, "Gold"');

                    // Structural stuff
                    this.insertData('space_items', 'itemID, name', '4, "Aluminum"');
                    this.insertData('space_items', 'itemID, name', '5, "Titanium"');
                    this.insertData('space_items', 'itemID, name', '6, "Iron"');

                    // Life support stuff
                    this.insertData('space_items', 'itemID, name', '7, "Oxygen"');
                    this.insertData('space_items', 'itemID, name', '8, "Hydrogen"');
                    this.insertData('space_items', 'itemID, name', '9, "Ammonia"');

                    // Manufactured stuff
                    this.insertData('space_items', 'itemID, name', '10, "Semiconductor components"');
                    this.insertData('space_items', 'itemID, name', '11, "Computer equipment"');
                    this.insertData('space_items', 'itemID, name', '12, "Experimental components"');

                    this.insertData('space_items', 'itemID, name', '20, "External structure components"');
                    this.insertData('space_items', 'itemID, name', '21, "Internal structure components"');
                    this.insertData('space_items', 'itemID, name', '22, "Solar panel components"');

                    this.insertData('space_items', 'itemID, name', '30, "Oxygen canister"');
                    this.insertData('space_items', 'itemID, name', '31, "Hydrogen fuel"');
                    this.insertData('space_items', 'itemID, name', '32, "Ammonia coolant"');
                }
                break;
            case 'locations':
                {
                    console.log("[MYSQL] Adding locations...");
                    // Locations

                    // Quarries for getting metals
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '1, "Kappa Quarry",       0.1, 0.7, 1');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '2, "Fisher Quarry",      0.2, 0.6, 1');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '3, "Cedar Creek Quarry", 0.2, 0.2, 1');

                    // Factories for making stuff
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '4, "Lundt Gas works",   0.4, 0.5, 2');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '5, "SemiFab",           0.5, 0.4, 2');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '6, "Boing",             0.3, 0.4, 2');

                    // Launch site
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '7, "Space taXi",        0.7, 0.5, 3');

                    // ISS
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '8, "ISS",               0.9, 0.4, 4');
                }
                break;
        }
    }

    this.getItems = function (req, res, callback) {
        var sqlString = 'SELECT itemID, name FROM space_items;';
        context.pool.query(sqlString, function (err, rows, fields) {
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

    this.getLocations = function (req, res, callback) {
        var sqlString = 'SELECT locationID, name, xLocation, yLocation, locationStyle FROM space_locations;';
        context.pool.query(sqlString, function (err, rows, fields) {
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


    /*this.updateWorkout = function (req, res, callback) {
        console.log('[MYSQL] /database.insertWorkout');
        var payload = {};
        var dataSet = [
            req.body.name,
            req.body.reps,
            req.body.weight,
            new Date(req.body.date),
            req.body.lbs,
            req.body.workoutID
        ];
        context.pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE workoutID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "updated": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "updated": true,
                        "createdID": req.body.workoutID
                    };
                    callback(payload);
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
            new Date(req.body.date),
            req.body.lbs
        ];
        context.pool.query("INSERT INTO workouts (name, reps, weight, date, lbs) VALUES (?, ?, ?, ?, ?)", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
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

    this.deleteAllWorkouts = function (req, res, callback) {
        console.log('[MYSQL] /database.deleteWorkout');
        var payload = {};
        var dataSet = [];
        context.pool.query("DELETE FROM workouts", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload.error = err;
                    callback(payload);
                    return;
                }
                payload = {
                    "deleted": "all"
                };
                callback(payload);
            });
    };*/

    this.createTables = function () {
        console.log('[MYSQL] Create Table');
        var createString =
            "CREATE TABLE space_items (" +
            "itemID int," +
            "name VARCHAR(255) NOT NULL," +
            "PRIMARY KEY(itemID)" +
            ") ENGINE=InnoDB;";
        context.pool.query(createString, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            } else {}
            context.insertCodex('items');
        });
        createString =
            "CREATE TABLE space_locations (" +
            "locationID int," +
            "name VARCHAR(255) NOT NULL," +
            "xLocation double NOT NULL," +
            "yLocation double NOT NULL," +
            "locationStyle int NOT NULL," +
            "PRIMARY KEY(locationID)" +
            ") ENGINE=InnoDB;";
        context.pool.query(createString, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            } else {}
            context.insertCodex('locations');
        });
    };

    // Functions are defined. Do any initialization needed.
    this.createTables();
}