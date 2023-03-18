add_rules("mode.debug", "mode.release")

set_languages("c99", "c++11")

function add_target(t)
    target(path.basename(t))
    add_files(t)
end

if is_plat("windows") then 
    add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force=true}) 
end

if is_plat("macosx") then
    add_frameworks("GLUT", "OpenGL")
    add_defines("GL_SILENCE_DEPRECATION")
else
    add_requires("freeglut")
    add_packages("freeglut")
end

add_subdirs("basic")
add_subdirs("curve")
add_subdirs("mesh")
add_subdirs("glaux")
add_subdirs("picture")