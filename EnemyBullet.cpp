#include "Enemy.h"
#include "EnemyBullet.h"
#include<cassert>

EnemyBullet::EnemyBullet() {

}


EnemyBullet::~EnemyBullet() {
	
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("enemyBullet.jpg");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();


	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//座標を移動させる(1フレーム分の移動力を足し込む)
	worldTransform_.translation_ += velocity_;
	//時間経過でdeath
	if (--deathTimer_ <= 0) {
		isDead_ = TRUE;
	}

}
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}