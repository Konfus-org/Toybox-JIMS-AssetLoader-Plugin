#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Assets/AssetLoaders.h>

namespace JIM
{
    class JIMAssetLoaderPlugin : public Tbx::ITextureLoader, public Tbx::IShaderLoader, public Tbx::Plugin
    {
    public:
        JIMAssetLoaderPlugin(const std::weak_ptr<Tbx::App>& app) {}

        std::shared_ptr<Tbx::Texture> LoadTexture(const std::string& filepath) override;
        std::shared_ptr<Tbx::Shader> LoadShader(const std::string& filepath) override;

        std::string LoadTextFile(const std::string& filepath);

        void DeleteTexture(Tbx::Texture* texture);
        void DeleteShader(Tbx::Shader* shader);
    };

    TBX_REGISTER_PLUGIN(JIMAssetLoaderPlugin);
}