package com.example.android.sqliteweather.data;

import android.arch.lifecycle.LiveData;
import android.arch.persistence.room.Dao;
import android.arch.persistence.room.Delete;
import android.arch.persistence.room.Insert;
import android.arch.persistence.room.OnConflictStrategy;
import android.arch.persistence.room.Query;
import java.util.List;

@Dao
public interface CityItemDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insert(CityItem city);

    @Delete
    void delete(CityItem city);

    @Query("SELECT * FROM cities")
    LiveData<List<CityItem>> getAllCities();

    @Query("SELECT * FROM cities WHERE city_name = :Name LIMIT 1")
    LiveData<CityItem> getCityItemByName(String Name);

}
