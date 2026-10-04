@echo off

git clone --depth 1 https://github.com/libsdl-org/SDL "lib/SDL3"
git clone --depth 1 https://github.com/libsdl-org/SDL_shadercross "lib/SDL3_shadercross"

powershell -ExecutionPolicy Bypass -File lib\SDL3_shadercross\external\Get-GitModules.ps1

pause