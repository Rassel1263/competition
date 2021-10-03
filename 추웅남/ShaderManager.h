#pragma once
class ShaderManager : public Singleton<ShaderManager>
{
private:
	std::map<std::string, LPD3DXEFFECT> effects;

public:
	~ShaderManager();

	HRESULT Create(std::string name, std::wstring path, DWORD flag);
	LPD3DXEFFECT& GetEffect(std::string name);

};

