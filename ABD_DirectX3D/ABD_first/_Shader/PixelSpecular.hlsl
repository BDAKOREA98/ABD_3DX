#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_Position;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
};
	

float4 main(VertexOutput input) : SV_TARGET
{
    float3 Light = normalize(lightDirection);
    
    float diffuseIntensity = dot(input.normal, -Light); // N dot L
    
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    
    float diffuse = albedo * diffuseIntensity;
    ///// Specular///////////////////////////////////////////////////////////
    float4 specular = 0;
    
    float3 reflection = normalize(reflect(Light, input.normal));
    
    specular = dot(-reflection, input.viewDir);
    
    specular = pow(specular, 24.0f);
    
    return diffuse + specular;

}