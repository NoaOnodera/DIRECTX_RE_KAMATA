#include "Enemy.h"
#include "EnemyBullet.h"
#include<cassert>

EnemyBullet::EnemyBullet() {

}


EnemyBullet::~EnemyBullet() {
	
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemyBullet.jpg");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	vectorMove_ = new VectorMove();


	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	vectorMove_->MyUpdate(worldTransform_);
	//���W���ړ�������(1�t���[�����̈ړ��͂𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂�death
	if (--deathTimer_ <= 0) {
		isDead_ = TRUE;
	}

}
void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}