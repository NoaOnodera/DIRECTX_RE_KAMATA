#pragma once
//���삵�����w�N���X

class MyMath {
public:
	MyMath();//�R���X�g���N�^�[

	~MyMath();//�f�X�g���N�^�[

	//�����o�֐�

	float MinNum(float min,float num);
	float MaxNum(float min,float num);
	float Clamp(float min, float max, float num);
};