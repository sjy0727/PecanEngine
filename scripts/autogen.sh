#git submodule add -f -b docking https://github.com/ocornut/imgui.git  Pecan/vendor/imgui
#git submodule add -f -b release-2.30.x https://github.com/libsdl-org/SDL.git  Pecan/vendor/SDL
#git submodule add -f -b release-2.8.x https://github.com/libsdl-org/SDL_image.git  Pecan/vendor/SDL_image
#git submodule add -f -b v1.x https://github.com/gabime/spdlog.git  Pecan/vendor/spdlog

git submodule update --init --recursive

sudo cp ./scripts/ImguiCMake/CMakeLists.txt ./Pecan/vendor/imgui/CMakeLists.txt