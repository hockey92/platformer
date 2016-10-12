package com.android.game;

public class ObjectsCounter {

    private static int lastId;

    public static int getLastId() {
        return lastId++;
    }
}
