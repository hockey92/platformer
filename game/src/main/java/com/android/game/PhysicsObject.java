package com.android.game;

public class PhysicsObject {

    static {
        System.loadLibrary("accelerometergraph");
    }

    private int id;
    protected PhysicsObject(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public PhysicsObject move(float x, float y) {
        move(id, x, y);
        return this;
    }

    public PhysicsObject setVel(float vx, float vy) {
        setVel(id, vx, vy);
        return this;
    }

    private static native void move(int id, float x, float y);

    private static native void setVel(int id, float vx, float vy);
}
