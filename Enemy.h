#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "EnemyBullet.h"
#include <memory>
#include <list>

class Player;//プレイヤーの前方宣言

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
	void Fire();
	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision();
	Vector3 GetWorldPosition();
	Vector3 GetRadius();
    static const int kFireInterval = 60;//発射感覚
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return enemyBullets_; }
private:
	WorldTransform worldTransform_;//ワールド変換データ

	Model* model_ = nullptr;//モデル

	uint32_t textureHandle_ = 0u;//テクスチャハンドル

	DebugText* debugText_ = nullptr;//デバッグテキスト

	MyMath* myMath_ = nullptr;//数学関数

	int32_t eFireTime = 60;

	VectorMove* vectorMove_ = nullptr;
    //フェーズ
	Phase phase_ = Phase::Approch;

	Player* player_ = nullptr;

	std::list<std::unique_ptr<EnemyBullet>>enemyBullets_;

	EnemyBullet* enemyBullet_ = nullptr;
};

