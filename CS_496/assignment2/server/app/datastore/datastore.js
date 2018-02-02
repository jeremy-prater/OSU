var Guid = require('guid');

let instance = null;

module.exports = class {
    constructor() {
        if (!instance) {
            instance = this;
            console.log('[DataStore] Created Boats/Slips Datastore');
            this.boats = {};
            this.slips = {};
        }
        return instance;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Boat Logic
    //

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

    DeleteBoatByID(id) {
        if (id in this.boats) {
            delete this.boats[id];

            // Check all slips for deleted boat.
            return true;
        }
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Slip Logic
    //


    CreateSlip(data) {
        // Check data
        var guid = Guid.create();
        if (("number" in data) &&
            (!(guid in this.slips))) {
                this.slips[guid] = {
                    "id": guid,
                    "number": data["number"],
                    "current_boat": "",
                    "arrival_date": "",
                    "departure_history": []
                };
            return this.slips[guid];
        } else {
            return undefined;
        }
    }

    GetAllSlips() {
        var slips = [];
        Object.keys(this.slips).forEach(function(key) {
            slips.push(this.slips[key]);
        }.bind(this));
        return slips;
    }

    GetSlipByID(id) {
        var slip = undefined;
        if (id in this.slips) {
            slip = this.slips[id];
        }
        return slip;
    }

    DeleteSlipByID(id) {
        if (id in this.slips) {
            delete this.slips[id];

            // Check all slips for deleted boat.
            return true;
        }
        return false;
    }

}