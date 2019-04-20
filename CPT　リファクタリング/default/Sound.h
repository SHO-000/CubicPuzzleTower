#pragma once
#define ALL_NUM 14

typedef enum SOUND_NUM
{
	BGM_TITLE,
	BGM_SELECT,
	BGM_PLAY,
	SE_SCAF,
	BGM_ALLCLEAR,
	SE_CURSOR,
	SE_DECISION,
	SE_START,
	SE_PAUSE,
	SE_CANCEL,
	SE_SHOT,
	SE_CUBEHIT,
	SE_JUMP,
	SE_CLEAR
}SOUND_NUM;

void loadSound();
void deleteSound();
void playSound(int sound_name);
void stopSound(int sound_name);
void resetSound(int sound_name);