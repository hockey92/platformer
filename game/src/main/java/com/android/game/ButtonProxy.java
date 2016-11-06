package com.android.game;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by qwerty on 06.11.16.
 */
public class ButtonProxy implements IButton {

    private List<IButton> buttons = new ArrayList<>();

    public void addButton(IButton button) {
        buttons.add(button);
    }

    @Override
    public void push(Vec2 pos, int id) {
        for (IButton button : buttons) {
            button.push(pos, id);
        }
    }

    @Override
    public void release(Vec2 pos, int id) {
        for (IButton button : buttons) {
            button.release(pos, id);
        }
    }

    @Override
    public void move(Vec2 pos, int id) {
        for (IButton button : buttons) {
            button.move(pos, id);
        }
    }
}
