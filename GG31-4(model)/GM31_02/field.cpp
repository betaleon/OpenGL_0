
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
	// ライティング無効
	glDisable( GL_LIGHTING );

	// マトリクス退避
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	// テクスチャ設定
	glBindTexture( GL_TEXTURE_2D, m_Texture );

	// ポリゴン描画
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

	// マトリクス復元
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

 	// ライティング有効
	glEnable( GL_LIGHTING );
}