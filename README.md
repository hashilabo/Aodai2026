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
