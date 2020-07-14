//=============================================================================
//
// OpenGL [main.h]
// Author : KATSUMA MURASE
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>			// DirectInput�֘A�̃w�b�_�[

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PI				(3.141592f)			// �~����

#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

#define	REGIST_MOVE				(0.55f)		// ��R�l
#define	REGIST_MOVE_AIR			(0.95f)		// ��R�l(��)
#define	REGIST_MOVE_AIR_Y		(0.985f)	// ��R�l(�󒆗���)
#define	REGIST_MOVE_SLIDE		(0.965f)	// ���鏰��R�l
#define	GRAVITY					(9.80f)		// �d��

#define PREPARE_SCENE_ARRAY		// �����V�[���̍쐬
#undef PREPARE_SCENE_ARRAY

#ifndef PREPARE_SCENE_ARRAY
#define PREPARE_SCENE_POINTER	// �����V�[���̍쐬
//#undef PREPARE_SCENE_POINTER
#endif

#define PREPARE_TEXTURE_ARRAY	// �����e�N�X�`���̍쐬
//#undef PREPARE_TEXTURE_ARRAY

#define	NUM_OBJECT		(3)			// �I�u�W�F�N�g��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HWND GetWindow();


#endif