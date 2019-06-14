package com.example.android.sqliteweather;
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.List;

import com.example.android.sqliteweather.data.CityItem;

public class LocationAdapter extends RecyclerView.Adapter<LocationAdapter.NavigationViewHolder> {
    private List<CityItem> mLocations;
    private OnNavigationItemClickListener mOnNavigationItemClickListener;

    public interface OnNavigationItemClickListener {
        void onNavigationItemClicked(CityItem location);
    }

    public LocationAdapter(OnNavigationItemClickListener clickListener) {
        mOnNavigationItemClickListener = clickListener;
    }

    public void updateLocations(List<CityItem> locations) {
        mLocations = locations;
        notifyDataSetChanged();
    }

    @Override
    public NavigationViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        LayoutInflater inflater = LayoutInflater.from(parent.getContext());
        View itemView = inflater.inflate(R.layout.location_list_item, parent, false);
        return new NavigationViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(NavigationViewHolder holder, int position) {
        holder.bind(mLocations.get(position));
    }

    @Override
    public int getItemCount() {
        if(mLocations != null)
            return mLocations.size();
        else
            return 0;
    }

    class NavigationViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {
        private TextView mTextView;

        public NavigationViewHolder(View itemView) {
            super(itemView);
            mTextView = itemView.findViewById(R.id.tv_location_text);
            itemView.setOnClickListener(this);
        }

        public void bind(CityItem Location) {
            mTextView.setText(Location.city_name);
        }

        @Override
        public void onClick(View v) {
            CityItem locationItem = mLocations.get(getAdapterPosition());
            mOnNavigationItemClickListener.onNavigationItemClicked(locationItem);
        }
    }
}
