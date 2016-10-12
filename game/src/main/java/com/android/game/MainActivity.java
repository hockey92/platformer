/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.game;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity {

    GLSurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle icicle) {

        float[] vertices = {
                0.1f, 0.2f,
                -0.1f, 0.2f,
                -0.1f, -0.2f,
                0.1f, -0.2f
        };

        PolygonShape main;
        PolygonShape prev = main = new PolygonShape(vertices);
        ScreenService.add(prev);

        for (int i = 0; i < 49; i++) {
            PolygonShape next = new PolygonShape(vertices);
            ScreenService.add(next);
            Joint joint = new Joint(3.14f / 2.0f, 0.2f, -3.14f / 2.0f, 0.2f);
            joint.setAngle(((i % 4 == 0) ? 1 : -1) * (3.14f - 0.2f));
            prev.addChildren(joint);
            joint.addChildren(next);
            prev = next;
        }

//        main.move(-8.0f, -4.0f);
        main.setAngle(0.4f);

        main.update();

        super.onCreate(icicle);
        World.getInstance().setMan(new Man());
        glSurfaceView = new MyGLSurfaceView(getApplication(), getWindowManager());
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                GameEngine.surfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                GameEngine.surfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                GameEngine.drawFrame();
            }
        });
        glSurfaceView.queueEvent(new Runnable() {
            @Override
            public void run() {

                Thread physicsThread = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        PhysicsService.start();
                        while (true) {
                            long time = System.currentTimeMillis();
//                            System.out.println("time physics " + (System.currentTimeMillis() - time));
                            try {

                                PhysicsService.nextFrame();

                                long timeToWait = 1000 / 60 - (System.currentTimeMillis() - time);

//                                System.out.println("time to wait " + timeToWait);

                                Thread.sleep(timeToWait <= 0 ? 2 : timeToWait);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                });
                physicsThread.setDaemon(true);
                physicsThread.start();

                GameEngine.init(getAssets());
            }
        });
        setContentView(glSurfaceView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
        glSurfaceView.queueEvent(new Runnable() {
            @Override
            public void run() {

            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
        glSurfaceView.queueEvent(new Runnable() {
            @Override
            public void run() {

            }
        });
    }
}
