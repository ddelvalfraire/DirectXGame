#pragma once
#include "Window.h"

class AppWindow : public Window
{
	// Inherited via Window
	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;
};

