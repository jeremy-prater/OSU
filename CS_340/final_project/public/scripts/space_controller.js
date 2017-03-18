////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

////////////////////////////////////////////////////////////
//
// Initalize any DOM objects data
//

var context = this;

this.setupGraphics = function () {
    this.spaceView = new SpaceView(document.getElementById("spaceView"));
}

////////////////////////////////////////////////////////////
//
// Global timer
//

this.timerRunning = true;
this.timerDelta = 1;

function timerClick() {
    if (context.timerRunning) {
        context.timerRunning = false;
        context.timerDelta = 0;
    } else {
        context.timerRunning = true;
        context.timerDelta = 1;
    }

}
this.startTimer = function () {
    var resetValue = 1000;
    var currentTime = resetValue;
    setInterval(function () {
        currentTime -= context.timerDelta;
        if (currentTime === 0) {
            currentTime = resetValue;
        }
        var curTimeString = currentTime;
        document.getElementById("timerControl").innerText = curTimeString;
    }, 25);
}


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
    console.log("[SPACE] Getting DB object : " + targetUrl);
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(JSON.parse(req.responseText));
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

this.Init = function () {
    this.setupGraphics();

    // Get static SQL data
    getDBItem('/getItems', function (items) {
        context.spaceItems = items;

        getDBItem('/getLocations', function (locations) {
            context.spaceLocations = locations;
            context.spaceView.CreateLocations(context.spaceLocations);
        });
    });
}

this.Init();
this.startTimer();