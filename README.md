# Aodai2026

## プロジェクトをコピーしてAodai2026を作る
1. etrobo_tr_ex3をコピーして、Aodai2026を作る
2. https://github.com/ETrobocon/etrobo/wiki/sim_ev3_lr_course_change を参考に左右コースの切り替えを組み込む
   * Aodai2026/app/LineTracer.h 22行目に追加
    ```
    #if defined(MAKE_RIGHT)
      static const int _LEFT = 0;
      #define _EDGE 1
    #else
      static const int _LEFT = 1;
      #define _EDGE -1
    #endif
    ```
    * Aodai2026/app/LineTracer.cpp 43行目を修正
    ```
    float turn = _EDGE * calcPropValue(diffReflection);
    ```
3. RamdomWalker を EntryWalker へ変更する
    * EntryWalker.h 変更箇所
      * 冒頭コメント
      * インクルードガード
      * クラス宣言
      * コンストラクタ名
    
    * EntryWalker.cpp 変更箇所
      *  インクルードファイル名
      *  定数名の一部
      *  メソッド名の一部
    
    * app.cpp 変更箇所
      * 11行目
        * ```#include "EntryWalker.h"```
      * 41行目
        * ```static EntryWalker *gEntryWalker;```
      * 71行目
        * ```gEntryWalker = new EntryWalker(gLineTracer,```
      * 99行目
        * ```delete gEntryWalker;```
      * 143行目
        * ```gEntryWalker->run();```
    * Makefile.inc 変更箇所 9行目
      * ```EntryWalker.o \```
  4. 動作確認
    * 左右コースの切り替えができるか、エラーがないか確認
       * ```make left app=Aodai2026 sim up```
       * ```make right app=Aodai2026 sim up```

## PidController クラス追加
1. Aodai2026/unit/フォルダに以下の2ファイル新規追加
  * PidController.h
  * PidController.cpp
### PidController.h
  
  1. インクルードガード追加

    /**
     * PidController.h
     */
    
    #ifndef ETTR_APP_PIDCONTROLLER_H_
    #define ETTR_APP_PIDCONTROLLER_H_
    
    #endif // ETTR_APP_PIDCONTROLLER_H_
  
  2. クラスブロック追加

    #ifndef ETTR_APP_PIDCONTROLLER_H_
    #define ETTR_APP_PIDCONTROLLER_H_
    
    class PidController
    {
    public:
    private:
    };
    
    #endif // ETTR_APP_PIDCONTROLLER_H_

  3. ```public``` なメンバ変数、関連端名、コンストラクタ、メソッド名を追加
    
    public:
      // pid.txt が存在しない場合に使うデフォルト値
      static const float DEFAULT_Kp;           // 比例ゲインのデフォルト値
      static const float DEFAULT_Ki;           // 積分ゲインのデフォルト値
      static const float DEFAULT_Kd;           // 微分ゲインのデフォルト値
      static const float DEFAULT_BIAS;         // バイアスのデフォルト値
      static const float PERIOD_SEC;           // 周期ハンドラの周期[s]のデフォルト値
      static const char *const PID_PARAM_FILE; // PIDパラメータ設定ファイル名
      
      // コンストラクタ
      PidController();
      
      // 積分項や前回偏差などの内部状態をリセットする
      void reset();

      // 偏差からPID制御量を計算する
      float calcValue(int diffReflection);

  4. ```private``` なメンバ変数、関連端名、メソッド名を追加

    private:
      float mKp;   // 比例ゲイン
      float mKi;   // 積分ゲイン
      float mKd;   // 微分ゲイン
      float mBias; // バイアス
      
      float mIntegral;         // 積分項の値
      int mPrevDiffReflection; // 前回の偏差値
      
      void loadPidParams(); // PIDパラメータをファイルから読み込む
    };
### PidController.cpp
1. PidControllerクラスのヘッダーファイルのインクルード
  ```
  #include "PidController.h"
  ```
2. その他のヘッダファイルのインクルード
  ```
  #include <cstdio>
  #include <cstring>
  ```
3. 定数宣言と初期値の追加
  ```
  #include "PidController.h"
  #include <cstdio>
  #include <cstring>
  
  // 定数宣言
  const float PidController::DEFAULT_Kp = 2.83;
  const float PidController::DEFAULT_Ki = 0.05;
  const float PidController::DEFAULT_Kd = 2.50;
  const float PidController::DEFAULT_BIAS = 0;
  // CYC_TRACER(app.cfg)の周期と合わせること
  const float PidController::PERIOD_SEC = 0.01;
  // 実行時のカレントディレクトリ（workspaceディレクトリ）に置く
  const char *const PidController::PID_PARAM_FILE = "pid.txt";
  ```
4. コンストラクタの定義
  ```
  /**
   * コンストラクタ
   */
  PidController::PidController()
      : mKp(PidController::DEFAULT_Kp),
        mKi(PidController::DEFAULT_Ki),
        mKd(PidController::DEFAULT_Kd),
        mBias(PidController::DEFAULT_BIAS),
        mIntegral(0.0f),
        mPrevDiffReflection(0)
  {
    loadPidParams();
  }
  ```
5. メソッドの定義
  ```
  /**
   * PIDパラメータを外部ファイル（pid.txt）から読み込む
   * ファイルが無い、または項目が無い場合はデフォルト値のまま
   * ファイル書式（1行に1項目）:
   *   Kp=0.83
   *   Ki=0.02
   *   Kd=0.05
   *   bias=0
   */
  void PidController::loadPidParams() {
      FILE* fp = fopen(PidController::PID_PARAM_FILE, "r");
      if (fp == NULL) {
          printf("%s not found. use default PID parameters.\n",
                 PidController::PID_PARAM_FILE);
          return;
      }
  
      char line[64];
      while (fgets(line, sizeof(line), fp) != NULL) {
          char key[16];
          float value;
          if (sscanf(line, "%15[^=]=%f", key, &value) == 2) {
              if (strcmp(key, "Kp") == 0) {
                  mKp = value;
              } else if (strcmp(key, "Ki") == 0) {
                  mKi = value;
              } else if (strcmp(key, "Kd") == 0) {
                  mKd = value;
              } else if (strcmp(key, "bias") == 0) {
                  mBias = value;
              }
          }  
      }
      fclose(fp);
      
      printf("PID parameters loaded from %s: Kp=%f Ki=%f Kd=%f bias=%f\n",
             PidController::PID_PARAM_FILE, mKp, mKi, mKd, mBias);
  }

  /**
   * 積分項や前回偏差などの内部状態をリセットする
   */
  void PidController::reset() {
      mIntegral = 0.0f;
      mPrevDiffReflection = 0;
  }
  
  /**
   * 偏差からPID制御量を計算する
   * @param diffReflection ラインから外れた度合い（ライン閾値との差）
   */
  float PidController::calcValue(int diffReflection) {
      // P項
      float pTerm = mKp * diffReflection;
      
      // I項（誤差の積分）
      mIntegral += diffReflection * PidController::PERIOD_SEC;
      float iTerm = mKi * mIntegral;
      
      // D項（誤差の変化率）
      float derivative = (diffReflection - mPrevDiffReflection) / PidController::PERIOD_SEC;
      float dTerm = mKd * derivative;
      
      mPrevDiffReflection = diffReflection;
      
      float turn = pTerm + iTerm + dTerm + mBias;
      
      return turn;
  }
   ```
### app.cfg
1. 追加
```
APPL_CXXOBJS += \
	Walker.o \
	LineTracer.o \
	Scenario.o \
	ScenarioTracer.o \
	EntryWalker.o \
	LineMonitor.o \
	Starter.o \
	SimpleTimer.o \
	PidController.o
