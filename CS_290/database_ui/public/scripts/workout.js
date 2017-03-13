////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

var sortType = 0;
var lastSortType = 0;
var localDataSet = [];

////////////////////////////////////////////////////////////
//
// Initalize any DOM objects data
//


////////////////////////////////////////////////////////////
//
// Click handler functions
//

function sortDate() {
    sortType = 0;
    updateSorttype();
}

function sortWeight() {
    sortType = 1;
    updateSorttype();
}

function sortReps() {
    sortType = 2;
    updateSorttype();
}

function clearAll() {
    deleteAllWorkouts();
}

////////////////////////////////////////////////////////////
//
// Client DOM update functions
//

function updateSorttype() {
    if (lastSortType == sortType) {
        return;
    } else {
        lastSortType = sortType;
        updateWorkouts();
    }
}

function deleteAllWorkouts()
{
    deleteAllWorkout(updateWorkouts);
}

function updateWorkouts() {

    console.log("[UPDATE] Rebuild Workouts - Sort method : " + sortType);

    switch (sortType) {
        case 0: //sort by date
            {

            }
            break;
        case 1: //sort by weight
            {

            }
            break;
        case 2: //sort by reps
            {

            }
            break;
    }

    console.log (localDataSet);
}

////////////////////////////////////////////////////////////
//
// Database access functions
//

function getWorkouts(callback) {
    console.log("[Workout] Getting workouts.");
    var req = new XMLHttpRequest();
    var targetUrl = '/getWorkouts';
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(null);
}

function addWorkout(callback) {
    console.log("[Workout] Adding workout.");
    var payload = {
        name: document.getElementById('name').value,
        reps: document.getElementById('reps').value,
        weight: document.getElementById('weight').value,
        date: document.getElementById('date').value,
        lbs: document.getElementById('weight_lbs').checked
    };
    var req = new XMLHttpRequest();
    var targetUrl = '/insertWorkout';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function deleteWorkout(workoutID, callback) {
    console.log("[Workout] Deleting workout :" + workoutID);
    var payload = {
        workoutID: workoutID
    };
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteWorkout';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function deleteAllWorkout(callback) {
    console.log("[Workout] Deleting all workouts.");
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteAllWorkouts';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = [];
                callback();
            } catch (exception) {}
        }
    };
    req.send(null);
}

////////////////////////////////////////////////////////////
//
// Client startup functions
//

// Set the Date input to the current DATETIEM (sql)
document.getElementById('date').value = new Date(Date.now()).toISOString();

getWorkouts(updateWorkouts);