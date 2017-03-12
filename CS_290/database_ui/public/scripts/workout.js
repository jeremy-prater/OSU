////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

function addWorkout()
{
    console.log ("[Workout] Adding workout.");
    var payload = {
        name: document.getElementById('name').value,
        reps: document.getElementById('reps').value,
        weight: document.getElementById('weight').value,
        date: document.getElementById('date').value,
        lbs: document.getElementById('weight_lbs').checked
    };
    var req = new XMLHttpRequest();
    var targetUrl = '/insertWorkout';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status >= 200 && req.status < 400) {
        }
    };
    console.log(payload);
    req.send(JSON.stringify(payload));
}