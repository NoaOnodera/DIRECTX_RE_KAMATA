#include "Enemy.h"
#include <cassert>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t texureHandle) {
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	this->model_ = model;
	textureHandle_ = TextureManager::Load("player_shade.jpg");
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
}

void Enemy::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();
}

void Enemy::LeaveMove() {
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { -kCharacterSpeed,-kCharacterSpeed,0 };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();
}

void Enemy::ApprochMove() {
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();

	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Update() {
	switch (phase_) {
	case Phase::Approch:
	default:
		//規定の位置に到達したら離脱
		ApprochMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}