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
