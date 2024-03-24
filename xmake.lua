add_rules("mode.debug", "mode.release")

set_languages("c99", "c++11")

function add_target(t)
    target(path.basename(t))
    add_files(t)
end

if is_plat("windows") then 
    add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force=true}) 
end

after_build(function (target)
	local outputdir = path.directory(target:targetfile())
	for _, pkg in ipairs(target:orderpkgs()) do
		for _, dllpath in ipairs(table.wrap(pkg:get("libfiles"))) do
			local dllname = path.filename(dllpath)
			if not os.isfile(path.join(outputdir, dllname))
				and dllpath:endswith(".dll")
				and os.isdir(outputdir) then
				os.vcp(dllpath, outputdir)
			end
		end
	end
end)

if is_plat("macosx") then
    add_frameworks("GLUT", "OpenGL")
    add_defines("GL_SILENCE_DEPRECATION")
else
    add_requires("freeglut", {configs = {shared = true}})
    add_packages("freeglut")
end

add_subdirs("basic")
add_subdirs("curve")
add_subdirs("mesh")
add_subdirs("glaux")
add_subdirs("picture")
add_subdirs("shader")