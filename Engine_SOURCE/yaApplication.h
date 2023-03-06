#pragma once
#include "yaEngine.h"
#include "yaGraphics.h"
#include "yaGraphicDevice_DX11.h"

namespace ya
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Initialize();
		virtual void Update(); // CPU UPDATE ( ���� ���� ĳ���� �̵� ��� )
		virtual void FixedUpdate(); // GPU update
		virtual void Render();
		virtual void Destroy();

		// Running main engine loop
		void Run();
		void Present();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool Initialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}
