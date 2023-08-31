#include "Framework.h"
#pragma region 1Day 기본
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
#pragma endregion

#pragma region 2Day bulid & initialize
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

#pragma endregion

#pragma region 3Day Rendering PipeLine
// 3DAY ----------------------------------------------------------------------------------------------------------------------------------------------
//
// (void**)를 사용하는 이유 : 포인트변수를 받을 예정이나 어떤 포인터가 올지 모를때 사용 == 어떤 반환형식이든 받겠다. 템플릿같다고 보면됨
// 
// 
// 
// 
// Rendering PipeLine
// - 렌더링 파이프 라인은 전부다 GPU에서 이루어지는 과정이다.
// - GPU에서 처리 후 CPU로 넘겨줌 (GPU : 업무를 처리 , CPU : 받은업무를 넘겨주기만함)
// - 3D공간을 2D의 화면으로 바꿔준다. 
// - (IA, VS, RS, PS, OM)기존의 있던단계 : 나머지는 기술의 발전으로 추가됬음
// - (IA, TS, RS, OM) 는 시스템의영역 
// - (VS, HS, DS, GS, PS) 은 사용자가 실제 다루는 영역
// Rendering PipeLIne 단계
// 
// 1. IA(Input Assembler) : 입력조립기
// - 응용프로그램에서 제공받은 정점 정보들을 조립한다.  
// == 입력된 데이터를 모으는 과정이다. == GPU가 CPU로부터 데이터를 가져오는과정
// - 입력 : 정점정보
// - asseble : 모으고 정리
// 
// 2. VS(Vertex Shader) : 정점좌표들을 연산한다.
// - Would Transform, View Transform, Projection Transform 으로 변환한다.
// -- Would Transform = local좌표계에서 would 좌표계로 변환 (local == object 각자 자신의 좌표계 : 객체는 자기 자신을 중심이기에) 
// --- Would : object 들을 모았을때 각각의 절대적인 위치를 나타낼 수 있도록 하는 절대적인 좌표계 ( World Transform은 SRT연산을 한다.)
// ---- SRT(scale. rotation. translation) : 각 정점의 위치를 1 X 4짜리 행렬로 계산한다.
// - View Transform : 카메라의 위치라고 생각하면됨 == 카메라의 좌표를 세상의 중심으로 하여 계산하는 것
// 
// - Projection Transform :실제로 내 시야에서 보이는것과 보이지 않는것을 구분하는 작업 == 카메라 위치에 따른 월드의 객체들을 투영하여 나타내줌
// -- 여기서는 보이는 부분을 2D로 나타낼 수 있도록 연산만 하고 실제 계산은 레스터라이저 단계에서한다.
// -- 2D에서는 이 작업이 평면으로 진행되며 3D에서는 절두체로 원근감이 있이 진행된다.
// 
// 
// Matrix끼리 곱할때 뒤에있는것이 부모가 된다. == 앞에있는 녀석의 중심점을 뒤에있는 녀석의 Would로 옮긴다.
// 
// - Shader인 이유 : shade(그늘)은 빛과 어둠이 있어야함 == shader는 GPU라고 생각하면 편함
// - HLSL(High Level Shading Language) : GPU를 다루는 언어
// 
// 
// 3. HS(Hull Shader) : 덮개셰이더 단계
// 
// 
// 4. TS(Tessellation Stage) : 한 메시의 삼각형을 더 잘게 쪼개서 새로운 삼각형을 만드는 작업 (세분화 작업)
// - Shader와 Stage는 크게 차이가 나는데 Hlsl을 사용하냐 안하냐 차이가 있다.
// -- hlsl : 실제 프로그래머가 코드를 작성하여 사용하는 영역
// -- 
// 
// 
// 5. DS(Domain Shader) : 영역셰이더 단계
// 
// 
// 6. GS(Geometry Shader) : 기하셰이더 단계
// - 이 단계는 정점 셰이더의 처리를 거친 정점데이터를 입력받는다. 
// -- 그리고 입력받은 정점에 정보를 추가하거나 삭제해 입력 기본 도형을 다른 여러 기본도형들로
// --- 확장 할 수도, 특정 조건에 따라서는 입력된 기본 도형을 출력하지않고 버릴 수 도 있다.
// - 기하셰이더의 흔한 용도는 하나의 점이나 선부늘 하나의 사각형으로 확장하는 것이다.
// 
// 7. RS(Rasterizer State) : 레스터라이저 단계
// - 이 단계에서는 투영된 3차원 삼각형으로부터 픽셀 색상들을 계산한다.
// -- Rasteriztation을 하는 동안 각 프리미티브를 구성하는 정점은 픽셀로 변환되고 
// -- 프리미티브 내부에 해당하는 점들은 보간을 통해 픽셀로 변환된다.
// 
// 
// 8. PS(Pixel Shader) :3D공간의 객체들의 색을 픽셀하나하나 계산해서 나타내는 과정
// - 2D로 변환된 정점들을 계산해준다.
// - PS단계에서 색깔이 생긴다. (VS단계에서는 색깔에 대하여 신경쓰지 않는다. 이유는 어차피 2D 변환 과정에서 가려지는 영역이 생기기 때문임)
// 
// 
// 
// 9. OM(Output Merger) : 출력 병합기
// - 계산된 모든 정점들을 모아서 출력해주는 단계
// -- 픽셀 셰이더가 생성한 픽셀 단편들은 이 단계로 입력된다. 최종적으로 픽셀의 색상을 생성해
// -- 렌더타깃으로 출력하는 단계이다. 이 단계에서 일부 픽셀 단편들이 깊이 판정이나 스텐실 판정에 의해 버려지게 되며
// -- 버려지지 않은 픽셀 단편은 후면 버퍼에 기록된다.
// -- 흔히 말하는 블렌딩도 이 단계에서 일어난다.
// 
// 
// 
// - 깊이-스텐실 검사 (Depth-Stencil Testing)
// -- 픽셀이 그려져야 하는지를 결정하기위해 깊이 값과 스텐실 값 데이터를 사용한다.
// -- 하나의 깊이 / 스텐실 버퍼만 활성화 되며 깊이-스텐실 버퍼에 스텐실 요소가 없으면 스텐실 검사는 항상 성공한다.
// -- 또한 깊이 - 스텐실 버퍼가 파이프라인에 연결되지 않으면 스텐실 검사는 항상 성공한다.
// 
// 
// hlsl에서 연두색 : sementic
// sementic을 쓰는 이유 : 우리가 사용할 변수의 용도를 써놓는다.
// sementic : 반환값의 용도
// SV Position : system value = 우리가 받은 VS를 RS로 보낸다.
// SV Target : 우리가 받은 PS를 OM으로 보낸다.
// 
#pragma endregion


