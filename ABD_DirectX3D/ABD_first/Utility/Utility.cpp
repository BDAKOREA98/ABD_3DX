#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{

	// ���� �������� �ִ� ���ڿ��� ã�� �Լ� 
	// ex) find_last_of('.') �̸� ���� �������� �ִ� .�� ã��
	UINT index = path.find_last_of('.');
	// . �ڿ��ִ� ���ڵ��� �ܾ�Ͷ�
	return path.substr(index + 1, path.length());


}

string Utility::ToString(wstring str)
{
	string temp;
	temp.assign(str.begin(), str.end());

	return temp;
}

wstring Utility::ToWstring(string str)
{
	wstring temp;
	
	temp.assign(str.begin(), str.end());

	return temp;
}

wstring Utility::GetProjectDir()
{
	WCHAR path[128];
	GetCurrentDirectory(128, path);


	wstring dir = path;
	
	return dir + L"/";
}

wstring Utility::GetTextureDir()
{
	return GetProjectDir() + L"_Resource/_Texture";
}
