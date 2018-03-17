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

    CreateAccount(id, name) {
        console.log(this.users);

        if (id in this.users) {
            console.log(`[DataStore] User already exists [${id}]`);
            console.log(this.users[id]);
            return this.users[id];
        }

        var newUser = {
            'id': id,
            'name': name,
            'creationTime': Date.now(),
            'posts': [
                {
                    imageData: "#imagethis",
                    lastEdit: 0,
                    caption: "caption 1",
                    body: "body 1",
                    liked: false,
                    comments: [
                        "this is dumb",
                        "no it's not!"
                    ]
                },
                {
                    imageData: "#imagethis2",    // Base64 image
                    lastEdit: 1521266624 * 1000, // uint32 time
                    caption: "caption 2",        // caption string
                    body: "body 2",              // body string
                    liked: true,                 // liked
                    comments: [                  // comments and stuff
                        "this is awesome",
                        "sure is!"
                    ]
                }
            ]
        };

        console.log(`[DataStore] Creating user [${id}][${name}]`);
        this.users[id] = newUser;
        console.log(this.users);
        return newUser;
    }

    GetAccount(id) {
        console.log(`[DataStore] Getting user [${id}]`);
        console.log(this.users);

        if (id in this.users) {
            return this.users[id];
        }
        console.log(`[DataStore] Getting user [${id}] not found`);

        return undefined;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Creation
    //

    AddImage(id, imageData, title, body) {
        var imageID = Guid.create();
        var currentTime = Date.now();
        console.log(`[DataStore] User [${id}] adding image [${imageID}] [${title}] [${body}] @ [${currentTime}]`);
        this.users[id].Posts[imageID] = {
            imageID: imageID,
            user: id,
            postTime: currentTime,
            imageData: imageData,
            title: title,
            body: body
        };
        return imageID;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Edit
    //

    EditImage(id, imageID, imageAttribute, value) {
        console.log(`[DataStore] User [${id}] edited image [${imageID}] [${imageAttribute}]->[${value}]`);
        this.users[id].Posts[imageID][imageAttribute] = value;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Getting
    //

    GetImage(id, imageID) {
        console.log(`[DataStore] User [${id}] getting image [${imageID}]`);
        return this.users[id].Posts[imageID];
    }

    GetAllImages(id) {
        console.log(`[DataStore] User [${id}] get all images`);
        return this.users[id].Posts;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Delete
    //

    DeleteImage(id, imageID) {
        console.log(`[DataStore] User [${id}] delete image [${imageID}]`);
        delete this.users[id].Posts[imageID];
    }

}