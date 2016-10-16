package com.android.game;

/**
 * Created by qwerty on 16.10.16.
 */
public class PhysicsObjectsFactory {

    public static PhysicsObject createRectangle(float w, float h, float invM) {
        return new PhysicsObject(
                ShapeFactory.createRectangle(w, h), invM, 12.0f * invM / (w * w + h * h));
    }

}
