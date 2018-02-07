var pug = require('pug');
var oauth2 = require('../../oauth2/state');

exports.oauth2 = function(req, res) {
    var options = {};
    var locals = {};

    if (req.method === 'GET') {
        if (req.query.state != oauth2.superSecret)
        {
            console.log(`State mismatch! [${req.query.state}] != [${oauth2.superSecret}]`);
            return;
        } else {
            console.log(`State matches! [${req.query.state}]`);
        }
        var code = req.query.code;
        var requestString = `https://www.googleapis.com/oauth2/v4/token?code=${code}&client_id=${clientID}&client_secret=${superSecret}&redirect_uri=${hostname}/oauth2&grant_type=authorization_code`;
        var newRequest = new XMLHttpRequest();
        newRequest.open("POST", requestString, false );
        newRequest.send(null);
    } else if (req.method === 'POST') {
        console.log(req);
    }
}