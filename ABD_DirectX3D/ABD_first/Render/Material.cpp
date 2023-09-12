#include "Framework.h"
#include "Material.h"

string Material::ID = "";

Material::Material()
{
	buffer = new MaterialBuffer();

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectDir = path;
	projectDir += "Resource/_Texture/";

	ID += ".";


}

Material::Material(wstring file)
{
	SetShader(file);
	buffer = new MaterialBuffer();

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectDir = path;

	projectDir += "Resource/_Texture/";
	ID += ".";
}

Material::~Material()
{
	delete buffer;
}

void Material::SetVertexShader(wstring file)
{
	vertexShader = Shader::GetVS(file);
}

void Material::SetPixelShader(wstring file)
{
	pixelShader = Shader::GetPS(file);
}

void Material::SetShader(wstring file)
{
	SetVertexShader	(file);
	SetPixelShader	(file);
}

void Material::SetMaterial()
{
	vertexShader -> SetShader();
	pixelShader	 -> SetShader();
	if (diffuseMap)
	{
		diffuseMap->PSSetShaderResource(0);
	}
	if (specularMap)
	{
		specularMap->PSSetShaderResource(1);
	}
	if (normalMap)
	{
		normalMap->PSSetShaderResource(2);
	}
	buffer->SetPSBuffer(1);
}

void Material::SetDiffuseMap(wstring file)
{
	diffuseMap = Texture::Get(file);

	buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	specularMap = Texture::Get(file);

	buffer->data.hasSpecularMap = true;
}

void Material::SetNormalMap(wstring file)
{
	normalMap = Texture::Get(file);

	buffer->data.hasNormalMap = true;
}

void Material::SelectMap()
{
	#define Dialog ImGuiFileDialog::Instance()

	if (ImGui::BeginChild(ID.c_str(), ImVec2(100, 85), true))
	{
		
		if (ImGui::Button("DiffuseMap"))
		{
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png,.jpg,.dds,.tga", "Resource/_Texture");
		}
		if (ImGui::Button("SpecularMap"))
		{
			Dialog->OpenDialog("Specular", "Select Specular", ".png, .jpg, .dds, .tga", "Resource/_Texture");
		}
		if (ImGui::Button("NormalMap"))
		{
			Dialog->OpenDialog("Normal", "Select Normal", ".png,.jpg, .dds, .tga", "Resource/_Texture");
		}

		if (Dialog->Display("Diffuse") || Dialog->Display("Specular") || Dialog->Display("Normal"))
		{
			if (Dialog->IsOk())
			{
				string path = Dialog->GetFilePathName();

				path = path.substr(projectDir.size() + 1, path.size());

				wstring wPath = ToWstring(path);

				if (Dialog->GetOpenedKey() == "Diffuse")
				{
					SetDiffuseMap(wPath);
				}
				else if (Dialog->GetOpenedKey() == "Specular")
				{
					SetSpecularMap(wPath);
				}
				else if (Dialog->GetOpenedKey() == "Normal")
				{
					SetNormalMap(wPath);
				}
			}
			Dialog->Close();
		}
		ImGui::EndChild();
	}
}

void Material::PostRender()
{
	ImGui::ColorEdit4("Diffuse", (float*)&buffer->data.Mdiffuse);
	ImGui::ColorEdit4("Specular", (float*)&buffer->data.Mspecular);
	ImGui::ColorEdit4("Ambient", (float*)&buffer->data.Mambient);

	ImGui::Checkbox("HasDiffuseMap", (bool*)&buffer->data.hasDiffuseMap);
	ImGui::Checkbox("HasSpecularMap", (bool*)&buffer->data.hasSpecularMap);
	ImGui::Checkbox("HasNormalMap", (bool*)&buffer->data.hasNormalMap);

	ImGui::SliderFloat("Shininesss", &buffer->data.shininess, 1.0f, 50.0f);


}
