var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.render = function(req, res) {

    this.stuff = [];

    var items = Object.keys(req.headers);
    console.log('[Parser] Headers: ' + JSON.stringify(req.headers));
    for (var itemIndex=0; itemIndex < items.length; itemIndex++) {
        var currentItem = req.headers[items[itemIndex]];
        this.stuff.push({
            name: items[itemIndex],
            value: currentItem
        });
    }

    this.boatResponse = {};

    if (req.method === 'GET')
    {
        //this.httpMethod = "Boat GET Request Received";
        if ("boat_id" in req.params) {
            dataStore.GetBoatByID(req.params.boat_id);
            res.send(this.boatResponse);
        } else {
            res.send(dataStore.GetAllBoats());
        }
    }
    else if (req.method === 'POST')
    {
        //this.httpMethod = "Boat POST Request Received";

        //console.log('[Parser] Post Data: ' + JSON.stringify(req.body))
        console.log(JSON.stringify(req.body));

        var newBoat = dataStore.CreateBoat(req.body);
        if (newBoat == undefined) {
            res.sendStatus(409);
        } else {
            res.send(newBoat);
        }
    }
};