#pragma region 4Day ViewPort설정, VS, PS 설정하기 및 점찍기
// 4DAY ----------------------------------------------------------------------------------------------------------------------------------------------
// -----OM이 RS보다 먼저 진행된 이유 : 현재 설정중이기에 순서가 크게 상관없다.------
//  
//  backbuffer->Release();
//
//  deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
//  
//  //////////////////////////////////////////////////////////////////
//  
//  D3D11_VIEWPORT viewPort;
//  
//  viewPort.TopLeftX = 0.0f;
//  viewPort.TopLeftY = 0.0f;
//  viewPort.Width = WIN_WIDTH;
//  viewPort.Height = WIN_HEIGHT;
//  viewPort.MinDepth = 0.0f;
//  viewPort.MaxDepth = 1.0f;
//  
//  
//  deviceContext->RSSetViewports(1, &viewPort);
//
// ------- framework에서 d3d는  library로 추가하는 이유
// - 우리가 cpp파일이 있는 경우는 .h로 추가가 가능하다
// -- library == cpp를 기계어로 번역해 놓은 것
// -- d3d는 cpp가 없으므로 library추가가 필요
// 
// 
// - Blob
// -- Shader이미지를 c++로 전환을 시켜놓는 아이 (shader는 c++언어가 아니기에 C++로 번역해주는 친구임)
// 
// 
// AlignedByteOffset이란?
// - 앞에 넘어간 데이터가 몇인가?? 
// 
// LayoutDesc를  Create할때 주소값을 넣어달라 하는데 주소값을 안 넣는 이유
// - 우리가 배열로 만들었기에
//
// BufferDesc에서 usage란?? 
// - API에서 Buffer를 어떻게 사용할지 정해주는것으로 
// ex) CPU에서 수정가능 GPU읽기가능 , 둘다 수정가능, 둘다읽기만 등등으로 설정가능
// 
// primitiveTopology란?? 
// - 일반적으로 외형적인 연결 모양을 의미
// - primitiveTopology은 주로 그래픽스 API의 렌더링 파이프라인 설정 중 하나로 사용됩니다. 
// - 다양한 primitiveTopology 값이 제공되며, 각 값은 다른 기하학적 모양을 나타냅니다.
// -- POINTLIST : 각점들의 리스트를 나타냄 각 점들은 독립적인 원소로 취급됨
// -- LINELIST  : 두개의 점을 연결해서 선을 만듦
// -- TRIANGLELIST : 세개의 점을 연결해서 면을 만듦
// -- LINESTRIP : 이전의 선의 정점 2개중 1개랑 연결된 새로운 점을 찍어서 선을 만듦
// -- TRIANGLESTRIP : 이전의 면에서 정점 3개중 2개랑 연결된 새로운 점 한개를 찍어서 면을 만듦
// 
// 다음 수업시간 : List와 Strip 차이 설명 
//



