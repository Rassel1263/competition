#include "DXUT.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
    for (auto& texture : textures)
    {
        SAFE_RELEASE(texture.second->src);
        SAFE_DELETE(texture.second);
    }
}

void TextureManager::SaveFilePath()
{
    for (auto& file : std::filesystem::recursive_directory_iterator(L"Assets/Sprites/"))
    {
        std::wstring path = std::filesystem::absolute(file.path());
        std::transform(path.begin(), path.end(), path.begin(), std::towlower);

        filePaths.push(path);
    }

    fileSize = filePaths.size();
}

void TextureManager::LoadTexture()
{
    while (true)
    {
        std::wstring path;
        {
            std::lock_guard<std::mutex> gaurd(lock);

            if (filePaths.empty())
                break;

            path = filePaths.front();
            filePaths.pop();
            fileSize = filePaths.size();
        }

        TextureManager::GetInstance().GetTexture(path);
    }

    ++threadCnt;
}

const Texture* TextureManager::GetTexture(std::wstring path)
{
    path = std::filesystem::absolute(path);
    std::transform(path.begin(), path.end(), path.begin(), std::towlower);

    auto tf = textures.find(path);

    if (tf != textures.end())
        return tf->second;

    Texture* texture = new Texture;

    if (FAILED(D3DXCreateTextureFromFileExW(Game::GetInstance().pDevice,
        path.c_str(),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        1,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &texture->info,
        0,
        &texture->src)))
    {
        delete texture;
        return nullptr;
    }

    std::lock_guard<std::mutex> gaurd(insertLock);
    return textures.insert(std::make_pair(path, texture)).first->second;
}
