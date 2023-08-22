#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewPort();
    CreatePerspective();
}

Environment::~Environment()
{
    delete viewBuffer;
    delete projBuffer;
}

void Environment::CreateViewPort()
{
    D3D11_VIEWPORT viewPort;

    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;


    DC->RSSetViewports(1, &viewPort);
}

void Environment::CreatePerspective()
{
    viewBuffer = new MatrixBuffer();
    projBuffer = new MatrixBuffer();



    // 눈의 위치
    XMVECTOR eyepos = XMVectorSet(+0.0f, +0.0f, -3.0f, 1.0f);
    // 눈이 바라보는 방향
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);
    // 카메라의 위 방향 : y축 회전 방향을 정하기 위함
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyepos, focuspos, upvector);


    viewBuffer->SetData(view);

    // fov == Field Of View == 시야각
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: 바라볼 각도, aspectiveratio :  화면 비율 , (nearZ, farZ) : 절두체 크기
        XM_PIDIV2,
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    );

    projBuffer->SetData(projection);

    viewBuffer->SetVSBuffer(1);
    projBuffer->SetVSBuffer(2);

}
