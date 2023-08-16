#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{ // 초기화


   



    //////////////////////////////////////////////////////////////////

    D3D11_VIEWPORT viewPort;

    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;


    DC->RSSetViewports(1, &viewPort);

    

    
   


   


    


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
        DEVICE->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
    }

    // InndexBuffer

    indices =
    {

        // front
        0,1,2,
        2,1,3,

        // 우측 면
        1,5,3,
        3,5,7,

        // 위쪽 면
        0,4,1,
        1,4,5,

        // 왼쪽 면
        4,0,6,
        6,0,2,

        // 뒤쪽 면
        5,4,7,
        7,4,6,

        // 바닥면
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
        DEVICE->CreateBuffer(&bufferDesc, &data, &IndexBuffer);

    }

    // WVP
    wvp.world = XMMatrixIdentity();
    // 눈의 위치
    XMVECTOR eyepos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
    // 눈이 바라보는 방향
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);
    // 카메라의 위 방향 : y축 회전 방향을 정하기 위함
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);



    // 카메라 좌표를 만들 것이다. : LH = lefthand 좌표계로
    wvp.view = XMMatrixLookAtLH(eyepos, focuspos, upvector);



    // fov == Field Of View == 시야각
    wvp.projection = XMMatrixPerspectiveFovLH
    (   // angle: 바라볼 각도, aspectiveratio :  화면 비율 , (nearZ, farZ) : 절두체 크기
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
        // constant Buffer는 실시간으로 데이터를 받기에 initdata가 필요 없음
        DEVICE->CreateBuffer(&bufferDesc, nullptr, &constBuffer);
    }

}

TutorialScene::~TutorialScene()
{
   
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
   
    // 정점찍기

    stride = sizeof(VertexColor);
    offset = 0;


    
    DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    DC->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 여기 역시 설정 하는 과정이기에 순서 중요하지 않음 

    
    // 여기부터 실제 렌더링 파이프라인이 시작되기에 이전까지는 순서 상관 없음!
    //deviceContext->Draw(indeices.size(), 0, 0);
    DC->DrawIndexed(indices.size(), 0, 0);





    // WVP
    WVP data;

    data.world = XMMatrixTranspose(wvp.world);
    data.view = XMMatrixTranspose(wvp.view);
    data.projection = XMMatrixTranspose(wvp.projection);

    DC->UpdateSubresource(constBuffer, 0, nullptr, &data, 0, 0);
    DC->VSSetConstantBuffers(0, 1, &constBuffer);

    static float angle = 0.0f;

    angle += 0.001f;

    wvp.world = XMMatrixRotationRollPitchYaw(angle, angle, angle);



  

}

void TutorialScene::PostRender()
{
}
