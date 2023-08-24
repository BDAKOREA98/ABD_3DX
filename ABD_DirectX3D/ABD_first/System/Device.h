#pragma once
class Device : public Singleton<Device>
{
private:
	friend class Singleton;

	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	



public:

	void Clear();
	void Present();

	ID3D11Device*			GetDevice() { return device; }
	ID3D11DeviceContext*	GetDC()		{ return deviceContext; }


private:
	ID3D11Device*		 device; // CPU를 다루는 객체
	ID3D11DeviceContext* deviceContext; // GPU를 다루는 객체

	IDXGISwapChain*			swapchain; // 더블버퍼링을 구현하는 객체
	ID3D11RenderTargetView* renderTargetView; // 백버퍼를 관리하는 객체
	ID3D11DepthStencilView* depthStencilView;  // 깊이를 결정하는 객체 DSV라고도 부름

};

