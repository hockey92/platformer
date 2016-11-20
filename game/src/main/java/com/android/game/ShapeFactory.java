package com.android.game;

import com.google.gson.Gson;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by qwerty on 14.10.16.
 */
public class ShapeFactory {

    public static PolygonShape createRectangle(float w, float h, float d) {
        float halfW = w / 2.f;
        float halfH = h / 2.f;
        float[] vertices = {
                halfW, halfH,
                -halfW, halfH,
                -halfW, -halfH,
                halfW, -halfH
        };
        return new PolygonShape(vertices, d);
    }

    public static PolygonShape createRectangle(float w, float h, String fileName) {
        float halfW = w / 2.f;
        float halfH = h / 2.f;
        float[] vertices = {
                halfW, halfH,
                -halfW, halfH,
                -halfW, -halfH,
                halfW, -halfH
        };
        return new PolygonShape(vertices, fileName);
    }

    public static Joint createJoint(float parentAngle, float parentR, float childAngle, float childR) {
        return new Joint(parentAngle, parentR, childAngle, childR);
    }

    public static Shape createShapeFromJson(String json) {
        Gson gson = new Gson();
        Map<String, Object> jsonMap = new HashMap<>();
        jsonMap = (Map<String, Object>) gson.fromJson(json, jsonMap.getClass());
        Map<String, Object> shapeMap = (Map<String, Object>) jsonMap.get("shape");
        return parseShape(shapeMap);
    }

    private static Shape parseShape(Map<String, Object> shapeMap) {
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

    private static Shape parseRectangle(Map<String, Object> rectangleMap) {
        float w = parseFloat(rectangleMap, "w", 0.f);
        float h = parseFloat(rectangleMap, "h", 0.f);
        float d = parseFloat(rectangleMap, "d", 0.f);
        Shape shape = ShapeFactory.createRectangle(w, h, d);

        float z = parseFloat(rectangleMap, "z", 0.f);
        shape.setZ(z);
        return shape;
    }

    private static float parseFloat(Map<String, Object> rectangleMap, String name, float defaultValue) {
        String value = (String) rectangleMap.get(name);
        return value == null ? defaultValue : Float.parseFloat(value);
    }

    private static Float parseFloat(Map<String, Object> rectangleMap, String name) {
        String value = (String) rectangleMap.get(name);
        return value == null ? null : Float.parseFloat(value);
    }

    private static Joint parseJoint(Map<String, Object> jointMap) {
        float parentR = Float.parseFloat((String) jointMap.get("parentR"));
        float parentAngle = Float.parseFloat((String) jointMap.get("parentAngle"));
        float childR = Float.parseFloat((String) jointMap.get("childR"));
        float childAngle = Float.parseFloat((String) jointMap.get("childAngle"));
        float angle = Float.parseFloat((String) jointMap.get("angle"));

        Joint joint = ShapeFactory.createJoint(parentAngle, parentR, childAngle, childR);
        joint.setAngle(angle);

        String name = (String) jointMap.get("name");
        joint.setName(name);

        return joint;
    }

    private static void addChild(Shape parentShape, Map<String, Object> childMap) {
        Map<String, Object> jointMap = (Map<String, Object>) childMap.get("joint");
        Joint joint = parseJoint(jointMap);

        parentShape.addChild(joint);

        Map<String, Object> shapeMap = (Map<String, Object>) childMap.get("shape");

        Shape child = parseShape(shapeMap);
        joint.addChild(child);
    }
}
