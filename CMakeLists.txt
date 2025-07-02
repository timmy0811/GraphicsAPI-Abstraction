file(GLOB_RECURSE GLWRAPPER_SOURCES
        "src/*.cpp"
        "src/*.c")

file(GLOB_RECURSE GLWRAPPER_HEADERS
        "src/*.h"
        "src/*.hpp")

# Remove .vshistory files from the sources and headers
list(FILTER GLWRAPPER_SOURCES EXCLUDE REGEX ".*\.vshistory/.*")
list(FILTER GLWRAPPER_HEADERS EXCLUDE REGEX ".*\.vshistory/.*")

set(EXCLUDE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/API/renderer/SpriteRenderer.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/API/renderer/SpriteRenderer.h"
)

foreach (file ${EXCLUDE_FILES})
    list(REMOVE_ITEM GLWRAPPER_SOURCES ${file})
    list(REMOVE_ITEM GLWRAPPER_HEADERS ${file})
endforeach ()

add_library(GLWrapper STATIC ${GLWRAPPER_SOURCES} ${GLWRAPPER_HEADERS})

target_include_directories(GLWrapper BEFORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(GLWrapper BEFORE PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/glew/include)

target_compile_features(GLWrapper PUBLIC cxx_std_17)
target_precompile_headers(GLWrapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/glpch.h)

target_link_libraries(GLWrapper PUBLIC assimp)
target_link_libraries(GLWrapper PUBLIC yaml-cpp)
target_link_libraries(GLWrapper PUBLIC glew_s)
target_link_libraries(GLWrapper PUBLIC spdlog)
# target_link_libraries(GLWrapper PUBLIC glm)

target_compile_definitions(GLWrapper PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:RELEASE>
)

if (WIN32)
    target_compile_definitions(GLWrapper PUBLIC
            GLW_PLATFORM_WINDOWS
    )
endif ()

if (NOT WIN32)
    target_compile_definitions(GLWrapper PUBLIC
            GLW_PLATFORM_LINUX
    )
endif ()