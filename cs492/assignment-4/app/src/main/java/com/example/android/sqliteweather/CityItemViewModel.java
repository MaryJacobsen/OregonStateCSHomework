package com.example.android.sqliteweather;

import android.app.Application;
import android.arch.lifecycle.AndroidViewModel;
import android.arch.lifecycle.LiveData;

import com.example.android.sqliteweather.data.CityItem;
import com.example.android.sqliteweather.data.CityItemRepository;

import java.util.List;

public class CityItemViewModel extends AndroidViewModel {
    private CityItemRepository mCityItemRepository;

    public CityItemViewModel(Application application) {
        super(application);
        mCityItemRepository = new CityItemRepository(application);
    }

    public void insertCityItem(CityItem city) {
        mCityItemRepository.insertCityItem(city);
    }

    public void deleteCityItem(CityItem city) {
        mCityItemRepository.deleteCityItem(city);
    }

    public LiveData<List<CityItem>> getAllCityItems() {
        return mCityItemRepository.getAllCityItems();
    }

    public LiveData<CityItem> getCityItemByName(String name) {
        return mCityItemRepository.getCityItemByName(name);
    }

}
