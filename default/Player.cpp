//-----------------------------------------------------------------------------
// �v���C���[�N���X.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "Define.h"
#include <math.h>
#include "Inputkey.h"
#include "Scaffold.h"
#include "Cube.h"
#include "Sound.h"

#include "InputInfo.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�^.
//-----------------------------------------------------------------------------
Player::Player()
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("data/model/slime.mqo");

	pos = VGet(0.f, -150.f, 120.f);
	dir = dir_back;
	angleY = 0.f;
	speed = 3.5f;

	Key = 0;
	Input = 0;
	inputX = 0;
	inputY = 0;

	joypad_flag = true;

	move_flag = false;
	shot_flag = false;
	return_flag = false;
	jump_flag = false;
	g = 0.3f;
	jump_accel = 4.f;
	jump_vec = 0;
	margin = 12;

	shot_cnt = 0;
	move_cnt = 0;
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^.
//-----------------------------------------------------------------------------
Player::~Player()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(modelHandle);
}

void Player::Init()
{
	pos = VGet(0.f, -150.f, 120.f);
	vec = VGet(0, 0, 0);
	dir = dir_back;
	angleY = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
	jump_vec = 0.0f;
	
	move_flag = false;
	shot_flag = false;
	return_flag = false;
	jump_flag = false;
	input_once = false;

	shot_cnt = 0;
	move_cnt = 0;
}

void Player::VectorControll()
{
	vec = VNorm(vec);

	vec.x = vec.x * speed;
	vec.z = vec.z * speed;

	pos = VAdd(pos, vec);
}

//-----------------------------------------------------------------------------
// �X�V.
//-----------------------------------------------------------------------------
void Player::Update(const Cube& cube, const Scaf& scaf)
{
	if (getKey(KEY_INPUT_F1))
	{
		joypad_flag = true;
	}
	if (getKey(KEY_INPUT_F2))
	{
		joypad_flag = false;
	}

	if (!cube.clear_flag && pos.y >= -1)
	{
		if (joypad_flag)
		{
			Input = GetJoypadInputState(DX_INPUT_PAD1);
			GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

			if (!shot_flag)
			{
				if (GetJoyAxis().x != 0 || GetJoyAxis().y != 0)
				{
					/*vec.x = (float)inputX;
					vec.z = (float)-inputY;*/
					vec.x = GetJoyAxis().x;
					vec.z = GetJoyAxis().y;

					VectorControll();
					angleY = AngleCalculation((float)inputX, (float)inputY);
				}

				// �E��ɓ��͂��Ă�����E�΂ߏ�ɐi��
				if ((Input & PAD_INPUT_UP) && (Input & PAD_INPUT_RIGHT))
				{
					dir = dir_f_right;
					move_flag = true;
				}
				// ����ɓ��͂��Ă����獶�΂ߏ�ɐi��
				else if ((Input & PAD_INPUT_UP) && (Input & PAD_INPUT_LEFT))
				{
					dir = dir_f_left;
					move_flag = true;
				}
				// �E���ɓ��͂��Ă�����E�΂߉��ɐi��
				else if ((Input & PAD_INPUT_DOWN) && (Input & PAD_INPUT_RIGHT))
				{
					dir = dir_b_right;
					move_flag = true;
				}
				// �����ɓ��͂��Ă����獶�΂߉��ɐi��
				else if ((Input & PAD_INPUT_DOWN) && (Input & PAD_INPUT_LEFT))
				{
					dir = dir_b_left;
					move_flag = true;
				}
				// ��������Ă������ɐi��
				else if (Input & PAD_INPUT_UP)
				{
					dir = dir_front;
					move_flag = true;
				}
				// ���������Ă����牺�ɐi��
				else if (Input & PAD_INPUT_DOWN)
				{
					dir = dir_back;
					move_flag = true;
				}
				// �E�������Ă�����E�ɐi��
				else if (Input & PAD_INPUT_RIGHT)
				{
					dir = dir_right;
					move_flag = true;
				}
				// ���������Ă����獶�ɐi��
				else if (Input & PAD_INPUT_LEFT)
				{
					dir = dir_left;
					move_flag = true;
				}
				else
				{
					move_flag = false;
					move_cnt = 0;
				}
			}

			if (GetInput(SHOT) == PUSHDOWN && !jump_flag && !shot_flag && !move_flag
				&& !input_once)
			{
				shot_flag = true;
				prev_pos = pos;
				playSound(SE_SHOT);
			}
		}
		else
		{
			if (!shot_flag)
			{
				// �E��ɓ��͂��Ă�����E�΂ߏ�ɐi��
				if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed * VECTOR_SCALING;
					pos.z += speed * VECTOR_SCALING;
					dir = dir_f_right;
					angleY = -135.0f;
					move_flag = true;
				}
				// ����ɓ��͂��Ă����獶�΂ߏ�ɐi��
				else if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed * VECTOR_SCALING;
					pos.z += speed * VECTOR_SCALING;
					dir = dir_f_left;
					angleY = 135.0f;
					move_flag = true;
				}
				// �E���ɓ��͂��Ă�����E�΂߉��ɐi��
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed * VECTOR_SCALING;
					pos.z -= speed * VECTOR_SCALING;
					dir = dir_b_right;
					angleY = -45.0f;
					move_flag = true;
				}
				// �����ɓ��͂��Ă����獶�΂߉��ɐi��
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed * VECTOR_SCALING;
					pos.z -= speed * VECTOR_SCALING;
					dir = dir_b_left;
					angleY = 45.0f;
					move_flag = true;
				}
				// ��������Ă������ɐi��
				else if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
				{
					pos.z += speed;
					dir = dir_front;
					angleY = 180.0f;
					move_flag = true;
				}
				// ���������Ă����牺�ɐi��
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
				{
					pos.z -= speed;
					dir = dir_back;
					angleY = 0.0f;
					move_flag = true;
				}
				// �E�������Ă�����E�ɐi��
				else if (getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed;
					dir = dir_right;
					angleY = -90.0f;
					move_flag = true;
				}
				// ���������Ă����獶�ɐi��
				else if (getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed;
					angleY = 90.0f;
					move_flag = true;
				}
				else
				{
					move_flag = false;
					move_cnt = 0;
				}
			}

			if (GetInput(SHOT) == PUSHDOWN && !jump_flag && !shot_flag)
			{
				shot_flag = true;
				prev_pos = pos;
				playSound(SE_SHOT);
			}
		}
	}
	//�����Ă���ԃJ�E���g����
	if (move_flag)
		move_cnt++;

	// ���삵�Ă��Ȃ��Ƃ��͓�������������
	if (!move_flag)
	{
		if (pos.x > -105 && pos.x < 105)
		{
			if (pos.z < 0)
			{
				dir = dir_front;
				angleY = 180.0f;
			}
			else
			{
				dir = dir_back;
				angleY = 0.0f;
			}
		}
		else if (pos.z > -105 && pos.z < 105)
		{
			if (pos.x < 0)
			{
				dir = dir_right;
				angleY = -90.0f;
			}
			else
			{
				dir = dir_left;
				angleY = 90.0f;
			}
		}
	}

	// �V���b�g����
	if (shot_flag)
	{
		Shot();
	}

	ScaleChange(scaf.GetPos().y);

	//�W�����v����
	if (!jump_flag && move_flag && move_cnt > 20 && !shot_flag)
	{
		jump_flag = true;
		jump_vec = jump_accel;
		playSound(SE_JUMP);
	}
	if (jump_flag)
	{
		pos.y = pos.y + jump_vec;
		jump_vec = jump_vec - g;
	}

	// ���n����
	if (pos.y < scaf.GetPos().y)
	{
		pos.y = scaf.GetPos().y;
		jump_flag = false;
	}

	//�����蔻��
	if (!shot_flag)
	{
		if (pos.x - margin < 105 && pos.x + margin > -105)
		{
			if (pos.z + margin > -110 && pos.z < 105)
				pos.z = -110 - margin;
			if (pos.z - margin < 110 && pos.z > -105)
				pos.z = 110 + margin;
		}
		if (pos.z - margin < 105 && pos.z + margin > -105)
		{
			if (pos.x + margin > -110 && pos.x < 105)
				pos.x = -110 - margin;
			if (pos.x - margin < 110 && pos.x > -105)
				pos.x = 110 + margin;
		}
		if (pos.x - margin < -140)
			pos.x = -140 + margin;
		if (pos.x + margin > 140)
			pos.x = 140 - margin;
		if (pos.z - margin < -140)
			pos.z = -140 + margin;
		if (pos.z + margin > 140)
			pos.z = 140 - margin;
	}

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, pos);

	// �RD���f���̉�]�p�ݒ�
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY / 180.0f * DX_PI_F, 0.0f));

	MV1SetScale(modelHandle, VGet(scaleX, scaleY, scaleZ));
}

