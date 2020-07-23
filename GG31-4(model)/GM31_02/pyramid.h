#pragma once


class CPyramid
{

private:
	int m_Texture;
	//�}�e���A���f�[�^
	float material_ambient[4] = { 0.24725, 0.1995, 0.0745, 1.0 }; //�����̐F
	float material_diffuse[4] = { 0.065164, 0.060648, 0.062648, 1.0 }; //���ˌ��̐F
	float material_specular[4] = { 0.828281, 0.855802, 0.866065, 1.0 }; //���ʔ��ˌ��̐F
	float material_shinness = 48; //���ʔ��ˌ��̋���
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

