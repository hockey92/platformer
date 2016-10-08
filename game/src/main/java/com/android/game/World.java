package com.android.game;

/**
 * Created by qwerty on 30.09.16.
 */
public class World {

    private static World INSTANCE = null;

    private Man man;

    public static World getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new World();
        }
        return INSTANCE;
    }

    private World() {
//        PhysicsService.add(new RectanglePO(50.f, 1.0f, 0.f).move(0.f, -2.5f));
//        PhysicsService.add(new RectanglePO(2.5f, 2.5f, 0.f).move(-2.5f, -2.f));
//        PhysicsService.add(new RectanglePO(2.5f, 5.f, 0.f).move(-5.f, 0.f));
//
//        PhysicsService.add(new RectanglePO(1.0f, 1.f, 1.f).move(0.f, 25.f));
//        PhysicsService.add(new RectanglePO(1.0f, 1.f, 1.f).move(0.f, 20.f));
//        PhysicsService.add(new RectanglePO(1.0f, 1.0f, 1.f).move(0.f, 15.f));
//        PhysicsService.add(new RectanglePO(1.0f, 1.0f, 1.f).move(0.f, 10.f));
    }

    public void setMan(Man man) {
        this.man = man;
//        PhysicsService.add(man.getPO());
    }

    public Man getMan() {
        return man;
    }
}
