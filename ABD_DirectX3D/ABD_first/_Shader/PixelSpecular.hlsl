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
    
    
    float diffuseIntensity = saturate(dot(input.normal, -Light)); // N dot L
    
    
    float4 albedo = float4(1, 1, 1, 1);
    
    
    if(hasDiffuseMap)
    {
        albedo = diffuseMap.Sample(samp, input.uv);
    }
         
    
        
    
    ///// Specular///////////////////////////////////////////////////////////
    
    float specularIntensity = 0;
    
    float3 reflection = normalize(reflect(Light, input.normal));
    
    specularIntensity = saturate(dot(-reflection, input.viewDir));
    
    float4 specularSample = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(hasSpeculaMap)
    {
        specularSample = specularMap.Sample(samp, input.uv);
    }
    
    
    
    
    float4 specular = pow(specularIntensity, shininess) * specularSample * Mspecular;
    
    
    float4 diffuse = albedo * diffuseIntensity * Mdiffuse;
    
 
 
    
    float4 ambient = albedo * ambientLight * Mambient;
    
    
    
    
    return diffuse + specular + ambient;

    
}