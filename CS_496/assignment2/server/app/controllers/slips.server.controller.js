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
        //this.httpMethod = "Slip GET Request Received";
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
    else if (req.method === 'POST')
    {
        //this.httpMethod = "Slip POST Request Received";

        //console.log('[Parser] Post Data: ' + JSON.stringify(req.body))

        var newSlip = dataStore.CreateSlip(req.body);
        if (newSlip == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Slip ${JSON.stringify(newSlip)}`);
            res.send(newSlip);
        }
    }
};
