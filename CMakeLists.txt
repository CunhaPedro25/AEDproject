cmake_minimum_required(VERSION 3.23)
project(AEDproject)

set(CMAKE_C_STANDARD 23)

add_executable(main main.c
                    ui/menu.c ui/ui.c
                    functions/global.c
                    functions/equipamento.c functions/aplicacoes.c functions/placas.c)