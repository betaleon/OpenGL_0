
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
	// ライティング無効
	glDisable(GL_LIGHTING);

	// マトリクス退避
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// テクスチャ設定
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	//回転しながら左右へ往復する（行列の乗算順序に注意）
	static GLfloat angle = 0.0f;	//デバッグ用
	static GLfloat angle2 = 0.0f;	//デバッグ用

	GLfloat posx = sinf(angle2 * (3.14159 / 180.0f))*30.0f;	//左右の移動値

	glTranslatef(posx, 0.0f, 0.0f);		//行列スタックへ平行移動行列を乗算				1
	glRotatef(angle, 1.0f, 1.0f, 1.0f);	//現在のカレント行列に X 回転行列が乗算される	2
	glScalef(10.0f, 10.0f, 10.0f);			//行列スタックへ拡大縮小行列を乗算				3

	angle += 1.0f;//角度更新
	angle2 += 1.0f;

	// ポリゴン描画
	glBegin(GL_TRIANGLES);
	//底面
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f(-(EDGE_LENGTH/ 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	//側面1
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(1, 0);glVertex3f((EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(0, 1);glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	//側面2
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));

	//側面3
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(1, 0); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 1); glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	glEnd();

	// マトリクス復元
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ライティング有効
	glEnable(GL_LIGHTING);
}