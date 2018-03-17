package edu.osu.praterj.coolpix;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class AddNewPostActivity extends AppCompatActivity {

    final private String debugTag= "AddPost";
    final private String debugTagCamera = "AddPost - Camera";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_new_post);
        if (null == savedInstanceState) {
            getSupportFragmentManager().beginTransaction()
                    .replace(R.id.camera2Container, Camera2BasicFragment.newInstance())
                    .commit();
        }    }
}
