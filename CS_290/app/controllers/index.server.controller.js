const pug = require('pug');

exports.render = function(req, res) {

    //console.log(req);

    if (req.method === 'GET')
    {
        this.httpMethod = "GET Request Received";
    }
    else
    {
        this.httpMethod = "POST Request Received";
    }

    res.render('index', {
        title: 'CS_290: Assignment 2 - HTML/CSS',
        message: 'Pug is awesome!',
        httpMethod: this.httpMethod
    })
};
