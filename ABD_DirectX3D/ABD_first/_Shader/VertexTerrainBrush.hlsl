#include "Header.hlsli"


    


struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float3 viewDir : VIEWDIR;
    
    float3 worldPos : POSITION;
    
};




VertexOutput main(VertexTextureNormalTangent Input)
{
    
    VertexOutput output;
    
    output.pos = mul(Input.pos, world);
    
    
    output.worldPos = output.pos;
    
    
    
    float3 cameraPos = invView._41_42_43;
    
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = Input.uv;
    
    float3 Normal = normalize(mul(Input.normal, (float3x3) world));
    output.normal = Normal;
    
    output.tangent = normalize(mul(Input.tangent, (float3x3) world));
    
    output.binormal = cross(output.normal, output.tangent);
    
    
    
    
    return output;
}