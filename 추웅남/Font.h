#pragma once

template <typename T>
class Font : public ObjectUI
{
public:
	std::vector<Sprite> font;
	std::wstring name = L"";
	T& num;
	float kerning = 0.0f;
	int index = 0;
	D3DXCOLOR* color = NULL;
	RenderInfo ri;

public:
	Font(std::wstring name, T& num, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float kerning, int index, int layer, D3DXCOLOR* color = NULL)
		:num(num)
	{
		this->name = name;
		this->pos = pos;
		ri.scale = scale;
		this->kerning = kerning;
		this->index = index;
		this->layer = layer;
		this->color = color;
	}

	virtual void Update(float deltaTime) override
	{
		WCHAR temp[256];
		wsprintf(temp, L"%02d", (int)num);
		if(index == 2)
			wsprintf(temp, L"%06d", (int)num);
		std::wstring str = temp;
		
		font.resize(str.size());
		int cnt = 0;
		for (auto& spr : font)
		{
			spr.LoadAll(L"Assets/Sprites/ui/Font/" + name + str.substr(cnt, 1) + L".png");
			spr.bCamera = false;
			if (color) spr.color = *color;
			cnt++;
		}
	}

	virtual void Render() override
	{
		ri.pos = pos;

		int size = font.size();

		if (index == 1)
		{
			for (int i = 0; i < size; ++i)
				font[i].Render(RenderInfo{ D3DXVECTOR2(ri.pos.x + i * kerning, ri.pos.y), ri.scale});
		}
		else if(index == 2)
		{
			for (int i = size - 1; i >= 0; --i)
			{
				font[size - i - 1].Render(RenderInfo{ D3DXVECTOR2(ri.pos.x - i * kerning, ri.pos.y), ri.scale });
			}
		}
	}
};