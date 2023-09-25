#include "Framework.h"
#include "Material.h"

int Material::ID = 0;

Material::Material()
{
	buffer = new MaterialBuffer();
	SetShader(L"TerrainBrush");
	SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	SetNormalMap(L"Landscape/fieldstone_NM.tga");

	
	

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectDir = path;

	projectDir += "Resource/_Texture/";
	ID += 1;

	label = "Material" + to_string(ID);
	
	Load(ToWstring(label + "Data"));


}

Material::Material(wstring file)
{
	buffer = new MaterialBuffer();

	SetShader(file);
	SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	SetNormalMap(L"Landscape/fieldstone_NM.tga");

	char path[128];
	GetCurrentDirectoryA(128, path);

	projectDir = path;

	projectDir += "Resource/_Texture/";
	ID += 1;
	label = "Material" + to_string(ID);
	Load(ToWstring(label + "Data"));
}

Material::~Material()
{
	Save(ToWstring(label + "Data"));

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
	

	if (ImGui::BeginMenu(label.c_str()))
	{
		
		if (ImGui::Button("DiffuseMap"))
		{
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png, .jpg, .dds, .tga", "Resource/_Texture");
		}
		if (ImGui::Button("NormalMap"))
		{
			Dialog->OpenDialog("Normal", "Select Normal", ".png,.jpg, .dds, .tga", "Resource/_Texture");
		}
		if (ImGui::Button("SpecularMap"))
		{
			Dialog->OpenDialog("Specular", "Select Specular", ".png, .jpg, .dds, .tga", "Resource/_Texture");
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
		ImGui::EndMenu();
	}
}

void Material::PostRender()
{
	
		ImGui::InputText("Label", (char*)label.data(), label.size());
	if (ImGui::BeginMenu(label.c_str()))
	{	
		

		ImGui::ColorEdit4((label + "Diffuse").c_str(), (float*)&buffer->data.Mdiffuse);
		ImGui::ColorEdit4((label + "Specular").c_str(), (float*)&buffer->data.Mspecular);
		ImGui::ColorEdit4((label + "Ambient").c_str(), (float*)&buffer->data.Mambient);

		ImGui::Checkbox((label + "HasDiffuseMap").c_str(), (bool*)&buffer->data.hasDiffuseMap);
		ImGui::Checkbox((label + "HasSpecularMap").c_str(), (bool*)&buffer->data.hasSpecularMap);
		ImGui::Checkbox((label + "HasNormalMap").c_str(), (bool*)&buffer->data.hasNormalMap);
		
		ImGui::SliderFloat((label + "Shininesss").c_str(), &buffer->data.shininess, 1.0f, 50.0f);


		if (ImGui::Button(("Save" + label).c_str()))
		{
			Save(ToWstring(label + "Data"));
		}
		if (ImGui::Button(("Load" + label).c_str()))
		{
			Load(ToWstring(label + "Data"));
		}
		ImGui::EndMenu();
	
	}
	SelectMap();
}

void Material::Save(wstring file)
{
	
	BinaryWriter data(file);

	data.WriteData(label);



	if (vertexShader)
	{
		data.WriteData(vertexShader->GetPath());
	}
	else
	{
		data.WriteData(L"");
	}
	if (pixelShader)
	{
		data.WriteData(pixelShader->GetPath());
	}
	else
	{
		data.WriteData(L"");
	}
	if (diffuseMap)
	{
		data.WriteData(diffuseMap->GetPath());
	}
	else
	{
		data.WriteData(L"");
	}
	if (specularMap)
	{
		data.WriteData(specularMap->GetPath());
	}
	else
	{
		data.WriteData(L"");
	}
	if (normalMap)
	{
		data.WriteData(normalMap->GetPath());
	}
	else
	{
		data.WriteData(L"");
	}
	


}

void Material::Load(wstring file)
{
	BinaryReader data(file);

	if (!data.Succeeded())
	{
		return;
	}


	label = data.ReadString();

	wstring str;

	str = data.ReadWstring();
	if (str != L"")
	{
		vertexShader = Shader::GetVS(str);
	}
	str = data.ReadWstring();
	if (str != L"")
	{
		pixelShader = Shader::GetPS(str);
	}
	str = data.ReadWstring();
	if (str != L"")
	{
		diffuseMap = Texture::Get(str);
	}
	str = data.ReadWstring();
	if (str != L"")
	{
		specularMap = Texture::Get(str);
	}
	str = data.ReadWstring();
	if (str != L"")
	{
		normalMap = Texture::Get(str);
	}



}