#pragma endregion

#pragma region 5Day Topology, vertex로 면그리기, 3Dvertex찍기
// 5DAY ----------------------------------------------------------------------------------------------------------------------------------------------
//
// - Topology : 외형적인 연결 모양
// -- 일반적으로 3D게임에서는 삼각형으로 폴리곤을 이용해서 제작함
// -- 폴리곤을 사용하는 이유 : 일일이 하나하나의 픽셀을 계산하는 것 보다 연산이 빠름
// -- 단점 : 계단현상이 생김 (안티 에일러싱이 필요함)
// 
// 
// - vector에서 주소값을 보낼때는 data()를 쓴다.
// -- vector[0]을 사용하면 데이터가 비어있을 시 문제가 생김
// 
// - NDC좌표계(Normalized Device Coordinate) : 화면 중앙을 0,0 으로 두고 화면을 비율로 사용하는 좌표계
// -- 단점 : 화면 크기가 달라지면 내용의 크기도 달라짐, Object이동시 x으로 1 만큼 이동과 y 로 1만큼 이동의 거리가 다름
// -- 그렇기에 우리가 계산하기 쉽게 상대 좌표계인 NDC좌표계를 화면 좌표계로 바꿔서 사용한다 == Rendering PipeLine 및 WVP
// 
// - TRIANGLE LIST로 사각형을 그리는법
// 1. 점을 6개 찍는다.
// 2. 점을 4개 찍고 어떻게 이을지 Index를 부여해준다.
// 
// - 프로그램에서 {} 으로 지역을 나눠주면 함수안에 새로운 이름없는 지역을 만들어 주는 것 이기에 같은 내용을 다시 쓸 때 유용함
// 
// -삼각형을 그릴때 시계방향으로만 그리는 이유
// - 효율적인 연산을 위해 반대방향 그림을 안보이게 처리함
// - backfaceculling에 의하여 그림은 그려지나 보이지를 않음
// 
// - 색은 거리에 따른 비율 : 선형보간으로 섞인다.
// 
// - 3D로 가기 위해서는 원근감이 필요함 : Projection이 필요함
// 
// - WVP는 ConstatBuffer로 slot을 할당하여 넘겨줘야함 == shader에서 cbuffer 버퍼명 : register(b0)
//////////////////////////////////////////////////////////////////////////////////////////////////////
// - WVP
// - wvp.world = XMMatrixIdentity();
// - // 눈의 위치 == 카메라 위치
// - XMVECTOR eyepos = XMVectorSet(+3.0f, +3.0f, -3.0f, 0.0f);
// - // 눈이 바라보는 방향 == 카메라가 바라보는 방향
// - XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 0.0f);
// - // 눈의 위쪽 벡터 (y축을 정해주기위함) == 카메라의 y축 (가로로 설치할 것인지, 세로로 설치할 것인지)
// - XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);

// - // 카메라 좌표를 만들 것이다. : LH = lefthand 좌표계로
// - wvp.view = XMMatrixLookAtLH(eyepos, focuspos, upvector);

