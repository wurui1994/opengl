# tcc -lgsl -lglut -lGL -run $1
sudo ln -s $(xcrun --show-sdk-path)/System/Library/Frameworks/GLUT.framework/Headers $(xcrun --show-sdk-path)/usr/include/GL
xcrun clang -framework GLUT -framework OpenGL -DGL_SILENCE_DEPRECATION $1
# set VCPKG_ROOT=%USERPROFILE%\Documents\vcpkg
# setx VCPKG_ROOT %USERPROFILE%\Documents\vcpkg
# RefreshEnv -> choco