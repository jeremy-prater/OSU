const APIKEY = '0XRgmcoq1HTEKEbDPx4ZXLtAPYpKVUfWHsdJ5ZNC';

function showNasa() {
    console.log('showNasa');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "block";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "none";
}

function showRaphael() {
    console.log('showRaphael');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "block";
    document.getElementById('exampleContent').style.display = "none";
}

function showExample() {
    console.log('showExample');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "block";
}

function showWelcome() {
    document.getElementById('welcomeContent').style.display = "block";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "none";

}

function getNeoWSData(start, end, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = 'https://api.nasa.gov/neo/rest/v1/feed?start_date=' + start + '&end_date=' + end + '&api_key=' + APIKEY;
    console.log('Getting NeoWs:' + targetUrl);
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status >= 200 && req.status < 400) {
            console.log(req.responseText);
            callback(req.responseText);
        } else {
            console.log("Error in network request: " + req.statusText);
        }
    };
    req.send(null);
}

showWelcome();