// - // fov == Field Of View == 시야각
// - wvp.projection = XMMatrixPerspectiveFovLH
// - (   // angle: 바라볼 각도, aspectiveratio :  화면 비율 , (nearZ, farZ) : 절두체 크기
// -     XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f
// - );
// - {
// - 
// -     D3D11_BUFFER_DESC bufferDesc = {};
// -     bufferDesc.ByteWidth = sizeof(WVP);
// -     bufferDesc.Usage = D3D11_USAGE_DEFAULT;
// -     bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
// -     bufferDesc.CPUAccessFlags = 0;
// -     bufferDesc.MiscFlags = 0;
// -     bufferDesc.StructureByteStride = 0;
// - 
// - 
// -     //D3D11_SUBRESOURCE_DATA data;
// -     //data.pSysMem = vertices.data(); 
// -     // constant Buffer는 실시간으로 데이터를 받기에 initdata가 필요 없음
// -     device->CreateBuffer(&bufferDesc, nullptr, &constBuffer);}
////////////////////////////////////////////////////////////////////////////////
// 
// - RollpitchYaw  :  어떤방향으로 회전 할 지 명령 을 주는 함수
// 
//  
//

#pragma endregion
#pragma region 6Day 게임회사의 주요 부서, class 나누기, singleton Templetclass로 만들기(진행중)
// 6DAY ----------------------------------------------------------------------------------------------------------------------------------------------
// front end : 눈에 보이는 UI 또는 디자인을 다루는 직종
// - 유행에 매우 민감함, 오늘 만든 코드가 2~3년뒤엔 못 쓸 수 도 있음
// - 만드는 보람이 좀 있음 : 소비자의 직접적인 피드백을 받음
// back end : 눈에 보이지 않는 코드 ex) 서버 등을 다루는 직종
// - 한번만들면 계속 사용 가능, 유행에 민감하지 않음
// - 만드는 보람이 좀 적음 : 소비자의 직접적인 피드백이 없음
// 
// - 게임회사의 주요 부서
// 1. QA(Quality Assurance) : 품질보증팀 (teter) 
// -  주업무 : 버그를 재연함 (어떤 상황에서 버그가 터지는지 확인) 및 게임 퀄리티 확인
// 2. QC(Quality Control) : 품질관리팀
// 3. QM(Qulity Management) : 품질경영팀 
// 4. 운영사업팀 : BM 혹은 투자관련을 진행
// 5. 마케팅 팀
// 6. 그래픽. 원화, 사운드 등 예술팀
// 
// - interface : 순수가상함수로만 이루어진것
// 
// 
// 생성자 : 객체를 생성하는 함수가 아님
// - 객체가 생성될 때 호출되는 함수임 (객체를 생성하는게 아닌 객체가 생성되고 난 다음에 호출되는 것임 제일 먼저 호출되기에 보통 초기화를 여기서 진행함)
// -- 그렇기에 생성자를 따로 안 만들어도 기본생성자가 알아서 호출됨 
// 순수가상함수 : 자식에서 재정의를 해줘야함
// 소멸자 = 0 : 순수가상함수
// 소멸자 {} : 아무내용없는 함수 inline 함수로 순수가상함수가 아닌 가상함수임
// 
// DX에서 자주 하는 실수 : 업데이트에서 SRT갱신을 안함 주의할것!
// Update : frame단위로 데이터를 갱신
// Render : 받은 데이터로 그림을 그림
// 
// - hWnd를 Framework에 선언이 안 되는 이유 : extern으로 해야 하는 이유
// - Scene에서도 TutorialScene에서도 Program에서도 계속 Framework가 선언되기 때문에 hWnd를 계속 재정의 하게 됨으로써 에러가 발생함
// - extern은 전방선언의 개념으로 보면 됨 
// 
// - Templet은 모든 함수를 정의할 때 헤더에다가 정의를한다.
// - Templet의 T는 함수를 선언할때 정해진다. 
// - compile에서 cpp를 읽을때는 그래도 번역이 되지만 build에서 링크단계에서 T를 알지 못하기 때문에 헤더에서 정의를한다.
// 
//

#pragma endregion



