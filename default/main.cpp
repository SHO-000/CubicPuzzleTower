//-----------------------------------------------------------------------------
// メイン処理
//-----------------------------------------------------------------------------
#include "SceneBase.h"
#include "FPS.h"
#include "Define.h"

//-----------------------------------------------------------------------------
// メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetGraphMode(SCREEN_W, SCREEN_H, 16);
	ChangeWindowMode(TRUE);

	// シーンベースを生成
	SceneBase *scene = new SceneBase();
	
	// フレームレート固定クラスを生成
	FPS fps;
	bool isFixedFPS = true;

	// 各クラスの初期化
	scene->Init();

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 更新
		fps.Update();
		scene->Update();

		// 画面を初期化する
		ClearDrawScreen();

		// 描画
		scene->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		if (isFixedFPS)
		{
			// 設定したフレームレートになるように待機
			fps.Wait();
		}
	}

	// waiiaiaiiaia

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}