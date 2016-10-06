package com.android.game;

public class PhysicsObject {
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

    public PhysicsObject setAcceleration(float ax, float ay) {
        setAcceleration(id, ax, ay);
        return this;
    }

    public Vec2 getVel() {
        return (Vec2) getVel(id);
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void move(int id, float x, float y);

    private static native void setVel(int id, float vx, float vy);

    private static native Object getVel(int id);

    private static native void setAcceleration(int id, float ax, float ay);
}
