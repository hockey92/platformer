package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class PolygonShape extends Shape {
    protected PolygonShape(float[] vertices) {
        super(createPolygon(vertices));
    }

    private static native int createPolygon(float[] vertices);
}
