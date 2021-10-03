#pragma once
class ShaderManager : public Singleton<ShaderManager>
{
private:
	std::map<std::string, LPD3DXEFFECT> effects;

public:
	HRESULT CreateEffect(std::string name, std::wstring filePath, DWORD flag);
	LPD3DXEFFECT& GetEffect(std::string name);
};

