package com.android.game;

/**
 * Created by qwerty on 30.10.16.
 */
public class StickButton {

    private Vec2 pushPosition = null;
    private Shape circle = ShapeFactory.createRectangle(2, 2, "circle1.tga").setVisible(false);
    private Shape point = ShapeFactory.createRectangle(0.5f, 0.5f, "circle.tga").setVisible(false);

    public StickButton() {
        ScreenService.add(circle);
        ScreenService.add(point);
    }

    public void push(Vec2 position) {
        position = ScreenService.convertToGameCoordinates(position);
        if (circle.containsPoint(position)) {
            this.pushPosition = position;
            circle.setCenter(position);
            circle.setVisible(true);
            point.setCenter(position);
            point.setVisible(true);
        }
    }

    public void move(Vec2 position) {
        if (pushPosition == null) return;

        position = ScreenService.convertToGameCoordinates(position);

        float dx = position.x - pushPosition.x;
        float dy = position.y - pushPosition.y;

        float dist = (float) Math.sqrt(dx * dx + dy * dy);
        if (dist > 1.f) {
            float c = 1.f / dist;
            dx = dx * c;
            dy = dy * c;
        }

        point.setCenter(new Vec2(
                pushPosition.x + dx,
                pushPosition.y + dy
        ));
    }

    public void release() {
        this.pushPosition = null;
        circle.setVisible(false);
        point.setVisible(false);
    }
}
