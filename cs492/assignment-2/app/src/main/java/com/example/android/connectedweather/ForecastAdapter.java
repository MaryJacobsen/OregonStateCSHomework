package com.example.android.connectedweather;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.ArrayList;

public class ForecastAdapter extends RecyclerView.Adapter<ForecastAdapter.ForecastItemViewHolder> {

    //private ArrayList<String> mForecastData;
    private WeatherUtils.OpenWeatherReport[] mForecastData;
    private OnForecastItemClickListener mOnForecastItemClickListener;

    public ForecastAdapter(OnForecastItemClickListener onForecastItemClickListener) {
        mOnForecastItemClickListener = onForecastItemClickListener;
    }

    public void updateForecastData(WeatherUtils.OpenWeatherReport[] forecastData) {
        mForecastData = forecastData;
        notifyDataSetChanged();
    }

    @Override
    public int getItemCount() {
        if (mForecastData != null) {
            return mForecastData.length;
        } else {
            return 0;
        }
    }

    @Override
    public ForecastItemViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View view = inflater.inflate(R.layout.forecast_list_item, parent, false);
        return new ForecastItemViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ForecastItemViewHolder holder, int position) {
        holder.bind(mForecastData[position]);
    }

    public interface OnForecastItemClickListener {
        void onForecastItemClick(WeatherUtils.OpenWeatherReport forecast);
    }

    class ForecastItemViewHolder extends RecyclerView.ViewHolder {
        private TextView mForecastTextView;

        public ForecastItemViewHolder(View itemView) {
            super(itemView);
            mForecastTextView = (TextView)itemView.findViewById(R.id.tv_forecast_text);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    WeatherUtils.OpenWeatherReport forecastResult = mForecastData[getAdapterPosition()];
                    mOnForecastItemClickListener.onForecastItemClick(forecastResult);
                }
            });
        }

        public void bind(WeatherUtils.OpenWeatherReport forecast) {
            mForecastTextView.setText(forecast.dt_txt + " " + forecast.weather[0].main + " " + forecast.main.temp);
        }
    }
}
