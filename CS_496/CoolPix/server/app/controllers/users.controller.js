var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.users = function (req, res) {
    if (req.method === 'POST') {
        var newUser = dataStore.CreateAccount(req.body.id, req.body.email, req.body.name);
        if (newUser == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`[HTTP] Created User ${JSON.stringify(newUser)}`);
            res.send(newUser);
        }
    } else if (req.method === "GET") {
        if ('userID' in req.params) {
            var userID = req.params.userID;
            console.log(`[HTTP] Getting User [${userID}]`);

            res.send(dataStore.GetAccount(userID));
        } else {
            res.sendStatus(502);
        }
    }
};