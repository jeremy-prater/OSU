var DataStore = require('../datastore/datastore');
var fs = require('fs');

var dataStore = new DataStore();

exports.content = function (req, res) {
    if (req.method === 'POST') {
        /////////////////////////////////////////
        //
        // Add new image to database
        //
        var newImage = dataStore.AddImage(req.body.id, req.body.imageData, req.body.title, req.body.body);
        if (newImage == undefined) {
            res.sendStatus(500);
        } else {
            console.log(`[HTTP] User Added content ${JSON.stringify(newImage)}`);
            res.send(newImage);
        }
    } else if (req.method === 'GET') {
        /////////////////////////////////////////
        //
        // Get Image from DB
        //
        console.log(req.params);
        console.log(`[HTTP] Getting Image [${req.params.imagefile}]`);
        fs.readFile(`./content/${req.params.imagefile}`, (err, data) => {
            if (err) {
                console.log(`[HTTP] Error feteching file [${req.parms.imagefile}] [${err}]`);
                res.sendStatus(500);
            }
            res.send(data);
        });
    } else if (req.method === 'DELETE') {
        /////////////////////////////////////////
        //
        // Delete Image from DB
        //
        console.log(`[HTTP] Deleting Image [${req.params.userid}] [${req.params.imageid}]`);
        var result = dataStore.DeleteImage(req.params.userid, req.params.imageid);
        if (result) {
            res.sendStatus(200);
        } else {
            res.sendStatus(502);
        }
    }
};