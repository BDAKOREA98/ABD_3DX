#include "Framework.h"
#include "Cube.h"

Cube::Cube()
{
    // Shader ���� �� ����
    material = new Material(L"Tutorial");
  

    worldBuffer = new MatrixBuffer();

    CreateMesh();
}

Cube::~Cube()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Cube::Update()
{
    //
    s = XMMatrixScaling(scale.x, scale.y, scale.z);
    r = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    t = XMMatrixTranslation(translation.x, translation.y, translation.z);

    world = s * r * t;

    worldBuffer->SetData(world);
}

void Cube::PreRender()
{
}

void Cube::Render()
{

    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 

    material->SetMaterial();
    mesh->SetMesh();
   


    


    //Draw
    worldBuffer->SetVSBuffer(0);

    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
    DC->DrawIndexed(indices.size(), 0, 0);

}

void Cube::PostRender()
{
}

void Cube::CreateMesh()
{
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

    mesh = new Mesh(vertices, indices);
}

void Cube::Debug()
{
    if (ImGui::BeginMenu("Cube"))
    {
        ImGui::DragFloat3("Scale",      (float*)&scale,         0.01f,    0.01f,    100.0f);
        //ImGui::DragFloat3("rotation",   (float*)&rotation,      0.01f,  -XM_2PI,    XM_2PI);
        ImGui::SliderAngle("rotation.x",   &rotation.x);
        ImGui::SliderAngle("rotation.y",   &rotation.y);
        ImGui::SliderAngle("rotation.z",   &rotation.z);
        ImGui::DragFloat3("translation",(float*)&translation,   0.01f,  -WIN_WIDTH, WIN_WIDTH);

        

        
        ImGui::EndMenu();
    }


}
