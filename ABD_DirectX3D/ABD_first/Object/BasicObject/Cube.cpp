#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
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

        // 앞쪽 면
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

        // 바닥 면
        2,3,6,
        6,3,7

    };

    indexBuffer = new IndexBuffer(indices);

    worldBuffer = new MatrixBuffer();

}

Cube::~Cube()
{
    delete vertexBuffer;
    delete indexBuffer;

    delete worldBuffer;
}

void Cube::Update()
{
    static float angle = 0.0f;

    angle += 0.0001f;

    XMMATRIX world = XMMatrixRotationRollPitchYaw(angle, angle, 0.0f);

    worldBuffer->SetData(world);
}

void Cube::PreRender()
{
}

void Cube::Render()
{

    // 여기 역시 설정 하는 과정이기에 순서 중요하지 않음 

    vertexShader->SetShader();
    pixelShader->SetShader();

    vertexBuffer->IASetBuffer();
    indexBuffer->IASetBuffer();


    


    //Draw
    worldBuffer->SetVSBuffer(0);

    // 여기부터 실제 렌더링 파이프라인이 시작되기에 이전까지는 순서 상관 없음!
    DC->DrawIndexed(indices.size(), 0, 0);

}

void Cube::PostRender()
{
}
