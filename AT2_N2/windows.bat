@echo off

set dir=%~dp0

cd %dir% && gcc ./functions/functions.c ./functions/menu.c ./main.c -o main.exe

if %errorlevel% equ 0 (
    cls && start cmd /k main.exe
) else (
    echo Erro ao compilar o programa.
)

pause