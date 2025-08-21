#pragma once
#include <Tbx/PluginAPI/RegisterPlugin.h>

namespace JIM
{
    class JIMAssetLoaderPlugin : public Tbx::ITextureLoaderPlugin, public Tbx::IShaderLoaderPlugin
    {
    public:
        JIMAssetLoaderPlugin() = default;
        ~JIMAssetLoaderPlugin() override = default;

        void OnLoad() override;
        void OnUnload() override;

        std::shared_ptr<Tbx::Texture> LoadTexture(const std::string& filepath) override;
        std::shared_ptr<Tbx::Shader> LoadShader(const std::string& filepath) override;

        std::string LoadTextFile(const std::string& filepath);

        void DeleteTexture(Tbx::Texture* texture);
        void DeleteShader(Tbx::Shader* shader);
    };

    TBX_REGISTER_PLUGIN(JIMAssetLoaderPlugin);
}