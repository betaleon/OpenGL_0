#pragma once

//#include "vector.h"
#include <assert.h>

// �F�\����
struct COLOR_MODEL
{
	float r;
	float g;
	float b;
	float a;
};

// 2D�x�N�g���\����
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

// 3D�x�N�g���\����
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

// 4D�x�N�g���\����
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

// �}�e���A���\����
struct MATERIAL_MODEL
{
	COLOR_MODEL		Ambient;
	COLOR_MODEL		Diffuse;
	COLOR_MODEL		Specular;
	COLOR_MODEL		Emission;
	float			Shininess;
};

// 3D���_�\����
struct VERTEX_3D_MODEL
{
	VECTOR2D_MODEL		TexCoord;
	COLOR_MODEL			Diffuse;
	VECTOR3D_MODEL		Normal;
	VECTOR3D_MODEL		Position;
};


// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL_MODEL				Material;
	char						TextureName[256];
	int							Texture;

};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// ���f���\����
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

	//�@���\���p
	VERTEX_3D_MODEL*	GetVertexArray() { return m_Model.VertexArray; }	//���_�o�b�t�@�̃|�C���^�擾
	UINT				GetVertexNum() { return m_Model.VertexNum; }		//���_�̐����擾
};

//�v���C���[�Ǘ��N���X
class CPlayer
{
protected:
	CModel* pModel;	//CModel�C���X�^���X�|�C���^
	VECTOR3D_MODEL Position;
	VECTOR3D_MODEL Rotation;

public:
	CPlayer() {};
	CPlayer(CModel* pmodel) { pModel = pmodel; };
	virtual ~CPlayer() {};

public:
	void			SetModel(CModel* pmodel) { pModel = pmodel; };		//CModel�C���X�^���X�Z�b�g
	CModel*			GetModel() { return pModel; };						//CModel�C���X�^���X�Q�b�g
	void			SetPosition(float x, float y, float z)
						{Position.x = x; Position.y = y, Position.z = z;};	//�\�����W�Z�b�g
	VECTOR3D_MODEL	GetPosition() { return Position; };		//�\�����W�Q�b�g
	void			SetRotation(float x, float y, float z)	//��]�p�x�Z�b�g
						{Rotation.x = x; Rotation.y = y; Rotation.z = z;};
	VECTOR3D_MODEL	GetRotation() { return Rotation; };		//��]�p�x�Q�b�g

public:
	void Update() {};
	void Draw() 
	{
	
	};
};

//���C�g�̃p�����[�^�[
struct LIGHT
{
	VECTOR4D_MODEL	Position = { 0,0,500,0 };	//�����̍��W w = 0 �̏ꍇ�͕��s���� W = 1 �̏ꍇ�͓_����
	COLOR_MODEL		Ambient = {0,0,0,1};			//����
	COLOR_MODEL		Diffuse = {0,1,0,1 };			//���ˌ�
	COLOR_MODEL		Specular = { 0,0,0,1 };			//���ʔ��ˌ�
};