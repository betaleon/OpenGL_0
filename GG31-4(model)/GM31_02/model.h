#pragma once

//#include "vector.h"
#include <assert.h>

// 色構造体
struct COLOR_MODEL
{
	float r;
	float g;
	float b;
	float a;
};

// 2Dベクトル構造体
struct VECTOR2D_MODEL
{
	VECTOR2D_MODEL()
	{
		x = 0.0f;
		y = 0.0f;
	}

	VECTOR2D_MODEL( float inX, float inY )
	{
		x = inX;
		y = inY;
	}

	float x;
	float y;
};

// 3Dベクトル構造体
struct VECTOR3D_MODEL
{
	VECTOR3D_MODEL()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	VECTOR3D_MODEL( float inX, float inY, float inZ )
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	float x;
	float y;
	float z;
};

// 4Dベクトル構造体
struct VECTOR4D_MODEL
{
	VECTOR4D_MODEL()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	VECTOR4D_MODEL( float inX, float inY, float inZ, float inW )
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	float x;
	float y;
	float z;
	float w;
};

// マテリアル構造体
struct MATERIAL_MODEL
{
	COLOR_MODEL		Ambient;
	COLOR_MODEL		Diffuse;
	COLOR_MODEL		Specular;
	COLOR_MODEL		Emission;
	float			Shininess;
};

// 3D頂点構造体
struct VERTEX_3D_MODEL
{
	VECTOR2D_MODEL		TexCoord;
	COLOR_MODEL			Diffuse;
	VECTOR3D_MODEL		Normal;
	VECTOR3D_MODEL		Position;
};


// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL_MODEL				Material;
	char						TextureName[256];
	int							Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	VERTEX_3D_MODEL		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


class CModel
{
private:

	MODEL m_Model;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

public:

	void Draw();

	void Load( const char *FileName );
	void Unload();

	//法線表示用
	VERTEX_3D_MODEL*	GetVertexArray() { return m_Model.VertexArray; }	//頂点バッファのポインタ取得
	UINT				GetVertexNum() { return m_Model.VertexNum; }		//頂点の数を取得
};

//プレイヤー管理クラス
class CPlayer
{
protected:
	CModel* pModel;	//CModelインスタンスポインタ
	VECTOR3D_MODEL Position;
	VECTOR3D_MODEL Rotation;

public:
	CPlayer() {};
	CPlayer(CModel* pmodel) { pModel = pmodel; };
	virtual ~CPlayer() {};

public:
	void			SetModel(CModel* pmodel) { pModel = pmodel; };		//CModelインスタンスセット
	CModel*			GetModel() { return pModel; };						//CModelインスタンスゲット
	void			SetPosition(float x, float y, float z)
						{Position.x = x; Position.y = y, Position.z = z;};	//表示座標セット
	VECTOR3D_MODEL	GetPosition() { return Position; };		//表示座標ゲット
	void			SetRotation(float x, float y, float z)	//回転角度セット
						{Rotation.x = x; Rotation.y = y; Rotation.z = z;};
	VECTOR3D_MODEL	GetRotation() { return Rotation; };		//回転角度ゲット

public:
	void Update() {};
	void Draw() 
	{
	
	};
};

//ライトのパラメーター
struct LIGHT
{
	VECTOR4D_MODEL	Position = { 0,0,500,0 };	//光源の座標 w = 0 の場合は平行光源 W = 1 の場合は点光源
	COLOR_MODEL		Ambient = {0,0,0,1};			//環境光
	COLOR_MODEL		Diffuse = {0,1,0,1 };			//反射光
	COLOR_MODEL		Specular = { 0,0,0,1 };			//鏡面反射光
};