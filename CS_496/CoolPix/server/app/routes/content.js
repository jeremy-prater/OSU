module.exports = function(app) {
    var index = require('../controllers/content.controller');

    // Post a new picture
    app.post('/content', index.content);
    app.delete('/content/:userid/:imageid', index.content);
    app.patch('/content', index.content);
};