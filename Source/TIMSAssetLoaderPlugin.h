#pragma once
#include "Tbx/Plugins/Plugin.h"
#include "Tbx/Assets/AssetLoaders.h"

namespace Tbx::Plugins::JIMS
{
    struct TIMSTexture : public Texture, public IProductOfPluginFactory
    {
        using Texture::Texture;
    };

    struct TIMSShader : public Shader, public IProductOfPluginFactory
    {
        using Shader::Shader;
    };

    struct TIMSText : public Text, public IProductOfPluginFactory
    {
        using Text::Text;
    };

    class TIMSAssetLoaderPlugin final
        : public ITextureLoader
        , public IShaderLoader
        , public ITextLoader
        , public virtual FactoryPlugin<TIMSTexture>
        , public virtual FactoryPlugin<TIMSShader>
        , public virtual FactoryPlugin<TIMSText>
    {
    public:
        TIMSAssetLoaderPlugin(Ref<EventBus> eventBus) {}

        bool CanLoad(const std::filesystem::path& filepath) const final;
        Ref<Texture> LoadTexture(const std::filesystem::path& filepath) final;
        Ref<Shader> LoadShader(const std::filesystem::path& filepath) final;
        Ref<Text> LoadText(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(TIMSAssetLoaderPlugin);
}