#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{ // �ʱ�ȭ

    // Shader ���� �� ����
    vertexShader = Shader::GetVS(L"Tutorial");
    pixelShader = Shader::GetPS(L"Tutorial");

    //////////////////////////////////////////////////////////////////

    {

        vertices = {
            VertexColor({ -1.0f, +1.0f, -1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}),
            VertexColor({ +1.0f, +1.0f, -1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}),
            VertexColor({ -1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}),
            VertexColor({ +1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),

            VertexColor({ -1.0f, +1.0f, +1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}),
            VertexColor({ +1.0f, +1.0f, +1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}),
            VertexColor({ -1.0f, -1.0f, +1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}),
            VertexColor({ +1.0f, -1.0f, +1.0f}, {1.0f, 0.0f, 0.0f, 1.0f})



        };

        vertexBuffer = new VertexBuffer(vertices);

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
        6,3,7

    };
    
    indexBuffer = new IndexBuffer(indices);

    worldBuffer      = new MatrixBuffer();
    viewBuffer       = new MatrixBuffer();
    projBuffer       = new MatrixBuffer();

  
    
    // ���� ��ġ
    XMVECTOR eyepos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
    // ���� �ٶ󺸴� ����
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);
    // ī�޶��� �� ���� : y�� ȸ�� ������ ���ϱ� ����
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyepos, focuspos, upvector);


    viewBuffer->SetData(view);

    // fov == Field Of View == �þ߰�
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: �ٶ� ����, aspectiveratio :  ȭ�� ���� , (nearZ, farZ) : ����ü ũ��
        XM_PIDIV4,
        WIN_WIDTH / WIN_HEIGHT, 
        0.1f, 
        1000.0f
    );

    projBuffer->SetData(projection);

}

TutorialScene::~TutorialScene()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
    delete viewBuffer;
    delete projBuffer;
}

void TutorialScene::Update()
{
}

void TutorialScene::PreRender()
{
}

void TutorialScene::Render()
{
   

    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 

    vertexShader ->SetShader();
    pixelShader  ->SetShader();

    vertexBuffer->IASetBuffer();
    indexBuffer->IASetBuffer();


    static float angle = 0.0f;

    angle += 0.0001f;

    XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f);

    worldBuffer->SetData(world);


    //WVP
    worldBuffer     ->SetVSBuffer(0);
    viewBuffer      ->SetVSBuffer(1);
    projBuffer      ->SetVSBuffer(2);



    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
    DC->DrawIndexed(indices.size(), 0,0);
    

    
  


}

void TutorialScene::PostRender()
{
}
