# 反復型開発 2巡目

## 要求
* 最上位クラスの名前を変更する ```RamdomWalker``` -> ```EntryWalker```

## 設計
* EntryWalker
    ![EntryWalker クラス](iter02_class.png)

    * クラス名の変更    ```RandomWalker``` -> ```EntryWalker```
        * メソッド名の一部を変更
    * 状態名の追加
        * ```GARAGE```  ガレージ走行中
        * ```STOP```    停止中
    * private メソッドの追加
        * ```execGarage()``` ガレージ走行中の処理
        * ```execStop()```   停止中の処理

## 実装
* ```RandomWalker.h```と```RandomWalker.cpp```をコピーして、```EntryWalker.h```と```EntryWalker.cpp```を作る
```
    $ cd workspace/Aodai2026/app
    $ cp RandomWalker.h EntryWalker.h
    $ cp RandomWalker.cpp EntryWalker.cpp
    $ cd ../../..
```
### EntryWalker.h
* インクルードガードのマクロ名を変更
```
#ifndef ETTR_APP_ENTRYWALKER_H_
#define ETTR_APP_ENTRYWALKER_H_
(途中省略)
#endif  // ETTR_APP_ENTRYWALKER_H_
```
* クラス名を変更する
```
class EntryWalker {
```
* ```RandomWalker``` , ```RANDOMWALKER``` を右クリックし、すべての出現箇所を変更を選択し、```EntryWalker``` , ```ENTRYWALKER``` に変更する

### EntryWalker.cpp
* ```RandomWalker``` を右クリックし、すべての出現箇所を変更を選択し、```EntryWalker``` に変更する

### app.cpp
* 以下の修正
```
// オブジェクトの定義
static Walker          *gWalker;
static LineMonitor     *gLineMonitor;
static Starter         *gStarter;
static SimpleTimer     *gScenarioTimer;
static SimpleTimer     *gWalkerTimer;
static LineTracer      *gLineTracer;
static Scenario        *gScenario;
static ScenarioTracer  *gScenarioTracer;
static EntryWalker    *gEntryWalker;    // 修正
```

```
    // オブジェクトの作成
    gWalker          = new Walker(gLeftWheel,
                                  gRightWheel);
    gStarter         = new Starter(gForceSensor);
    gLineMonitor     = new LineMonitor(gColorSensor);
    gScenarioTimer   = new SimpleTimer(gClock);
    gWalkerTimer     = new SimpleTimer(gClock);
    gLineTracer      = new LineTracer(gLineMonitor, gWalker);
    gScenario        = new Scenario(0);
    gScenarioTracer  = new ScenarioTracer(gWalker,
                                          gScenario,
                                          gScenarioTimer);
    gEntryWalker    = new EntryWalker(gLineTracer,  //修正
                                        gScenarioTracer,
                                        gStarter,
                                        gWalkerTimer);
```

```
/**
* システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.stop();
    gRightWheel.stop();
    gLeftWheel.resetCount();
    gRightWheel.resetCount();

    delete gEntryWalker;    //修正
```

```
/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
  Button button;
  
	if (button.isLeftPressed()) {
	    wup_tsk(MAIN_TASK);  // レフトボタン押下
    } else {
        gEntryWalker->run();  // 走行 修正
    }

    ext_tsk();
}

```


### Makefile.inc
* 以下の修正
```
APPL_CXXOBJS += \
	Walker.o \
	LineTracer.o \
	Scenario.o \
	ScenarioTracer.o \
	EntryWalker.o \
	LineMonitor.o \
	Starter.o \
	SimpleTimer.o 
```

## 検証
* シミュレータを起動し、動作確認する
```
    $ make app=Aodai2026 sim up
```
* 確認事項
    * エラーチェック

