#pragma once
class OutlineShader 
{
public:
	LPD3DXEFFECT shader = NULL;

public:
	OutlineShader();
	~OutlineShader();

	HRESULT PrePare();
	HRESULT Begin();
	HRESULT End();
	HRESULT SetTexture(const Texture* texture);
	HRESULT SetColor(D3DXVECTOR4 color);

	void Render(OutlineShader* shader, Sprite& spr, RenderInfo& ri, D3DXVECTOR4 color = { 1, 0, 0, 1 });

};

