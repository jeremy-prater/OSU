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

    UpdateBoatByID(id, data) {
        var boat = undefined;
        if (id in this.boats) {
            if ('name' in data) {
                this.boats[id].name = data.name;
            }
            if ('type' in data) {
                this.boats[id].type = data.type;
            }
            if ('length' in data) {
                this.boats[id].length = data.length;
            }
            return true;
        }
        return false;
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
                    "current_boat": null,
                    "arrival_date": "",
                    "departure_history": []
                };
            return this.slips[guid];
        } else {
            return undefined;
        }
    }

    UpdateSlipByID(id, data) {
        var boat = undefined;
        if (id in this.slips) {
            if ('number' in data) {
                this.slips[id].number = data.number;
            }
            return true;
        }
        return false;
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


    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Slip Logic
    //

    DockBoat(boatid, slipid) {
        if (!(boatid in this.boats)) {
            console.log (`[DockBoat] Unknown boat [${boatid}]`);
            return false;
        }
        if (!(slipid in this.slips)) {
            console.log (`[DockBoat] Unknown slip [${slipid}]`);
            return false;
        }

        // Ok, boatid and slip exists in the data set...

        // Check if slip is empty
        if (this.slips[slipid].current_boat != null)
        {
            console.log (`[DockBoat] Slip [${slipid}] not empty [${this.slips[slipid].current_boat}]`);
            return false;
        }
        
        // Check boats at sea.
        if (this.boats[boatid].at_sea == false)
        {
            console.log (`[DockBoat] Boat [${boatid}] is not at sea`);
            return false;
        }

        console.log (`Setting boat ${boatid} to slip ${slipid}`);
        this.slips[slipid].current_boat = this.boats[boatid].id;
        return true;
    }

    UndockBoat(slipid) {
        if (!(slipid in this.slips)) {
            console.log (`[UnDockBoat] Unknown slip [${slipid}]`);
            return false;
        }

        // Ok, slipid in the data set...
        // Check boats at port.
        if (this.slips[slipid].current_boat != null)
        {
            console.log (`[UnDockBoat] Boat [${slipid}] is now at sea`);
            // TODO: boat logic
            currentBoat = this.boats[this.slips[slipid].current_boat]
            // Tuger-knots
            currentBoat['at_sea'] = true;

            this.slips[slipid].current_boat = null;
            return true;
        }

        console.log (`Setting boat ${slipid} to sea (null) from slip ${slipid}`);
        this.slips[slipid].current_boat = null;
        return true;
    }
}