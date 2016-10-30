package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class PolygonShape extends Shape {
    public PolygonShape(float[] vertices) {
        super(createPolygon(vertices));
    }

    public PolygonShape(float[] vertices, String tgaFileName) {
        super(createPolygonWithTexture(vertices, tgaFileName));
    }

    private static native int createPolygon(float[] vertices);

    private static native int createPolygonWithTexture(float[] vertices, String tgaFileName);
}
