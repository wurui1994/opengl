if is_plat("macosx") then
    add_requires("brew::gl2ps")
else 
    add_requires("vcpkg::gl2ps", 
        "vcpkg::libpng",
        "vcpkg::zlib")
end

set_group("curve")

target("axis")
    add_files("axis.c")

target("grid")
    add_files("grid.c")

target("gl2ps")
    add_files("gl2ps.c")
    if is_plat("macosx") then
        add_packages("brew::gl2ps")
    else 
        add_packages("vcpkg::gl2ps", 
            "vcpkg::libpng",
            "vcpkg::zlib")
    end

target("curve")
    add_files("curve.c")

target("curve2")
    add_files("curve2.c")

target("curve+grid")
    add_files("curve+grid.c")