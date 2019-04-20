//---------------------------------------------------------------
// �v���C���[�R���g���[���N���X
//---------------------------------------------------------------
#include "PlayerControll.h"
#include "InputInfo.h"
#include "Sound.h"
#include <math.h>

//---------------------
// �R���X�g���N�^
//---------------------
PlayerControll::PlayerControll()
{
	// �R�c���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("data/model/slime.mqo");

	m_pos = VGet(0, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_scale = VGet(0, 0, 0);
	m_floorPos = VGet(0, 0, 0);
	m_prevPos = VGet(0, 0, 0);
	m_shotVec = VGet(0, 0, 0);
}

//---------------------
// �f�X�g���N�^
//---------------------
PlayerControll::~PlayerControll()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_modelHandle);
}

//---------------------
// ������
//---------------------
void PlayerControll::Init()
{
	// �e�ϐ�������
	m_pos = VGet(0.f, -150.f, 120.f);
	m_velocity = VGet(0.f, 0.f, 0.f);
	m_scale = VGet(1.f, 1.f, 1.f);
	m_prevPos = VGet(0, 0, 0);
	m_shotVec = VGet(0, 0, 0);
	m_returnVec = VGet(0, 0, 0);

	m_angleY = 0.f;
	m_moveSpeed = 3.5f;
	m_grabity = 0.3f;
	m_jumpAccel = 4.f;
	m_radius = 12.f;

	m_isCanMove = false;
	m_isGround = false;
	m_isMove = false;
	m_isJump = false;
	m_isShot = false;
	m_isReturn = false;

	m_moveCnt = 0;
}

//---------------------
// �X�V
//---------------------
void PlayerControll::Update()
{
	// ���n
	CheckGround();

	if (m_isCanMove)
	{
		// �ړ�
		MovePlayer();
	}
}

//---------------------
// �`��
//---------------------
void PlayerControll::Draw()
{
	// �R�c���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// �R�c���f���̉�]�p�ݒ�
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angleY / 180.0f * DX_PI_F, 0.0f));

	// �R�c���f���̊g�嗦�ݒ�
	MV1SetScale(m_modelHandle, VGet(m_scale.x, m_scale.y, m_scale.z));

	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

}

//---------------------
// �֐��Q
//---------------------

// �ړ��Ǘ�����
void PlayerControll::MovePlayer()
{
	// �V���b�g�t���O��true�Ȃ�V���b�g����
	if (m_isShot)
	{
		Shot();
	}
	else
	{
		// �X�e�B�b�N��\���L�[�̓��͂��������珈���ɓ���
		if (GetJoyAxis().x != 0 || GetJoyAxis().y != 0)
		{
			m_isMove = true;
			m_moveCnt++;

			// �ړ��x�N�g�����X�V
			UpdateVelocity();

			// ��]�p���v�Z
			CalculateAngleY(GetJoyAxis().x, -GetJoyAxis().y);

			// �|�W�V�����Ɉړ��x�N�g�������Z
			m_pos = VAdd(m_pos, m_velocity);
		}
		// ���͂��Ȃ��ꍇ�͌������Œ肷��
		else
		{
			m_isMove = false;
			m_moveCnt = 0;

			// �����Œ菈��
			FixedDirection();
		}

		// �g�嗦�X�V
		CangeScale();

		// �����蔻�菈��
		DetectionCollision();
	}

	// �V���b�g�ł����ԂŃV���b�g�{�^���������ꂽ�猂��
	const bool isCanShot = !m_isMove && !m_isJump && !m_isShot;
	if (isCanShot && GetInput(SHOT) == PUSHDOWN)
	{
		m_isShot = true;
		m_prevPos = m_pos;
		playSound(SE_SHOT);
	}

	// �ړ��J�E���^���Q�O�𒴂�����W�����v����
	if (m_moveCnt > 15 && !m_isJump)
	{
		m_isJump = true;
		m_jumpVec = m_jumpAccel;
		playSound(SE_JUMP);
	}

	// �W�����v�i�ړ����I�[�g�W�����v�j
	if (m_isJump)
	{
		Jump();
	}
}

// ���n����
void PlayerControll::CheckGround()
{

	if (m_pos.y < m_floorPos.y)
	{
		m_pos.y = m_floorPos.y;
		m_isJump = false;
		m_isGround = true;
	}
	else if (m_isJump)
	{
		m_isGround = false;
	}
}

// �ړ��x�N�g���X�V����
void PlayerControll::UpdateVelocity()
{
	m_velocity.x = GetJoyAxis().x;
	m_velocity.z = GetJoyAxis().y;

	m_velocity = VNorm(m_velocity);

	m_shotVec = VScale(m_velocity, 3.f);
	m_velocity = VScale(m_velocity, m_moveSpeed);
}

// ��]�p�v�Z����
void PlayerControll::CalculateAngleY(float x, float y)
{
	VECTOR v = VGet(0, 0, 0);
	m_angleY = 0.f;
	v.x = x;
	v.z = y;
	v = VNorm(v);

	m_angleY = (float)atan2((double)v.z, (double)v.x) * 180.f / DX_PI_F;
	m_angleY -= 90.f;
}

