var pug = require('pug');
var oauth2 = require('../../client/state');
var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

var OAuth2 = new oauth2();

exports.oauth2 = function(req, res) {
    var options = {};
    var locals = {};

    console.log("Did something");
    console.log(OAuth2);
    if (req.method === 'GET') {
        if (req.query.state != OAuth2.superSecret)
        {
            console.log(`State mismatch! [${req.query.state}] != [${OAuth2.superSecret}]`);
            return;
        } else {
            console.log(`State matches! [${req.query.state}]`);
        }
        var code = req.query.code;
        var requestString = `https://www.googleapis.com/oauth2/v4/token?code=${code}&client_id=${OAuth2.clientID}&client_secret=${OAuth2.superSecret}&redirect_uri=${OAuth2.hostname}/oauth2&grant_type=authorization_code`;
        var newRequest = new XMLHttpRequest();
        newRequest.open("POST", requestString, false );
        newRequest.send(null);
    } else if (req.method === 'POST') {
        console.log(req);
    }
}