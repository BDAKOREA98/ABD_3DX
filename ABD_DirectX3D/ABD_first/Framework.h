﻿// header.h: 표준 시스템 포함 파일
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
#pragma comment(lib, "dxguid.lib")
#include "DirectXTex.h"
#include "DirectXTex.inl"
#pragma comment(lib,"DirectXTex.lib")

using namespace std;
using namespace DirectX;
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#pragma comment(lib, "imGui.lib")



#define RED		{ 1.0f, 0.0f, 0.0f, 1.0f }
#define BLUE	{ 0.0f, 0.0f, 1.0f, 1.0f }
#define WHITE	{ 1.0f, 1.0f, 1.0f, 1.0f }
#define GREEN	{ 0.0f, 1.0f, 0.0f, 1.0f }
#define PURPLE	{ 0.54f, 0.0f, 1.0f, 1.0f }
#define PI 3.141592

#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define DEVICE	 Device::GetInstance()->GetDevice()	
#define DC		 Device::GetInstance()->GetDC()		

#define KEY_UP(p) Keyboard::GetInstance()->Up(p)
#define KEY_PRESS(p) Keyboard::GetInstance()->Press(p)
#define Key_DOWN(p) Keyboard::GetInstance()->Down(p)



typedef XMMATRIX Matrix;
typedef XMFLOAT4 Vector4;
typedef XMFLOAT2 Vector2;



// Utility
#include "Utility/Singleton.h"
#include "Utility/Vector3.h"
#include "Utility/Keyboard.h"
#include "Utility/Time.h"
// Object :: Transform
#include "Object/Transform.h"



// System
#include "System/Device.h"

// Render :: Shader
#include "Render/Shader/Shader.h"
#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"



// Render
#include "Render/Texture/Texture.h"
#include "Render/Material.h"

// Render :: Buffer
#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstantBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"

// Render
#include "Render/Mesh.h"

// Render :: State
#include "Render/State/RasterizerState.h"
#include "Render/State/SamplerState.h"
#include "Render/State/StateManager.h"

// System
#include "System/Environment.h"
#include "System/Camera.h"

// Object
#include "Object/BasicObject/Cube.h"
#include "Object/BasicObject/DiffuseCube.h"
#include "Object/BasicObject/Quad.h"
#include "Object/BasicObject/Box.h"
#include "Object/BasicObject/TextureCube.h"
#include "Object/LandScape/Terrain.h"
#include "Object/BasicObject/Robot.h"
#include "Object/BasicObject/Sphere.h"



// Scene
#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"
#include "Scene/TextureScene.h"
#include "Scene/RobotScene.h"
#include "Scene/BoxScene.h"
#include "Scene/TerrainScene.h"

// main
#include "Program.h"

extern HWND hWnd;
extern Vector3 MousePos;