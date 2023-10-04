#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring path);
	~BinaryReader();

	int ReadInt();
	UINT ReadUINT();
	float ReadFloat();
	string ReadString();
	wstring ReadWstring();
	Vector3 ReadVector3();
	Vector4 ReadVector4();

	void ReadData(OUT void** data, UINT dataSize);

	bool Succeeded();
	
private:
	// HANDLE == void*
	HANDLE file = nullptr;
	// DWORD unsigned long
	DWORD size = 0;

};

