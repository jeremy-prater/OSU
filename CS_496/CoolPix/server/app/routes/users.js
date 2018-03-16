module.exports = function(app) {
    var index = require('../controllers/users.controller');
     
    // Create a user
    app.post('/users', index.users);
    app.get('/users/:userID', index.users);
};