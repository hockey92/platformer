package com.android.game;

/**
 * Created by qwerty on 30.09.16.
 */
public class Man {

    PhysicsObject po = new RectanglePO(0.5f, 1.0f, 1.f);

    public void runRight() {
        po.setAcceleration(40.f, 0.0f);
    }

    public void runLeft() {
        po.setAcceleration(-40.f, 0.0f);
    }

    public void stop() {
        Vec2 vel = po.getVel();
        po.setAcceleration(0.0f, 0.0f).setVel(0.0f, vel.second);
    }

    public void jump() {
        Vec2 vel = po.getVel();
        po.setVel(vel.first, 7.0f);
    }

    public PhysicsObject getPO() {
        return po;
    }
}
