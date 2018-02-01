var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.boat = function(req, res) {
    if (req.method === 'GET')
    {
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
        var newBoat = dataStore.CreateBoat(req.body);
        if (newBoat == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Boat ${JSON.stringify(newBoat)}`);
            res.send(newBoat);
        }
    }
};
