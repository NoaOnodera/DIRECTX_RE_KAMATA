#include "Enemy.h"
#include <cassert>

Enemy::Enemy() {

}

Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t texureHandle) {
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//NULL�|�C���^�`�F�b�N
	assert(model);
	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	textureHandle_ = TextureManager::Load("player_shade.jpg");
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = { 0,2,30 };
	worldTransform_.scale_ = { 1,1,1 };
}

void Enemy::Move() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	//�L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.1f;

	move = { 0,0,-kCharacterSpeed };

	worldTransform_.translation_ += move;

	vectorMove_->MyUpdate(worldTransform_);

	//�s��X�V
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Enemy::Update() {
	Move();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_,viewProjection,textureHandle_);
}