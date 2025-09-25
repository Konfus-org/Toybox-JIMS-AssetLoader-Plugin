#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Assets/AssetLoaders.h>

namespace JIMS
{
    class JIMSAssetLoaderPlugin
        : public Tbx::Plugin
        , public Tbx::ITextureLoader
        , public Tbx::IShaderLoader
        , public Tbx::ITextLoader
    {
    public:
        JIMSAssetLoaderPlugin(std::weak_ptr<Tbx::App> app) {}
        bool CanLoad(const std::filesystem::path& filepath) const final;
        Tbx::Texture LoadTexture(const std::filesystem::path& filepath) final;
        Tbx::Shader LoadShader(const std::filesystem::path& filepath) final;
        Tbx::Text LoadText(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(JIMSAssetLoaderPlugin);
}