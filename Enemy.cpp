#include "Enemy.h"
#include <cassert>
#include "Player.h"
#include "VectorMove.h"

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

	debugText_ = DebugText::GetInstance();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	vectorMove_ = new VectorMove();

	myMath_ = new MyMath();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
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

	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& EnemyBullet) {
		return EnemyBullet->IsDead();
		});
	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	eFireTime--;//発射タイマーカウントダウン

	if (eFireTime == 0) {
		Fire();//弾を発射

		eFireTime = kFireInterval;//発射タイマーを初期化
	}

	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		if (EnemyBullet) {
			EnemyBullet->Update();
		}
	}


	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	//行列更新
	//行列の転送
	worldTransform_.TransferMatrix();
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
	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		EnemyBullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (std::unique_ptr<EnemyBullet>& EnemyBullet : enemyBullets_) {
		if (EnemyBullet) {
			EnemyBullet->Draw(viewProjection);
		}
	}
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;

}

void Enemy::Fire()
{
	assert(player_);
	//弾の速度
	const float eBulletSpeed = 0.01f;
	Vector3 playerVec = player_->GetWorldPosition();
	Vector3 enemyVec = GetWorldPosition();
	Vector3 Difference = playerVec;
	Difference -= enemyVec;
	Vector3 normalize(Difference);
	Difference *= eBulletSpeed;
	Vector3 velocity(Difference);

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//弾を登録する
	enemyBullets_.push_back(std::move(newBullet));
}