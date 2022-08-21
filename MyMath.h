#pragma once
//自作した数学クラス

class MyMath {
public:
	MyMath();//コンストラクター

	~MyMath();//デストラクター

	//メンバ関数

	float MinNum(float min,float num);
	float MaxNum(float min,float num);
	float Clamp(float min, float max, float num);
};