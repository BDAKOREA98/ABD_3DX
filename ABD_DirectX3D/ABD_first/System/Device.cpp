#include "Framework.h"
#include "Device.h"

Device::Device()
{
    CreateDeviceAndSwapChain();
    CreateBackBuffer();




}

Device::~Device()
{
                  device    ->Release();
           deviceContext    ->Release();
               swapchain    ->Release();
        renderTargetView    ->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    // BufferCount : Backbuffer�� � �ִ°�
    swapChainDesc.BufferCount = 1;
    // BackBuffer�� ũ�⸦ ������
    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    // Format : RGBA�� color�� normalize�� ������ �ְڴ�.
    // - RGBA : 8bit * 4  = 32 bir, unorm : unsigned int = 0 ~ 1
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // RefeshRate : ���ΰ�ħ�� == ���ź� : �󸶳� ���� ���Ž�Ű�°� == ����� �ֻ��� (1�ʿ� 60�� ���� == 60HZ)
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // BufferUsage : backBuffer�� ��뵵�� �� ���ΰ� (�츮�� RenderTarget�� ��¿����� ����Ұ���)
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // windowoutput���� �� ����� ���ΰ�  hWnd
    swapChainDesc.OutputWindow = hWnd;
    // sampling : ǥ��ȭ
    // - Ȯ�� ����Ҷ� ������ �������µ� �װ��� �����ٶ� samping�� ���� , Ȯ�� �Ǵ� ��� �Ҷ� ������ ��� �������� �����ִ°� sampling��
    // �ִ� sampling : ���� Ŭ���� �̸� ����س��� , ���� sampling : ���� ũ�⸦ �̸� ����س���
    // Count : �ȼ��� Ȯ�������� �ֺ��� �ȼ��� �߰����ٵ� ��� �ȼ��� ���� ���Ұ��ΰ�
    // Quality : ũ�Ⱑ Ŭ ���� ������ �߰��� 
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    // Winodwed : âȭ���� �� �� ����, ��üȭ���� �� ������
    swapChainDesc.Windowed = true;
    // device�� swapchain�� �ѹ��� ������ִ� �Լ�
    D3D11CreateDeviceAndSwapChain(

        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapchain,
        &device,
        nullptr,
        &deviceContext

    );
}

void Device::CreateBackBuffer()
{
    // BackBuffer ����� �κ�
    // ������� ǥ�õǴ� ������ �ᱹ 2D�̱⿡ 2D�� ��
    ID3D11Texture2D* backBuffer;

    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);


    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void Device::Clear()
{
    float clearcolor[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearcolor);

}

void Device::Present()
{
    // backbuffer�� frontbuffer�� �ٲ��ִ� �Լ� �� ������ �������� ������ cloea�� �ϴ��� backbuffer���� clear�Ǳ⿡ �Ͼ� ȭ���� ����
    swapchain->Present(0, 0);
}
