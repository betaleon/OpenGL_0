#pragma once
#include "main.h"

class OpenGLManager
{

public:
	static void Init(HWND hwnd);
	static void Uninit(HWND hwnd, HDC dc);
	static void Update();
	static void Draw(HDC dc);
	static void Draw3D(HDC dc);

};