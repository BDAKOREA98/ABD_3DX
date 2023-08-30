#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
public:

	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRaterizerState();
	

private:
	SamplerState* samplerstate = nullptr;
	RasterizerState* raterizerstate = nullptr;
};