// �����Œ菈��
void PlayerControll::FixedDirection()
{
	// ���݈ʒu�ɉ����Č������Œ肷��
	const bool inBack = m_pos.x > -105 && m_pos.x < 105 && m_pos.z < 0;	// ��O�ɂ���
	const bool inFront = m_pos.x > -105 && m_pos.x < 105 && m_pos.z > 0;// ���ɂ���
	const bool inLeft = m_pos.z > -105 && m_pos.z < 105 && m_pos.x < 0; // ���ɂ���
	const bool inRight = m_pos.z > -105 && m_pos.z < 105 && m_pos.x > 0;// �E�ɂ���
	if (inFront)
	{
		// ��O���������āA�V���b�g�x�N�g������O�����ɂ���
		m_angleY = 0.0f;
		m_shotVec = VGet(0, 0, -3);
	}
	if (inBack)
	{
		// �����������āA�V���b�g�x�N�g�����������ɂ���
		m_angleY = 180.0f;
		m_shotVec = VGet(0, 0, 3);
	}
	if (inLeft)
	{
		// �E���������āA�V���b�g�x�N�g�����E�����ɂ���
		m_angleY = -90.0f;
		m_shotVec = VGet(3, 0, 0);
	}
	if (inRight)
	{
		// �����������āA�V���b�g�x�N�g�����������ɂ���
		m_angleY = 90.0f;
		m_shotVec = VGet(-3, 0, 0);
	}
}

// �W�����v����
void PlayerControll::Jump()
{
	m_pos.y += m_jumpVec;
	m_jumpVec -= m_grabity;
}

// �X�P�[����ύX���ĂՂ�Ղ悳���鏈��
void PlayerControll::CangeScale()
{
	// ��ړ����ɂ͌��̑傫���ɖ߂�
	if (!m_isMove && !m_isJump)
	{
		if (m_scale.x != 1.f)
		{
			m_scale.x = 1.f;
			m_scale.y = 1.f;
			m_scale.z = 1.f;
		}
	}

	// �ړ����A�W�����v����܂ŏk�߂�
	if (m_isMove && !m_isJump)
	{
		m_scale.x += 0.01f;
		m_scale.y -= 0.01f;
		m_scale.z += 0.01f;
	}

	// �W�����v��
	if (m_isJump)
	{
		// ���n���O�ɑS�͂Œׂ�
		if (m_jumpVec < 0 && m_pos.y < m_floorPos.y + 5)
		{
			m_scale.x += 0.2f;
			m_scale.y -= 0.2f;
			m_scale.z += 0.2f;
		}
		// �����Ă���ԁA���������ɖ߂�
		else if (m_scale.y < 1.f)
		{
			m_scale.x -= 0.1f;
			m_scale.y += 0.1f;
			m_scale.z -= 0.1f;
		}
	}
}

// �V���b�g����
void PlayerControll::Shot()
{
	// ���̈ʒu���猻�݈ʒu�̋������擾
	float length = pow((m_pos.x - m_prevPos.x) * (m_pos.x - m_prevPos.x) +
					   (m_pos.y - m_prevPos.y) * (m_pos.y - m_prevPos.y) +
					   (m_pos.z - m_prevPos.z) * (m_pos.z - m_prevPos.z), 0.5);

	if (!m_isReturn && length >= 12.f)
	{
		m_isReturn = true;
		// �߂�p�x�N�g���ɃV���b�g�x�N�g���̔��Ε����̃x�N�g��������
		m_returnVec = VScale(m_shotVec, -1);
	}

	// ������0.1��菬�����Ȃ�����
	if (m_isReturn && length == 0.f)
	{
		m_isShot = false;
		m_isReturn = false;
		m_prevPos = VGet(0, 0, 0);
		m_returnVec = VGet(0, 0, 0);
	}

	if (m_isShot && !m_isReturn)
	{
		m_pos = VAdd(m_pos, m_shotVec);
	}
	else
	{
		m_pos = VAdd(m_pos, m_returnVec);
	}
}

// �����蔻��
void PlayerControll::DetectionCollision()
{
	// �}�X�ڂ̒��ɓ���Ȃ��悤�ɂ��锻��
	if (m_pos.x - m_radius < 105 && m_pos.x + m_radius > -105)
	{
		if (m_pos.z + m_radius > -110 && m_pos.z < 105)
			m_pos.z = -110 - m_radius;
		if (m_pos.z - m_radius < 110 && m_pos.z > -105)
			m_pos.z = 110 + m_radius;
	}
	if (m_pos.z - m_radius < 105 && m_pos.z + m_radius > -105)
	{
		if (m_pos.x + m_radius > -110 && m_pos.x < 105)
			m_pos.x = -110 - m_radius;
		if (m_pos.x - m_radius < 110 && m_pos.x > -105)
			m_pos.x = 110 + m_radius;
	}

	// ���ꂩ�痎���Ȃ��悤�ɂ��锻��
	if (m_pos.x - m_radius < -135)
		m_pos.x = -135 + m_radius;
	if (m_pos.x + m_radius > 135)
		m_pos.x = 135 - m_radius;
	if (m_pos.z - m_radius < -135)
		m_pos.z = -135 + m_radius;
	if (m_pos.z + m_radius > 135)
		m_pos.z = 135 - m_radius;
}