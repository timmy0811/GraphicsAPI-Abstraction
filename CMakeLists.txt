file(GLOB_RECURSE WRAPPER_SOURCES
    "src/*.cpp"
    "src/*.c"
)  

file(GLOB_RECURSE WRAPPER_HEADERS
    "src/*.h"
    "src/*.hpp"
) 

set(EXCLUDE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/API/renderer/SpriteRenderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/API/renderer/SpriteRenderer.h"
)

foreach(file ${EXCLUDE_FILES})
    list(REMOVE_ITEM WRAPPER_SOURCES ${file})
    list(REMOVE_ITEM WRAPPER_HEADERS ${file})
endforeach()

add_library(GLWrapper STATIC ${WRAPPER_SOURCES} ${WRAPPER_HEADERS})

target_include_directories(GLWrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(GLWrapper PUBLIC cxx_std_17)
target_precompile_headers(GLWrapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/glpch.h)

target_link_libraries(GLWrapper PRIVATE assimp)
target_link_libraries(GLWrapper PUBLIC yaml-cpp)
target_link_libraries(GLWrapper PUBLIC glew_s)
target_link_libraries(GLWrapper PUBLIC spdlog)
# target_link_libraries(GLWrapper PUBLIC glm)

target_include_directories(GLWrapper PUBLIC ${CMAKE_SOURCE_DIR}/dependencies/glew/include)