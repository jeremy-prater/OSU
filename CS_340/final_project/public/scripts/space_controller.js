////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

////////////////////////////////////////////////////////////
//
// Initalize any DOM objects data
//


////////////////////////////////////////////////////////////
//
// Click handler functions
//


////////////////////////////////////////////////////////////
//
// Client DOM update functions
//

////////////////////////////////////////////////////////////
//
// UI database generator functions
//

////////////////////////////////////////////////////////////
//
// Database access functions
//

function getDBItem(targetUrl, callback) {
    var req = new XMLHttpRequest();
    console.log("[SPACE] Getting Item List");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = JSON.parse(req.responseText);
                console.log(req.responseText);
                callback();
            } catch (exception) {}
        }
    };
    req.send(null);
}

/*function addWorkout(callback) {
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
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function updateWorkout(payload, callback) {
    console.log("[Workout] Adding workout.");
    var req = new XMLHttpRequest();
    var targetUrl = '/updateWorkout';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
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
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}*/

////////////////////////////////////////////////////////////
//
// Client startup functions
//

// Set the Date input to the current DATETIEM (sql)
getDBItem('/getItems', function (items){
    this.spaceItems = items;
});
getDBItem('/getLocations',function (locations){
    this.spaceLocations = locations;
});

console.log(this.spaceItems);
console.log(this.spaceLocations);