```

### app/LineTracer.h
1. 追加　15行目
```
#include "LineMonitor.h"
#include "Walker.h"
#include "PidController.h"
```

2. 追加 40行目
```
private:
    const LineMonitor *mLineMonitor;
    Walker *mWalker;
    bool mIsInitialized;

    PidController mPidController;

    float calcPropValue(int diffReflection);
```

### app/LineTracer.cpp
1. コンストラクタの修正
```
LineTracer::LineTracer(const LineMonitor *lineMonitor, Walker *walker)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mIsInitialized(false),
      mPidController()
{
}
```
2. run()修正
```
/**
 * ライントレースする
 */
void LineTracer::run()
{
    if (mIsInitialized == false)
    {
        mWalker->init();
        mIsInitialized = true;
        mPidController.reset();  //修正
    }

    int diffReflection = mLineMonitor->calDiffReflection();

    // 走行体の操作量を計算する
   	float turn = _EDGE * mPidController.calcValue(diffReflection);  //修正
    mWalker->setCommand(turn);

    // 走行を行う
    mWalker->run();
}
```
3. pid.txt 新規追加
  ＊ 追加するフォルダ  simdist/Aodai2026/_ev3rtfs/pid.txt
```
Kp=1.60
Ki=0.000
Kd=2.250
bias=0
```
4. 動作確認
  * pid.txt の各パラメータを読み取り、実行時に表示するかどうか
  * PID制御を使ったライントレースをするかどうか

## 状態遷移を変更する
### app/EntryWalker.h 変更

1. 状態```STOP```の追加　24行目
```
private:
    enum State
    {
        UNDEFINED,
        WAITING_FOR_START,
        LINE_TRACING,
        SCENARIO_TRACING,
        STOP
    };
```
2. 状態```STOP```のメソッドを追加 49行目付近
```
    void execStop();
```
### app/EntryWalker.cpp 変更
1. ヘッダファイルの追加 14行目
```
#include "etroboc_ext.h"
```
2. run() 修正
```
void EntryWalker::run()
{
    switch (mState)
    {
    case UNDEFINED:
        execUndefined();
        break;
    case WAITING_FOR_START:
        execWaitingForStart();
        break;
    case LINE_TRACING:
        execLineTracing();
        break;
    case SCENARIO_TRACING:
        execScenarioTracing();
        break;
    case STOP:
        execStop();
        break;
    default:
        break;
    }
}
```
3. 


