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

    public void addChildren(Shape shape) {
        addChildren(id, shape.id);
    }

    public void update() {
        update(id);
    }

    public void setAngle(float angle) {
        setAngle(id, angle);
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void move(int id, float x, float y);

    private static native void addChildren(int id, int childId);

    private static native void update(int id);

    private static native void setAngle(int id, float angle);
}
