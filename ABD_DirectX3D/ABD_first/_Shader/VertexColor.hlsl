#include "Header.hlsli"

struct VertexOutput
{
    float4   pos : SV_POSITION;
    float2 color : UV;
    float3 normal : NORMAL;
};


VertexOutput main(VertexColorNormal Input)
{
    
    VertexOutput output;
    
    output.pos = mul(Input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = Input.color;
    
    float3 Normal = normalize(mul(Input.normal, (float3x3) world));
    
    output.normal = Normal;
    
    
   
    

    
    
    
    return output;
    
    
}