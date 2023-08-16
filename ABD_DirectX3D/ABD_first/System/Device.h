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
	ID3D11Device*		 device; // CPU�� �ٷ�� ��ü
	ID3D11DeviceContext* deviceContext; // GPU�� �ٷ�� ��ü

	IDXGISwapChain*			swapchain; // ������۸��� �����ϴ� ��ü
	ID3D11RenderTargetView* renderTargetView; // ����۸� �����ϴ� ��ü

};

