////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

var sortType = 0;
var lastSortType = 0;

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
    updateWorkouts();
}

function sortWeight() {
    sortType = 1;
    updateWorkouts();
}

function sortReps() {
    sortType = 2;
    updateWorkouts();
}

function clearAll() {
    // Delete local client data...
    updateWorkouts();
}

////////////////////////////////////////////////////////////
//
// Client DOM update functions
//

function updateWorkouts() {
    if (lastSortType == sortType) {
        return;
    } else {
        lastSortType = sortType;
    }

    console.log("[UPDATE] Workout Sort : " + sortType);

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
}

////////////////////////////////////////////////////////////
//
// Database access functions
//

function addWorkout() {
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
        if (req.status >= 200 && req.status < 400) {}
    };
    req.send(JSON.stringify(payload));
}

////////////////////////////////////////////////////////////
//
// Client startup functions
//

// Set the Date input to the current DATETIEM (sql)
document.getElementById('date').value = new Date(Date.now()).toISOString();

updateWorkouts();