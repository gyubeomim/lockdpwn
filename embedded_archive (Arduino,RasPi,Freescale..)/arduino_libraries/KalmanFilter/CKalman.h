class CKalman
{
private:
	float Q;
    float R;
    float P;
    float X;
    float K;

 public:

    // 첫번째값을 입력받아 초기화 한다. 예전값들을 계산해서 현재값에 적용해야 하므로 반드시 하나이상의 값이 필요하므로~
    CKalman(float initValue)
    {
        X = initValue;
		Q = 0.00001f;
		R = 0.001f;
		P = 1.0f;
    }

	void Init(float v) {X = v;}

    // 예전값들을 공식으로 계산한다
    void measurementUpdate()
    {
        K = (P + Q) / (P + Q + R);
        P = R * (P + Q) / (P + Q + R);
    }


    // 현재값을 받아 계산된 공식을 적용하고 반환한다
    float update(float measurement)
    {
        measurementUpdate();
        X = X + (measurement - X) * K;
        return X;
    }
};
