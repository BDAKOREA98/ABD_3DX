#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateViewPort();
    CreatePerspective();

    lightBuffer = new LightBuffer();
   lightBuffer2 = new LightBuffer();
}

Environment::~Environment()
{
   
    delete projBuffer;
    delete lightBuffer;
   delete lightBuffer2;

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
    
    lightBuffer->SetPSBuffer(3);

    lightBuffer2->SetVSBuffer(3);
    
}

void Environment::PostRender()
{
    

    ImGui::SliderFloat3("PSLightDirection", (float*)&lightBuffer->data.LightDirection, -1.0f, +1.0f);
    ImGui::ColorEdit3("PSAmbientLight", (float*)&lightBuffer->data.ambientLight);

    //ImGui::SliderFloat3("VSLightDirection", (float*)&lightBuffer2->data.LightDirection, -1.0f, +1.0f);
    //ImGui::ColorEdit3("VSAmbientLight", (float*)&lightBuffer2->data.ambientLight);



}
