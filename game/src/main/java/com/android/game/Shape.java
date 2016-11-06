package com.android.game;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by qwerty on 01.10.16.
 */
public class Shape {

    private int id;
    private String name;
    private List<Shape> children = new ArrayList<>();

    protected Shape(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public Shape move(float x, float y) {
        move(id, x, y);
        return this;
    }

    public Shape setCenter(float x, float y) {
        setCenter(id, x, y);
        return this;
    }

    public Shape setVisible(boolean visible) {
        setVisible(id, visible);
        return this;
    }

    public Shape setCenter(Vec2 v) {
        setCenter(id, v.x, v.y);
        return this;
    }

    public Vec2 getCenter() {
        return (Vec2) getCenter(id);
    }

    public void addChild(Shape shape) {
        addChild(id, shape.id);
        children.add(shape);
    }

    public List<Shape> getChildren() {
        return children;
    }

    public void update() {
        update(id);
    }

    public void setAngle(float angle) {
        setAngle(id, angle);
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public boolean containsPoint(Vec2 point) {
        return containsPoint(id, point.x, point.y);
    }

    static {
        System.loadLibrary("accelerometergraph");
    }

    private static native void move(int id, float x, float y);

    private static native void setCenter(int id, float x, float y);

    private static native void setVisible(int id, boolean visible);

    private static native Object getCenter(int id);

    private static native void addChild(int id, int childId);

    private static native void update(int id);

    private static native void setAngle(int id, float angle);

    private static native boolean containsPoint(int id, float x, float y);
}
