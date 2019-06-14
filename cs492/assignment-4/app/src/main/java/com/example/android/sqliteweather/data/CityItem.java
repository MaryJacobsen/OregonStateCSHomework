package com.example.android.sqliteweather.data;

import android.arch.persistence.room.ColumnInfo;
import android.arch.persistence.room.Entity;
import android.arch.persistence.room.PrimaryKey;
import android.support.annotation.NonNull;
import java.io.Serializable;

@Entity(tableName = "cities")
public class CityItem implements Serializable {
    @NonNull
    @PrimaryKey
    public String city_name;
}

