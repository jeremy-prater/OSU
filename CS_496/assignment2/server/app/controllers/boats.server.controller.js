var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.render = function(req, res) {

    this.headers = [];

    var items = Object.keys(req.headers);
    //console.log('[Parser] Headers: ' + JSON.stringify(req.headers));
    for (var itemIndex=0; itemIndex < items.length; itemIndex++) {
        var currentItem = req.headers[items[itemIndex]];
        this.headers.push({
            name: items[itemIndex],
            value: currentItem
        });
    }

    if (req.method === 'GET')
    {
        //this.httpMethod = "Boat GET Request Received";
        if ("boatid" in req.params) {
            var boat = dataStore.GetBoatByID(req.params.boatid);
            if (boat !== undefined) {
                res.send(boat);
            } else {
                res.sendStatus(404);
            }
        } else {
            res.send(dataStore.GetAllBoats());
        }
    }
    else if (req.method === 'POST')
    {
        //this.httpMethod = "Boat POST Request Received";

        //console.log('[Parser] Post Data: ' + JSON.stringify(req.body))

        var newBoat = dataStore.CreateBoat(req.body);
        if (newBoat == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Boat ${JSON.stringify(newBoat)}`);
            res.send(newBoat);
        }
    }
};
