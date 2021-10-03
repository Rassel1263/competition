#pragma once
class ColorShader 
{
private:
	LPD3DXEFFECT shader = NULL;

public:
	ColorShader();
	~ColorShader();
	HRESULT PrePare();
	HRESULT Begin();
	HRESULT End();
	HRESULT SetTexture(const Texture* texture);
	HRESULT SetColor(D3DXVECTOR4 color);
	void Render(ColorShader* shader, Sprite& spr, RenderInfo& ri, D3DXVECTOR4 color = D3DXVECTOR4(1, 1, 1, 1));
};

