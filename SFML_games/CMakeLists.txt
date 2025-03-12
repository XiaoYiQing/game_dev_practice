

set( SFML_games_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/TikTakTok.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TTT_wt_but_XYQ.h
    ${CMAKE_CURRENT_SOURCE_DIR}/checkers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CHK_SFML_eng.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cardReact.h
    ${CMAKE_CURRENT_SOURCE_DIR}/CRG_SFML_eng.h
)

set( SFML_games_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/TikTakTok.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TTT_wt_but_XYQ.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/checkers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CHK_SFML_eng.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cardReact.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CRG_SFML_eng.cpp
)


add_library(SFML_games ${SFML_games_HEADERS} ${SFML_games_SOURCES})

target_link_libraries( SFML_games PRIVATE sfml-graphics )

target_link_libraries( SFML_games PRIVATE SFML_utils )
target_include_directories(SFML_games PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML_utils"
)

target_link_libraries( SFML_games PRIVATE utils_XYQ )
target_include_directories(SFML_games PUBLIC
    "${PROJECT_SOURCE_DIR}/utils_XYQ"
)


