project(MultiCell)

set (SIMPLE_SOURCES
    src/MultiCell.cpp
)
source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SIMPLE_SOURCES})

add_executable(${PROJECT_NAME} ${SIMPLE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} LTE-Sim::LTE-Sim)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Simulations)