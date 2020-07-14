#include<windows.h>
#include <GL/gl.h >
#include <GL/glu.h >
#include "OpenGLManager.h"
#include "textureGL.h"
//�x�N�g���\���̒�`
#include "vector.h"
#include "field.h"
#include "pyramid.h"
#include "model.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//#define MODEL_FILE "asset\model\torus.obj"

//�O���[�o���ϐ�
HGLRC glrc;

//�N���X�錾
CField* g_Field;
CPyramid* g_Pyramid;

CModel Box;	//CModel �C���X�^���X

int TexChangeCnt;
int TexPat;

//�Ƃ肠�����J�����p�ɍŒ���p��
#define VIEW_ANGLE (45.0f) // ����p
#define VIEW_NEAR_Z (10.0f) // �ߖʋ���
#define VIEW_FAR_Z (100000.0f) //���ʋ���
#define SCALE_NORMAL (1.0)
VECTOR3D m_posP; // ���_
VECTOR3D m_posR; // �����_
VECTOR3D m_vecUp; // ������x�N�g��

VERTEX_3D_MODEL*	NormalLine;	//�@���\���p���_
UINT				VertexNum;	//���f���̒��_��


void OpenGLManager::Init(HWND hwnd)
{

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   //�\���̂̃T�C�Y
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // OpenGL�Ń_�u���o�b�t�@���g��
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     // no alpha buffer 
		0,                     // shift bit ignored 
		0,                     // no accumulation buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32,                    // 32-bit z-buffer 
		0,                     // no stencil buffer 
		0,                     // no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     // reserved 
		0, 0, 0                // layer masks ignored 
	};

	HDC dc = GetDC(hwnd);

	//
	//�s�N�Z���t�H�[�}�b�g�̐ݒ�
	//

	int format = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, format, &pfd);
	glrc = wglCreateContext(dc);
	wglMakeCurrent(dc, glrc);
	TexChangeCnt = 0;
	TexPat = 1;
	//SendMessage(hwnd, WM_PAINT, 0, 0);
	
	//�e�N�X�`���ۑ�
	g_Field = new CField();
	g_Field->Init();

	g_Pyramid = new CPyramid();
	g_Pyramid->Init();
	//���f���f�[�^�ǂݍ���
	Box.Load("asset\\model\\cube.obj");



	//���f�����_���擾
	VertexNum = Box.GetVertexNum();
	//�@�����_�̔z����m��
	NormalLine = new VERTEX_3D_MODEL[VertexNum*2];
	//���f���̒��_�z��|�C���^�[�擾
	VERTEX_3D_MODEL* pVertex = Box.GetVertexArray();
	//�@���\���p���_�쐬
	for (int i = 0; i < VertexNum; i++)
	{
		//���_���W�̃R�s�[
		NormalLine[i * 2].Position = pVertex[i].Position;
		NormalLine[i * 2 + 1].Position = pVertex[i].Position;
		//�\���p�@���x�N�g���쐬
		VECTOR3D_MODEL normal = pVertex[i].Normal;	//���K������Ă���
		normal.x *= SCALE_NORMAL;
		normal.y *= SCALE_NORMAL;
		normal.z *= SCALE_NORMAL;
		//���_���W�։��Z
		NormalLine[i * 2 + 1].Position.x += normal.x;
		NormalLine[i * 2 + 1].Position.y += normal.y;
		NormalLine[i * 2 + 1].Position.z += normal.z;
		//���_�F��ݒ�(���₷���F��)//�K���ɐԂ����Ƃ�
		NormalLine[i * 2].Diffuse.r = 1.0f;	
		NormalLine[i * 2].Diffuse.g = 0.0f;
		NormalLine[i * 2].Diffuse.b = 0.0f;
		NormalLine[i * 2].Diffuse.a = 1.0f;
		NormalLine[i * 2 + 1].Diffuse.r = 1.0f;
		NormalLine[i * 2 + 1].Diffuse.g = 0.0f;
		NormalLine[i * 2 + 1].Diffuse.b = 0.0f;
		NormalLine[i * 2 + 1].Diffuse.r = 1.0f;
		//�e�N�X�`�����W�i�Ӗ��͂Ȃ��j
		NormalLine[i * 2].TexCoord = pVertex[i].TexCoord;
		NormalLine[i * 2 + 1].TexCoord = pVertex[i].TexCoord;

	}


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

}

