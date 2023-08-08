//
// 1DAY ----------------------------------------------------------------------------------------------------------------------------------------------
// vcx == projectfile : 지우면 안됨!
//
// DirectX3D == solution경로
// first == project경로
// 
// 절대경로 : 컴퓨터에있는 절대적인  값(파일을 옮길때마다 바뀌기 때문에 잘 사용 안함)
// 
// 상대경로 : 프로젝트부터 시작되는 값(프로젝트부터 시작되기에 파일을 옮겨도 타고가기 쉬움)
// 
// API를 배운 이유 : 창을 띄우기 위해 & 메시지 루프를 받기 위해
// 
// message는 queu 형식으로 나감
// 
// 모든 파일 표시 : 폴더같은것을 만들면 폴더로 표시
// 
// 2DAY ----------------------------------------------------------------------------------------------------------------------------------------------
// 
// c코드들이라 사용할 필요 없음
// #include <stdlib.h>
// #include <malloc.h>
// #include <memory.h>
// #include <tchar.h>
// 
// build : 
// bulid의 4가지 단계 
// 1. 전처리기 : 매크로(문자를 치환하는 것) 읽기, 주석 없애기, inline함수(헤더에서 정의된 함수)
// - #define A 4+4,  A*A == 4+4*4+4
// - int B = 4+4,  B*B == 8*8
// 
// 2. comfile : 고급어를 저급어(기계어)로 번역하는 단계. (cpp를 번역함)
// - cpp가 컴파일 된것이 라이브러리(cpp를 기계어로 번역해서 뿌려놓은것)
// - 
// 
// 3. 어셈블러 : 기계어와 일대일 대응이 되는 어셈블리어로 번역을 해준다.
// - 2진수 기계어: 001000 00001 00000 0000000000001010
// - 16진수 기계어 : 20 20 00 00 00 00 00 0A
// - 어셈블리어 : addi $0, $1, 10[8] // 뜻: $0 = $1 + 1010 (2)
// 
// 4. 링커 : 컴파일러가 생성한 기계어(목적 코드)들을 서로 연결시켜주는 프로그램.
// - 컴파일러가 프로그래밍 언어를 해석해서 기계어로 번역하는 작업(컴파일)을 수행한다면 
// - 링커는 이렇게 나온 결과물들을 하나로 연결시켜 실행 파일을 만드는 작업(링킹, Linking)을 수행한다.
// 
// DirectX : API들이 모여있는것(CUI 에서 GUI 로 넘어가는 과정에서 CPU가 그래픽을 그리는것만으로도 힘들어해서 만들어진 프로세스)
// Direct2D + Direct3D + DirectDraw + etc == DirectX
// - 더좋은 그래픽을 속도가 빠르게 그리도록 발전해왔음 == GAME을 위해 만듬
// - DirecX는 GPU가 없을때 만들어 졌음 == GPU에 접근하기 위해 만들어 진것이 아님
// - 
// - CUI : Charactor User Interface == 문자를 이용한 유저 인터페이스 (DOS운영체제)
// - GUI : Graphic User Interface == 그랠픽을 이용한 유저 인터페이스 (WINDOW운영체제)
// 
// Client개발자 : 게임의 관련된 모든것을 만드는 개발자(캐릭터, 데미지, 맵, 업데이트 등등, 수학&물리를 개념을 이해한뒤 사용하면 됨)
// Engene개발자 : 게임을 만들기 위한 도구(엔진)를 만드는 개발자(Object를 쉽게 만드는 함수등등 , 수학&물리를 잘 이용할 줄 알아야함)
// 
// 
// ID3D11 == Interface Direct
// Device : CPU 사용함 (Create같은 만드는 함수를 가짐)
// DeviceContext : GPU 사용함 (Set, Render등 그리는 함수를 가짐) DeviceContext == HDC
// 
// SwapChain : doublebuffering을 위해 사용함 
// - doublebuffering : 화면이 두개 인 것이 아닌 화면을 그려주는 도화지가 두개인것 
// - 복사과정이 없기에 연산이 빨라짐
// - Buffer : 완충제(데이터가 담겨있는 공간) CPU와 GPU의 속도차이를 완충시켜줌 == 데이터가 담겨있는 임시저장공간
// --  
// -
// rederTargetView : backbuffer를 관리 하는 객체
// - view가 들어가는 변수들은 전부 GPU에서 다룬다고 보면 됨
// - rederTargetView를 이용하면 PIP가 가능해짐 Picture In Picture (화면안에 화면이 하나 더 있는것)
// -- 미니맵 같은것도 RTV를 이용함, main화면에서 일부를 blur처리하거나 할때도 사용함
// -- RTV는 카메라 1대라고 생각하면 됨
// -- RTV는 최대 8개까지 가능
// 
// CPU : 똑똑한 대학교수(어려운 문제를 계산함) 
// GPU : 대학원생(단순하지만 많은 문제를 계산함)
// - 1개의 연산만 봤을때는 CPU가 빠르나 연산이 많아지면 GPU가 빠름
// - GPU가 많은 연산을 해야하는 이유 pixel하나하나의 연산을 해줘야 하기때문임
// 
// swapChainDesc {
// 
// DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
// // BufferCount : Backbuffer가 몇개 있는가
// swapChainDesc.BufferCount = 1;
// // BackBuffer의 크기를 정해줌
// swapChainDesc.BufferDesc.Width = WIN_WIDTH;
// swapChainDesc.BufferDesc.Height = WIN_HEIGHT;
// // Format : RGBA의 color를 normalize된 값으로 넣겠다.
// // - RGBA : 8bit * 4  = 32 bir, unorm : unsigned int = 0 ~ 1
// swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
// // RefeshRate : 새로고침빈도 == 갱신빈도 : 얼마나 자주 갱신시키는가 == 모니터 주사율 (1초에 60번 갱신 == 60HZ)
// swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
// swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
// // BufferUsage : backBuffer를 어떤용도로 쓸 것인가 (우리는 RenderTarget을 출력용으로 사용할것임)
// swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// // windowoutput으로 뭘 사용할 것인가  hWnd
// swapChainDesc.OutputWindow = hWnd;
// // sampling : 표본화
// // - 확대 축소할때 연산이 많아지는데 그것을 도와줄때 samping이 많음 , 확대 또는 축소 할때 색깔을 어떻게 섞어줄지 정해주는게 sampling임
// // 최대 sampling : 가장 클때만 미리 계산해놓음 , 다중 sampling : 여러 크기를 미리 계산해놓음
// // Count : 픽셀을 확대했을때 주변에 픽셀이 추가될텐데 몇개의 픽셀의 색을 더할것인가
// // Quality : 크기가 클 수록 연산이 추가됨 
// swapChainDesc.SampleDesc.Count = 1;
// swapChainDesc.SampleDesc.Quality = 0;
// // Winodwed : 창화면을 쓸 것 인지, 전체화면을 쓸 것인지
// swapChainDesc.Windowed = true;
// }
// 
// 3DAY ----------------------------------------------------------------------------------------------------------------------------------------------
//


