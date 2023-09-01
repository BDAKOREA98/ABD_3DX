#include "Header.hlsli"
struct VertexOutput
{
    float4 pos    : SV_POSITION;
    float2 uv     : UV;
    float diffuse : DIFFUSE;
};


VertexOutput main(VertexTextureNormal Input)
{
    
    VertexOutput output;
    
    output.pos = mul(Input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = Input.uv;
    
    float3 Light = normalize(-lightDirection);
    
    float3 Normal = normalize(mul(Input.normal, (float3x3) world));
    
    output.diffuse = dot(Normal, Light); // N dot L
    
    return output;
}