#include "Framework.h"
#include "Sphere.h"

Sphere::Sphere(float radius,Vector4 color)
{
    material = new Material(L"CubeShader");


    CreateMesh(radius, color);

    worldBuffer = new MatrixBuffer();
    //CreateNormal();
    mesh = new Mesh(vertices, indices);
}

Sphere::~Sphere()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Sphere::Update()
{
    Transform::Update();
    worldBuffer->SetData(world);
}

void Sphere::PreRender()
{
}

void Sphere::Render()
{
    // 여기 역시 설정 하는 과정이기에 순서 중요하지 않음 

    material->SetMaterial();
    mesh->SetMesh();


    //Draw
    worldBuffer->SetVSBuffer(0);

    // 여기부터 실제 렌더링 파이프라인이 시작되기에 이전까지는 순서 상관 없음!
    DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere::PostRender()
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


void Sphere::CreateSphereVertices(float radius, int sliceCount, int stackCount, Vector4 color)
{
    


    //float phiStep = XM_PI / stackCount;
    //float thetaStep = 2.0f * XM_PI / sliceCount;



    //for (int i = 0; i <= stackCount; ++i)
    //{
    //    float phi = i * phiStep;

    //    for (int j = 0; j <= sliceCount; ++j)
    //    {
    //        float theta = j * thetaStep;

    //        // 구체의 정점 위치 계산
    //        float x = radius * sinf(phi) * cosf(theta);
    //        float y = radius * cosf(phi);
    //        float z = radius * sinf(phi) * sinf(theta);

    //        vertices.push_back(VertexColor({x, y, z}, color));
    //    }
    //}


    //for (DWORD stack = 0; stack < stackCount; ++stack)
    //{
    //    for (DWORD slice = 0; slice < sliceCount; ++slice)
    //    {
    //        DWORD index0 = stack * (sliceCount + 1) + slice;
    //        DWORD index1 = index0 + 1;
    //        DWORD index2 = (stack + 1) * (sliceCount + 1) + slice;
    //        DWORD index3 = index2 + 1;

    //        // 첫 번째 삼각형
    //        indices.push_back(index0);
    //        indices.push_back(index2);
    //        indices.push_back(index1);

    //        // 두 번째 삼각형
    //        indices.push_back(index1);
    //        indices.push_back(index2);
    //        indices.push_back(index3);
    //    }
    //}

    //mesh = new Mesh(vertices, indices);

}

void Sphere::CreateNormal()
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

void Sphere::CreateMesh(float radius, Vector4 color)
{
    int stackCount = 30;
    int sliceCount = 30;

    float phiStep = XM_PI / stackCount;
    float thetaStep = 2.0f * XM_PI / sliceCount;



    for (int i = 0; i <= stackCount; ++i)
    {
        float phi = i * phiStep;

        for (int j = 0; j <= sliceCount; ++j)
        {
            float theta = j * thetaStep;

            // 구체의 정점 위치 계산
            float x = radius * sinf(phi) * cosf(theta);
            float y = radius * cosf(phi);
            float z = radius * sinf(phi) * sinf(theta);

            VertexCube vertex = VertexCube({ x, y, z }, color);
            vertex.normal = vertex.pos / radius;

            vertices.push_back(vertex);
        }
    }


    for (DWORD stack = 0; stack < stackCount; ++stack)
    {
        for (DWORD slice = 0; slice < sliceCount; ++slice)
        {
            DWORD index0 = stack * (sliceCount + 1) + slice;
            DWORD index1 = index0 + 1;
            DWORD index2 = (stack + 1) * (sliceCount + 1) + slice;
            DWORD index3 = index2 + 1;

            // 첫 번째 삼각형
            indices.push_back(index0);
            indices.push_back(index2);
            indices.push_back(index1);

            // 두 번째 삼각형
            indices.push_back(index1);
            indices.push_back(index2);
            indices.push_back(index3);
        }
    }

 
}
