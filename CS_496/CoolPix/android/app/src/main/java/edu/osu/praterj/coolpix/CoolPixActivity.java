package edu.osu.praterj.coolpix;

import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Intent;
import android.app.PendingIntent;
import android.net.Uri;
import android.util.Log;

import android.view.View;
import android.widget.Button;
import android.widget.ListView;

import android.graphics.BitmapFactory;
import android.graphics.Bitmap;

import java.util.Date;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

import android.content.SharedPreferences;

import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONArray;

import net.openid.appauth.AuthState;
import net.openid.appauth.AuthorizationException;
import net.openid.appauth.AuthorizationServiceConfiguration;
import net.openid.appauth.AuthorizationRequest;
import net.openid.appauth.AuthorizationService;
import net.openid.appauth.ResponseTypeValues;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

//
// OAuth2 Client ID
//
// 397564378096-17aeefr098viu7u701prsql3ra7r8d54.apps.googleusercontent.com
//
public class CoolPixActivity extends AppCompatActivity {

    private AuthorizationService localAuthorizationService;
    private AuthState localAuthState;
    private JSONObject localUserObject;
    private String userIDString;

    final private String debugTag = "CoolPix";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
        setContentView(R.layout.activity_cool_pix);
        localAuthorizationService = new AuthorizationService(this);
        Button refresh = findViewById(R.id.button_refresh);
        refresh.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(debugTag, "Refreshing Posts");
                if (localAuthState != null) {
                    signinComplete();
                }
            }
        });

        Button addPost= findViewById(R.id.button_add_post);
        addPost.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(debugTag, "Launching Activity Add Post");

                SharedPreferences authPreferences = getSharedPreferences("userInfo", MODE_PRIVATE);
                authPreferences.edit().putString("userID", userIDString).apply();

                Intent intent = new Intent(CoolPixActivity.this, AddNewPostActivity.class);
                startActivity(intent);
            }
        });

        Button signOut= findViewById(R.id.button_sign_out);
        signOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(debugTag, "Signing out...");
                SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
                authPreferences.edit().remove("state").apply();
                onStart();
            }
        });

    }

    @Override
    protected void onStart() {
        localAuthState = getOrCreateAuthState();
        if (localAuthState != null) {
            signinComplete();
        }
        super.onStart();
    }


    void signinComplete() {
        localAuthState.performActionWithFreshTokens(localAuthorizationService, new AuthState.AuthStateAction() {
            @Override
            public void execute(@Nullable String accessToken, @Nullable String idToken, @Nullable AuthorizationException error) {
                if (error == null) {
                    OkHttpClient httpClient = new OkHttpClient();
                    HttpUrl reqUrl = HttpUrl.parse("https://www.googleapis.com/plus/v1/people/me");
                    Log.i(debugTag, "Access Token : " + accessToken);
                    Request request = new Request.Builder()
                            .url(reqUrl)
                            .addHeader("Authorization", "Bearer " + accessToken)
                            .build();
                    httpClient.newCall(request).enqueue(new Callback() {
                        @Override
                        public void onFailure(Call call, IOException e) {
                            e.printStackTrace();
                        }

                        @Override
                        public void onResponse(Call call, Response response) throws IOException {
                            String resp = response.body().string();
                            try {
                                JSONObject jsonObject = new JSONObject(resp);
                                userIDString = jsonObject.getString("id");
                                Log.i(debugTag, "User ID : " + userIDString);


                                GetUserInfo(userIDString);
                            } catch (JSONException error) {
                                error.printStackTrace();
                            }
                        }
                    });

                } else {
                    Log.e(debugTag, "Auth error " + error.toString());
                }
            }
        });
    }

    void CreateUser() {
        localAuthState.performActionWithFreshTokens(localAuthorizationService, new AuthState.AuthStateAction() {
            @Override
            public void execute(@Nullable String accessToken, @Nullable String idToken, @Nullable AuthorizationException error) {
                if (error == null) {
                    OkHttpClient httpClient = new OkHttpClient();
                    HttpUrl reqUrl = HttpUrl.parse("https://www.googleapis.com/plus/v1/people/me");
                    Log.i(debugTag, "Access Token : " + accessToken);
                    Request request = new Request.Builder()
                            .url(reqUrl)
                            .addHeader("Authorization", "Bearer " + accessToken)
                            .build();
                    httpClient.newCall(request).enqueue(new Callback() {
                        @Override
                        public void onFailure(Call call, IOException e) {
                            e.printStackTrace();
                        }

                        @Override
                        public void onResponse(Call call, Response response) throws IOException {
                            String resp = response.body().string();
                            try {
                                JSONObject jsonObject = new JSONObject(resp);
                                String userID = jsonObject.getString("id");
                                Log.i(debugTag, "Creating user with id " + userID);
                                String displayName = jsonObject.getString("displayName");
                                String payload = "{" +
                                        "\"id\": \"" + userID + "\"," +
                                        "\"name\": \"" + displayName + "\"," +
                                        "\"creationTime\": " + new Date().getTime() + "," +
                                        "\"posts\": {}" +
                                        "}";

                                Log.i(debugTag, payload);
                                MediaType JSON = MediaType.parse("application/json");
                                RequestBody body = RequestBody.create(JSON, payload);

                                OkHttpClient httpClient = new OkHttpClient();
                                HttpUrl reqUrl = HttpUrl.parse("http://dev-smart.ddns.net:1337/users");
                                //HttpUrl reqUrl = HttpUrl.parse("http://10.0.2.2:1337/users");
                                Request request = new Request.Builder()
                                        .url(reqUrl)
                                        .post(body)
                                        .build();
                                httpClient.newCall(request).enqueue(new Callback() {
                                    @Override
                                    public void onFailure(Call call, IOException e) {
                                        e.printStackTrace();
                                    }

                                    @Override
                                    public void onResponse(Call call, Response response) throws IOException {
                                        String resp = response.body().string();
                                        try {
                                            localUserObject = new JSONObject(resp);
                                            // Update something...
                                            SharedPreferences authPreferences = getSharedPreferences("userInfo", MODE_PRIVATE);
                                            authPreferences.edit().putString("userInfo", resp).apply();

                                            updateUserPosts();
                                        } catch (JSONException error) {
                                            error.printStackTrace();
                                        }
                                    }
                                });

                            } catch (JSONException error) {
                                error.printStackTrace();
                            }
                        }
                    });
                } else {
                    Log.e(debugTag, "Auth error " + error.toString());
                }
            }
        });
    }

    void GetUserInfo(final String userID) {
        localAuthState.performActionWithFreshTokens(localAuthorizationService, new AuthState.AuthStateAction() {
            @Override
            public void execute(@Nullable String accessToken, @Nullable String idToken, @Nullable AuthorizationException error) {
                if (error == null) {
                    OkHttpClient httpClient = new OkHttpClient();
                    HttpUrl reqUrl = HttpUrl.parse(" http://dev-smart.ddns.net:1337/users/" + userID);
                    //HttpUrl reqUrl = HttpUrl.parse(" http://10.0.2.2:1337/users/" + userID);
                    Log.i(debugTag, "User info for user : " + userID);
                    Request request = new Request.Builder()
                            .url(reqUrl)
                            .build();
                    httpClient.newCall(request).enqueue(new Callback() {
                        @Override
                        public void onFailure(Call call, IOException e) {
                            e.printStackTrace();
                        }

                        @Override
                        public void onResponse(Call call, Response response) throws IOException {
                            String resp = response.body().string();
                            if (resp.length() == 0) {
                                Log.i(debugTag, "User does not exist : " + userID);
                                // User does not exists.
                                CreateUser();
                                return;
                            } else {
                                Log.i(debugTag, "User Info : " + resp);
                                try {
                                    localUserObject = new JSONObject(resp);
                                    // Update something...
                                    SharedPreferences authPreferences = getSharedPreferences("userInfo", MODE_PRIVATE);
                                    authPreferences.edit().putString("userInfo", resp).apply();
                                    updateUserPosts();
                                } catch (JSONException error) {
                                    error.printStackTrace();
                                }
                            }
                        }
                    });

                } else {
                    Log.e(debugTag, "Auth error " + error.toString());
                }
            }
        });
    }

    void updateUserPosts()
    {
        try {
            JSONArray itemArray = localUserObject.getJSONArray("posts");
            List<Map<String, Object>> posts = new ArrayList<Map<String, Object>>();

            if (itemArray.length() == 0){
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        ((ListView) findViewById(R.id.picList)).setAdapter(null);
                    }
                });
                return;
            }

            for (int i = itemArray.length() - 1 ; i >= 0 ; i--) {
                byte[] imageData = android.util.Base64.decode(itemArray.getJSONObject(i).getString("imageData"), android.util.Base64.DEFAULT);
                Bitmap decodedImage= BitmapFactory.decodeByteArray(imageData, 0, imageData.length);
                Date editDate = new Date(itemArray.getJSONObject(i).getLong("lastEdit"));
                String caption = itemArray.getJSONObject(i).getString("caption");
                String body = itemArray.getJSONObject(i).getString("body");
                boolean liked = itemArray.getJSONObject(i).getBoolean("liked");
                String imageID = itemArray.getJSONObject(i).getString("imageID");

                Log.i(debugTag, imageID);
                Log.i(debugTag, editDate.toString());
                Log.i(debugTag, caption);
                Log.i(debugTag, body);
                Log.i(debugTag, Boolean.toString(liked));

                HashMap<String, Object> hashMap = new HashMap<String, Object>();
                hashMap.put("userID", userIDString);
                hashMap.put("imageID", imageID);
                hashMap.put("imageData", decodedImage);
                hashMap.put("lastEdit", editDate);
                hashMap.put("caption", caption);
                hashMap.put("body", body);
                hashMap.put("liked", liked);
                hashMap.put("deleteImage", "deleteImage");
                hashMap.put("editImage", "editImage");
                posts.add(hashMap);
            }

            final PostAdapter postAdapter = new PostAdapter(
                    CoolPixActivity.this,
                    posts,
                    R.layout.posts_layout,
                    new String[]{"caption", "lastEdit", "liked", "body", "imageData", "editImage", "deleteImage"},
                    new int[]{R.id.post_caption, R.id.post_date, R.id.post_liked, R.id.post_body, R.id.post_image, R.id.editButton, R.id.deleteButton});
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ((ListView) findViewById(R.id.picList)).setAdapter(postAdapter);
                }
            });
        } catch (JSONException error) {
            error.printStackTrace();
        }
    }

    AuthState getOrCreateAuthState() {
        Log.i(debugTag, "Entering getOrCreateAuthState");
        AuthState state = null;
        SharedPreferences authPreferences = getSharedPreferences("auth", MODE_PRIVATE);
        String authState = authPreferences.getString("state", null);
        if (authState != null) {
            try {
                Log.i(debugTag, "auth State" + authState);
                state = localAuthState.jsonDeserialize(authState);
            } catch (JSONException error) {
                error.printStackTrace();
                return null;
            }
        }

        if ((state != null) && (state.getAccessToken() != null)) {
            Log.i(debugTag, "Valid AuthState");
            return state;
        } else {
            Log.i(debugTag, "Updating AuthState");
            updateAuthState();
            return null;
        }
    }

    void updateAuthState() {
        Log.i(debugTag, "Entered updateAuthState");

        Uri authEndpoint = new Uri.Builder().scheme("https").authority("accounts.google.com").path("/o/oauth2/v2/auth").build();
        Uri tokenEndpoint = new Uri.Builder().scheme("https").authority("www.googleapis.com").path("/oauth2/v4/token").build();
        Uri redirect = new Uri.Builder().scheme("edu.osu.praterj.coolpix").path("user").build();

        AuthorizationServiceConfiguration config = new AuthorizationServiceConfiguration(authEndpoint, tokenEndpoint, null);
        AuthorizationRequest req = new AuthorizationRequest.Builder(
                config,
                "397564378096-17aeefr098viu7u701prsql3ra7r8d54.apps.googleusercontent.com",
                ResponseTypeValues.CODE,
                redirect)
                .setScopes("https://www.googleapis.com/auth/plus.me")
                .build();

        Intent authComplete = new Intent(this, AuthCompleteActivity.class);
        localAuthorizationService.performAuthorizationRequest(req, PendingIntent.getActivity(this, req.hashCode(), authComplete, 0));
    }
}
