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
    this.spaceView = new SpaceView(document.getElementById("spaceView"), context);
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
    context.timerRunning = true;
    context.timerDelta = 1;
    this.currentTime = 0;
}
this.startTimer = function () {
    var resetValue = 999;
    this.currentTime = resetValue;
    setInterval(function () {
        this.currentTime -= context.timerDelta;
        if (this.currentTime < 1) {
            this.currentTime = resetValue;
            this.updateDatabaseContent();
        }
        var curTimeString = this.currentTime;
        document.getElementById("timerControl").innerText = curTimeString;
    }, 25);
}


////////////////////////////////////////////////////////////
//
// Database logic functions
//

this.updateDatabaseContent = function () {
    for (var productionIndex = 0; productionIndex < this.spaceProduction.length; productionIndex++) {
        var currentProduction = this.spaceProduction[productionIndex];
        addItemToLocation({
            itemID: currentProduction.f_itemID,
            locationID: currentProduction.f_locationID,
            qty: (Math.random() * (currentProduction.max - currentProduction.min)) + currentProduction.min,
        }, undefined);
    }

    getItemsByLocation(this.spaceView.currentLocation, this.spaceView.updateSideBarItems);
}

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

function addItemToLocation(payload, callback) {
    console.log("[SPACE ITEM] Adding " + payload.itemID + " at location " + payload.locationID + " [Qty: " + payload.qty + "]");
    var req = new XMLHttpRequest();
    var targetUrl = '/createItem';
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

function getItemsByLocation(currentLocation, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getItemsAtLocation?locationID=' + currentLocation.locationID;
    console.log("[SPACE ITEM] Getting items at [" + currentLocation.locationID + "]");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(currentLocation, JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

function getLocationDestinations(currentLocation, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getLocationDestinations?locationID=' + currentLocation.locationID;
    console.log("[SPACE ITEM] Getting destinations for [" + currentLocation.locationID + "]");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(currentLocation, JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

/*function updateWorkout(payload, callback) {
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

            getDBItem('/getProduction', function (production) {
                context.spaceProduction = production;
            });
        });
    });
}

this.Init();
this.startTimer();