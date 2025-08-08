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
    }
    links
    {
    }
