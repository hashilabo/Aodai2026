/******************************************************************************
 *  Scene.h  (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Struct Scene
 *  Author: Kenya Yabe
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_SCENE_H_
#define ETTR_APP_SCENE_H_

enum SceneCommands {
    GO_STRAIGHT = 0,    // 直進
    TURN_LEFT,          // 左前ターン
    TURN_RIGHT,         // 右前ターン
    BACKWARD,           // 後退
    TURN_BACK_LEFT,     // 左後ターン
    TURN_BACK_RIGHT,    // 右後ターン
    STOP,               // 停止
    FINISH              // 完全停止
};

struct Scene {
    SceneCommands command;
    int           time;
    Scene*        next;
};

#endif  // ETTR_APP_SCENE_H_
