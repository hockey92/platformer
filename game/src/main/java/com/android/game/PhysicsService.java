package com.android.game;

/**
 * Created by qwerty on 20.09.16.
 */
public class PhysicsService {
    static {
        System.loadLibrary("accelerometergraph");
    }

    public static native void nextFrame();
    public static native void start();
    public static native void stop();

    private static native void add(int id);

    public static void add(PhysicsObject physicsObject) {
        add(physicsObject.getId());
    }
}
