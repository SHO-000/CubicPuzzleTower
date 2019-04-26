//-----------------------------------------------------------------------------
// ���C������
//-----------------------------------------------------------------------------
#include "SceneBase.h"
#include "FPS.h"

//-----------------------------------------------------------------------------
// ���C���֐�.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(1920, 1080, 16);
	ChangeWindowMode(FALSE);

	// �V�[���x�[�X�𐶐�
	SceneBase *scene = new SceneBase();

	// �t���[�����[�g�Œ�N���X�𐶐�
	FPS fps;
	bool isFixedFPS = true;

	// �e�N���X�𐶐�
	scene->Create();

	// �e�N���X�̏�����
	scene->Init();

	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �X�V
		fps.Update();
		scene->Update();

		// ��ʂ�����������
		ClearDrawScreen();

		// �`��
		scene->Draw();

		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		if (isFixedFPS)
		{
			// �ݒ肵���t���[�����[�g�ɂȂ�悤�ɑҋ@
			fps.Wait();
		}
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}