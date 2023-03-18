add_requires("vcpkg::soil")

add_target("readbmp.c")
add_target("bmpinfo.c")
add_target("texture.c")

add_target("soiljpg.c")
add_packages("vcpkg::soil")
if is_plat("macosx") then
    add_frameworks("CoreFoundation")
end