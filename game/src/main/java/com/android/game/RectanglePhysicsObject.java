package com.android.game;

/**
 * Created by qwerty on 22.09.16.
 */
public class RectanglePhysicsObject extends PhysicsObject {
    static {
        System.loadLibrary("accelerometergraph");
    }

    public RectanglePhysicsObject(float w, float h, float invM) {
        super(createCube(w, h, invM));
    }

    private static native int createCube(float w, float h, float invM);
}
