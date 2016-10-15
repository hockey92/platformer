package com.android.game;

import com.google.gson.Gson;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by qwerty on 30.09.16.
 */
public class Man {

    Man(String json) {
        Gson gson = new Gson();
        Map<String, Object> map = new HashMap<>();
        map = (Map<String, Object>) gson.fromJson(json, map.getClass());

        Map<String, Object> shapeMap = (Map<String, Object>) map.get("shape");

        parseShape(shapeMap).update();
    }

    Shape parseShape(Map<String, Object> shapeMap) {
        Shape shape = null;

        String type = (String) shapeMap.get("type");

        switch (type) {
            case "RECTANGLE":
                shape = parseRectangle(shapeMap);
                ScreenService.add(shape);
                break;
        }

        List<Object> childrenList = (List<Object>) shapeMap.get("children");

        if (childrenList != null) {
            for (Object childMap : childrenList) {
                addChild(shape, (Map<String, Object>) childMap);
            }
        }

        return shape;
    }

    Shape parseRectangle(Map<String, Object> rectangleMap) {
        float w = Float.parseFloat((String) rectangleMap.get("w"));
        float h = Float.parseFloat((String) rectangleMap.get("h"));
        return ShapeFactory.createRectangle(w, h);
    }

    void addChild(Shape parentShape, Map<String, Object> childMap) {
        float parentR = Float.parseFloat((String) childMap.get("parentR"));
        float parentAngle = Float.parseFloat((String) childMap.get("parentAngle"));
        float childR = Float.parseFloat((String) childMap.get("childR"));
        float childAngle = Float.parseFloat((String) childMap.get("childAngle"));
        float angle = Float.parseFloat((String) childMap.get("angle"));

        Joint joint = ShapeFactory.createJoint(parentAngle, parentR, childAngle, childR);
        joint.setAngle(angle);

        parentShape.addChild(joint);

        Map<String, Object> shapeMap = (Map<String, Object>) childMap.get("shape");
        Shape child = parseShape(shapeMap);
        joint.addChild(child);
    }

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
