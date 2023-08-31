#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewPort();
    CreatePerspective();
}

Environment::~Environment()
{
   
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
   
    projBuffer = new MatrixBuffer();



   

    // fov == Field Of View == 시야각
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: 바라볼 각도, aspectiveratio :  화면 비율 , (nearZ, farZ) : 절두체 크기
        XM_PIDIV2,
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    );

    projBuffer->SetData(projection);

    projBuffer->SetVSBuffer(2);

}
