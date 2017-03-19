var SpaceView = function (domElement, controller) {
    console.log('[SPACE VIEW] Initalizing graphics.')

    var context = this;

    this.parentDOMObject = domElement;
    this.viewportWidth = this.parentDOMObject.offsetWidth;
    this.viewportHeight = this.parentDOMObject.offsetHeight;
    this.viewportSize = this.viewportHeight + this.viewportWidth;
    this.graphics = Raphael(this.parentDOMObject, this.viewportWidth, this.viewportHeight);


    this.GenerateLocationClick = function (currentLocation) {
        return function () {
            context.currentLocation = currentLocation;
            console.log("[SPACE VIEW] Selected location : " + currentLocation.name);
            controller.getItemsByLocation(currentLocation, context.updateSideBarItems);
        }
    };

    this.updateSideBarItems = function (currentLocation, dataSet) {
        console.log("[SPACE VIEW] Updating location ui : " + currentLocation.name);
        var summedData = {};
        for (var dataIndex = 0; dataIndex < dataSet.length; dataIndex++) {
            var currentData = dataSet[dataIndex];
            if (summedData[currentData.itemName] === undefined) {
                summedData[currentData.itemName] = {};
                summedData[currentData.itemName].totalAmmount = 0;
                summedData[currentData.itemName].packages = 0;
                summedData[currentData.itemName].name = currentData.itemName;
            }
            summedData[currentData.itemName].totalAmmount += currentData.qty;
            summedData[currentData.itemName].packages++;
        }
        console.log(summedData);
        document.getElementById('locationName').innerText = currentLocation.name;
        var locItems = document.getElementById('locationItems');
        locItems.innerHTML = "";
        var keys = Object.keys(summedData);
        if (keys.length === 0) {
            locItems.innerHTML = "<br>No items are at this location.<br><br>";
        } else {
            for (var summedIndex = 0; summedIndex < keys.length; summedIndex++) {
                var currentData = summedData[keys[summedIndex]];
                locItems.innerHTML += currentData.name + " : " + currentData.totalAmmount.toPrecision(5) + "<br>";
            }
        }
    }

    this.CreateLocations = function (locationData) {
        for (var locationIndex = 0; locationIndex < locationData.length; locationIndex++) {
            var currentLocation = locationData[locationIndex];
            console.log("[SPACE VIEW] Creating location : " + currentLocation.name);
            console.log("[SPACE VIEW] x: " + currentLocation.xLocation + " y: " + currentLocation.yLocation);
            var newObject = this.graphics.circle(currentLocation.xLocation * this.viewportWidth, currentLocation.yLocation * this.viewportHeight, this.viewportSize * 0.007);
            switch (currentLocation.locationStyle) {
                case 1:
                    {
                        newObject.attr("fill", "#fff");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation));
                    }
                    break;
                case 2:
                    {
                        newObject.attr("fill", "#34e");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation));
                    }
                    break;
                case 3:
                    {
                        newObject.attr("fill", "#4fa");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation));
                    }
                    break;
                case 4:
                    {
                        newObject.attr("fill", "#27e");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation));
                    }
                    break;
            }

            // Go ahead and select the first location...
            if (locationIndex === 0) {
                context.currentLocation = currentLocation;
                console.log("[SPACE VIEW] Selected location : " + currentLocation.name);
                controller.getItemsByLocation(currentLocation, context.updateSideBarItems);
            }
        }
    }
};