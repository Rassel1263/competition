#pragma once

template <typename T>
class Font : public ObjectUI
{
public:
	std::vector<Sprite> sprites;
	RenderInfo ri;

	T& num;
	int index = 0;
	float kerning = 0.0f;
	std::wstring name = L"";
	D3DXCOLOR * color = NULL;

	Font(std::wstring name, T& num, D3DXVECTOR2 pos, D3DXVECTOR2 scale, int index, float kerning, int layer, D3DXCOLOR* color = NULL)
		: num(num)
	{
		this->name = name;
		this->pos = pos;
		this->ri.scale = scale;
		this->index = index;
		this->kerning = kerning;
		this->layer = layer;
		this->color = color;
	}

	virtual void Update(float deltaTime) override
	{
		WCHAR temp[256];

		std::wstring str = L"";
		wsprintf(temp, L"%02d", (int)num);
		str = temp;

		if (index == 2)
		{
			wsprintf(temp, L"%06d", (int)num);
			str = temp;
		}

		sprites.resize(str.size());

		int cnt = 0;
		for (auto& spr : sprites)
		{
			spr.LoadAll(L"Assets/Sprites/UI/Font/" + name + str.substr(cnt, 1) + L".png");
			spr.bCamera = false;
			if (color) spr.color = *color;
			cnt++;
		}
	}

	virtual void Render()
	{
		int size = sprites.size();

		if (index == 0)
		{
			for (int i = 0; i < size; ++i)
			{
				ri.pos = pos + D3DXVECTOR2(kerning * i, 0);
				sprites[i].Render(ri);
			}
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				ri.pos = pos + D3DXVECTOR2(-kerning * i, 0);
				sprites[size - i - 1].Render(ri);
			}
		}
	}
};
