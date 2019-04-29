//-----------------------------------------------------------------------------
// @brief  �J�����N���X.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#include "DxLib.h"

class Camera
{
public:
	Camera();							// �R���X�g���N�^.
	~Camera();							// �f�X�g���N�^.

	void TitleUpdate();
	void Update();	// �X�V.

	// �|�W�V������getter/setter.
	VECTOR GetPos() { return pos; }

private:
	VECTOR	pos;			// �|�W�V����.

};