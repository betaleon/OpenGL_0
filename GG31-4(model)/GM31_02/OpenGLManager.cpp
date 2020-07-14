#include<windows.h>
#include <GL/gl.h >
#include <GL/glu.h >
#include "OpenGLManager.h"
#include "textureGL.h"
//ベクトル構造体定義
#include "vector.h"
#include "field.h"
#include "pyramid.h"
#include "model.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//#define MODEL_FILE "asset\model\torus.obj"

//グローバル変数
HGLRC glrc;

//クラス宣言
CField* g_Field;
CPyramid* g_Pyramid;

CModel Box;	//CModel インスタンス

int TexChangeCnt;
int TexPat;

//とりあえずカメラ用に最低限用意
#define VIEW_ANGLE (45.0f) // 視野角
#define VIEW_NEAR_Z (10.0f) // 近面距離
#define VIEW_FAR_Z (100000.0f) //遠面距離
#define SCALE_NORMAL (1.0)
VECTOR3D m_posP; // 視点
VECTOR3D m_posR; // 注視点
VECTOR3D m_vecUp; // 上方向ベクトル

VERTEX_3D_MODEL*	NormalLine;	//法線表示用頂点
UINT				VertexNum;	//モデルの頂点数


void OpenGLManager::Init(HWND hwnd)
{

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   //構造体のサイズ
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // OpenGLでダブルバッファを使い
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
	//ピクセルフォーマットの設定
	//

	int format = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, format, &pfd);
	glrc = wglCreateContext(dc);
	wglMakeCurrent(dc, glrc);
	TexChangeCnt = 0;
	TexPat = 1;
	//SendMessage(hwnd, WM_PAINT, 0, 0);
	
	//テクスチャ保存
	g_Field = new CField();
	g_Field->Init();

	g_Pyramid = new CPyramid();
	g_Pyramid->Init();
	//モデルデータ読み込み
	Box.Load("asset\\model\\cube.obj");



	//モデル頂点数取得
	VertexNum = Box.GetVertexNum();
	//法線頂点の配列を確保
	NormalLine = new VERTEX_3D_MODEL[VertexNum*2];
	//モデルの頂点配列ポインター取得
	VERTEX_3D_MODEL* pVertex = Box.GetVertexArray();
	//法線表示用頂点作成
	for (int i = 0; i < VertexNum; i++)
	{
		//頂点座標のコピー
		NormalLine[i * 2].Position = pVertex[i].Position;
		NormalLine[i * 2 + 1].Position = pVertex[i].Position;
		//表示用法線ベクトル作成
		VECTOR3D_MODEL normal = pVertex[i].Normal;	//正規化されている
		normal.x *= SCALE_NORMAL;
		normal.y *= SCALE_NORMAL;
		normal.z *= SCALE_NORMAL;
		//頂点座標へ加算
		NormalLine[i * 2 + 1].Position.x += normal.x;
		NormalLine[i * 2 + 1].Position.y += normal.y;
		NormalLine[i * 2 + 1].Position.z += normal.z;
		//頂点色を設定(見やすい色に)//適当に赤くしとく
		NormalLine[i * 2].Diffuse.r = 1.0f;	
		NormalLine[i * 2].Diffuse.g = 0.0f;
		NormalLine[i * 2].Diffuse.b = 0.0f;
		NormalLine[i * 2].Diffuse.a = 1.0f;
		NormalLine[i * 2 + 1].Diffuse.r = 1.0f;
		NormalLine[i * 2 + 1].Diffuse.g = 0.0f;
		NormalLine[i * 2 + 1].Diffuse.b = 0.0f;
		NormalLine[i * 2 + 1].Diffuse.r = 1.0f;
		//テクスチャ座標（意味はない）
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
	//レンダリングコンテキスト破棄

	g_Field->Uninit();
	delete g_Field;

	g_Pyramid->Uninit();
	delete g_Pyramid;

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hwnd, dc);
	wglDeleteContext(glrc);

	//終了処理
	Box.Unload();	//モデルデータを解放
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



	// ライティング無効
	glDisable(GL_LIGHTING);

	// 2D用マトリクス設定
	glMatrixMode(GL_PROJECTION);//プエロジェクション行列操作モード
	glPushMatrix();//現在のプロジェクション行列を保存
	glLoadIdentity();//現在のプロジェクション行列を単位行列にする
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);//平行投影行列
	glMatrixMode(GL_MODELVIEW);//モデルビュー行列操作モード
	glPushMatrix();//現在のモデルビュー行列を保存
	glLoadIdentity();//現在のモデルビュー行列を単位行列にする

	// ポリゴン描画
	//g_Field->Draw();

	// ライティング有効
	glEnable(GL_LIGHTING);

	// マトリクスを戻す
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



	// ビューポートセット
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//各自の画面サイズを使う
	/******************************************************************************/
	/*2D と 3D でプロジェクション・（モデル）ビュー行列の設定はしっかり切り替えること*/
	/******************************************************************************/
	// アスペクト比を作っておく
	double aspect = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;//各自の画面サイズを使う
	// 3D 用プロジェクションマトリクス設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//カレント行列を単位行列にする
	gluPerspective(VIEW_ANGLE, aspect, VIEW_NEAR_Z, VIEW_FAR_Z);//カレント行列にプロジェクション行列が乗算される
	//m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //カメラ座標
	m_posP = VECTOR3D(0.0f, 100.0f, -300.0f); //カメラ座標
	m_posR = VECTOR3D(0.0f, 10.0f, 0.0f); //カメラ注視点
	m_vecUp = VECTOR3D(0.0f, 1.0f, 0.0f); //上方ベクトル
	// 3D 用（モデル）ビューマトリクス設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//カレント行列を単位行列にする
	gluLookAt((double)m_posP.x, (double)m_posP.y, (double)m_posP.z,
		(double)m_posR.x, (double)m_posR.y, (double)m_posR.z,
		0.0, 1.0, 0.0);//カレント行列にビュー行列乗算される


	// ライティング無効
	glDisable(GL_LIGHTING);

	// モデルビューマトリクスの設定
	glMatrixMode(GL_MODELVIEW);
	//カレント行列をコピー
	glPushMatrix();					

	// 3D オブジェクトの描画
	//g_Field->Draw();
	g_Pyramid->Draw();
	//Box.Draw();	//モデルデータの描画


	//テクスチャを使用しない
	glBindTexture(GL_TEXTURE_2D, NULL);
	//ライティング無効
	glDisable(GL_LIGHTING);
	//線の幅設定
	glLineWidth(3.0f);
	//ライン表示モード
	glBegin(GL_LINES);
	for (int i = 0; i < VertexNum*2; i++)
	{
		glColor4f(	NormalLine[i].Diffuse.r,
					NormalLine[i].Diffuse.g,
					NormalLine[i].Diffuse.b,
					NormalLine[i].Diffuse.a);	//頂点カラー
	
		glVertex3f(	NormalLine[i].Position.x,
					NormalLine[i].Position.y,
					NormalLine[i].Position.z);	//頂点座標
	}
	glEnd();
	

	// モデルビューマトリクスを復元
	glMatrixMode(GL_MODELVIEW);
	//カレント行列を削除
	glPopMatrix();	

	// ライティング有効
	glEnable(GL_LIGHTING);

	SwapBuffers(dc);

}