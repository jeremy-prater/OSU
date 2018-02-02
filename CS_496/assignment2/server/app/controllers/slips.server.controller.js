var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.boatinslip = function (req, res) {
    if (req.method === 'GET') {
        if ("slipid" in req.params) {
            var slip = dataStore.GetSlipByID(req.params.slipid);
            if (slip !== undefined) {
                res.send(slip);
            } else {
                res.sendStatus(404);
            }
        } else {
            res.send(dataStore.GetAllSlips());
        }
    }
}

exports.slips = function (req, res) {
    if (req.method === 'GET') {
        if ("slipid" in req.params) {
            var slip = dataStore.GetSlipByID(req.params.slipid);
            if (slip !== undefined) {
                res.send(slip);
            } else {
                res.sendStatus(404);
            }
        } else {
            res.send(dataStore.GetAllSlips());
        }
    } else if (req.method === 'POST') {
        var newSlip = dataStore.CreateSlip(req.body);
        if (newSlip == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Slip ${JSON.stringify(newSlip)}`);
            res.send(newSlip);
        }
    }
    else if (req.method === 'DELETE')
    {
        if ("slipid" in req.params) {
            if (dataStore.DeleteSlipByID(req.params.slipid))
            {
                res.sendStatus(204);
            }
        }
        res.sendStatus(404);
    }

};