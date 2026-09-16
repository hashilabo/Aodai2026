# 反復型開発 3巡目

## 要求
* 左右コースの自動切替を組み込む

## 設計
* 以下のURLを参考に、左右コースの切替を組み込む
    * https://github.com/ETrobocon/etrobo/wiki/sim_ev3_lr_course_change

## 実装

### ```LineTracer.h```
* クラスブロックのpublicに以下のコードを追加
```
/**
 * 左コース/右コース向けの設定を定義します
 * デフォルトは左コース(ラインの右エッジをトレース)です
 */
#if defined(MAKE_RIGHT)
    static const int _LEFT = 0;
    #define _EDGE 1
#else
    static const int _LEFT = 1;
    #define _EDGE -1
#endif　
 ```
### ```LineTracer.cpp```
* run() の以下の部分を修正
```
   float turn = _EDGE * calcPropValue(diffReflection);
```
## 検証

* 確認事項
    * 左コースを走行しLAPゲート側をライントレースしているか確認する
    ```
    make left app=Aodai2026 sim up
    ```
    * 右コースを走行しLAPゲート側をライントレースしているか確認する
    ```
    make right app=Aodai2026 sim up
    ```
    * ライントレースするエッジが逆サイドの場合、```_EDGE``` の符号を逆転する
