package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class ScreenService {

    public static void add(PhysicsObject physicsObject) {
        add(physicsObject.getId());
    }

    public static void add(Shape shape) {
        add(shape.getId());
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void add(int id);
}
