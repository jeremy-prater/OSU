module.exports = function(app) {
    var database = require('../controllers/database.server.controller');
    app.get('/getItems', database.getItems);
    app.get('/getLocations', database.getLocations);
    app.get('/getProduction', database.getProductions);
    app.get('/getItemsAtLocation', database.getItemsByLocation);
    app.post('/createItem', database.createItem);
};