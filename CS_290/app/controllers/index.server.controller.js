const pug = require('pug');

exports.render = function(req, res) {

    //console.log(req.headers);

    this.stuff = [];

    var items = Object.keys(req.headers);
    for (var itemIndex=0; itemIndex < items.length; itemIndex++) {
        var currentItem = req.headers[items[itemIndex]];
        stuff.push({
            name: items[itemIndex],
            value: currentItem
        });
    }

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
        httpMethod: this.httpMethod,
        stuff: this.stuff
    })
};
