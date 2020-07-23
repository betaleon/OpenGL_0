
#include "main.h"
//#include "renderer.h"
#include "pyramid.h"
#include "textureGL.h"
#include "vector.h"
#include <math.h>
#include "model.h"

#define TEXTURE_J_FILENAME "asset/texture/field.tga"
#define EDGE_LENGTH (10.0f)

GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
	GLfloat fVert3[], GLfloat *fNormalX,
	GLfloat *fNormalY, GLfloat *fNormalZ);

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
	// ライティング有効
	glEnable(GL_LIGHTING);
	// ライティング無効
	//glDisable(GL_LIGHTING);

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
	//angle2 += 1.0f;

	// ポリゴン描画
	glBegin(GL_TRIANGLES);
	//底面
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 0);  glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); glTexCoord2f(0, 1);  glVertex3f(-(EDGE_LENGTH/ 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);  glTexCoord2f(1, 0);  glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	GLfloat fVert1[] = { 0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3) };
	GLfloat fVert2[] = { -(EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };
	GLfloat fVert3[] = { (EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };
	GLfloat fNormalX,fNormalY,fNormalZ;

	CalculateVectorNormal(fVert1,fVert2,fVert3,&fNormalX,&fNormalY,&fNormalZ);
	glNormal3f(fNormalX, fNormalY, fNormalZ);

	//側面1
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); glTexCoord2f(0, 0);  glNormal3f(1, 0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(1, 0); glNormal3f(1, 0, 0); glVertex3f((EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);glTexCoord2f(0, 1); glNormal3f(1, 0, 0); glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	GLfloat fVert4[]= { 0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f };
	GLfloat fVert5[] = { (EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };
	GLfloat fVert6[] = { -(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };

	CalculateVectorNormal(fVert4, fVert5, fVert6, &fNormalX, &fNormalY, &fNormalZ);
	glNormal3f(fNormalX, fNormalY, fNormalZ);
	//側面2
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 0);  glNormal3f(-1, 0, 0); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(1, 0);  glNormal3f(-1, 0, 0); glVertex3f(-(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); glTexCoord2f(0, 1);  glNormal3f(-1, 0, 0); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));

	GLfloat fVert7[] = { 0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f };
	GLfloat fVert8[] = { -(EDGE_LENGTH / 2.0f), 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };
	GLfloat fVert9[] = { 0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3) };

	CalculateVectorNormal(fVert7, fVert8, fVert9, &fNormalX, &fNormalY, &fNormalZ);
	glNormal3f(fNormalX, fNormalY, fNormalZ);
	//側面3
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 0);  glNormal3f(0, 0, 1); glVertex3f(0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f);		//top
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(1, 0);  glNormal3f(0, 0, 1); glVertex3f(0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3));
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); glTexCoord2f(0, 1);  glNormal3f(0, 0, 1); glVertex3f((EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3));

	GLfloat fVert10[] = { 0.0f, EDGE_LENGTH*sqrtf(2) / sqrtf(3), 0.0f };
	GLfloat fVert11[] = { 0.0f, 0.0f, EDGE_LENGTH / 3.0f *sqrtf(3) };
	GLfloat fVert12[] = { (EDGE_LENGTH / 2.0f) , 0.0f, -EDGE_LENGTH / 6.0f *sqrtf(3) };

	CalculateVectorNormal(fVert10, fVert11, fVert12, &fNormalX, &fNormalY, &fNormalZ);
	glNormal3f(fNormalX, fNormalY, fNormalZ);

	COLOR color = { 0,0,0,1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float*)&color);
	color = { 1,1,1,1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float*)&color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float*)&color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,0);

	glEnd();

	// マトリクス復元
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// ライティング有効
	//glEnable(GL_LIGHTING);
	// ライティング無効
	//glDisable(GL_LIGHTING);
}

GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
	GLfloat fVert3[], GLfloat *fNormalX,
	GLfloat *fNormalY, GLfloat *fNormalZ)
{
	GLfloat Qx, Qy, Qz, Px, Py, Pz;

	Qx = fVert2[0] - fVert1[0];
	Qy = fVert2[1] - fVert1[1];
	Qz = fVert2[2] - fVert1[2];
	Px = fVert3[0] - fVert1[0];
	Py = fVert3[1] - fVert1[1];
	Pz = fVert3[2] - fVert1[2];

	*fNormalX = Py * Qz - Pz * Qy;
	*fNormalY = Pz * Qx - Px * Qz;
	*fNormalZ = Px * Qy - Py * Qx;

};