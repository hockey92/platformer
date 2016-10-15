package com.android.game;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.WindowManager;

/**
 * Created by qwerty on 30.09.16.
 */
public class MyGLSurfaceView extends GLSurfaceView {

    float downXPos;
    MoveType moveType = MoveType.STOP;
    WindowManager windowManager;

    int leftSidePointId = -1;
    int rightSidePointId = -1;

    public MyGLSurfaceView(Context context, WindowManager windowManager) {
        super(context);
        this.windowManager = windowManager;
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {

        DisplayMetrics metrics = new DisplayMetrics();
        windowManager.getDefaultDisplay().getMetrics(metrics);

        int height = metrics.heightPixels;
        int width = metrics.widthPixels;

        int currentIndex = e.getActionIndex();

        System.out.println("currentIndex = " + currentIndex);
        System.out.println("e.getAction() = " + e.getAction());

        float x = e.getX(currentIndex);
        float y = e.getY(currentIndex);

        switch (e.getActionMasked()) {
//            case MotionEvent.ACTION_DOWN:
//            case MotionEvent.ACTION_POINTER_DOWN:
//                if (x > width / 2) {
//                    if (rightSidePointId < 0) {
//                        World.getInstance().getMan().jump();
//                        rightSidePointId = currentIndex;
//                    }
//                } else {
//                    if (leftSidePointId < 0) {
//                        leftSidePointId = currentIndex;
//                        downXPos = x;
//                    }
//                }
//                break;
//            case MotionEvent.ACTION_UP:
//            case MotionEvent.ACTION_POINTER_UP:
//                if (leftSidePointId == currentIndex) {
//                    moveType = MoveType.STOP;
//                    World.getInstance().getMan().stop();
//                    leftSidePointId = -1;
//                } else if (rightSidePointId == currentIndex) {
//                    rightSidePointId = -1;
//                }
//                break;
//            case MotionEvent.ACTION_MOVE:
//                if (leftSidePointId == currentIndex) {
//                    if (downXPos - x > 20) {
//                        if (moveType == MoveType.RIGHT || moveType == MoveType.STOP) {
//                            World.getInstance().getMan().stop();
//                            World.getInstance().getMan().runLeft();
//                        }
//                        moveType = MoveType.LEFT;
//                    } else if (downXPos - x < 20) {
//                        if (moveType == MoveType.LEFT || moveType == MoveType.STOP) {
//                            World.getInstance().getMan().stop();
//                            World.getInstance().getMan().runRight();
//                        }
//                        moveType = MoveType.RIGHT;
//                    } else {
//                        moveType = MoveType.STOP;
//                        World.getInstance().getMan().stop();
//                    }
//                }
//                break;
        }
        return true;
    }

    static enum MoveType {
        LEFT, RIGHT, STOP
    }
}
