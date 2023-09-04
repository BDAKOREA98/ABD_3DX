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
    // BufferCount : Backbuffer가 몇개 있는가
    swapChainDesc.BufferCount = 1;
    // BackBuffer의 크기를 정해줌
    swapChainDesc.BufferDesc.Width = WIN_WIDTH;
    swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
    // Format : RGBA의 color를 normalize된 값으로 넣겠다.
    // - RGBA : 8bit * 4  = 32 bir, unorm : unsigned int = 0 ~ 1
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // RefeshRate : 새로고침빈도 == 갱신빈도 : 얼마나 자주 갱신시키는가 == 모니터 주사율 (1초에 60번 갱신 == 60HZ)
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    // BufferUsage : backBuffer를 어떤용도로 쓸 것인가 (우리는 RenderTarget을 출력용으로 사용할것임)
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // windowoutput으로 뭘 사용할 것인가  hWnd
    swapChainDesc.OutputWindow = hWnd;
    // sampling : 표본화
    // - 확대 축소할때 연산이 많아지는데 그것을 도와줄때 samping이 많음 , 확대 또는 축소 할때 색깔을 어떻게 섞어줄지 정해주는게 sampling임
    // 최대 sampling : 가장 클때만 미리 계산해놓음 , 다중 sampling : 여러 크기를 미리 계산해놓음
    // Count : 픽셀을 확대했을때 주변에 픽셀이 추가될텐데 몇개의 픽셀의 색을 더할것인가
    // Quality : 크기가 클 수록 연산이 추가됨 
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    // Winodwed : 창화면을 쓸 것 인지, 전체화면을 쓸 것인지
    swapChainDesc.Windowed = true;
    // device와 swapchain을 한번에 만들어주는 함수
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
    // BackBuffer 만드는 부분
    // 모니터의 표시되는 공간이 결국 2D이기에 2D를 씀
    ID3D11Texture2D* backBuffer;

    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);


    backBuffer->Release();

    // DSV
    ID3D11Texture2D* depthBuffer;

    D3D11_TEXTURE2D_DESC depthdesc;

   depthdesc. Width                  = WIN_WIDTH;
   depthdesc. Height                 = WIN_HEIGHT;
   depthdesc. MipLevels              = 1 ;  // 확대 축소
   depthdesc. ArraySize              = 1 ;
   depthdesc. Format                 = DXGI_FORMAT_D24_UNORM_S8_UINT; // depth를 24비트를 UNORM로  stencil을 UINT로 8비트 쓰겠다.
   depthdesc. SampleDesc.Count       = 1;
   depthdesc. SampleDesc.Quality     = 0;
   depthdesc. Usage                  = D3D11_USAGE_DEFAULT;
   depthdesc. BindFlags              = D3D11_BIND_DEPTH_STENCIL;
   depthdesc. CPUAccessFlags         = 0;
   depthdesc. MiscFlags              = 0;


    device->CreateTexture2D(&depthdesc, nullptr, &depthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvdesc = {};
    dsvdesc.Format = depthdesc.Format;
    dsvdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;


    device->CreateDepthStencilView(depthBuffer, &dsvdesc, &depthStencilView);

    depthBuffer->Release();
   
    deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);



}

void Device::Clear()
{
    float clearcolor[4] = { 0.5451f, 0.0f, 1.0f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearcolor);

    deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void Device::Present()
{
    // backbuffer를 frontbuffer로 바꿔주는 함수 이 과정을 진행하지 않으면 cloea를 하더라도 backbuffer에서 clear되기에 하얀 화면이 나옴
    swapchain->Present(0, 0);
}
