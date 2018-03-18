package edu.osu.praterj.coolpix;

/**
 * Created by prater on 3/17/18.
 */

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Checkable;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.util.Log;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

//
// Adapter code adapted from
//
// https://stackoverflow.com/questions/6327465/displaying-bitmap-image-in-imageview-by-simple-adapter
//


public class PostAdapter extends SimpleAdapter{
    List<? extends Map<String, ?>> map; // if fails to compile, replace with List<HashMap<String, Object>> map
    String[] from;
    int layout;
    int[] to;
    Context context;
    LayoutInflater mInflater;

    private final String userID;

    public PostAdapter(Context context, List<? extends Map<String, ?>> data, // if fails to compile, do the same replacement as above on this line
                                 int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
        layout = resource;
        map = data;
        this.from = from;
        this.to = to;
        this.context = context;
        userID = map.get(0).get("userID").toString();
        Log.i("PostAdapter", "User ID :" + userID);
    }


    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        mInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        return this.createViewFromResource(position, convertView, parent, layout);
    }

    private View createViewFromResource(int position, View convertView,
                                        ViewGroup parent, int resource) {
        View v;
        if (convertView == null) {
            v = mInflater.inflate(resource, parent, false);
        } else {
            v = convertView;
        }

        this.bindView(position, v);

        return v;
    }


    private void bindView(int position, View view) {
        final Map dataSet = map.get(position);
        if (dataSet == null) {
            return;
        }

        final ViewBinder binder = super.getViewBinder();
        final int count = to.length;

        for (int i = 0; i < count; i++) {
            final View v = view.findViewById(to[i]);
            if (v != null) {
                final Object data = dataSet.get(from[i]);
                String text = data == null ? "" : data.toString();
                if (text == null) {
                    text = "";
                }

                boolean bound = false;
                if (binder != null) {
                    bound = binder.setViewValue(v, data, text);
                }

                if (!bound) {
                    if (v instanceof Checkable) {
                        if (data instanceof Boolean) {
                            ((Checkable) v).setChecked((Boolean) data);
                        } else if (v instanceof TextView) {
                            // Note: keep the instanceof TextView check at the bottom of these
                            // ifs since a lot of views are TextViews (e.g. CheckBoxes).
                            setViewText((TextView) v, text);
                        } else {
                            throw new IllegalStateException(v.getClass().getName() +
                                    " should be bound to a Boolean, not a " +
                                    (data == null ? "<unknown type>" : data.getClass()));
                        }
                    } else if (v instanceof TextView) {
                        if (v instanceof Button) {
                            Log.i("PostAdapter", "Setup Handler : " + (String) data);

                            ((Button) v).setOnClickListener(new View.OnClickListener() {
                                String localData = (String) data;
                                String imageID = dataSet.get("imageID").toString();
                                CoolPixActivity pixActivity = (CoolPixActivity)context;

                                @Override
                                public void onClick(View v) {
                                    Log.i("PostAdapter", "Clicked something : " + localData + ":" + userID + ":" + imageID);
                                    if (localData.compareTo("deleteImage") == 0) {
                                        // Delete the image...
                                        OkHttpClient httpClient = new OkHttpClient();
                                        //HttpUrl reqUrl = HttpUrl.parse("http://dev-smart.ddns.net:1337/content/" + userID + "/" + imageID);
                                        HttpUrl reqUrl = HttpUrl.parse("http://10.0.2.2:1337/content/" + userID + "/" + imageID);
                                        Request request = new Request.Builder()
                                                .url(reqUrl)
                                                .delete()
                                                .build();
                                        httpClient.newCall(request).enqueue(new Callback() {
                                            @Override
                                            public void onFailure(Call call, IOException e) {
                                                e.printStackTrace();
                                            }

                                            @Override
                                            public void onResponse(Call call, Response response) throws IOException {
                                                Log.i("Post Adapter", "Deleted Image");
                                                pixActivity.signinComplete();
                                            }
                                        });

                                    }
                                }
                            });
                        } else {
                            // Note: keep the instanceof TextView check at the bottom of these
                            // ifs since a lot of views are TextViews (e.g. CheckBoxes).
                            setViewText((TextView) v, text);
                        }
                    } else if (v instanceof ImageView) {
                        if (data instanceof Integer) {
                            setViewImage((ImageView) v, (Integer) data);
                        } else if (data instanceof Bitmap){
                            setViewImage((ImageView) v, (Bitmap)data);
                        } else {
                            setViewImage((ImageView) v, text);
                        }
                    } else {
                        throw new IllegalStateException(v.getClass().getName() + " is not a " +
                                " view that can be bounds by this SimpleAdapter");
                    }
                }
            }
        }
    }

    private void setViewImage(ImageView v, Bitmap bmp){
        v.setImageBitmap(bmp);
    }
}