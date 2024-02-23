#include "Window.h"

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg , WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->OnCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::Init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;

	if (!::RegisterClassEx(&wc))
		return false;

	m_hwnd = ::CreateWindowEx(WS_OVERLAPPEDWINDOW, L"MyWindowClass",L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd)
		return false;

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);



	m_isRun = true;
	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->OnUpdate();

	Sleep(0);

	return true;
}

bool Window::IsRun()
{
	return m_isRun;
}

bool Window::Release()
{
	if(!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

Window::~Window()
{
}

void Window::OnDestroy()
{
	m_isRun = false;
}
