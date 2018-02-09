var pug = require('pug');
var oauth2 = require('../../client/state');
var userInfo = require('../common/getUserInfo');
var https = require("https");

var OAuth2 = new oauth2();

exports.oauth2 = function(req, res) {
    var options = {};
    var locals = {};

    if (req.method === 'GET') {
        if (req.query.state != OAuth2.superSecret)
        {
            console.log(`State mismatch! [${req.query.state}] != [${OAuth2.superSecret}]`);
            return;
        } else {
            console.log(`State matches! [${req.query.state}]`);
        }
        var code = req.query.code;
        console.log (`OAuth 2 Code [${code}]`);
        var requestString = `/oauth2/v4/token?code=${code}&client_id=${OAuth2.clientID}&client_secret=${OAuth2.clientSecret}&redirect_uri=${OAuth2.hostname}/oauth2&grant_type=authorization_code`;
        console.log (`OAuth request path [${requestString}]`);
        var request = https.request({
            host: 'www.googleapis.com',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded'
            },
            method: 'POST',
            path: requestString
        }, function (response) {
            console.log(`STATUS: ${response.statusCode}`);
            console.log(`HEADERS: ${JSON.stringify(response.headers)}`);
            response.setEncoding('utf8');
            var data = "";
            response.on('data', (chunk) => {
              data += chunk;
            });
            response.on('end', () => {
                var tokenObject = JSON.parse(data);
                console.log (`Token Object [${JSON.stringify(tokenObject)}]`);
                var currentUserInfo = new userInfo();
                currentUserInfo.Connect(tokenObject, function(userData) {
                    console.log ("Rendering signin...");

                    //////////////////
                    // Super test!
                    //userData =JSON.parse('{"kind":"plus#person","etag":"_Ek1oAZn65JmcnNnmHdEAQCMkKA/VbM_lLCb2EYnVV2lCbFVq46IQKA","gender":"male","emails":[{"value":"silverevo03@gmail.com","type":"account"}],"urls":[{"value":"http://www.youtube.com/user/DirtMcGurtskie","type":"otherProfile","label":"Jeremy Prater"}],"objectType":"person","id":"116626949997452353203","displayName":"Jeremy Prater","name":{"familyName":"Prater","givenName":"Jeremy"},"tagline":"Aloha!","url":"https://plus.google.com/116626949997452353203","image":{"url":"https://lh6.googleusercontent.com/-GCdPoQeYXho/AAAAAAAAAAI/AAAAAAAAAiw/6fGb361gx9Q/photo.jpg?sz=50","isDefault":false},"organizations":[{"name":"Georgia State University","title":"Computer Science","type":"school","startDate":"2001","endDate":"2002","primary":false},{"name":"United States Navy","title":"Electrician","type":"work","startDate":"2004","primary":true}],"placesLived":[{"value":"96706","primary":true}],"isPlusUser":true,"circledByCount":35,"verified":false}');
                    console.log (`Token Object [${JSON.stringify(userData)}]`);

                    var html = pug.renderFile('./app/views/oauth2.pug', userData);
                    res.send(html);
                });
            });
        });
          
        request.on('error', (e) => {
            console.error(`problem with request: ${e.message}`);
        });
        request.end();
    }
}