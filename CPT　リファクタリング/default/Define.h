#pragma once

#define SCREEN_W 1920
#define SCREEN_H 1080

#define VECTOR_SCALING 0.70710678118f //�΂߈ړ��W��

typedef enum GAME_STATE
{
	TITLE,
	SELECT,
	PLAY,
	PAUSE,
	CLEAR,
	GAMEOVER
}GAME_STATE;

enum DIR	//����
{
	dir_left,
	dir_right,
	dir_front,
	dir_back,
	dir_f_left,
	dir_f_right,
	dir_b_left,
	dir_b_right
};

enum LEVEL
{
	easy,
	normal,
	hard,
	extra
};