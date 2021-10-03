#include "DXUT.h"
#include "ColorShader.h"

ColorShader::ColorShader()
{
	shader = ShaderManager::GetInstance().GetEffect("Color");
}

ColorShader::~ColorShader()
{
	SAFE_RELEASE(shader);
}

HRESULT ColorShader::PrePare()
{
	return shader->SetTechnique(shader->GetTechniqueByName("Color"));
}

HRESULT ColorShader::Begin()
{
	if (FAILED(shader->Begin(0, NULL))) return E_FAIL;
	return shader->BeginPass(0);
}

HRESULT ColorShader::End()
{
	return shader->End();
}

HRESULT ColorShader::SetTexture(const Texture * texture)
{
	if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src)))
		return E_FAIL;
}

HRESULT ColorShader::SetColor(D3DXVECTOR4 color)
{
	if(FAILED(shader->SetVector(shader->GetParameterByName(0, "color"), &color)))
		return E_FAIL;
}

void ColorShader::Render(ColorShader * shader, Sprite & spr, RenderInfo & ri, D3DXVECTOR4 color)
{
	shader->PrePare();
	shader->SetTexture(spr.GetNowScene());
	shader->SetColor(color);
	shader->Begin();
	spr.Render(ri);
	shader->End();
}
