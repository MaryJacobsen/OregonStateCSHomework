package com.example.android.lifecycleweather;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.annotation.Nullable;
import android.support.v4.content.AsyncTaskLoader;
import android.support.v7.preference.PreferenceManager;
import android.util.Log;
import com.example.android.lifecycleweather.utils.NetworkUtils;
import com.example.android.lifecycleweather.utils.OpenWeatherMapUtils;
import android.content.Intent;

import java.io.IOException;

public class ForecastLoader extends AsyncTaskLoader<String> {

    private static final String TAG = ForecastLoader.class.getSimpleName();
    private String mForecastJSON;
    private String mURL;

    ForecastLoader(Context context, String url) {
        super(context);
        mURL = url;
    }

    @Override
    protected void onStartLoading() {
        if (mURL != null) {
            if (mForecastJSON != null) {
                Log.d(TAG, "Delivering cached results");
                deliverResult(mForecastJSON);
            } else {
                forceLoad();
            }
        }
    }

    @Nullable
    @Override
    public String loadInBackground() {
        if (mURL != null) {
            String results = null;
            try {
                Log.d(TAG, "loading results from Open Weather Map with URL: " + mURL);
                results = NetworkUtils.doHTTPGet(mURL);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return results;
        } else {
            return null;
        }
    }

    @Override
    public void deliverResult(@Nullable String data) {
        mForecastJSON = data;
        super.deliverResult(data);
    }

}
