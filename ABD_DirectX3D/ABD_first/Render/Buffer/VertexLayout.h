#pragma once

struct Vertex
{
    Vertex() {}

    Vertex(float x, float y, float z)
    {
        pos = XMFLOAT3(x, y, z);
    }
    XMFLOAT3 pos = {};
};
struct VertexColor
{
    VertexColor() {}

    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        : pos(pos), color(color)
    {
    }
    XMFLOAT3 pos   = {};
    XMFLOAT4 color = {};
};

struct VertexTexture
{

    VertexTexture() {}


    VertexTexture(XMFLOAT3 pos, XMFLOAT2 uv)
        : pos(pos), uv(uv)
    {
    }
    XMFLOAT3 pos = {};
    XMFLOAT2 uv  = {};

    
};

struct VertexTextureNormal
{

    VertexTextureNormal() {}

    VertexTextureNormal(Vector3 pos, Vector2 uv, Vector3 normal)
        : pos(pos), uv(uv), normal(normal)
    {
    }

    
    Vector3 pos     = {};
    Vector2 uv      = {};
    Vector3 normal  = {};


};


struct VertexCube
{
    VertexCube() {}

    VertexCube(Vector3 pos, Vector4 color)
        : pos(pos), color(color)
    {
    }
    Vector3 pos = {};
    Vector4 color = {};
    Vector3 normal = {0.0f, 0.0f,0.0f};
    
};


struct VertexColorNormal
{
    VertexColorNormal() {}

    VertexColorNormal(Vector3 pos, Vector4 color, Vector3 normal)
        : pos(pos), color(color), normal(normal)
    {
    }
    Vector3 pos      = {};
    Vector4 color    = {};
    Vector3 normal   = {};
};


struct VertexTextureNormalTangent
{

    VertexTextureNormalTangent() {}

    VertexTextureNormalTangent(Vector3 pos, Vector2 uv, Vector3 normal, Vector3 tangent)
        : pos(pos), uv(uv), normal(normal), tangent(tangent)
    {
    }


    Vector3 pos     = {};
    Vector2 uv      = {};
    Vector3 normal  = {};
    Vector3 tangent = {};



};


struct VertexTextureNormalTangentAlpha
{

    VertexTextureNormalTangentAlpha() {

    }

    


    Vector3 pos = {};
    Vector2 uv = {};
    Vector3 normal = {};
    Vector3 tangent = {};
    float   alpha[4] = {};


};