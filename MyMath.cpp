#include "MyMath.h"

MyMath::MyMath(){}//�R���X�g���N�^�[

MyMath::~MyMath(){}//�f�X�g���N�^�[

//�����o�֐�
float MyMath::MinNum(float min,float num) {
	//�����ŏ��l���傫���Ȃ�
	if (min < num){
		return min;//�ŏ��l��Ԃ�
	}
	//�����ŏ��l�ɂ�菬�����Ȃ�
	return num;//�ŏ��l��Ԃ�
}

float MyMath::MaxNum(float max, float num) {
	//�����ő�l��菬�����Ȃ�
	if (num < max) {
		return max;//�ő�l��Ԃ�
	}
	//�����ő�l���傫���Ȃ�
	return num;//�ő�l��Ԃ�
}

float Clamp(float min, float max, float num) {
	//�����ŏ��l���傫��
	if (min < num) {
		return min;//�ŏ��l��Ԃ�
	}
	//�����ő�l��菬��������
	if (num < max) {
		return max;//�ő�l��Ԃ�
	}
	//����ȊO�Ȃ�
	return num;//�l��Ԃ�
}