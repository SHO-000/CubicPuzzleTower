#pragma once

#define SCREEN_W 1920					// スクリーン横幅
#define SCREEN_H 1080					// スクリーン縦幅

#define VECTOR_SCALING 0.70710678118f	//斜め移動係数

#define CAMERA_X 0						// カメラ位置X
#define CAMERA_Y 270					// カメラ位置Y
#define CAMERA_Z -300					// カメラ位置Z

// シーンの種類
typedef enum SCENE_TYPE
{
	TITLE,
	SELECT,
	PLAY,
	NEXT,
	PAUSE,
	CLEAR,
}SCENE_TYPE;

// レベル
enum LEVEL
{
	EASY = 0,
	NORMAL,
	HARD,
	EXTRA
};