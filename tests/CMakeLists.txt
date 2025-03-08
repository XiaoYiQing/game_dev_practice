
set( tests_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/window_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/button_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/txtBox_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/HPBar_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/infoBox_test.h
	${CMAKE_CURRENT_SOURCE_DIR}/pageObj_test.h
)

set( tests_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/window_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/button_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/txtBox_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/HPBar_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/infoBox_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/pageObj_test.cpp
)


add_library(tests ${tests_HEADERS} ${tests_SOURCES})

target_link_libraries( tests PRIVATE sfml-graphics )

target_link_libraries( tests PRIVATE SFML_utils )
target_include_directories(tests PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML_utils"
)

target_link_libraries( tests PRIVATE SFML_games )
target_include_directories(tests PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML_games"
)

