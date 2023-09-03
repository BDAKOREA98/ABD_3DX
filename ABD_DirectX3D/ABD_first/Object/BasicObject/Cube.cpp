#include "Framework.h"
#include "Cube.h"

Cube::Cube(Vector4 color)
{
    // Shader 생성 및 설정
    material = new Material(L"Tutorial");
  

    CreateMesh(color);
    
    worldBuffer = new MatrixBuffer();


}

Cube::~Cube()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Cube::Update()
{
    Transform::Update();
    worldBuffer->SetData(world);

}

void Cube::PreRender()
{
}

void Cube::Render()
{

    // 여기 역시 설정 하는 과정이기에 순서 중요하지 않음 

    material->SetMaterial();
    mesh->SetMesh();
   

    //Draw
    worldBuffer->SetVSBuffer(0);

    // 여기부터 실제 렌더링 파이프라인이 시작되기에 이전까지는 순서 상관 없음!
    DC->DrawIndexed(indices.size(), 0, 0);

}

void Cube::PostRender()
{
    ImGui::SliderAngle("rotation.x", &rotation.x);
    ImGui::SliderAngle("rotation.y", &rotation.y);
    ImGui::SliderAngle("rotation.z", &rotation.z);
    ImGui::SliderAngle("translation.x", &translation.x);
    ImGui::SliderAngle("translation.y", &translation.y);
    ImGui::SliderAngle("translation.z", &translation.z);
    ImGui::SliderAngle("scale.x", &scale.x);
    ImGui::SliderAngle("scale.y", &scale.y);
    ImGui::SliderAngle("scale.z", &scale.z);
}

void Cube::CreateMesh(Vector4 color)
{
    //////////////////////////////////////////////////////////////////

    {

        vertices = {
            VertexColor({ -1.0f, +1.0f, -1.0f}, color),
            VertexColor({ +1.0f, +1.0f, -1.0f}, color),
            VertexColor({ -1.0f, -1.0f, -1.0f}, color),
            VertexColor({ +1.0f, -1.0f, -1.0f}, color),
                                                
            VertexColor({ -1.0f, +1.0f, +1.0f}, color),
            VertexColor({ +1.0f, +1.0f, +1.0f}, color),
            VertexColor({ -1.0f, -1.0f, +1.0f}, color),
            VertexColor({ +1.0f, -1.0f, +1.0f}, color)

        };



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

    mesh = new Mesh(vertices, indices);
}


