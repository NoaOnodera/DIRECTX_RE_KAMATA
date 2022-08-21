#include "GameScene.h"
#include <cassert>
#include"Player.h"
#include"MyMath.h"

Player::Player() {

}

Player::~Player() {
	delete vectorMove_;
	delete myMath_;
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	//シングルトンインスタンスを取得する
	textureHandle_ = TextureManager::Load("mario.jpg");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();//ワールド変換の初期化
	myMath_ = new MyMath();
}

void Player::Rotate() {
	const float kRotateSpeed = 0.05f;
	if (input_->PushKey(DIK_Q)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	}
	else if (input_->PushKey(DIK_E)) {
		worldTransform_.rotation_.y += kRotateSpeed;
	}
}
void Player::Update() {
	{
		Vector3 move = { 0,0,0 };

		const float kCharacterSpeed = 0.2f;


		if (input_->PushKey(DIK_A)) {
			move = { -kCharacterSpeed, 0, 0 };

		}
		else if (input_->PushKey(DIK_D)) {
			move = { kCharacterSpeed, 0, 0 };
		}
		else if (input_->PushKey(DIK_W)) {
			move = { 0, kCharacterSpeed, 0 };
		}
		else if (input_->PushKey(DIK_S)) {
			move = { 0, -kCharacterSpeed, 0 };
		}

		//座標移動（ベクトルの加算）
		worldTransform_.translation_ += move;
		//移動限界座標
		const float kMoveLimitX = 35;
		const float kMoveLimitY = 20;
		//範囲を超えない処理
		worldTransform_.translation_.x = myMath_->MaxNum(worldTransform_.translation_.x, -kMoveLimitX);
		worldTransform_.translation_.x = myMath_->MinNum(worldTransform_.translation_.x, +kMoveLimitX);
		worldTransform_.translation_.y = myMath_->MaxNum(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = myMath_->MinNum(worldTransform_.translation_.y, +kMoveLimitY);

		//キャラクターの座標を画面表示する処理
		vectorMove_->MyUpdate(worldTransform_);
	    
		Rotate();

		Attack();//キャラクターの攻撃処理

		if (playerBullet_) {
			playerBullet_->Update();
		}
	}
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//弾描画
	if (playerBullet_) {
	    playerBullet_->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE))
	{
		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();



		newBullet->Initialize(model_, worldTransform_.translation_);

		//弾を登録する
		playerBullet_ = newBullet;
	}
}