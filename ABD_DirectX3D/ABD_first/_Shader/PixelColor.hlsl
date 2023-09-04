#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float3 normal : NORMAL;
};
	



float4 main(VertexOutput input) : SV_TARGET
{
    
    float3 Light  = normalize(-lightDirection);
    float diffuse = dot(input.normal, Light); // N dot L
    
    
    return input.color * diffuse;
	
}