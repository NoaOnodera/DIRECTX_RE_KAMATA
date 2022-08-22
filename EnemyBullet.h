#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "DebugText.h"



class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:
	WorldTransform worldTransform_;	//ワールド変換データ

	Model* model_ = nullptr;	//モデルのポインタ(借りてくる)
	
	uint32_t textureHandle_ = 0u;//テクスチャハンドル
	
	Vector3 velocity_;//速度

	DebugText* debugText_ = nullptr;

	VectorMove* vectorMove_ = nullptr;
	
	static const int32_t eLifeTime = 60 * 5; //寿命<frm>

	int32_t deathTimer_ = eLifeTime;	//デスタイマー

	
	bool isDead_ = false;	//デスフラグ

};

