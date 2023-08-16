#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{ // �ʱ�ȭ


   



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
        DEVICE->CreateBuffer(&bufferDesc, &data, &IndexBuffer);

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
   
    // �������

    stride = sizeof(VertexColor);
    offset = 0;


    
    DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

    DC->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 

    
    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
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
