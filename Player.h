#pragma once
#include "WorldTransform.h"
#include "DebugText.h"
#include "Input.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "TextureManager.h"
#include "VectorMove.h"
#include "MyMath.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
class Player
{
public:
	Player();//�R���X�g���N�^�[
	~Player();//�f�X�g���N�^�[
	void Rotate();
	void Initialize(Model*model,uint32_t textureHandle);//������
	void Update();
	void Draw(ViewProjection&viewProjection);
	void Attack();
private:
	WorldTransform worldTransform_;//���[���h�ϊ��f�[�^
	Model* model_ = nullptr;//���f��
	uint32_t textureHandle_ = 0u;//�e�N�X�`���n���h��
	Input* input_ = nullptr;//���͏��������邽��
	DebugText* debugText_ = nullptr;//�f�o�b�O�e�L�X�g
	MyMath* myMath_ = nullptr;//����̐��w�֐�
	VectorMove* vectorMove_ = nullptr;//�s��̌v�Z
	//std::list<std::unique_ptr<PlayerBullet>>playerBullets_;//���e�̃��j�[�N�|�C���^�[
	PlayerBullet* playerBullet_ = nullptr;//�e
};

