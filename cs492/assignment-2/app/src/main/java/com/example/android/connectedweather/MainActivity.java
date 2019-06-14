package com.example.android.connectedweather;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.widget.Toast;
import android.view.View;
import android.util.Log;
import java.io.IOException;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements ForecastAdapter.OnForecastItemClickListener {

    private static final String TAG = MainActivity.class.getSimpleName();

    private RecyclerView mForecastListRV;
    private ForecastAdapter mForecastAdapter;
    private Toast mToast;
    private ProgressBar mLoadingPB;
    private TextView mLoadingErrorTV;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mForecastListRV = findViewById(R.id.rv_forecast_list);
        mLoadingPB = findViewById(R.id.pb_loading_indicator);
        mLoadingErrorTV = findViewById(R.id.tv_loading_error_message);

        mForecastListRV.setLayoutManager(new LinearLayoutManager(this));
        mForecastListRV.setHasFixedSize(true);

        mForecastAdapter = new ForecastAdapter(this);
        mForecastListRV.setAdapter(mForecastAdapter);

        doOpenWeather();
    }

    private void doOpenWeather() {
        String url = WeatherUtils.buildWeatherURL();
        Log.d(TAG, "querying weather URL: " + url);
        new OpenWeatherTask().execute(url);
    }

    @Override
    public void onForecastItemClick(WeatherUtils.OpenWeatherReport forecast) {
        Intent intent = new Intent(this, WeatherDetailActivity.class);
        intent.putExtra(WeatherUtils.EXTRA_FORECAST, forecast);
        startActivity(intent);
    }

    class OpenWeatherTask extends AsyncTask<String, Void, String> {

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            mLoadingPB.setVisibility(View.VISIBLE);
        }

        @Override
        protected String doInBackground(String... urls) {
            String url = urls[0];
            String results = null;
            try {
                results = NetworkUtils.doHTTPGet(url);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return results;
        }

        @Override
        protected void onPostExecute(String s) {
            if (s != null) {
                mLoadingErrorTV.setVisibility(View.INVISIBLE);
                mForecastListRV.setVisibility(View.VISIBLE);
                WeatherUtils.OpenWeatherReport[] forecasts = WeatherUtils.parseForecastResults(s);
                mForecastAdapter.updateForecastData(forecasts);
            } else {
                mLoadingErrorTV.setVisibility(View.VISIBLE);
                mForecastListRV.setVisibility(View.INVISIBLE);
            }
            mLoadingPB.setVisibility(View.INVISIBLE);
        }
    }
}
