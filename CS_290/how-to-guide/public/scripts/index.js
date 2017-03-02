////////////////////////////////////////////////////////////
//
// Show/Hide functions
//

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

////////////////////////////////////////////////////////////
//
// NeoWs example
//

const APIKEY = '0XRgmcoq1HTEKEbDPx4ZXLtAPYpKVUfWHsdJ5ZNC';

function getNeoWSData(start, end, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = 'https://api.nasa.gov/neo/rest/v1/feed?start_date=' + start + '&end_date=' + end + '&api_key=' + APIKEY;
    console.log('Getting NeoWs:' + targetUrl);
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status >= 200 && req.status < 400) {
            callback(JSON.parse(req.responseText));
        } else {
            console.log("Error in network request: " + req.statusText);
        }
    };
    req.send(null);
}

function setExampleText(data) {
    var dataString = JSON.stringify(data);
    document.getElementById('example1_code').innerHTML = dataString.substring(0, 250) + '...';
    document.getElementById('example2_code').innerHTML += 'element_count: ' + data.element_count + '<br>';
    var dates = Object.keys(data.near_earth_objects);
    document.getElementById('example2_code').innerHTML += 'first date: ' + dates[0] + '<br>';
    var asteroid = data.near_earth_objects[dates[0]][0];
    console.log(asteroid);
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].name = ' + asteroid.name + '<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].is_potentially_hazardous_asteroid = ' + asteroid.is_potentially_hazardous_asteroid + '<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].estimated_diameter(avg) = ' + (asteroid.estimated_diameter.kilometers.estimated_diameter_min + asteroid.estimated_diameter.kilometers.estimated_diameter_max) / 2 + ' km<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].missed_earth_by = ' + asteroid.close_approach_data[0].miss_distance.kilometers + ' km<br>';
}

showWelcome();
getNeoWSData('2017-02-22', '2017-02-27', setExampleText);

////////////////////////////////////////////////////////////
//
// Raphael JS example
//

var viewportWidth = document.getElementById('raphaelExample1').offsetWidth;
var viewportHeight = document.getElementById('raphaelExample1').offsetHeight;
console.log(viewportHeight);
console.log(viewportWidth);
/*var graphics = Raphael('raphaelExample1', viewportWidth, viewportHeight);
var circleObject = graphics.circle(viewportWidth / 4, viewportHeight / 4, viewportHeight / 4);
circleObject.attr("fill", "#f00");
circleObject.attr("stroke", "#fff");*/