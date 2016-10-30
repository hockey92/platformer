package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class ScreenService {

    public static native void surfaceCreated();

    public static native void surfaceChanged(int width, int height);

    public static native void drawFrame();

    public static native Vec2 convertToGameCoordinates(float x, float y);

    public static Vec2 convertToGameCoordinates(Vec2 vec) {
        return convertToGameCoordinates(vec.x, vec.y);
    }

    public static void add(Shape shape) {
        add(shape.getId());
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void add(int id);
}
