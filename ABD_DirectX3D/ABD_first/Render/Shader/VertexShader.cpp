#include "Framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    ///VertexShader
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    
    
    D3DCompileFromFile
    (
        file.c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
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
    // blob에서 쉐이더 정보를 CPU로 가져옴 
    D3DReflect(blob->GetBufferPointer(), blob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
    // 가져온 쉐이더 정보에 따라서 쉐이더 Desc를 만듦
    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName         = paramDesc.SemanticName;
        elementDesc.SemanticIndex        = paramDesc.SemanticIndex;
        elementDesc.InputSlot            = 0;
        elementDesc.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask == 1)
        {                                   // DXGI의 Format을 설정함
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32_UINT;  //
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask <= 3)    // mask가 메모리 크기를 결정해줌(원소의 갯수)
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask <= 7)   // componentType 
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask <= 15)
        {
                 if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)  elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }        

        string semantic = paramDesc.SemanticName;

        if (semantic == "POSITION") // position은 매트릭스 연산을 위해 4차원으로 넘기기 때문에 R32G32B32로 넘기지만 받을땐 FLoat4
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        inputLayouts.push_back(elementDesc);
    }   

    DEVICE->CreateInputLayout
    (
        inputLayouts.data(),
        inputLayouts.size(),
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );

}
