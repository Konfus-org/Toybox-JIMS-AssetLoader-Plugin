project "JIM Asset Loader"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    RegisterDynamicPlugin("JIM Asset Loader")

    files
    {
        "./**.hpp",
        "./**.cpp",
        "./**.h",
        "./**.c",
        "./**.md",
        "./**.plugin"
    }
    includedirs
    {
        "./Source",
        _MAIN_SCRIPT_DIR .. "/Dependencies/nlohmann_json/include",
        _MAIN_SCRIPT_DIR .. "/Dependencies/stbimg/include",
    }
    links
    {
        "stbimg",
        "nlohmann_json",
    }
