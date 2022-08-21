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
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	//�V���O���g���C���X�^���X���擾����
	textureHandle_ = TextureManager::Load("mario.jpg");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();//���[���h�ϊ��̏�����
	myMath_ = new MyMath();
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

		//���W�ړ��i�x�N�g���̉��Z�j
		worldTransform_.translation_ += move;
		//�ړ����E���W
		const float kMoveLimitX = 35;
		const float kMoveLimitY = 20;
		//�͈͂𒴂��Ȃ�����
		worldTransform_.translation_.x = myMath_->MaxNum(worldTransform_.translation_.x, -kMoveLimitX);
		worldTransform_.translation_.x = myMath_->MinNum(worldTransform_.translation_.x, +kMoveLimitX);
		worldTransform_.translation_.y = myMath_->MaxNum(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = myMath_->MinNum(worldTransform_.translation_.y, +kMoveLimitY);

		//�L�����N�^�[�̍��W����ʕ\�����鏈��
		vectorMove_->MyUpdate(worldTransform_);
	}
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}