#pragma once
struct Texture 
{
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	std::map<std::wstring, Texture*> textures;
	std::queue<std::wstring> filePaths;
	std::mutex lock;
	std::mutex insertLock;

public:
	int fileSize = 0;
	int threadCnt = 0;

	~TextureManager();
	int GetPathsSize();
	void SaveFilePath();
	void LoadTexture();
	const Texture* GetTexture(std::wstring filePath);
};

