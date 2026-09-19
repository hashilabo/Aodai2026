#pragma once

/// 1次IIRローパスフィルタ（指数移動平均型）
///
/// センサ値やPID微分項のノイズ除去に使用する。
/// カットオフ周波数とサンプリング周期（制御周期）から
/// 平滑化係数(alpha)を自動算出する。
///
/// y[n] = alpha * x[n] + (1 - alpha) * y[n-1]

class LowPassFilter {
public:
    /// @param cutoffFreqHz  カットオフ周波数 [Hz]
    /// @param sampleTimeSec サンプリング周期 [s]（制御周期と一致させること）
    LowPassFilter(float cutoffFreqHz, float sampleTimeSec);

    /// フィルタ処理を1ステップ進め、平滑化された値を返す
    float update(float input);

    /// 内部状態を指定値でリセットする（起動直後の飛びつき防止）
    void reset(float initialValue = 0.0);

    /// 現在のフィルタ出力を取得する（updateを呼ばずに参照のみ）
    double getValue() const { return mOutput; }

private:
    float mAlpha;        // 平滑化係数 [0,1]。大きいほど追従性が高くノイズ除去効果は弱まる
    float mOutput;       // フィルタ出力（内部状態）
    bool mInitialized;   // 初回update呼び出しの判定フラグ
};
