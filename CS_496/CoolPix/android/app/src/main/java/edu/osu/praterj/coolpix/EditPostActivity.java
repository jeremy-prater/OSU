package edu.osu.praterj.coolpix;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.util.Log;

import android.widget.EditText;
import android.widget.ImageView;
import android.widget.CheckBox;
import android.widget.CompoundButton;

import android.text.TextWatcher;
import android.text.Editable;
import android.widget.CompoundButton.OnCheckedChangeListener;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.Date;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class EditPostActivity extends AppCompatActivity {

    private String userID;
    private String imageID;
    private String caption;
    private String body;
    private Boolean liked;
    private JSONObject localUserObject;

    private final String debugTag = "EditPost";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_post);

        SharedPreferences authPreferences =  getSharedPreferences("userInfo", Context.MODE_PRIVATE);
        userID = authPreferences.getString("userID", null);
        imageID = authPreferences.getString("editImageID", null);

        try {
            localUserObject = new JSONObject(authPreferences.getString("userInfo", null));
            JSONArray itemArray = localUserObject.getJSONArray("posts");

            for (int index = 0; index < itemArray.length(); index++) {
                if (itemArray.getJSONObject(index).getString("imageID").compareTo(imageID) == 0) {
                    Log.i (debugTag, "Matched image ID : " + imageID);

                    final byte[] imageData = android.util.Base64.decode(itemArray.getJSONObject(index).getString("imageData"), android.util.Base64.DEFAULT);
                    Bitmap decodedImage = BitmapFactory.decodeByteArray(imageData, 0, imageData.length);
                    caption = itemArray.getJSONObject(index).getString("caption");
                    body = itemArray.getJSONObject(index).getString("body");
                    liked = itemArray.getJSONObject(index).getBoolean("liked");

                    ((EditText)findViewById(R.id.editCaption)).setText(caption);
                    ((EditText)findViewById(R.id.editBody)).setText(body);
                    ((CheckBox)findViewById(R.id.editLiked)).setChecked(liked);
                    ((ImageView)findViewById(R.id.imagePreview)).setImageBitmap(decodedImage);

                    ((EditText)findViewById(R.id.editCaption)).addTextChangedListener(new TextWatcher() {
                        @Override
                        public void afterTextChanged(Editable s) {}
                        @Override
                        public void beforeTextChanged(CharSequence s, int start, int count, int after) { }
                        @Override
                        public void onTextChanged(CharSequence s, int start, int before, int count) { UpdateImageValue(userID, imageID, "caption", s.toString()); }
                    });

                    ((EditText)findViewById(R.id.editBody)).addTextChangedListener(new TextWatcher() {
                        @Override
                        public void afterTextChanged(Editable s) {}
                        @Override
                        public void beforeTextChanged(CharSequence s, int start, int count, int after) { }
                        @Override
                        public void onTextChanged(CharSequence s, int start, int before, int count) { UpdateImageValue(userID, imageID, "body", s.toString()); }
                    });

                    ((CheckBox)findViewById(R.id.editLiked)).setOnCheckedChangeListener(new OnCheckedChangeListener() {
                            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                                UpdateImageValue(userID, imageID, "liked", isChecked);
                            }
                        });
                    break;
                }
            }

        } catch (JSONException error) {
            error.printStackTrace();
        }
    }

    private void UpdateImageValue(String userID, String imageID, String attribute, Object value) {
        Log.i(debugTag, "Updating [" + userID + "][" + imageID + "].[" + attribute + "]=[" + value.toString() + "]");
        // Post it to the cloud...
        String payload = "{" +
                "\"userid\": \"" + userID+ "\"," +
                "\"imageid\": \"" + imageID + "\"," +
                "\"attrib\": \"" + attribute+ "\"," +
                "\"value\": ";

        if (value instanceof Boolean) {
            payload += value.toString();
        } else if (value instanceof  String) {
            payload += "\"" + value + "\"";
        }

        payload += "}";

        Log.i(debugTag, "Updating Post : " + payload);
        MediaType JSON = MediaType.parse("application/json");
        RequestBody body = RequestBody.create(JSON, payload);

        OkHttpClient httpClient = new OkHttpClient();
        HttpUrl reqUrl = HttpUrl.parse("http://dev-smart.ddns.net:1337/content");
        //HttpUrl reqUrl = HttpUrl.parse("http://10.0.2.2:1337/content");
        Request request = new Request.Builder()
                .url(reqUrl)
                .patch(body)
                .build();
        httpClient.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                Log.i(debugTag, "Post Updated");
            }
        });
    }
}
