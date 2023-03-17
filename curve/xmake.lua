add_requires("brew::gl2ps")

target("axis")
    set_kind("binary")
    add_files("axis.c")

target("grid")
    set_kind("binary")
    add_files("grid.c")

target("gl2ps")
    set_kind("binary")
    add_files("gl2ps.c")
    add_packages("brew::gl2ps")

target("curve")
    set_kind("binary")
    add_files("curve.c")

target("curve2")
    set_kind("binary")
    add_files("curve2.c")

target("curve+grid")
    set_kind("binary")
    add_files("curve+grid.c")