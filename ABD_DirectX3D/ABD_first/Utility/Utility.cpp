#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{

	// 가장 마지막에 있는 문자열을 찾는 함수 
	// ex) find_last_of('.') 이면 가장 마지막에 있는 .을 찾음
	UINT index = path.find_last_of('.');
	// . 뒤에있는 글자들을 긁어와라
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
