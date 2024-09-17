//-----------------------------------------------------------------------------
// シーンベースクラス
//-----------------------------------------------------------------------------
#include "SceneBase.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
SceneBase::SceneBase()
{
	p_sceneControll = new SceneControll();
	p_sceneControll->Create();
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
SceneBase::~SceneBase()
{
	delete(p_sceneControll);

	deleteSound();
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void SceneBase::Init()
{
	m_nowScene = TITLE;

	InitInput();

	loadSound();

	p_sceneControll->Init();
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void SceneBase::Update()
{
	UpdateInput();

	m_nowScene = p_sceneControll->GetNowScene();

	if (m_nowScene == TITLE)
	{
		p_sceneControll->UpdateTitle();
	}
	else if (m_nowScene == SELECT)
	{
		p_sceneControll->UpdateSelect();
	}
	else if (m_nowScene == PLAY || m_nowScene == NEXT)
	{
		p_sceneControll->UpdatePlay();
	}

	p_sceneControll->ChangeScene();
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void SceneBase::Draw()
{
	if (m_nowScene == TITLE)
	{
		p_sceneControll->DrawTitle();
	}
	else if (m_nowScene == SELECT)
	{
		p_sceneControll->DrawSelect();
	}
	else if (m_nowScene == PLAY || m_nowScene == NEXT)
	{
		p_sceneControll->DrawPlay();
	}
}
