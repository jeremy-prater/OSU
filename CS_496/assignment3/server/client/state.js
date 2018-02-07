var superSecret = "olafsdoughnutwasnasty";

module.exports = function() {
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
    this.superSecret = "olafsdoughnutwasnasty";

    // Well all the clients are the same... That is bad!!
    this.clientID = "75813711380-gq1nf7ig8s13rsvat8r25tf0h35iea5b.apps.googleusercontent.com";

    this.hostname = "http://olafs-doughnut.appspot.com";

    console.log ("Init client side");

    this.StartOAuth = function(state) {
        console.log("Requesting OAuth");
        window.location = `https://accounts.google.com/o/oauth2/v2/auth?response_type=code&client_id=${this.clientID}&redirect_uri=${this.hostname}/oauth2&scope=email&state=${state}`;
    }
};