#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float diffuse : DIFFUSE;
};
	
Texture2D map : register(t0);

float4 main(VertexOutput input) : SV_TARGET
{
	
    
    return input.color * input.diffuse;

}