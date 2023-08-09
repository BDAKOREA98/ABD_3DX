// ABD_first.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

ID3D11Device* device;
ID3D11DeviceContext* deviceContext;

IDXGISwapChain* swapchain;
ID3D11RenderTargetView* renderTargetView;




void Initialize();
void Render();
void Release();




HWND hWnd;






// 전역 변수: 변수를 선언함
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ABDFIRST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ABDFIRST));

    Initialize();
    MSG msg;

    // 기본 메시지 루프입니다: 메시지를 번역해서 전달함

    while (true)
    {


        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            }
        else 
        {
            // TODO : Update, Render

            Render();

        }

    }

    Release();
    
    return (int) msg.wParam;
}



void Initialize()
{
    // 초기화


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

    // 모니터의 표시되는 공간이 결국 2D이기에 2D를 씀
    ID3D11Texture2D* backbuffer;

    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
    
    device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);


    backbuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
    
}

void Render()
{
    float clearcolor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearcolor);


    // backbuffer를 frontbuffer로 바꿔주는 함수 이 과정을 진행하지 않으면 cloea를 하더라도 backbuffer에서 clear되기에 하얀 화면이 나옴
    swapchain->Present(0, 0);




}

void Release()
{
    device->Release();
    deviceContext->Release();
    swapchain->Release();
    renderTargetView->Release();




}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ABDFIRST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ABDFIRST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

// 윈도우창을 생성하는 함수
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    RECT rect = { 0,0, WIN_WIDTH, WIN_HEIGHT };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

     hWnd = CreateWindowW
     (
      szWindowClass, 
         szTitle, 
         WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT, 0,
      
          rect.right - rect.left, rect.bottom - rect.top,
         nullptr, nullptr,  hInstance, nullptr
     );


     SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//                             번역된 메시지가 들어옴
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
