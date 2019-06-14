package com.example.android.connectedweather;

import android.net.Uri;
import com.google.gson.Gson;
import java.io.Serializable;

public class WeatherUtils {
    private final static String WEATHER_URL = "https://api.openweathermap.org/data/2.5/forecast?q=Puyallup,us&units=imperial&APPID=f3910be46b89485cf0f5054a8e5bd3df";


    public static String buildWeatherURL() {
        return Uri.parse(WEATHER_URL).buildUpon().build().toString();
    }

    public static final String EXTRA_FORECAST = "WeatherUtils.OpenWeatherReport";

    public static class OpenWeatherResults {
        OpenWeatherReport[] list;
    }

    public static class OpenWeatherReport implements Serializable {
        public String dt_txt;
        public Main main;
        public Weather[] weather;
    }

    public static class Main implements Serializable {
        public float temp;
    }

    public static class Weather implements Serializable {
        public String main;
        public String description;
    }

    public static OpenWeatherReport[] parseForecastResults(String json){
        Gson gson = new Gson();
        OpenWeatherResults results = gson.fromJson(json, OpenWeatherResults.class);
        if (results != null && results.list != null) {
            return results.list;
        } else {
            return null;
        }
    }
}


