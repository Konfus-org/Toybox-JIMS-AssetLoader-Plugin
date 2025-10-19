#pragma once
#include "Tbx/Plugins/Plugin.h"
#include "Tbx/Assets/AssetLoaders.h"

namespace Tbx::Plugins::JIMS
{
    struct TIMSTexture : public Texture, public IProductOfPluginFactory
    {
        using Texture::Texture;
    };

    class TIMSTextureLoaderPlugin final
        : public ITextureLoader
        , public FactoryPlugin<TIMSTexture>
    {
    public:
        TIMSAssetLoaderPlugin(Ref<EventBus> eventBus) {}
        bool CanLoad(const std::filesystem::path& filepath) const final;
        Ref<Texture> LoadTexture(const std::filesystem::path& filepath) final;
    };

    TBX_REGISTER_PLUGIN(TIMSTextureLoaderPlugin);
}