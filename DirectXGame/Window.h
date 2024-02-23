#pragma once
#include "Windows.h"



class Window
{
public:
	Window();
	bool Init();
	bool Broadcast();
	bool IsRun();

	bool Release();
	~Window();

	virtual void OnCreate()=0;
	virtual void OnUpdate()=0;
	virtual void OnDestroy();


protected:
	HWND m_hwnd;
	bool m_isRun;
};

