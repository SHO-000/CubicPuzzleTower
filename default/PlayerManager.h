//---------------------------------------------------------------
// �v���C���[�}�l�[�W���[�N���X
//---------------------------------------------------------------
#pragma once
#include "PlayerControll.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Init();	// ������
	void Update();	// �X�V
	void Draw();	// �`��

	VECTOR GetPlayerPos(){ return p_playerControll->GetPos(); }				// �|�W�V�����̃Q�b�g�֐�
	bool GetIsGround() { return p_playerControll->GetIsGround(); }			// ���n�t���O�̃Q�b�g�֐�
	void SetFloorPos(VECTOR v) { p_playerControll->SetFloorPos(v); }		// ���̃|�W�V�����̃Z�b�g�֐�
	void SetIsCanMove(bool flag) { p_playerControll->SetIsCanMove(flag); }	// ������t���O�̃Z�b�g�֐�

private:
	PlayerControll *p_playerControll;		// �v���C���[�R���g���[���N���X�̃|�C���^�[
};

