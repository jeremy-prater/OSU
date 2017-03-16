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

    // Sort the data by requested type
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

    var parentElement = document.getElementById('workoutData');

    // Remove all child nodes
    while (parentElement.hasChildNodes())
    {
        parentElement.removeChild(parentElement.lastChild);
    }

    // Add new data elements to the DOM
    for (var workoutIndex = 0; workoutIndex < localDataSet.length; workoutIndex++)
    {
        var currentWorkout = localDataSet[workoutIndex];

        var newDiv = document.createElement("div");
        newDiv.className = "workout-content";

        var nameDiv = document.createElement("div");
        nameDiv.id = currentWorkout.name + "-name";
        nameDiv.className = "workout-content-text"
        var nameSpan = document.createElement("span");
        nameSpan.className = "workout-content-span";
        nameSpan.innerText = currentWorkout.name;
        nameDiv.appendChild(nameSpan);

        var dateDiv = document.createElement("div");
        dateDiv.id = currentWorkout.name + "-date";
        dateDiv.className = "workout-content-text"
        var dateSpan = document.createElement("span");
        dateSpan.className = "workout-content-span";
        dateSpan.innerText = new Date(currentWorkout.date).toLocaleString();
        dateDiv.appendChild(dateSpan);

        var repsDiv = document.createElement("div");
        repsDiv.id = currentWorkout.name + "-reps";
        repsDiv.className = "workout-content-text"
        var repsSpan = document.createElement("span");
        repsSpan.className = "workout-content-span";
        repsSpan.innerText = currentWorkout.reps;
        repsDiv.appendChild(repsSpan);

        var weightTypeDiv = document.createElement("div");
        weightTypeDiv.id = currentWorkout.name + "-weightType";
        weightTypeDiv.className = "workout-content-text"
        var lbs = 0;
        var kg = 0;
        if (currentWorkout.lbs === 1)
        {
            lbs = currentWorkout.weight;
            kg = currentWorkout.weight * 0.453592;
        }
        else
        {
            kg = currentWorkout.weight;
            lbs = currentWorkout.weight * 2.20462;
        }
        var weightSpan = document.createElement("span");
        weightSpan.className = "workout-content-span";
        weightSpan.innerHTML = lbs.toFixed(0) + " lbs<br>" + kg.toFixed(0) + " kg";
        weightTypeDiv.appendChild(weightSpan);

        var clearStyleDiv = document.createElement("div");
        clearStyleDiv.id = currentWorkout.name + "-reset";
        clearStyleDiv.className = "workout-content-reset"

        var deleteWorkout = document.createElement("div");
        deleteWorkout.id = currentWorkout.name + "-delete";
        deleteWorkout.className = "workout-content-delete";
        var deleteSpan = document.createElement("span");
        deleteSpan.className = "workout-content-span";
        deleteSpan.innerText = "Delete Workout";
        deleteWorkout.appendChild(deleteSpan);
        deleteWorkout.onclick = GenerateDeleteFunction(currentWorkout.workoutID);

        newDiv.appendChild(dateDiv);
        newDiv.appendChild(nameDiv);
        newDiv.appendChild(weightTypeDiv);
        newDiv.appendChild(repsDiv);
        newDiv.appendChild(clearStyleDiv);
        newDiv.appendChild(deleteWorkout);

        parentElement.appendChild(newDiv);
    }
}

////////////////////////////////////////////////////////////
//
// UI database generator functions
//

function GenerateDeleteFunction(workoutID)
{
    return function()
    {
        deleteWorkout(workoutID, function() {
            getWorkouts(updateWorkouts);
        })
    }
}

function postAddWorkout()
{
    getWorkouts(updateWorkouts);
    updateClientTime();
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
                localDataSet = JSON.parse(req.responseText);
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

function updateClientTime()
{
    document.getElementById('date').value = new Date(Date.now()).toISOString();
}

////////////////////////////////////////////////////////////
//
// Client startup functions
//

// Set the Date input to the current DATETIEM (sql)
updateClientTime();

getWorkouts(updateWorkouts);