#pragma region 7DAY - DirecX초기화(깊이스텐실버퍼, 표본화, flag, 비트연산), Device클래스화, Shader클래스화
// 깊이스텐실버퍼 차이
//
// 깊이: z축으로 얼마나 모니터와 가까운지 체크
// 스텐실 : z축으로 뒤쪽에 있는 아이들을 그리지않음 연산속도를 위함
// 
// 다중표본화 설정 : 픽셀을 한번만 계산하고 포괄도를 이용하여(주변 색과 비교하여 평균값) 최종색상결정 
// - 여러개의 샘플을 두고?? 근데 책에서는 이것도 4배사이즈로 만드는데?
// - 미리 연산이 끝난 표본을 여러개 만들어놓음
// - 큰사이즈 중간사이즈 작은사이즈 등등으로 만든후 근처 사이즈로 연산 -> 연산이 빠름
// 
// 초과표본화 설정 : 후면버퍼 크기를 실제보다 크게 만들어서 하향평균화 - 큰사이즈를 만들어서 줄여나간다.
// - 일단 큰사이즈 연산 때림
// - 확대든 축소든 일단 제일큰 사이즈로 연산 후 하향평균화
//																
// flag : 
// - 설정값 같은것 이라고 보면됨
// - << : shift 연신
// - 쉬프트 연산 : 2진수로 할당된 메모리 영역의 칸을 밀어낸다 라고 생각하면 됨
// - int a = 5;
// - ex) 5 == 101, << 를 사용 하면 10100이 됨 20
// - a에다가 2^1을 곱한다. < 는 한칸 << 는 두칸
// - flag는 최종적으로 정수값을 반환하는것으로 보면 됨.
// - 단지 비트연산을 통하여 2의 배수로 값을 넣음 : 비트연산 or을 걸면 두개의 조합이 됬을때 같은수가 안나옴 무조건 다른값이 나오기에 값으로 어떤게 or됬는지 유추가능
// - 설정값을 하나의 숫자로 보는데 어떤 애들의 조합인지 유추하기 위한것임 
// 
// #define은 상수 같은 숫자자체의 의미가 있는경우 이름을 붙여주기 위함
// 
// Driver 를 사용하지 않는 이유 : nullptr 같은것은 좀더 높은 디테일을 위함 ex) 디자이너들의 장치설정같은것들
//
// 
// mash : 그물망
// - 
// 
// instancing : ObjectFulling과 비슷하나 중복된 경우 하나의 Draw 를 공유함
//  
// HLSL의 경우 계속 수정하며 진행하는게 아닌 한번만 만들면 런타임내내 사용 가능하기에 관리하기위해 필요함
// 
// map : 정렬을 하기에 데이터를 조회 혹은 탐색할때 유리
// - 만들때 정렬 
// - 객체가 많으면 이게 나음
// unorderedmap : 정렬을 안 하기에 들어온대로 찾을 수 있음
// - 정렬을 안하기에 탐색시 한번 훑어야함
// - 객체가 많지 않으면 이게 나음
// 
// 
// 	static unordered_map<wstring, Shader*> shaders;
//  Shader를 담아두는 map이 하나만 필요하기에 static사용
//  singleton처럼 내가 자기자신의 포인터 변수를 갖고있으므로 동적할당 시 자기자신이 있어서 무한루프에 빠질 수 있기에 static으로 초기화를 한번만 핢
//  static으로 만들면 만들때 초기화 되서 무한루프에 빠지지 않고 이전의 값으로 함수를 진행함
//	static 은 하나의 변수로 모든 객체를 컨트롤 할때 사용함
//
// -전방선언할때 함수하나에서만 쓰고 말거면 함수 앞에다 써도됨
// 
// - reflection = Shader
// 
// SmartPointer : 
// - 다른 언어에서는 메모리는 할당됬으나 가리키는 포인터주소가 없으면 그 메모리 영역들을 모아서 삭제해주는 garvage collector가 있음
// - 동적할당을 해놓고 해제를 하지 않고 프로그램을 종료시 할당된 메모리를 해제할 방법이 없음
// - 이 문제를 해결하기 위해 자동적으로 서로 참조된 횟수를 기록하는 smartpointer가 C++에서 생김
// 
// 
//  
//
#pragma endregion

