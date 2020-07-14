#ifndef _VECTOR_H_
#define _VECTOR_H_
// �F�\����
struct COLOR
{
	float r;
	float g;
	float b;
	float a;
};
// 2D �x�N�g���\����
struct VECTOR2D
{
	VECTOR2D()//�R���X�g���N�^
	{
		x = 0.0f;
		y = 0.0f;
	}
	VECTOR2D(float inX, float inY)//�����t���R���X�g���N�^
	{
		x = inX;
		y = inY;
	}
	float x;
	float y;
};
// 3D �x�N�g���\����
struct VECTOR3D
{
	VECTOR3D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	VECTOR3D(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
	float x;
	float y;
	float z;
};
// 4D �x�N�g���\����
struct VECTOR4D
{
	VECTOR4D()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	VECTOR4D(float inX, float inY, float inZ, float inW)
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
struct MATERIAL
{
	COLOR Ambient;
	COLOR Diffuse;
	COLOR Specular;
	COLOR Emission;
	float Shininess;
};
// 3D ���_�\����
struct VERTEX_3D
{
	VECTOR2D TexturePos;
	COLOR Diffuse;
	VECTOR3D Normal;
	VECTOR3D Position;
};
#endif