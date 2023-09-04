#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewPort();
    CreatePerspective();

    lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
   
    delete projBuffer;
    delete lightBuffer;

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



   

    // fov == Field Of View == �þ߰�
    XMMATRIX projection = XMMatrixPerspectiveFovLH
    (   // angle: �ٶ� ����, aspectiveratio :  ȭ�� ���� , (nearZ, farZ) : ����ü ũ��
        XM_PIDIV4,
        WIN_WIDTH / WIN_HEIGHT,
        0.1f,
        1000.0f
    );

    projBuffer->SetData(projection);

    projBuffer->SetVSBuffer(2);

}

void Environment::SetEnvironment()
{
    
    lightBuffer->SetVSBuffer(3);
    lightBuffer->SetData(lightDirection);
}

void Environment::PostRender()
{
    

    ImGui::SliderFloat3("LightDirection", (float*)&lightDirection, -1.0f, +1.0f);


}
