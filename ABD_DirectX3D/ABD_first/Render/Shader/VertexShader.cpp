#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    ///VertexShader
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    file = L"_Shader/" + file + L".hlsl";



    
    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &blob,
        nullptr

    );

    DEVICE->CreateVertexShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &vertexShader
    );


    CreateInputLayout();

}

VertexShader::~VertexShader()
{
    vertexShader -> Release();
    inputLayout  -> Release();

}

void VertexShader::SetShader()
{
    DC->IASetInputLayout(inputLayout);
    DC->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::CreateInputLayout()
{
    // InputLayout
    ////////////////////////////////////
    D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};
    LayoutDesc[0].SemanticName = "POSITION";
    LayoutDesc[0].SemanticIndex = 0;
    LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    LayoutDesc[0].InputSlot = 0;
    LayoutDesc[0].AlignedByteOffset = 0;
    LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    LayoutDesc[0].InstanceDataStepRate = 0;

    LayoutDesc[1].SemanticName = "COLOR";
    LayoutDesc[1].SemanticIndex = 0;
    LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    LayoutDesc[1].InputSlot = 0;
    LayoutDesc[1].AlignedByteOffset = 12;
    LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    LayoutDesc[1].InstanceDataStepRate = 0;

 
    ARRAYSIZE(LayoutDesc);


    DEVICE->CreateInputLayout
    (   // 주소값을 넣어달라는데 그냥 넣는 이유 : 우리가 배열로 만들었으니까
        LayoutDesc,
        ARRAYSIZE(LayoutDesc),
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );

}
