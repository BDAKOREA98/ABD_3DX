#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{ // 초기화

    // Shader 생성 및 설정
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
        6,3,7

    };
    
    indexBuffer = new IndexBuffer(indices);

    worldBuffer      = new MatrixBuffer();
    viewBuffer       = new MatrixBuffer();
    projBuffer       = new MatrixBuffer();

  
    
    // 눈의 위치
    XMVECTOR eyepos = XMVectorSet(+3.0f, +3.0f, -3.0f, 1.0f);
    // 눈이 바라보는 방향
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);
    // 카메라의 위 방향 : y축 회전 방향을 정하기 위함
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyepos, focuspos, upvector);


    viewBuffer->SetData(view);

    // fov == Field Of View == 시야각
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: 바라볼 각도, aspectiveratio :  화면 비율 , (nearZ, farZ) : 절두체 크기
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
   

    // 여기 역시 설정 하는 과정이기에 순서 중요하지 않음 

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



    // 여기부터 실제 렌더링 파이프라인이 시작되기에 이전까지는 순서 상관 없음!
    DC->DrawIndexed(indices.size(), 0,0);
    

    
  


}

void TutorialScene::PostRender()
{
}
