package edu.osu.praterj.geotagger;

import android.Manifest;
import android.location.Location;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v4.app.ActivityCompat;
import android.os.Bundle;
import android.content.pm.PackageManager;
import android.util.Log;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;


public class Geotagger
        extends AppCompatActivity
        implements  GoogleApiClient.ConnectionCallbacks,
                    GoogleApiClient.OnConnectionFailedListener
    {

    static int PERMISSION_LOCATION = 0x100;

    private GoogleApiClient localGoogleApiClient;
    private LocationRequest localLocationRequest;
    private Location localLastLocation;
    private LocationListener localLocationListener;
    private String debugTag = "geotagger_main";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_geotagger);
        if (localGoogleApiClient == null) {
            Log.i (debugTag, "Creating Google Api");
            localGoogleApiClient = new GoogleApiClient.Builder(this)
                    .addConnectionCallbacks(this)
                    .addOnConnectionFailedListener(this)
                    .addApi(LocationServices.API)
                    .build();
        }

        localLocationRequest = LocationRequest.create();
        localLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
        localLocationRequest.setInterval(1000);
        localLocationRequest.setFastestInterval(1000);
        localLocationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (location != null) {
                    // Do stuff with location
                    Log.i (debugTag, "Location is valid");
                } else {
                    // Location not available :(
                    Log.i (debugTag, "Location is not valid");
                }
            }
        };
    }

    @Override
    protected void onStart() {
        Log.i (debugTag, "Activity start");
        localGoogleApiClient.connect();
        super.onStart();
    }

    @Override
    protected void onStop() {
        Log.i (debugTag, "Activity stop");
        localGoogleApiClient.disconnect();
        super.onStop();
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {
        // onconnect
        Log.i (debugTag, "Activity connected");

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_LOCATION);
            // Show some error stuff since we are rejected
            Log.i (debugTag, "No Location permissions");
            return;
        }
        updateLocation();
    }

    @Override
    public void onConnectionFailed(ConnectionResult result) {

    }

    @Override
    public void onConnectionSuspended(int data) {

    }

    /*@Override
    public void onRequestPermissionResult(int requestCode, String[] permissions, int[] grantResults) {
        if (requestCode == PERMISSION_LOCATION)
        {
            if (grantResults.length > 0)
            {
                updateLocation();
            }
        }
    }*/

    private void updateLocation() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            Log.i (debugTag, "No Location permissions");
            return;
        }

        // Update location
        localLastLocation = LocationServices.FusedLocationApi.getLastLocation(localGoogleApiClient);

        if (localLastLocation != null) {
            // update location :)
            Log.i (debugTag, "Location Updated");
        } else {
            Log.i (debugTag, "Requesting Location update");
            LocationServices.FusedLocationApi.requestLocationUpdates(localGoogleApiClient, localLocationRequest, localLocationListener);
        }
    }
}