#pragma region 8Day Shader class화 마무리, Buffer만들기
//
// static map == singleton이라고 생각하면 됨
// 메모리 낭비를 최소화 하기위해 이런패턴을 많이 사용할 것 임
// 쉐이더 자체는 메모리 차이가 크게 나지 않지만 텍스쳐에서 메모리사용이 많이 되기에 이런 방식을 채용
// 
// float에 정수를 넣으면 int로 인식함, .0만 붙이면 더블로 인식함, .0f 라고 적어야 float으로 인식함
// 
// 
// 
// 명시적 형변환
// - casting으로 직접 어떤 것으로 변환할지 표시 
// - (VertexShader*) : c의 형변환 되든 안되는 일단 형변환
// -- 때로는 터져버려야 버그 찾기가 쉬워서 c의 형변환이 더 나을 수 있음
// - dynamic cast<VertexShader> : c++의 형변환 변환이 안되면 nullptr 반환
// 암묵적 형변환
// - int a = 10;
// - double b = a;
// 
// map에서는
// shader[file] = 
// 이런식으로 써도 인덱스가 없으면 생성하기에 사용가능 하나 벡터에서는 이런식으로 사용시 인덱스가 없어서 터짐
// 
// map이든 vector든 자료구조가 끝나면 비워주는 clear작업을 해줘야함
// - 안 그러면 딜리트 후 다시 for문 돌때 비어있는 공간에서 자료를 찾으러 순회함
// 
// ConstantBuffer : Shader에 정보를 넘겨주기 위함(어떤 정보가 넘어갈지 모름)
// - 대표적인게 WVP
// 
// Draw 전까지는 Rendering Pipe LINE 설정하는 단계이기에 순서는 상관 없음!
// Draw 부터 렌더링파이프라인시작!
// DC->DrawIndexed(indices.size(), 0, 0);
//
#pragma endregion

#pragma region 9Day Buffer
//
// DirectX 에 Resource는 두개다 
// 1. Buffer
// -  UpdateSubResource는 적절한 타이밍에 
// -
// 2. Texture
// -
// 
// Desc는 뭔가 사용하기위한 설명서 같은것임
// - 안에보면 접근가능한 매개변수들을 모아놓은 구조체임
// 
// 
// 
// enum D3D11_USAGE // Buffer를 만든 이후에 접근성을 다루는 함수임, 일단 최초 CPU가 데이터를 넘겨주기는 해야함
// {
//    D3D11_USAGE_DEFAULT = 0, - GPU는 읽고쓰기가능, CPU는 읽고쓰기 불가능
//        D3D11_USAGE_IMMUTABLE = 1, - GPU & CPU 둘다 쓰는것은 불가능 , CPU는 읽지도 못함
//        D3D11_USAGE_DYNAMIC = 2, - CPU가 쓸 수 있으나 읽지는 못함, GPU는 읽기만 가능하고 쓸 수 없음 : data를 넘기면 다시 받아서 읽지 못함 대신 수정해서 넘기는건 가능
//        D3D11_USAGE_STAGING = 3 - GPU에서 CPU가 MemoryCopy허용
//    } 	D3D11_USAGE;
// 
// constantBuffer, IndexBuffer는 D3D11_USAGE_DYNAMIC = 2를 사용
// 
// DYNAMIC을 사용 하기 위해서 CPUACCess도 바꿔줘야함
// 
// Map(), UnMap()
// - Map() : 사용가능하게 권한을 열어준다.
// - UnMap() : 열었던 권한을 다시 닫아준다.
// - Map()을 사용하지 않으면 memcpy를 써도 데이터가 안 들어감
// - UpdateSubResource를 쓰는게 콘스탄트 버퍼에 리소스를 넣어주는 것인데.
// - Map(),UnMap()으로 넘겨주는게  더 빠르기에 사용핢
// 
// 
// 
// 동적 : 원할때 할당 후 해제
// - 장점 : 메모리 관리에 효율적
// - 단점 : 실시간으로 프레임 드랍 같은게 생길 수 있음
// 정적 : 선언과 동시에 할당
// - 장점 :  
// - 단점 : 
// 
// 모니터의 크기는 정해져 있기 때문에 시야각이 커지면 그만큼 보는게 많아지기에 Object의 크기는 작아진다.
// - environment :: XM_PIDIV2, XM_PIDIV4 
// 
// 
// 
//
#pragma endregion

