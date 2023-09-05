#include "Framework.h"
#include "Cube.h"

Cube::Cube(Vector4 color)
{
    // Shader 생성 및 설정
    material = new Material(L"Color");
  

    CreateMesh(color);
    CreateNormal();
    
    mesh = new Mesh(vertices, indices);
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


void Cube::CreateMesh(Vector4 color)
{
    //////////////////////////////////////////////////////////////////

    {

        vertices = {
            VertexType({ -0.5f, +0.5f, -0.5f}, color, Vector3()),
            VertexType({ +0.5f, +0.5f, -0.5f}, color, Vector3()),
            VertexType({ -0.5f, -0.5f, -0.5f}, color, Vector3()),
            VertexType({ +0.5f, -0.5f, -0.5f}, color, Vector3()),          

            VertexType({ -0.5f, +0.5f, +0.5f}, color, Vector3()),
            VertexType({ +0.5f, +0.5f, +0.5f}, color, Vector3()),
            VertexType({ -0.5f, -0.5f, +0.5f}, color, Vector3()),
            VertexType({ +0.5f, -0.5f, +0.5f}, color, Vector3())
                                                      
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

  
}

void Cube::CreateNormal()
{
    for (UINT i = 0; i < indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector3 v01 = p1 - p0;
        Vector3 v02 = p2 - p0;

        Vector3 normal = Vector3::Cross(v01, v02).GetNormalize();


        vertices[index0].normal += normal;
        vertices[index1].normal += normal;
        vertices[index2].normal += normal;

    }
}


