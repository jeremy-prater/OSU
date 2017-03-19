var SpaceView = function(domElement) {
    console.log('[SPACE VIEW] Initalizing graphics.')
    this.parentDOMObject = domElement;
    this.viewportWidth = this.parentDOMObject.offsetWidth;
    this.viewportHeight = this.parentDOMObject.offsetHeight;
    this.viewportSize = this.viewportHeight + this.viewportWidth;
    this.graphics = Raphael(this.parentDOMObject, this.viewportWidth, this.viewportHeight);


    this.CreateLocations = function(locationData) {
        for (var locationIndex = 0; locationIndex < locationData.length; locationIndex++){
            var currentLocation = locationData[locationIndex];
            console.log ("[SPACE VIEW] Creating location : " + currentLocation.name);
            console.log ("[SPACE VIEW] x: " + currentLocation.xLocation + " y: " + currentLocation.yLocation);
            var newObject = this.graphics.circle (currentLocation.xLocation * this.viewportWidth, currentLocation.yLocation * this.viewportHeight, this.viewportSize * 0.007);
            switch (currentLocation.locationStyle) {
                case 1:
                {
                    newObject.attr("fill", "#fff");
                    newObject.attr("title", currentLocation.name);
                }
                break;
                case 2:
                {
                    newObject.attr("fill", "#34e");
                    newObject.attr("title", currentLocation.name);
                }
                break;
                case 3:
                {
                    newObject.attr("fill", "#4fa");
                    newObject.attr("title", currentLocation.name);
                }
                break;
                case 4:
                {
                    newObject.attr("fill", "#27e");
                    newObject.attr("title", currentLocation.name);
                }
                break;
            }
        }
    }
};