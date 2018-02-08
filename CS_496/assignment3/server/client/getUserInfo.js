

function UserInfo() {

    this.userInfoURL = "www.googleapis.com/plus/v1/people/me"

    this.Connect = function(tokenObject) {
        var req = new XMLHttpRequest();
        req.open('GET', userInfoURL, true);
        req.setRequestHeader("Authorization", `${tokenObject.token_type} ${tokenObject.access_token}`);
        req.onreadystatechange = function () {
            if (req.status == 200 && req.readyState === 4) {
                console.log(http.responseText);
                // Update DOM elements!
            } else {
                console.log(`Google API request failed [${http.status}] [${http.responseText}]`);
            }
        };
        req.send(null);
    }

    return this;
};

var currentUser = UserInfo();
