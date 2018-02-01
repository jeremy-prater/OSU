var Guid = require('Guid');

module.exports = class {
    constructor() {
        console.log('[DataStore] Created Boats/Slips Datastore');
        this.boats = {};
    }

    CreateBoat(data) {
        // Check data
        var guid = Guid.create();
        if (("name" in data) &&
            ("type" in data) &&
            ("length" in data) &&
            (!(guid in this.boats))) {
                this.boats[guid] = {
                    "id": guid,
                    "name": data["name"],
                    "type": data["type"],
                    "length": data["length"],
                    "at_sea": true
                };
            return this.boats[guid];
        } else {
            return undefined;
        }
    }

    GetAllBoats() {
        var boats = [];
        Object.keys(this.boats).forEach(function(key) {
            boats.push(this.boats[key]);
        }.bind(this));
        return boats;
    }

    GetBoatByID(id) {
        var boat = undefined;
        if (id in this.boats) {
            boat = this.boats[id];
        }
        return boat;
    }
 }