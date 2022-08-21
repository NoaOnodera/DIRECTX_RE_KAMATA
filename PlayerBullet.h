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
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);
private:
	WorldTransform worldTransform_;//ワールド変換データ
    
	Model* model_ = nullptr;//モデルのポインタ

	uint32_t textureHandle_ = 0u;//テクスチャハンドル
	
	VectorMove* vectorMove_ = nullptr;
};

