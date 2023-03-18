if is_plat("macos") then
    add_requires("brew::gl2ps")
else 
    add_requires("vcpkg::gl2ps")
end

target("axis")
    set_kind("binary")
    add_files("axis.c")

target("grid")
    set_kind("binary")
    add_files("grid.c")

target("gl2ps")
    set_kind("binary")
    add_files("gl2ps.c")
    if is_plat("macos") then
        add_packages("brew::gl2ps")
    else 
        add_packages("vcpkg::gl2ps")
    end

target("curve")
    set_kind("binary")
    add_files("curve.c")

target("curve2")
    set_kind("binary")
    add_files("curve2.c")

target("curve+grid")
    set_kind("binary")
    add_files("curve+grid.c")