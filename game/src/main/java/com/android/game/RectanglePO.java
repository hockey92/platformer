package com.android.game;

/**
 * Created by qwerty on 22.09.16.
 */
public class RectanglePO extends PhysicsObject {

    public RectanglePO(float w, float h, float invM) {
        super(createCube(w, h, invM));
    }

    private static native int createCube(float w, float h, float invM);
}
