#pragma once
#include "Model.h"
#include "DebugText.h"
#include "VectorMove.h"
enum class Phase {
	Approch,//接近する
	Leave,//離脱する
};
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle);
	void Move();
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void ApprochMove();
	void LeaveMove();
private:
	WorldTransform worldTransform_;//ワールド変換データ

	Model* model_ = nullptr;//モデル

	uint32_t textureHandle_ = 0u;//テクスチャハンドル

	VectorMove* vectorMove_ = nullptr;
    //フェーズ
	Phase phase_ = Phase::Approch;
};

