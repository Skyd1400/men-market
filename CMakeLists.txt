cmake_minimum_required(VERSION 3.6)
project(men_maket)

set(CMAKE_C_STANDARD 11)

set(LIB_FILES lib/conio.c lib/conio2.h lib/libcsv.c lib/csv.h)

set(SOURCE_FILES Maket.h ges_succ.c ges_cli.c
        ges_vent.c rapp.c ges_mak.c acc.c done/strikti.c done/strikti.h
        page.c page.h meni.c meni.h util.c util.h antre.c antre.h done/fichye.c done/fichye.h ges_prod.c)
add_executable(men_maket ${SOURCE_FILES} ${LIB_FILES})
target_link_libraries(men_maket pdcurses)
