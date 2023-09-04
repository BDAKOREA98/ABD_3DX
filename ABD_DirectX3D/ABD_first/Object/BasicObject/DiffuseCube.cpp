#include "Framework.h"
#include "DiffuseCube.h"

DiffuseCube::DiffuseCube(Vector4 color)
{
    // Shader ���� �� ����
    material = new Material(L"Texture");
    material->SetShader(L"CubeShader");
   // material->SetDiffuseMap(L"Texture");
    CreateMesh(color);

    worldBuffer = new MatrixBuffer();
    CreateNormal();

    mesh = new Mesh(vertices, indices);
}

DiffuseCube::~DiffuseCube()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void DiffuseCube::Update()
{
    Transform::Update();
    worldBuffer->SetData(world);

}

void DiffuseCube::PreRender()
{
}

void DiffuseCube::Render()
{

    // ���� ���� ���� �ϴ� �����̱⿡ ���� �߿����� ���� 

    material->SetMaterial();
    
    mesh->SetMesh();


    //Draw
    worldBuffer->SetVSBuffer(0);

    // ������� ���� ������ ������������ ���۵Ǳ⿡ ���������� ���� ��� ����!
    DC->DrawIndexed(indices.size(), 0, 0);

}

void DiffuseCube::PostRender()
{
 
}

void DiffuseCube::CreateMesh(Vector4 color)
{
    {

        vertices = {
            VertexType({ -0.5f, +0.5f, -0.5f}, color),
            VertexType({ +0.5f, +0.5f, -0.5f}, color),
            VertexType({ -0.5f, -0.5f, -0.5f}, color),
            VertexType({ +0.5f, -0.5f, -0.5f}, color),        
            VertexType({ -0.5f, +0.5f, +0.5f}, color),
            VertexType({ +0.5f, +0.5f, +0.5f}, color),
            VertexType({ -0.5f, -0.5f, +0.5f}, color),
            VertexType({ +0.5f, -0.5f, +0.5f}, color)
                         
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



}

void DiffuseCube::CreateNormal()

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

    for (UINT i = 0; i < vertices.size(); i++)
    {
        vertices[i].normal.Normalize();
    }
}





