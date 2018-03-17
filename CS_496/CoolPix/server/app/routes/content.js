module.exports = function(app) {
    var index = require('../controllers/content.controller');

    // Post a new picture
    app.get('/content/:imagefile', index.content);
    app.post('/content', index.content);
};