float Player::AngleCalculation(float x, float y)
{
	VECTOR vec = VGet(0,0,0);
	float angle = 0;
	vec.x = x;
	vec.z = y;
	vec = VNorm(vec);

	angle = (float)atan2((double)vec.z, (double)vec.x) * 180.0f / DX_PI_F;
	angle -= 90.0f;

	return angle;
}

//�V���b�g����
void Player::Shot()
{
	if (shot_flag && !return_flag)
	{
		if (shot_cnt > 3)
			return_flag = true;
		shot_cnt++;
		if (dir == dir_front)
		{
			pos.z += 3;
		}
		else if (dir == dir_back)
		{
			pos.z -= 3;
		}
		else if (dir == dir_left)
		{
			pos.x -= 3;
		}
		else if (dir == dir_right)
		{
			pos.x += 3;
		}
	}
	
	if (return_flag)
	{
		if (pos.x == prev_pos.x && pos.z == prev_pos.z)
		{
			return_flag = false;
			shot_flag = false;
			shot_cnt = 0;
		}
		if (dir == dir_front)
			pos.z -= 1;
		else if (dir == dir_back)
			pos.z += 1;
		else if (dir == dir_left)
			pos.x += 1;
		else if (dir == dir_right)
			pos.x -= 1;
	}
}

void Player::ScaleChange(float scaf_y)
{
	// �����Ă��Ȃ��Ƃ��ɑ傫�����ς���Ă����猳�̑傫���܂Ŗ߂�
	if (!move_flag && !jump_flag)
	{
		if (scaleX > 1)
			scaleX -= 0.1f;
		if (scaleY < 1)
			scaleY += 0.1f;
		if (scaleZ > 1)
			scaleZ -= 0.1f;
	}
	// �����Ă�Ƃ��W�����v����܂ŏk�߂�
	if (move_flag && !jump_flag)
	{
		scaleX += 0.01f;
		scaleY -= 0.01f;
		scaleZ += 0.01f;
	}

	if (jump_flag)
	{
		// ���n���钼�O�ɑS�͂łԂ�
		if (jump_vec < 0 && pos.y < scaf_y + 5)
		{
			scaleX += 0.2f;
			scaleY -= 0.2f;
			scaleZ += 0.2f;
		}
		// �����Ă���Ԃ͏������ׂ�����
		else if (scaleY < 1.f)
		{
			scaleX -= 0.1f;
			scaleY += 0.1f;
			scaleZ -= 0.1f;
		}
	}
}

//-----------------------------------------------------------------------------
// �`��.
//-----------------------------------------------------------------------------
void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
}