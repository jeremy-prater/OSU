

function UserInfo() {

    this.userInfoURL = "www.googleapis.com/plus/v1/people/me"

    this.Connect = function(tokenObject) {
        http.open("GET", this.userInfoURL);
        http.onreadystatechange = function() {//Call a function when the state changes.
            if(http.readyState == 4 && http.status == 200) {
                console.log(http.responseText);
                // Update DOM elements!
            } else {
                console.log(`Google API request failed [${http.status}] [${http.responseText}]`);
            }
        }
        http.send(null);
    }

    return this;
};

var currentUser = UserInfo();
