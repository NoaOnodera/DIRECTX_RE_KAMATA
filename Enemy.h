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
	WorldTransform worldTransform_;//ワールド変換データ

	Model* model_ = nullptr;//モデル

	uint32_t textureHandle_ = 0u;//テクスチャハンドル

	VectorMove* vectorMove_ = nullptr;
};

