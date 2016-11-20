package com.android.game;

/**
 * Created by qwerty on 16.10.16.
 */
public class PhysicsObjectsFactory {

    public static PhysicsObject createRectangle(float w, float h, float d, float invM) {
        return new PhysicsObject(
                ShapeFactory.createRectangle(w, h, d), invM, 12.0f * invM / (w * w + h * h));
    }

}
