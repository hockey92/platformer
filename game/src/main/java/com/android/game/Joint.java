package com.android.game;

/**
 * Created by qwerty on 09.10.16.
 */
public class Joint extends Shape {
    protected Joint(float parentAngle, float parentR, float childAngle, float childR) {
        super(createJoint(parentAngle, parentR, childAngle, childR));
    }

    private static native int createJoint(float parentAngle, float parentR,
                                          float childAngle, float childR);
}
