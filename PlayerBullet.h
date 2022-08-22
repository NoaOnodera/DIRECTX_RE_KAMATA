#pragma once
#include"Player.h"
#include "Model.h"
#include "Input.h" 
#include "WorldTransform.h"
#include "ViewProjection.h"
#include"TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);
	void Update();
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
private:
	WorldTransform worldTransform_;//ワールド変換データ
    
	Model* model_ = nullptr;//モデルのポインタ

	uint32_t textureHandle_ = 0u;//テクスチャハンドル
	
	Vector3 velocity_;//速度

	VectorMove* vectorMove_ = nullptr;

	static const int32_t kLifeTime = 60 * 5;//寿命

	int32_t deathTimer_ = kLifeTime;//デスタイマー

	bool isDead_ = FALSE;
};

