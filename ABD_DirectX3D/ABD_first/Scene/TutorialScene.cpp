#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{ // �ʱ�ȭ


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

    // ������� ǥ�õǴ� ������ �ᱹ 2D�̱⿡ 2D�� ��
    ID3D11Texture2D* backBuffer;

    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);


    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    //////////////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;

    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;


    deviceContext->RSSetViewports(1, &viewPort);



    ///VertexShader
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* vertexBlob;
    D3DCompileFromFile
    (
        L"_Shader/VertexTutorial.hlsl",
        nullptr,
        nullptr,
        "main",
        "vs_5_0",
        flags,
        0,
        &vertexBlob,
        nullptr

    );

    device->CreateVertexShader
    (
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        nullptr,
        &vertexShader
    );


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


    device->CreateInputLayout
    (   // �ּҰ��� �־�޶�µ� �׳� �ִ� ���� : �츮�� �迭�� ��������ϱ�
        LayoutDesc,
        ARRAYSIZE(LayoutDesc),
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        &inputLayout
    );

    vertexBlob->Release();


    ////////PixelShader

    ID3DBlob* pixelBlob;
    D3DCompileFromFile
    (
        L"_Shader/PixelTutorial.hlsl",
        nullptr,
        nullptr,
        "main",
        "ps_5_0",
        flags,
        0,
        &pixelBlob,
        nullptr

    );

    device->CreatePixelShader
    (
        pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(),
        nullptr,
        &pixelShader
    );


    pixelBlob->Release();


    // vertex
    // Vertex BUFFER(0.0f, 0.0f, 0.0f);

    {

        vertices = {
            VertexColor({ -1.0f, +1.0f, -1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
            VertexColor({ +1.0f, +1.0f, -1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}),
            VertexColor({ -1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}),
            VertexColor({ +1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

            VertexColor({ -1.0f, +1.0f, +1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
            VertexColor({ +1.0f, +1.0f, +1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}),
            VertexColor({ -1.0f, -1.0f, +1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}),
            VertexColor({ +1.0f, -1.0f, +1.0f}, {0.0f, 0.0f, 1.0f, 1.0f})



        };



        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(VertexColor) * vertices.size();
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;


        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = vertices.data(); // 
        device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
    }

    // InndexBuffer

    indices =
    {

        // front
        0,1,2,
        2,1,3,

        // ���� ��
        1,5,3,
        3,5,7,

        // ���� ��
        0,4,1,
        1,4,5,

        // ���� ��
        4,0,6,
        6,0,2,

        // ���� ��
        5,4,7,
        7,4,6,

        // �ٴڸ�
        2,3,6,
        6,3,7,

    };

    {



        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;


        D3D11_SUBRESOURCE_DATA data;

        data.pSysMem = indices.data(); // 
        device->CreateBuffer(&bufferDesc, &data, &IndexBuffer);

    }

    // WVP
    wvp.world = XMMatrixIdentity();
    // ���� ��ġ
    XMVECTOR eyepos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
    // ���� �ٶ󺸴� ����
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);
    // ī�޶��� �� ���� : y�� ȸ�� ������ ���ϱ� ����
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);



    // ī�޶� ��ǥ�� ���� ���̴�. : LH = lefthand ��ǥ���
    wvp.view = XMMatrixLookAtLH(eyepos, focuspos, upvector);



    // fov == Field Of View == �þ߰�
    wvp.projection = XMMatrixPerspectiveFovLH
    (   // angle: �ٶ� ����, aspectiveratio :  ȭ�� ���� , (nearZ, farZ) : ����ü ũ��
        XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f
    );

    {

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(WVP);
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;


        //D3D11_SUBRESOURCE_DATA data;
        //data.pSysMem = vertices.data(); 
        // constant Buffer�� �ǽð����� �����͸� �ޱ⿡ initdata�� �ʿ� ����
        device->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
    }

}

TutorialScene::~TutorialScene()
{
    device->Release();
    deviceContext->Release();
    swapchain->Release();
    renderTargetView->Release();
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
    float clearcolor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearcolor);

    // �������

    stride = sizeof(VertexColor);
    offset = 0;


    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);


    deviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);




    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 


    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);

    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
    //deviceContext->Draw(indeices.size(), 0, 0);
    deviceContext->DrawIndexed(indices.size(), 0, 0);





    // WVP
    WVP data;

    data.world = XMMatrixTranspose(wvp.world);
    data.view = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    deviceContext->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

    static float angle = 0.0f;

    angle += 0.001f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, angle);



    // backbuffer�� frontbuffer�� �ٲ��ִ� �Լ� �� ������ �������� ������ cloea�� �ϴ��� backbuffer���� clear�Ǳ⿡ �Ͼ� ȭ���� ����
    swapchain->Present(0, 0);

}

void TutorialScene::PostRender()
{
}
