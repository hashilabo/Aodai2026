/******************************************************************************
 *  app.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"
#include "EntryWalker.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
//void *__dso_handle=0;

#include "Light.h"
#include "Button.h"
#include "Display.h"

// using宣言
using namespace spikeapi;


// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(EPort::PORT_E);
ForceSensor gForceSensor(EPort::PORT_D);
Motor       gLeftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
Motor       gRightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
Clock       gClock;

// オブジェクトの定義
static Walker          *gWalker;
static LineMonitor     *gLineMonitor;
static ColorDetector   *gColorDetector;
static Starter         *gStarter;
static SimpleTimer     *gScenarioTimer;
static SimpleTimer     *gWalkerTimer;
static LineTracer      *gLineTracer;
static Scenario        *gScenario;
static ScenarioTracer  *gScenarioTracer;
static EntryWalker     *gEntryWalker;

// scene object
static Scene gScenes[] = {
    { GO_STRAIGHT,       500 * 1000, 0 },   // 直進0.5秒
    { STOP,              100 * 1000, 0 },   // 停止0.1秒
    { TURN_LEFT,         967 * 1000, 0 },   // 左旋回0.98秒
    { GO_STRAIGHT, 12 * 1000 * 1000, 0 },   // 直進12秒
    { STOP,         1 * 1000 * 1000, 0 },   // 停止1秒
    { BACKWARD,     3 * 1000 * 1000, 0 },   // 後退3秒
    { TURN_LEFT,         440 * 1000, 0 },   // 左前ターン0.44秒
    { GO_STRAIGHT,      7990 * 1000, 0 },   // 前進8秒
    { TURN_LEFT,         570 * 1000, 0 },   // 左前ターン0.57秒
    { GO_STRAIGHT,      6750 * 1000, 0 },   // 前進7秒   
    { STOP,         1 * 1000 * 1000, 0 },   // 停止1秒
    { FINISH,      10 * 1000 * 1000, 0 },   // 完全停止10秒
};

/**
 * システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2U * 1000U);

    // オブジェクトの作成
    gWalker          = new Walker(gLeftWheel,
                                  gRightWheel);
    gStarter         = new Starter(gForceSensor);
    gLineMonitor     = new LineMonitor(gColorSensor, 20.0f, 0.01f);
    gScenarioTimer   = new SimpleTimer(gClock);
    gWalkerTimer     = new SimpleTimer(gClock);
    gLineTracer      = new LineTracer(gLineMonitor, gWalker);
    gScenario        = new Scenario(0);
    gScenarioTracer  = new ScenarioTracer(gWalker,
                                          gScenario,
                                          gScenarioTimer);
    gColorDetector   = new ColorDetector(gColorSensor);
    gEntryWalker    = new EntryWalker(gLineTracer,
                                      gScenarioTracer,
                                      gStarter,
                                      gWalkerTimer,
                                      gColorDetector);

    // シナリオを構築する
    for (uint32_t i = 0; i < (sizeof(gScenes)/sizeof(gScenes[0])); i++) {
        gScenario->add(&gScenes[i]);
    }
    
	// 初期化完了通知
    Display display;
    display.showText("test",500,0);
	Light light;
    light.turnOnColor(Light::EColor::ORANGE);
}

/**
* システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.stop();
    gRightWheel.stop();
    gLeftWheel.resetCount();
    gRightWheel.resetCount();

    delete gEntryWalker;
    delete gScenarioTracer;
    delete gScenario;
    delete gLineTracer;
    delete gWalkerTimer;
    delete gScenarioTimer;
    delete gLineMonitor;
    delete gColorDetector;
    delete gStarter;
    delete gWalker;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    sta_cyc(CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    stp_cyc(CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
  Button button;
  
	if (button.isLeftPressed()) {
	    wup_tsk(MAIN_TASK);  // レフトボタン押下
    } else {
        gEntryWalker->run();  // 走行
    }

    ext_tsk();
}
