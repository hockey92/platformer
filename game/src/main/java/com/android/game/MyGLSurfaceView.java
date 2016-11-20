package com.android.game;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.WindowManager;

/**
 * Created by qwerty on 30.09.16.
 */
public class MyGLSurfaceView extends GLSurfaceView {

    float downXPos;
    MoveType moveType = MoveType.STOP;
    WindowManager windowManager;
    GameCharacter gameCharacter;

    ButtonProxy buttons = new ButtonProxy();

    StickButton stickButton;

    int leftSidePointId = -1;
    int rightSidePointId = -1;

    public MyGLSurfaceView(Context context, WindowManager windowManager, GameCharacter gameCharacter) {
        super(context);
        this.windowManager = windowManager;
        this.gameCharacter = gameCharacter;

//        this.buttons.addButton(new StickButton());

        stickButton = new StickButton(gameCharacter);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {

        int pointerIndex = e.getActionIndex();
        int id = e.getPointerId(pointerIndex);

//        System.out.println("currentIndex = " + currentIndex);
//        System.out.println("e.getAction() = " + e.getAction());

        float x = e.getX(pointerIndex);
        float y = e.getY(pointerIndex);

        switch (e.getActionMasked()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
                stickButton.push(new Vec2(x, y), id);
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                stickButton.release(new Vec2(x, y), id);
                break;
            case MotionEvent.ACTION_MOVE:
                stickButton.move(new Vec2(x, y), id);
                break;
        }
        return true;
    }

    static enum MoveType {
        LEFT, RIGHT, STOP
    }
}
