cmake_minimum_required(VERSION 3.25)
project(SistemasOperacionais C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(Aula02)
include_directories(Aula04)
include_directories(Trabalho01)

add_executable(SistemasOperacionais
        Aula02/main.c
        Aula04/main.c
        Trabalho01/Beto_04_04_2023/main.c
        Trabalho01/Beto_04_04_2023/main_06_04.c
        Trabalho01/trabalho01Pedro/main.c "Trabalho01/Beto_04_04_2023/main - pedro 08_04 - Prob Ponteiros.c" "Trabalho01/Beto_04_04_2023/main - pedro 08_04.c" Trabalho01/Beto_04_04_2023/group_policy_test_2.c)
