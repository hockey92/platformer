package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class PolygonShape extends Shape {
    public PolygonShape(float[] vertices, float d) {
        super(createPolygon(vertices, d));
    }

    public PolygonShape(float[] vertices, String tgaFileName) {
        super(createPolygonWithTexture(vertices, tgaFileName));
    }

    private static native int createPolygon(float[] vertices, float d);

    private static native int createPolygonWithTexture(float[] vertices, String tgaFileName);
}
