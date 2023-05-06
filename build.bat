cmake -S . -B ./build -G "Visual Studio 17 2022" -T host=x64 -A x64
cmake --build ./build --config Debug --target ALL_BUILD