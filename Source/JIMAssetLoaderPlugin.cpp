#include "JIMAssetLoaderPlugin.h"
#include <Tbx/Debug/Tracers.h>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace Tbx::Plugins::JIMS
{
    /////////////// LOADER /////////////////////

    bool JIMSAssetLoaderPlugin::CanLoad(const std::filesystem::path& filepath) const
    {
        if (filepath.extension() == ".png" ||
            filepath.extension() == ".jpg" ||
            filepath.extension() == ".jpeg" ||
            filepath.extension() == ".vert" ||
            filepath.extension() == ".frag" ||
            filepath.extension() == ".txt")
        {
            return true;
        }
        return false;
    }

    Texture JIMSAssetLoaderPlugin::LoadTexture(const std::filesystem::path& filepath)
    {
        // Load texture with stbimg
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(filepath.string().c_str(), &width, &height, &channels, 0);
        
        // Ensure texture loaded correctly
        if (!data)
        {
            TBX_ASSERT(false, "JIMS: Failed to load texture file at {}!", filepath.string());
            return Texture();
        }

        // Allocate and copy into vector
        size_t dataSize = static_cast<size_t>(width) * height * channels;
        std::vector<unsigned char> pixelData(dataSize);
        std::memcpy(pixelData.data(), data, dataSize);

        // Create tbx in memory texture and return it
        auto texture = Texture(
            Size(width, height),
            TextureWrap::Repeat,
            TextureFilter::Nearest,
            channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB,
            pixelData);

        // Free the stb data
        stbi_image_free(data);

        return texture;
    }

    Shader JIMSAssetLoaderPlugin::LoadShader(const std::filesystem::path& filepath)
    {
        // Get shader type from extension
        ShaderType shaderType;
        if (filepath.extension() == ".vert")
        {
            shaderType = ShaderType::Vertex;
        }
        else if (filepath.extension() == ".frag")
        {
            shaderType = ShaderType::Fragment;
        }
        else
        {
            TBX_ASSERT(false, "JIMS: Invalid shader file extension at {}!", filepath.string());
            return Shader();
        }

        // Load and validate shader
        auto shaderSource = LoadText(filepath);
        if (shaderSource.Value.empty())
        {
            TBX_ASSERT(false, "JIMS: Failed to load shader file at {}!", filepath.string());
            return Shader();
        }

        // Create tbx in memory shader and return it
        auto shader = Shader(shaderSource.Value, shaderType);
        return shader;
    }

    Text JIMSAssetLoaderPlugin::LoadText(const std::filesystem::path& filepath)
    {
        auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
        if (!file)
        {
            TBX_ASSERT(false, "JIMS: Failed to load text file at {}!", filepath.string());
            return {};
        }

        std::ostringstream contents;
        contents << file.rdbuf();
        file.close();

        return Text(contents.str());
    }
}
