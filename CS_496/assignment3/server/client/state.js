///////////////////////////////////
//
// This runs in the browser...

// The client_secret is a secret known only to the application and the authorization server.
// It must be sufficiently random to not be guessable, which means you should avoid
// using common UUID libraries which often take into account the timestamp or MAC address
// of the server generating it. A great way to generate a secure secret is to use a
// cryptographically-secure library to generate a 256-bit value and converting it to a
// hexadecimal representation.
// https://www.oauth.com/oauth2-servers/client-registration/client-id-secret/
var superSecret = "olafsdoughnutwasnasty";

// Well all the clients are the same... That is bad!!
var clientID = "83fd29ee96888b83bacdf5a5";

var hostname = "http://127.0.0.1"

console.log ("Init client side");

function StartOAuth(client_id, state) {
    console.log("Requesting OAuth");
    window.location = `https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=${client_id}&redirect_uri=${hostname}/oauth2&scope=email&state=${state}`;
}