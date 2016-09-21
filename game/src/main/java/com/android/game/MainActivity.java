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
        super.onCreate(icicle);
        glSurfaceView = new GLSurfaceView(getApplication());
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
                PhysicsService.add(new RectanglePhysicsObject(100.f, 1.f, 0.f).move(0.f, -20.f));
                PhysicsService.add(new RectanglePhysicsObject(5.f, 5.f, 1.f)
                        .move(-40.f, 0.f)
                        .setVel(10.f, 0.f));

                for (int i = 0; i < 4; i++) {
                    PhysicsService.add(new RectanglePhysicsObject(1.f, 10.f, 1.f)
                            .move(5.f, -14.5f + 11 * i));
                    PhysicsService.add(new RectanglePhysicsObject(1.f, 10.f, 1.f)
                            .move(15.f, -14.5f + 11 * i));
                    PhysicsService.add(new RectanglePhysicsObject(12.f, 1.f, 1.f)
                            .move(10.f, -9.f + 11 * i));
                }

                GameEngine.init(getAssets());
            }
        });
        setContentView(glSurfaceView);

        Thread physicsThread = new Thread(new Runnable() {
            @Override
            public void run() {
                PhysicsService.start();
                while (true) {
                    long time = System.currentTimeMillis();
                    PhysicsService.nextFrame();
                    System.out.println("time physics " + (System.currentTimeMillis() - time));
                    try {

                        long timeToWait = 20 - (System.currentTimeMillis() - time);

                        System.out.println("time to wait " + timeToWait);

                        Thread.sleep(timeToWait <= 0 ? 2 : timeToWait);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        physicsThread.setDaemon(true);
        physicsThread.start();
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