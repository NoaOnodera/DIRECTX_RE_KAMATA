#include "MyMath.h"

MyMath::MyMath(){}//コンストラクター

MyMath::~MyMath(){}//デストラクター

//メンバ関数
float MyMath::MinNum(float min,float num) {
	//もし最小値より大きいなら
	if (min < num){
		return min;//最小値を返す
	}
	//もし最小値により小さいなら
	return num;//最小値を返す
}

float MyMath::MaxNum(float max, float num) {
	//もし最大値より小さいなら
	if (num < max) {
		return max;//最大値を返す
	}
	//もし最大値より大きいなら
	return num;//最大値を返す
}

float Clamp(float min, float max, float num) {
	//もし最小値より大きい
	if (min < num) {
		return min;//最小値を返す
	}
	//もし最大値より小さいから
	if (num < max) {
		return max;//最大値を返す
	}
	//それ以外なら
	return num;//値を返す
}