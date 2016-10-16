package com.android.game;

import com.google.gson.Gson;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * Created by qwerty on 15.10.16.
 */
public class Animation {

    private Map<String, Pair<Joint, Float[]>> nameToJointMap = new TreeMap<>();
    private int numberOfFrames;

    private float angleCoeff = 1.0f;

    public int numOfIterationsBetweenFrames = 100;
    public int currentIterationNumber = 0;
    public int currentFrameNumber = 0;

    public Animation(Shape shape, String animationJson) {

        Gson gson = new Gson();
        List<Map<String, Object>> jsonList = new ArrayList<>();
        jsonList = (List<Map<String, Object>>) gson.fromJson(animationJson, jsonList.getClass());
        this.numberOfFrames = jsonList.size();

        fillNameToJointMap(shape, nameToJointMap);

        for (Map<String, Object> frameMap : jsonList) {
            int frameNumber = Integer.valueOf((String) frameMap.get("frameNumber"));
            Map<String, Object> anglesMap = (Map<String, Object>) frameMap.get("angles");
            for (Map.Entry entry : anglesMap.entrySet()) {
                nameToJointMap.get(entry.getKey()).b[frameNumber] = Float.valueOf((String) entry.getValue());
            }
        }
    }

    public void nextFrame() {
        for (Pair<Joint, Float[]> pair : nameToJointMap.values()) {
            int size = pair.b.length;
            float newAngle = pair.b[currentFrameNumber] + ((pair.b[(currentFrameNumber + 1) % size] - pair.b[currentFrameNumber]) / (float) numOfIterationsBetweenFrames) * (float) currentIterationNumber;
            pair.a.setAngle(angleCoeff * newAngle);
            currentIterationNumber++;
            if (currentIterationNumber >= numOfIterationsBetweenFrames) {
                currentIterationNumber = 0;
                currentFrameNumber++;
                if (currentFrameNumber >= size) {
                    currentFrameNumber = 0;
                }
            }
        }
    }

    public void setAngleCoeff(float angleCoeff) {
        this.angleCoeff = angleCoeff;
    }

    private void fillNameToJointMap(Shape shape, Map<String, Pair<Joint, Float[]>> nameToJointMap) {
        for (Shape nextShape : shape.getChildren()) {
            if (nextShape instanceof Joint && nextShape.getName() != null) {
                nameToJointMap.put(nextShape.getName(), new Pair<>((Joint) nextShape, new Float[numberOfFrames]));
            }
            fillNameToJointMap(nextShape, nameToJointMap);
        }
    }
}
