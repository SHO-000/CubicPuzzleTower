//---------------------------------------------------------------
// �v���C���[�R���g���[���N���X
//---------------------------------------------------------------
#pragma once
#include "DxLib.h"

class PlayerControll
{
public:
	PlayerControll();
	~PlayerControll();

	void Init();	// ������
	void Update();	// �X�V
	void Draw();	// �`��

	const VECTOR& GetPos() const { return m_pos; }
	void SetFloorPos(VECTOR v) { m_floorPos = v; }
	bool GetIsGround() { return m_isGround; }
	void SetIsCanMove(bool flag) { m_isCanMove = flag; }

private:
	void MovePlayer();						// �ړ��Ǘ�����
	void CheckGround();						// ���n����
	void UpdateVelocity();					// �ړ��x�N�g���X�V����
	void CalculateAngleY(float x, float y);	// ��]�p�v�Z����
	void FixedDirection();					// �����Œ菈��
	void Jump();							// �W�����v����
	void CangeScale();						// �X�P�[����ύX���ĂՂ�Ղ悳���鏈��
	void Shot();							// �V���b�g����
	void DetectionCollision();				// �����蔻��

	int m_modelHandle;	// ���f���n���h��

	VECTOR m_pos;		// �|�W�V����
	VECTOR m_velocity;	// �ړ��x�N�g��
	VECTOR m_scale;		// �g�嗦
	VECTOR m_floorPos;	// ���̃|�W�V����
	VECTOR m_prevPos;	// ���̃|�W�V�����i�V���b�g���g�p�j
	VECTOR m_shotVec;	// �V���b�g���̃x�N�g��
	VECTOR m_returnVec;	// �V���b�g���̖߂�p�x�N�g��

	float m_angleY;		// Y���̉�]�p�x
	float m_moveSpeed;	// �ړ����x
	float m_grabity;	// �d��
	float m_jumpAccel;	// �W�����v�̏���
	float m_jumpVec;	// �W�����v���̍��W�X�V�p�ϐ�
	float m_radius;		// ���f���̔��a

	bool m_isCanMove;
	bool m_isGround;	// ���n�t���O
	bool m_isMove;		// �ړ����t���O
	bool m_isJump;		// �W�����v�t���O
	bool m_isShot;		// �V���b�g�t���O
	bool m_isReturn;	// �V���b�g���Ɍ��̈ʒu�ɖ߂邽�߂̃t���O

	int m_moveCnt;		// �ړ����̃J�E���^
};