#pragma region 10Day - material, mesh, ImGui, 회전
//
// Meterial : Shader를 보완하는 내용
// Mesh :  Buffer를 보완하는 내용
// 
// indices와 vertices를 원본참조로 받는이유
// - 크기를 줄이기 위해
// - 배열은 기본적으로 값이 큰데 이것을 callbyvalue로 받게된다면 매우 비효율적이기에 배열은 기본적으로 포인터로 작동한다.
// - 원본참조로 크기를 줄이기 위함
//
// gimbal lock 현상
// 회전에서 중간값이 특정값일경우 축 나머지 축들이 겹쳐지는 현상 
// 두개의 회전축이 똑같은 값이 되면서 회전축이 3개에서 2개로 감소하게됨
// 이 문제를 해결하기위해 쿼터니언을 사용함
//  
// 숙제 gimbal lock 현상에 대하여 최대한 이해해오기
//
#pragma endregion

#pragma region 11Day - Transformation
//
// Matrix에서 뒤에다가 곱해준다는것 == 뒤에있는것에다가 상속시키겠다. == 앞에있는녀석을 뒤에있는녀석의 좌표계로 이동하겠다.
// 
// gimbal lock현상 : 회전을 오일러 연산을 사용하여 진행하게되면 축들을 순서대로 곱하게 되면서 상속관계가 맺어지게 되는데 중간값의 값이 90' 혹은 270'가 되버리면
// 축두개가 하나로 통합되며 축이 2개로 줄어드는 현상
// 
// 오일러 연산 - 롤피치요
// 
// 
// 쿼터니언 - 오일러보다 연산이 빠르며 짐벌락현상이 발생하지 않음
// 
// XMMATRIX 와 XMFLOAT4X4의 차이는 각 행렬의 원소들에 접근 할 수 있냐 없냐 차이가 있음
// XMFLOAT4X4는 (?,?) 에 있는 숫자에 접근이 가능
// 
// Transform을 상속시키는 방법과 컴포넌트패턴 (구성품처럼 따로 Transform을 만듦)을 사용하는데
// 컴포넌트 패턴은 Transform에 간접 접근을 해야하고 상속은 직접접근이 가능하기에 일반적으로 상속을 선호
// 하지만 만약에 상속을 두개이상 받지는 못 하기때문에 만약 싱글턴을 상속받을경우 컴포넌트로 해야함
//
#pragma endregion

#pragma region 12Day - depth view, world
//
// -depth view
// -픽셀에서 깊이를 측정해 그릴것과 안 그릴 것을 취합하는 것
// - zfighting : z축의 깊이가 비슷하여 지지직거리며 그려지는 현상
// 
//
#pragma endregion

#pragma region 13Day
//
// - f5는 실행이고 build와는 다른 개념임
// - 컴파일만 따로 해주는 단축키가 있음 ctrl + f7
// - 컴파일만 하는 경우 : 문법적으로 오류가 있는경우를 찾을때 빠르게 찾을 수 있음
// - 컴파일 : 프로그래밍 언어를 기계어로 번역하는것
// - 논리적인 오류를 찾는 방법 : 디버깅
// - 미리 컴파일된 헤더를 사용하는 것도 컴파일 내용이 수정된게 없으면 다시 할 필요가 없으니 사용하는것임
//  
// - UV Mapping  텍스쳐의 정보를 대응시켜서 픽셀을 찍는 방식
// - SamplerState : Desc같은거라고 보면됨 설정값들을 모아놓는것?
// - 일반적으로는 CPU가 작성한것을 따라서 Shader가 계산함
// - Shader에 적혀있는 형식을 보고 CPU가 유추해서 작성해주는 것 : reflection
// - reflection은 하드코딩이 들어감
// 
//
#pragma endregion

