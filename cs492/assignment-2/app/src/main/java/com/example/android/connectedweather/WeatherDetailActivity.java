package com.example.android.connectedweather;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.net.Uri;
import android.support.v4.app.ShareCompat;

public class WeatherDetailActivity extends AppCompatActivity {
    private TextView mWeatherTimeTV;
    private TextView mWeatherDescriptionTV;
    private TextView mWeatherTempTV;
    private WeatherUtils.OpenWeatherReport mForecast;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weather_detail);

        mWeatherTimeTV = findViewById(R.id.tv_weather_time);
        mWeatherDescriptionTV = findViewById(R.id.tv_weather_description);
        mWeatherTempTV = findViewById(R.id.tv_weather_temp);

        mForecast = null;
        Intent intent = getIntent();
        if (intent != null && intent.hasExtra(WeatherUtils.EXTRA_FORECAST)) {
            mForecast = (WeatherUtils.OpenWeatherReport) intent.getSerializableExtra(WeatherUtils.EXTRA_FORECAST);
            mWeatherTimeTV.setText("Date and time: " + "\n" + mForecast.dt_txt);
            mWeatherTempTV.setText("Temperature: " + "\n" + mForecast.main.temp + " F");
            mWeatherDescriptionTV.setText("Description: " + "\n" + mForecast.weather[0].description);

        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.weather_detail, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_view_location:
                viewLocation();
                return true;
            case R.id.action_share:
                shareWeather();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void viewLocation() {
        if (mForecast != null) {
            Uri cityURI = Uri.parse("https://www.google.com/maps/place/Puyallup");
            Intent intent = new Intent(Intent.ACTION_VIEW, cityURI);
            if (intent.resolveActivity(getPackageManager()) != null) {
                startActivity(intent);
            }
        }
    }

    public void shareWeather() {
        if (mForecast != null) {
            String shareText = "Puyallup, WA" + "\n" + "Date and Time: " + mForecast.dt_txt + "\n" + "Temperature: " + mForecast.main.temp + " F" + "\n" + "Description: " + mForecast.weather[0].description;
            ShareCompat.IntentBuilder.from(this)
                    .setType("text/plain")
                    .setText(shareText)
                    .setChooserTitle(R.string.share_chooser_title)
                    .startChooser();
        }
    }

}
