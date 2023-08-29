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



    // ���� ��ġ
    XMVECTOR eyepos = XMVectorSet(+0.0f, -0.0f, -2.0f, 1.0f);
    // ���� �ٶ󺸴� ����
    XMVECTOR focuspos = XMVectorSet(+0.0f, +0.0f, 0.0f, 1.0f);                                                                                                                      
    // ī�޶��� �� ���� : y�� ȸ�� ������ ���ϱ� ����
    XMVECTOR upvector = XMVectorSet(+0.0f, +1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(eyepos, focuspos, upvector);


    viewBuffer->SetData(view);

    // fov == Field Of View == �þ߰�
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: �ٶ� ����, aspectiveratio :  ȭ�� ���� , (nearZ, farZ) : ����ü ũ��
        XM_PIDIV2,
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    );

    projBuffer->SetData(projection);

    viewBuffer->SetVSBuffer(1);
    projBuffer->SetVSBuffer(2);

}
