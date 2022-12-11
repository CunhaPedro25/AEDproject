cmake_minimum_required(VERSION 3.23)
project(AEDproject)

set(CMAKE_C_STANDARD 23)

add_executable(main main.c
        ui/menu/menu.c ui/table/table.c ui/utilities/ui.c ui/pages/pages.c
                    functions/global.c
                    functions/insertFuncs.c functions/deleteFuncts.c functions/editFuncts.c)