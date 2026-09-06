# Aodai2026

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
