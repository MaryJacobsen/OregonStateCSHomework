package com.example.android.basicweather;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import java.util.ArrayList;

public class WeatherAdapter extends RecyclerView.Adapter<WeatherAdapter.WeatherViewHolder> {
    private ArrayList<String> mWeather;
    private OnClickedToastWeather mClickedToast;

    public interface OnClickedToastWeather {
        void onClickedToast(String weather);
    }

    public WeatherAdapter(OnClickedToastWeather clickedToastWeather) {
        mWeather = new ArrayList<>();
        mClickedToast = clickedToastWeather;
    }

    public void addWeather(String weather) {
        mWeather.add(weather);
        notifyItemInserted(0);
    }

    @Override
    public int getItemCount() {
        return mWeather.size();
    }

    @NonNull
    @Override
    public WeatherViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        LayoutInflater inflater = LayoutInflater.from(viewGroup.getContext());
        View itemView = inflater.inflate(R.layout.weather_item, viewGroup, false);
        return new WeatherViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull WeatherViewHolder WeatherViewHolder, int i) {
        String weather = mWeather.get(adapterPositionToArrayIndex(i));
        WeatherViewHolder.bind(weather);
    }

    public int adapterPositionToArrayIndex(int i) {
        return mWeather.size() - i - 1;
    }

    class WeatherViewHolder extends RecyclerView.ViewHolder {
        private TextView mWeatherTV;

        public WeatherViewHolder(View itemView) {
            super(itemView);
            mWeatherTV = itemView.findViewById(R.id.tv_weather_text);
            mWeatherTV.setOnClickListener(new View.OnClickListener()
            {
                public void onClick(View view)
                {
                    String weather = mWeather.get(adapterPositionToArrayIndex(getAdapterPosition()));
                    mClickedToast.onClickedToast(weather);
                }
            });
        }

        public void bind(String weather) {
            mWeatherTV.setText(weather);
        }
    }

}