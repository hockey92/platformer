package com.android.game;

/**
 * Created by qwerty on 01.10.16.
 */
public class Shape {
    private int id;

    protected Shape(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public Shape move(float x, float y) {
        move(id, x, y);
        return this;
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void move(int id, float x, float y);
}
