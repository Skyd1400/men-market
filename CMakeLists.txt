cmake_minimum_required(VERSION 3.6)
project(men_maket)

set(CMAKE_C_STANDARD 11)

set(LIB_FILES lib/conio.c lib/conio2.h lib/libcsv.c lib/csv.h)

set(SOURCE_FILES Maket.h ges_succ.c ges_succ.h ges_prod.c ges_prod.h ges_cli.c ges_cli.h
        ges_vent.c ges_vent.h rapp.c rapp.h ges_mak.c ges_mak.h acc.c acc.h data.c data.h
        test.c test.h page.c page.h menu.c menu.h)
add_executable(men_maket ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(men_maket pdcurses)
