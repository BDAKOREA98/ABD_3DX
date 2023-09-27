#include "Framework.h"
#include "ModelExporter.h"


ModelExporter::ModelExporter(string file)
{
	importer = new Assimp::Importer();

	scene = importer->ReadFile(file, aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	assert(scene != nullptr);
		


}

ModelExporter::~ModelExporter()
{

	delete importer;

}

void ModelExporter::ExportMaterial(string name)
{

	this->name = name;
	ReadMaterial();


}

void ModelExporter::ReadMaterial()
{

	for (UINT i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = scene->mMaterials[i];

		Material* material = new Material();

		material->SetLabel(srcMaterial->GetName().C_Str());

		aiColor3D color;

		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->GetBuffer()->data.Mdiffuse = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->GetBuffer()->data.Mspecular = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->GetBuffer()->data.Mambient = Vector4(color.r, color.g, color.b, 1.0f);


		srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		material->GetBuffer()->data.emissive = Vector4(color.r, color.g, color.b, 1.0f);

		srcMaterial->Get(AI_MATKEY_SHININESS, material->GetBuffer()->data.shininess);
		

		delete material;

	}


}

wstring ModelExporter::CreateTexture(string file)
{
	if (file.length() == 0)
	{
		return L"";
	}

	


	return wstring();
}
