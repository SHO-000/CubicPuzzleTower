#include "GameManager.h"



GameManager::GameManager()
{
	Create();
}


GameManager::~GameManager()
{
	Delete();
}

void GameManager::Create()
{
	player = new Player();	// �v���C���[�𐶐�
	shadow = new Shadow();	// �e�𐶐�
	cube = new Cube();		// �L���[�u�𐶐�
	camera = new Camera();	// �J�����𐶐�
	map = new Map();		// �}�b�v�𐶐�
	mini = new miniMap();	// �~�j�}�b�v�𐶐�
	scaf = new Scaf();		// ����𐶐�
	state = new State();	// �X�e�[�g�𐶐�
	title = new Title();	// �^�C�g���𐶐�
	select = new Select();	// �Z���N�g�𐶐�
	clear = new Clear();	// �N���A�𐶐�
	ui = new UI();			// UI�𐶐�
}

void GameManager::Delete()
{
	delete(player);	// �v���C���[���폜
	delete(shadow);	// �e���폜
	delete(cube);	// �L���[�u���폜
	delete(camera);	// �J�������폜
	delete(map);	// �}�b�v���폜
	delete(mini);	// �~�j�}�b�v���폜
	delete(scaf);	// ������폜
	delete(state);	// �X�e�[�g���폜
	delete(title);	// �^�C�g�����폜
	delete(select);	// �Z���N�g���폜
	delete(clear);	// �N���A���폜
	delete(ui);		// UI���폜
	deleteSound();	// ���f�[�^���폜
}

void GameManager::Init()
{
	//�L�[���͔��菈���̏�����
	InitKeyInput();
	initKey();

	InitInput();

	state->Init();

	player->Init();

	cube->Init();

	scaf->Init();

	shadow->Init();

	title->Init();

	select->Init();

	clear->Init();

	mini->Init(*cube);

	ui->Init();

	loadSound();

}

//----------------------
// �A�b�v�f�[�g�֐�
//----------------------
void GameManager::Update()
{
	updateKey();//�L�[����

	UpdateInput();

	if (state->game_state == TITLE)
	{
		camera->TitleUpdate();

		title->Update();

		shadow->TitleUpdate(*title);
	}
	if (state->game_state == SELECT)
	{
		select->Update();
	}
	if (state->game_state == PLAY)
	{
		// �v���C���[����.
		player->Update(*cube, *scaf);

		// �J��������.
		camera->Update();

		cube->Update(*player);

		shadow->Update(*player, *scaf);

		scaf->Update(*cube);

		mini->Update(*player, *cube);

		ui->Update(*state);
	}
	if (state->game_state == CLEAR)
	{
		clear->Update();
	}
	state->Update(*player, *cube, *scaf, *title, *select);

	if (state->GetInitFlag())
	{
		Init();
	}
}

//----------------------
// �`��֐�
//----------------------
void GameManager::Draw()
{
	if (state->game_state == TITLE)
	{
		title->Draw();

		shadow->Draw();
	}
	if (state->game_state == SELECT)
	{
		select->Draw();
	}
	if (state->game_state == PLAY || state->game_state == PAUSE)
	{
		map->Draw();

		// �v���C���[�`��.
		player->Draw();

		cube->Draw();

		shadow->Draw();

		scaf->Draw();

		mini->Draw();

		ui->Draw();

		//effect->Draw();
	}
	if (state->game_state == CLEAR)
	{
		clear->Draw();
	}
	state->Draw();
}
