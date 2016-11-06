package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class ScreenService {

    private static Vec2 realSize = null;
    private static Vec2 gameCoords = null;
    private static float scale = 10.0f;

    public static Vec2 getRealSize() {
        return realSize;
    }

    public static native void surfaceCreated();

    public static void surfaceChanged(int width, int height) {
        surfaceChangedNative(width, height);
        realSize = new Vec2(width, height);
    }

    public static native void drawFrame();

    public static Vec2 convertToGameCoordinates(Vec2 vec) {

        float x = vec.x;
        float y = vec.y;

        float rel = realSize.x / realSize.y;

        return new Vec2(
                -1.f * scale + x / realSize.x * 2.f * scale,
                1.f * scale / rel - y / realSize.y * 2.f * scale / rel
        );
    }

    public static void add(Shape shape) {
        add(shape.getId());
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void add(int id);

    private static native void surfaceChangedNative(int width, int height);
}