void OpenGLManager::Uninit(HWND hwnd, HDC dc)
{
	//�����_�����O�R���e�L�X�g�j��

	g_Field->Uninit();
	delete g_Field;

	g_Pyramid->Uninit();
	delete g_Pyramid;

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hwnd, dc);
	wglDeleteContext(glrc);

	//�I������
	Box.Unload();	//���f���f�[�^�����
	delete NormalLine;
}

void OpenGLManager::Update()
{
	g_Field->Update();

	g_Pyramid->Update();
}


void OpenGLManager::Draw(HDC dc)
{

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// 2D�p�}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);//�v�G���W�F�N�V�����s�񑀍샂�[�h
	glPushMatrix();//���݂̃v���W�F�N�V�����s���ۑ�
	glLoadIdentity();//���݂̃v���W�F�N�V�����s���P�ʍs��ɂ���
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);//���s���e�s��
	glMatrixMode(GL_MODELVIEW);//���f���r���[�s�񑀍샂�[�h
	glPushMatrix();//���݂̃��f���r���[�s���ۑ�
	glLoadIdentity();//���݂̃��f���r���[�s���P�ʍs��ɂ���

	// �|���S���`��
	//g_Field->Draw();

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);

	// �}�g���N�X��߂�
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	SwapBuffers(dc);

}

void OpenGLManager::Draw3D(HDC dc)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// �r���[�|�[�g�Z�b�g
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//�e���̉�ʃT�C�Y���g��
	/******************************************************************************/
	/*2D �� 3D �Ńv���W�F�N�V�����E�i���f���j�r���[�s��̐ݒ�͂�������؂�ւ��邱��*/
	/******************************************************************************/
	// �A�X�y�N�g�������Ă���
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//�e���̉�ʃT�C�Y���g��
	// 3D �p�v���W�F�N�V�����}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//�J�����g�s��Ƀv���W�F�N�V�����s�񂪏�Z�����
	//m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //�J�������W
	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //�J�������W
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //�J���������_
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //����x�N�g��
	// 3D �p�i���f���j�r���[�}�g���N�X�ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//�J�����g�s���P�ʍs��ɂ���
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//�J�����g�s��Ƀr���[�s���Z�����


	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// ���f���r���[�}�g���N�X�̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	//�J�����g�s����R�s�[
	glPushMatrix();					

	// 3D �I�u�W�F�N�g�̕`��
	//g_Field->Draw();
	g_Pyramid->Draw();
	//Box.Draw();	//���f���f�[�^�̕`��


	//�e�N�X�`�����g�p���Ȃ�
	glBindTexture(GL_TEXTURE_2D, NULL);
	//���C�e�B���O����
	glDisable(GL_LIGHTING);
	//���̕��ݒ�
	glLineWidth(3.0f);
	//���C���\�����[�h
	glBegin(GL_LINES);
	for (int i = 0; i < VertexNum*2; i++)
	{
		glColor4f(	NormalLine[i].Diffuse.r,
					NormalLine[i].Diffuse.g,
					NormalLine[i].Diffuse.b,
					NormalLine[i].Diffuse.a);	//���_�J���[
	
		glVertex3f(	NormalLine[i].Position.x,
					NormalLine[i].Position.y,
					NormalLine[i].Position.z);	//���_���W
	}
	glEnd();
	

	// ���f���r���[�}�g���N�X�𕜌�
	glMatrixMode(GL_MODELVIEW);
	//�J�����g�s����폜
	glPopMatrix();	

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);

	SwapBuffers(dc);

}