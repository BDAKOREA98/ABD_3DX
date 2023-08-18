#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
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

        // ���� ��
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

        // �ٴ� ��
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

    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 

    vertexShader->SetShader();
    pixelShader->SetShader();

    vertexBuffer->IASetBuffer();
    indexBuffer->IASetBuffer();


    


    //Draw
    worldBuffer->SetVSBuffer(0);

    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
    DC->DrawIndexed(indices.size(), 0, 0);

}

void Cube::PostRender()
{
}
