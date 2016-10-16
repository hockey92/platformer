package com.android.game;

/**
 * Created by qwerty on 16.10.16.
 */
public class GameCharacter {
    private Shape animatedShape;
    private PhysicsObject rectangle;
    private Animation animation;

    public GameCharacter(String shapeJson, String animationJson) {
        animatedShape = ShapeFactory.createShapeFromJson(shapeJson);
        animatedShape.setAngle((-3.14f / 2.f) - 0.1f);

        animation = new Animation(animatedShape, animationJson);

        rectangle = new PhysicsObject(
                ShapeFactory.createRectangle(0.6f, 1.8f), 1, 0);

        PhysicsService.add(rectangle);
    }

    public void update() {
        animatedShape.setCenter(rectangle.getShape().getCenter());
        animatedShape.move(0, 0.35f);
        animation.nextFrame();
        animatedShape.update();
    }

    public void left() {
        rectangle.setAcceleration(-80, 0);
        animatedShape.setAngle((-3.14f / 2.f) + 0.1f);
        animation.setAngleCoeff(-1);
    }

    public void right() {
        rectangle.setAcceleration(80, 0);
        animatedShape.setAngle((-3.14f / 2.f) - 0.1f);
        animation.setAngleCoeff(1);
    }

    public void stop() {
        rectangle.setAcceleration(0, 0);
        rectangle.setVel(0, rectangle.getVel().y);
    }

    public void jump() {
        rectangle.setVel(rectangle.getVel().x, 7f);
    }
}
