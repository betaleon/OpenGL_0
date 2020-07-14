
#include "main.h"
//#include "renderer.h"
#include "pyramid.h"
#include "textureGL.h"
#include "vector.h"
#include <math.h>

#define TEXTURE_J_FILENAME "asset/texture/field.tga"
#define EDGE_LENGTH (10.0f)



void CPyramid::Init()
{
	m_Texture = LoadTexture((char*)TEXTURE_J_FILENAME);
}


void CPyramid::Uninit()
{
	UnloadTexture(m_Texture);
}


void CPyramid::Update()
{

}


void CPyramid::Draw()
{
	// ���C�e�B���O����
	glDisable(GL_LIGHTING);

	// �}�g���N�X�ޔ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// �e�N�X�`���ݒ�
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	//��]���Ȃ��獶�E�։�������i�s��̏�Z�����ɒ��Ӂj
	static GLfloat angle = 0.0f;	//�f�o�b�O�p
	static GLfloat angle2 = 0.0f;	//�f�o�b�O�p

	GLfloat posx = sinf(angle2 * (3.14159 / 180.0f))*30.0f;	//���E�̈ړ��l

	glTranslatef(posx, 0.0f, 0.0f);		//�s��X�^�b�N�֕��s�ړ��s�����Z				1
	glRotatef(angle, 1.0f, 1.0f, 1.0f);	//���݂̃J�����g�s��� X ��]�s�񂪏�Z�����	2
	glScalef(10.0f, 10.0f, 10.0f);			//�s��X�^�b�N�֊g��k���s�����Z				3

	angle += 1.0f;//�p�x�X�V
	angle2 += 1.0f;

	// �|���S���`��
	glBegin(GL_TRIANGLES);
	//���
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f(-(EDGE_LENGTH/ 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	//����1
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(1, 0);glVertex3f((EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(0, 1);glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	//����2
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));

	//����3
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	glEnd();

	// �}�g���N�X����
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);
}