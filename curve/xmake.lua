if is_plat("macosx") then
    add_requires("brew::gl2ps")
else 
    add_requires("vcpkg::gl2ps", 
        "vcpkg::libpng",
        "vcpkg::zlib")
end

set_group("curve")

add_target("axis.c")
add_target("grid.c")
add_target("curve.c")
add_target("curve2.c")
add_target("curve+grid.c")

add_target("gl2ps.c")
if is_plat("macosx") then
    add_packages("brew::gl2ps")
else 
    add_packages("vcpkg::gl2ps", 
        "vcpkg::libpng",
        "vcpkg::zlib")
end