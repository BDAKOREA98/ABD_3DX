#pragma once
class StructuredBuffer
{
public:

	StructuredBuffer(void* InputData, UINT inputStride,UINT inputCount, UINT outputStride, UINT outputCount);
	~StructuredBuffer();

	void Copy(void* data, UINT size);

	ID3D11UnorderedAccessView* GetUAV() { return uav; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }


private:
	void CreateOutput();
	void CreateUAV();
	void CreateResult();
	void CreateInput();
	void CreateSRV();


private:

	ID3D11UnorderedAccessView* uav;
	ID3D11ShaderResourceView*  srv;
	
	// srv = GPU�� texture Ȥ�� ray �� ������ �Ѱ���
	// uav = GPU���� ����� ��
	//  input->srv->uav->output->result
	//
	ID3D11Resource*  input;
	ID3D11Resource* output;
	ID3D11Resource* result;

	void*	inputData;
	UINT	inputStride;
	UINT	inputCount;

	UINT	outputStride;
	UINT	outputCount;

};

