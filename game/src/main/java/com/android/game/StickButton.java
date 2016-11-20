package com.android.game;

/**
 * Created by qwerty on 30.10.16.
 */
public class StickButton extends Button {

    private Shape circle = ShapeFactory.createRectangle(2, 2, "circle1.tga").setVisible(false);
    private Shape point = ShapeFactory.createRectangle(0.5f, 0.5f, "circle.tga").setVisible(false);

    GameCharacter gameCharacter;

    public StickButton(GameCharacter gameCharacter) {
        ScreenService.add(circle);
        ScreenService.add(point);

        this.gameCharacter = gameCharacter;
    }

    @Override
    public void push(Vec2 pushPos, int id) {
        if (this.pos != null || pushPos.x > ScreenService.getRealSize().x / 2.0f) {
            return;
        }
        this.id = id;
        this.pos = ScreenService.convertToGameCoordinates(pushPos);
        renderButton();
    }

    @Override
    public void release(Vec2 releasePos, int id) {
        if (this.id != id) return;
        this.pos = null;
        circle.setVisible(false);
        point.setVisible(false);

        gameCharacter.stop();
    }

    @Override
    public void move(Vec2 movePos, int id) {
        if (this.pos == null || this.id != id) return;

        movePos = ScreenService.convertToGameCoordinates(movePos);

        float dx = movePos.x - this.pos.x;
        float dy = movePos.y - this.pos.y;

        float dist = (float) Math.sqrt(dx * dx + dy * dy);
        if (dist > 1.f) {
            float c = 1.f / dist;
            dx = dx * c;
            dy = dy * c;
        }

        point.setCenter(new Vec2(
                this.pos.x + dx,
                this.pos.y + dy
        ));

        if (dx > 0.1f) {
            gameCharacter.right();
        } else if (dx < 0.1f) {
            gameCharacter.left();
        } else {
            gameCharacter.stop();
        }
    }

    private void renderButton() {
        circle.setCenter(pos);
        circle.setVisible(true);
        point.setCenter(pos);
        point.setVisible(true);
    }
}
