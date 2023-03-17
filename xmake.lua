add_rules("mode.debug", "mode.release")

set_languages("c99", "c++11")

add_frameworks("GLUT", "OpenGL")

target("rect")
    set_kind("binary")
    add_files("rect.c")

target("rotate")
    set_kind("binary")
    add_files("rotate.c")

target("house")
    set_kind("binary")
    add_files("house.c")

target("fivecircle")
    set_kind("binary")
    add_files("fivecircle.c")

target("point")
    set_kind("binary")
    add_files("point.c")

target("opengl")
    set_kind("binary")
    add_files("opengl.c")

target("center")
    set_kind("binary")
    add_files("center.c")

target("keyrotate")
    set_kind("binary")
    add_files("keyrotate.c")

add_subdirs("curve")
add_subdirs("mesh")