#pragma region 14Day
//
// - SRT
// - 제일 중요함 이해해야함
// - 
// indices순서 : {0,1,2} {2,1,3} 
// - 공식처럼 외울것!
// - indices를 시계방향으로 안그리면 백페이스 컬링으로 인하여 안 보임 - 메모리아끼기위해 뒷면을 그리지 않아서
// 
// - 얕은복사 : 데이터의 주소값을 복사해서 사용한다. 
// - 연결되어있기에 하나를 수정하면 다른것도 바뀜
// - 깊은복사 : 데이터의 객체자체를 복사해서 새로할당하여 사용
// - 연결되어있지 않기에 하나를 수정한다해서 다른것도 바뀌지 않음
// 
// 
//  - LOD : Level of detail
// - 멀리있는것 일 수록 흐리게 보이도록 디테일 설정하는것
// 
// 과제 박스완성시키
// - 클래스 하나 만들고
// - 큐브 회전하기
// 방법 2가지
// 1. 쿼드로 여섯개 그리기
// 2. 정점24개찍은다음에 UV값 할당하기
//
#pragma endregion

#pragma region 15Day, 16Day - TextureCube, TerrianScene(지형그리기 ex) 높낮이)
//
// 
// 
// Difusemap은 난반사로 깊이나 색상으로 입체감을 조성한다.
//
// 회전에서 방향을 정하는 방식 : 각축의 +에서 -를 바라봤을때 +회전은 시계방향 - 회전은 반 시계방향
// 
// 정점정보인 wireframe을 보기위해서는
// ResterizeState를 건드려야함
// 
// width와 height로 정점을 찍었기에 원하는 width만큼 정점을 찍기 원하면 indices를 빼줌 
// 
//
#pragma endregion


#pragma region 17Day - 
// -  
// - Quarter view"는 게임 및 그래픽 디자인 분야에서 사용되는 용어로, 객체나 장면을 보는 시각적인 관점을 나타낸다
// -- "Quarter view"는 "1/4 뷰" 또는 "사분면 뷰"로 번역될 수 있다. ex) 디아, 리니지, 등 위에서 아래로 내려보는 카메라
// - 
// - 카메라의 종류는 다양함
// - 캐릭터의 종속되어 따라가는 카메라가 있고
// - 캐릭터가 보고있는것만 볼 수 있는 카메라가있고
// - 자유롭게 움직일 수 있는 카메라가 있음
// -
// - 배열은 무조건 이어져 있기때문에 하나만 알아도 뒤에를 이어서 쓸 수 있음
// - 숫자의 포인터일 경우 숫자의 배열이다. ex) uint_t == unsigned charactor == 숫자의 배열
// 
// - 프로그램에서는 나누기보다 곱하기 연산을 많이 사용하는데 그 이유는 곱하기가 나누기보다 연산이 빠르기 때문임
// 
// - vector<Vector4> color(size); == color.resize(size)
// --두개는 같은 것임
// 
// - 표기법
// Camel Case:
// - Camel Case는 첫 번째 단어를 소문자로 시작하고 이후의 단어들의 첫 글자는 대문자로 작성하는 방식입니다.예를 들어 : myVariableName, calculateTotalAmount.
// - 
// - Pascal Case :
// - Pascal Case는 모든 단어의 첫 글자를 대문자로 작성하는 방식입니다.주로 클래스나 타입의 이름을 작성할 때 사용됩니다.예를 들어 : MyClassName, CalculateTotalAmount.
// - 
// - Snake Case :
// - Snake Case는 단어를 모두 소문자로 작성하고 단어 사이를 밑줄(_)로 구분하는 방식입니다.예를 들어 : my_variable_name, calculate_total_amount.
// - 
// - Kebab Case :
// - Kebab Case는 단어를 모두 소문자로 작성하고 단어 사이를 하이픈(-)으로 구분하는 방식입니다.예를 들어 : my - variable - name, calculate - total - amount.
// - 
// - Hungarian Notation :
// - Hungarian Notation은 변수 이름 앞에 해당 변수의 데이터 타입이나 특성을 나타내는 접두사를 붙이는 방식입니다.예를 들어 : strName(문자열 이름), nCount(정수 카운트).
// - 
// - Screaming Snake Case : 일반적인 상수 표기할때 사용
// - Screaming Snake Case는 모든 단어를 대문자로 작성하고 단어 사이를 밑줄(_)로 구분하는 방식입니다.대부분 상수나 매크로의 이름에 사용됩니다.예를 들어 : MAX_VALUE, PI_CONSTANT.
// - 표기법을 나누는 구분 : 띄어쓰기를 무엇으로 할것인가?
// 
// -
#pragma endregion