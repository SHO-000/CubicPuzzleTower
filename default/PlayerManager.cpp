//---------------------------------------------------------------
// �v���C���[�}�l�[�W���[�N���X
//---------------------------------------------------------------
#include "PlayerManager.h"

//---------------------
// �R���X�g���N�^
//---------------------
PlayerManager::PlayerManager()
{
	p_playerControll = new PlayerControll();
}

//---------------------
// �f�X�g���N�^
//---------------------
PlayerManager::~PlayerManager()
{
	// �����Ȃ�
}

//---------------------
// ������
//---------------------
void PlayerManager::Init()
{
	p_playerControll->Init();
}

//---------------------
// �X�V
//---------------------
void PlayerManager::Update()
{
	p_playerControll->Update();
}

//---------------------
// �`��
//---------------------
void PlayerManager::Draw()
{
	p_playerControll->Draw();
}
