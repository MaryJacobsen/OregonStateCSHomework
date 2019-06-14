package com.example.android.lifecycleweather;

import android.content.Intent;
import android.net.Uri;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.Loader;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.support.v7.preference.PreferenceManager;
import android.content.SharedPreferences;

import com.example.android.lifecycleweather.data.WeatherPreferences;
import com.example.android.lifecycleweather.utils.NetworkUtils;
import com.example.android.lifecycleweather.utils.OpenWeatherMapUtils;

import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity
        implements ForecastAdapter.OnForecastItemClickListener, LoaderManager.LoaderCallbacks<String> {

    private static final String TAG = MainActivity.class.getSimpleName();
    private static final String WEATHER_URL_KEY = "weatherURL";
    private static final int WEATHER_LOADER_ID = 0;

    private TextView mForecastLocationTV;
    private RecyclerView mForecastItemsRV;
    private ProgressBar mLoadingIndicatorPB;
    private TextView mLoadingErrorMessageTV;
    private ForecastAdapter mForecastAdapter;
    private SharedPreferences.OnSharedPreferenceChangeListener listener;

    private ArrayList<OpenWeatherMapUtils.ForecastItem> mForecasts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Remove shadow under action bar.
        getSupportActionBar().setElevation(0);

        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
        String location = preferences.getString(getString(R.string.pref_location_key), getString(R.string.pref_location_default));

        mForecastLocationTV = findViewById(R.id.tv_forecast_location);
        mForecastLocationTV.setText(location);

        mLoadingIndicatorPB = findViewById(R.id.pb_loading_indicator);
        mLoadingErrorMessageTV = findViewById(R.id.tv_loading_error_message);
        mForecastItemsRV = findViewById(R.id.rv_forecast_items);

        mForecastAdapter = new ForecastAdapter(this);
        mForecastItemsRV.setAdapter(mForecastAdapter);
        mForecastItemsRV.setLayoutManager(new LinearLayoutManager(this));
        mForecastItemsRV.setHasFixedSize(true);
        mForecasts = null;

        loadForecast();

        getSupportLoaderManager().initLoader(WEATHER_LOADER_ID, null, this);

        listener = new SharedPreferences.OnSharedPreferenceChangeListener() {
            public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
                loadForecast();
            }
        };

        preferences.registerOnSharedPreferenceChangeListener(listener);
    }

    @Override
    public void onForecastItemClick(OpenWeatherMapUtils.ForecastItem forecastItem) {
        Intent intent = new Intent(this, ForecastItemDetailActivity.class);
        intent.putExtra(OpenWeatherMapUtils.EXTRA_FORECAST_ITEM, forecastItem);
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_settings:
                Intent intent = new Intent(this, SettingsActivity.class);
                startActivity(intent);
                return true;
            case R.id.action_location:
                showForecastLocation();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void loadForecast() {
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
        String unit = preferences.getString(getString(R.string.pref_unit_key), getString(R.string.pref_unit_default));
        String location = preferences.getString(getString(R.string.pref_location_key), getString(R.string.pref_location_default));
        mForecastLocationTV.setText(location);
        String openWeatherMapForecastURL = OpenWeatherMapUtils.buildForecastURL(location, unit);
        Log.d(TAG, "got forecast url: " + openWeatherMapForecastURL);
        Bundle args = new Bundle();
        args.putString(WEATHER_URL_KEY, openWeatherMapForecastURL);
        mLoadingIndicatorPB.setVisibility(View.VISIBLE);
        getSupportLoaderManager().restartLoader(WEATHER_LOADER_ID, args, this);
    }

    public void showForecastLocation() {
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(this);
        String location = preferences.getString(getString(R.string.pref_location_key), getString(R.string.pref_location_default));
        Uri geoUri = Uri.parse("geo:0,0").buildUpon()
                .appendQueryParameter("q", location)
                .build();
        Intent mapIntent = new Intent(Intent.ACTION_VIEW, geoUri);
        if (mapIntent.resolveActivity(getPackageManager()) != null) {
            startActivity(mapIntent);
        }
    }

    @Override
    public Loader<String> onCreateLoader(int id, final Bundle args) {
        String weatherURL = null;
        if (args != null) {
            weatherURL = args.getString(WEATHER_URL_KEY);
        }
        return new ForecastLoader(this, weatherURL);
    }

    @Override
    public void onLoadFinished(Loader<String> loader, String data) {
        Log.d(TAG, "Got results from the loader");
        if (data != null) {
            mLoadingErrorMessageTV.setVisibility(View.INVISIBLE);
            mForecastItemsRV.setVisibility(View.VISIBLE);
            mForecasts = OpenWeatherMapUtils.parseForecastJSON(data);
            mForecastAdapter.updateForecastItems(mForecasts);
        } else {
            mForecastItemsRV.setVisibility(View.INVISIBLE);
            mLoadingErrorMessageTV.setVisibility(View.VISIBLE);
        }
        mLoadingIndicatorPB.setVisibility(View.INVISIBLE);
    }


    @Override
    public void onLoaderReset(@NonNull Loader<String> loader) {
        // Nothing to do here...
    }
}
