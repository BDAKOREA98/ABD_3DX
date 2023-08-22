// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <unordered_map>




#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace std;
using namespace DirectX;

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "imGui.lib")




#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define DEVICE	 Device::GetInstance()->GetDevice()	
#define DC		 Device::GetInstance()->GetDC()		




// Utility
#include "Utility/Singleton.h"

// System
#include "System/Device.h"

// Render :: Shader
#include "Render/Shader/Shader.h"
#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"

// Render
#include "Render/Material.h"

// Render :: Buffer
#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstantBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"

// Render
#include "Render/Mesh.h"


#include "System/Environment.h"

#include "Object/BasicObject/Cube.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"

// main
#include "Program.h"

extern HWND hWnd;