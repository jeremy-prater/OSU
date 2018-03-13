var Guid = require('guid');

let instance = null;

module.exports = class {

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialization functions
    //

    constructor() {
        if (!instance) {
            instance = this;
            console.log('[DataStore] Created CoolPix');
            this.ResetUsers();
        }
        return instance;
    }

    ResetUsers() {
        this.users = {};
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Account Creation
    //

    CreateAccount (email, name) {
        console.log (`[DataStore] Creating user [${email}]`);
        this.users[email] = {
            'Name': name,
            'Posts': {}
        };
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Creation
    //

    AddImage (email, imageData, title, body) {
        var imageID = Guid.create();
        var currentTime = Date.now();
        console.log (`[DataStore] User [${email}] adding image [${imageID}] [${title}] [${body}] @ [${currentTime}]`);
        this.users[email].Posts[imageID] = {
            imageID: imageID,
            user: email,
            postTime: currentTime,
            imageData: imageData,
            title: title,
            body: body
        };
        return imageID;
    }

    EditImage (email, imageID, imageAttribute, value) {
        console.log (`[DataStore] User [${email}] edited image [${imageID}] [${imageAttribute}]->[${value}]`);
        this.users[email].Posts[imageID][imageAttribute] = value;
    }

    GetImage (email, imageID) {
        console.log (`[DataStore] User [${email}] getting image [${imageID}]`);
        return this.users[email].Posts[imageID];
    }

    GetAllImages (email) {
        console.log (`[DataStore] User [${email}] get all images`);
        return this.users[email].Posts;
    }

    DeleteImage(email, imageID) {
        console.log (`[DataStore] User [${email}] delete image [${imageID}]`);
        delete this.users[email].Posts[imageID];
    }

}