package com.example.android.sqliteweather.data;

import android.app.Application;
import android.arch.lifecycle.LiveData;
import android.os.AsyncTask;
import java.util.List;

public class CityItemRepository {
    private CityItemDao mCityItemDao;

    public CityItemRepository(Application application) {
        AppDatabase db = AppDatabase.getDatabase(application);
        mCityItemDao = db.cityItemDao();
    }

    public void insertCityItem(CityItem city) {
        new InsertAsyncTask(mCityItemDao).execute(city);
    }

    public void deleteCityItem(CityItem city) {
        new DeleteAsyncTask(mCityItemDao).execute(city);
    }

    public LiveData<List<CityItem>> getAllCityItems() {
        return mCityItemDao.getAllCities();
    }

    public LiveData<CityItem> getCityItemByName(String Name) {
        return mCityItemDao.getCityItemByName(Name);
    }

    private static class InsertAsyncTask extends AsyncTask<CityItem, Void, Void> {
        private CityItemDao mAsyncTaskDao;
        InsertAsyncTask(CityItemDao dao) {
            mAsyncTaskDao = dao;
        }

        @Override
        protected Void doInBackground(CityItem... cities) {
            mAsyncTaskDao.insert(cities[0]);
            return null;
        }
    }

    private static class DeleteAsyncTask extends AsyncTask<CityItem, Void, Void> {
        private CityItemDao mAsyncTaskDao;
        DeleteAsyncTask(CityItemDao dao) {
            mAsyncTaskDao = dao;
        }

        @Override
        protected Void doInBackground(CityItem... cities) {
            mAsyncTaskDao.delete(cities[0]);
            return null;
        }
    }
}
