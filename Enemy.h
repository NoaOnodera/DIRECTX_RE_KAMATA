#pragma once
#include "Model.h"
#include "DebugText.h"
#include "VectorMove.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle);
	void Move();
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	WorldTransform worldTransform_;//���[���h�ϊ��f�[�^

	Model* model_ = nullptr;//���f��

	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��

	VectorMove* vectorMove_ = nullptr;
};

