#pragma once


class CPyramid
{

private:
	int m_Texture;
	//マテリアルデータ
	float material_ambient[4] = { 0.24725, 0.1995, 0.0745, 1.0 }; //環境光の色
	float material_diffuse[4] = { 0.065164, 0.060648, 0.062648, 1.0 }; //反射光の色
	float material_specular[4] = { 0.828281, 0.855802, 0.866065, 1.0 }; //鏡面反射光の色
	float material_shinness = 48; //鏡面反射光の強さ
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

