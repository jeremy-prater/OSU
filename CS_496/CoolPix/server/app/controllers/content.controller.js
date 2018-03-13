var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.content = function (req, res) {
    if (req.method === 'POST') {
        var newUser = dataStore.AddImage(req.body.email, req.body.name);
        if (newUser == undefined) {
            res.sendStatus(500);
        } else {
            console.log(`[HTTP] User Added content ${JSON.stringify(newUser)}`);
            res.send(newUser);
        }  
    }
    /*if ("user" in req.params) {
        var boat = dataStore.GetBoatInSlipByID(req.params.slipid);
        if (boat !== undefined) {
            res.send(boat);
        } else {
            res.sendStatus(404);
        }
    }*/
};