package com.android.game;

/**
 * Created by qwerty on 06.11.16.
 */
public interface IButton {
    void push(Vec2 pos, int id);

    void release(Vec2 pos, int id);

    void move(Vec2 pos, int id);
}
