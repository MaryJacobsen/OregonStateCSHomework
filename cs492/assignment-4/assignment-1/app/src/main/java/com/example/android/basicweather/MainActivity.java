package com.example.android.basicweather;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.widget.Toast;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity implements WeatherAdapter.OnClickedToastWeather {

    private RecyclerView mWeatherRV;
    private WeatherAdapter mWeatherAdapter;
    private Toast mToast;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mWeatherRV = findViewById(R.id.rv_weather);


        mWeatherRV.setLayoutManager(new LinearLayoutManager(this));
        mWeatherRV.setHasFixedSize(true);

        mWeatherAdapter = new WeatherAdapter(this);
        mWeatherRV.setAdapter(mWeatherAdapter);

        mWeatherRV.setItemAnimator(new DefaultItemAnimator());

        mToast = null;

        mWeatherAdapter.addWeather("Tue February 5 - Partly cloudy - 46F");
        mWeatherAdapter.addWeather("Mon February 4 - Partly cloudy - 45F");
        mWeatherAdapter.addWeather("Sun February 3 - Cold and raining - 44F");
        mWeatherAdapter.addWeather("Sat February 2 - Expect rain - 48F");
        mWeatherAdapter.addWeather("Fri February 1 - Expect rain - 48F");
        mWeatherAdapter.addWeather("Thu January 31 - Rain and Cloudy - 51F");
        mWeatherAdapter.addWeather("Wed January 30 - Partly Sunny - 52F");
        mWeatherAdapter.addWeather("Tue January 29 - Partly Sunny - 50F");
        mWeatherAdapter.addWeather("Mon January 28 - Partly Sunny - 52F");
        mWeatherAdapter.addWeather("Sun January 27 - Partly Sunny - 54F");
        mWeatherAdapter.addWeather("Sat January 26 - Cloudy - 53F");
        mWeatherAdapter.addWeather("Fri January 25 - Wind and Cloudy - 52F");
        mWeatherAdapter.addWeather("Thu January 24 - Wind and Cloudy - 52F");
        mWeatherAdapter.addWeather("Wed January 23 - Rain and Cloudy - 54F");

    }

    @Override
    public void onClickedToast(String weather) {
        HashMap<String, String> map = new HashMap<>();

        map.put("Tue February 5 - Partly cloudy - 46F", "Partly cloudy with a 10% chance of rain, with a high of 46F and a low of 30F. The sun comes out in the afternoon.");
        map.put("Mon February 4 - Partly cloudy - 45F", "Partly cloudy, with a high of 45F and a low of 32F. The sun is shining through the clouds.");
        map.put("Sun February 3 - Cold and raining - 44F", "Overcast with a 75% chance of rain, with a high of 44F and a low of 34F.");
        map.put("Sat February 2 - Expect rain - 48F", "Cloudy with a 90% chance of rain, with a high of 48F and a low of 38F.");
        map.put("Fri February 1 - Expect rain - 48F", "Cloudy with an 85% chance of rain, with a high of 48F and a low of 38F.");
        map.put("Thu January 31 - Rain and Cloudy - 51F", "Overcast and 90% chance of rain, with a high of 51F and a low of 37F. Rains all day.");
        map.put("Wed January 30 - Partly Sunny - 52F", "Sunny and some clouds, with a high of 52F and a low of 37F.");
        map.put("Tue January 29 - Partly Sunny - 50F", "Sunny and some clouds, with a high of 50F and a low of 36F.");
        map.put("Mon January 28 - Partly Sunny - 52F", "Sunny and some clouds, with a high of 52F and a low of 30F. It will freeze at night.");
        map.put("Sun January 27 - Partly Sunny - 54F", "Sunny and some clouds, with a high of 54F and a low of 34F.");
        map.put("Sat January 26 - Cloudy - 53F", "Overcast and 10% chance of rain, with a high of 53F and a low of 34F.");
        map.put("Fri January 25 - Wind and Cloudy - 52F", "Overcast and strong winds, with a high of 52F and a low of 35F. Fog in the morning.");
        map.put("Thu January 24 - Wind and Cloudy - 52F", "Overcast and strong winds, with a high of 52F and a low of 37F. Fog at night.");
        map.put("Wed January 23 - Rain and Cloudy - 54F", "Overcast and 80% chance of rain, with a high of 54F and a low of 41F. The rain stops late in the day.");
        if (mToast!= null) {
            mToast.cancel();
        }
            mToast.makeText(this, map.get(weather), Toast.LENGTH_LONG).show();
    }
}
