//-----------------------------------------------------------------------------
// �v���C���[�N���X.
//-----------------------------------------------------------------------------
#pragma once

#include "DxLib.h"

class Cube;
class Scaf;

class Player
{
public:
	Player();				// �R���X�g���N�^.
	~Player();				// �f�X�g���N�^.

	void Init();
	void VectorControll();
	void Update(const Cube& cube, const Scaf& scaf);			// �X�V.
	void Draw();			// �`��.

	// ���f���n���h���̎擾.
	//int GetModelHandle() { return modelHandle; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	const int GetDir() const { return dir; }
	const float GetAngle() const { return angleY; }
	const VECTOR GetScale() const { return VGet(scaleX, 0.f, scaleZ); }
	void SetPos(const VECTOR set) { pos = set; }
	float AngleCalculation(float x, float y);

	VECTOR	pos, vec;		// �|�W�V����.

	const bool SlideStart() const { if (shot_cnt > 1) return true; else return false;}
private:
	void Shot();
	void ScaleChange(float scaf_y);

	int	modelHandle;	// ���f���n���h��.

	int dir;			//����
	float angleY;		//��]�p
	float scaleX;
	float scaleY;
	float scaleZ;
	float speed;
	bool move_flag;
	bool shot_flag;
	bool return_flag;
	bool jump_flag;
	float jump_vec;
	float g;
	float jump_accel;
	float margin;

	VECTOR prev_pos;
	int shot_cnt;
	int move_cnt;

	int Key;
	int Input;
	int inputX, inputY;	//�A�i���O�p�b�h�̓��͏��
	bool joypad_flag;
	bool input_once;
};