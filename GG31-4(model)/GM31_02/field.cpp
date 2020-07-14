
#include "main.h"
//#include "renderer.h"
#include "field.h"
#include "textureGL.h"
#include "vector.h"
#include <math.h>

#define TEXTURE_J_FILENAME "asset/texture/field.tga"



void CField::Init()
{
	m_Texture = LoadTexture( (char*)TEXTURE_J_FILENAME);
}


void CField::Uninit()
{
	UnloadTexture( m_Texture );
}


void CField::Update()
{

}


void CField::Draw()
{
	// ���C�e�B���O����
	glDisable( GL_LIGHTING );

	// �}�g���N�X�ޔ�
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	// �e�N�X�`���ݒ�
	glBindTexture( GL_TEXTURE_2D, m_Texture );

	// �|���S���`��
	glBegin(GL_TRIANGLE_STRIP);

		glColor4f(0.5, 0.5, 0.5, 1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-200.0f, -100.0f, 200.0f);

		glColor4f(0.5, 0.5, 0.5, 1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(200.0f,- 100.0f, 200.0f);

		glColor4f(0.5, 0.5, 0.5, 1.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-200.0f, -100.0f,-200.0f);

		glColor4f(0.5, 0.5, 0.5, 1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(200.0f,- 100.0f, -200.0f);

		

	glEnd();

	// �}�g���N�X����
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

 	// ���C�e�B���O�L��
	glEnable( GL_LIGHTING );
}