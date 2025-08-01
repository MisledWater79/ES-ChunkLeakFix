add_rules("mode.debug", "mode.release")

add_repositories(
    "liteldev-repo https://github.com/LiteLDev/xmake-repo.git",
    "groupmountain-repo https://github.com/GroupMountain/xmake-repo.git"
)

add_requires("glaciehook 1.0.2", { configs = { static = true } })

add_requires("endstone 0.10.0")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

target("ChunkLeakFix")
    add_defines(
        "NOMINMAX", 
        "UNICODE", 
        "_HAS_CXX23=1"
    )
    add_packages(
        "endstone",
        "glaciehook"
    )
    set_kind("shared")
    set_languages("cxx20")
    set_symbols("debug")
    add_includedirs("src")
    add_files("src/**.cpp")

    add_cxxflags("/Zc:__cplusplus")
    add_cxflags(
        "/EHa",
        "/utf-8",
        -- "/W4",
        "/sdl"
    )

    if is_mode("debug") then
        add_defines("DEBUG")
    elseif is_mode("release") then
        add_defines("NDEBUG")
    end

    after_build(function(target)
        local output_dir = path.join(os.projectdir(), "bin")

        if os.exists(output_dir) then
            os.rm(output_dir)
        end

        os.mkdir(output_dir)

        os.cp(target:targetfile(), output_dir)
        os.cp(target:symbolfile(), output_dir)

        cprint("${bright green}[plugin Packer]: ${reset}plugin already generated to " .. output_dir)
    end)
