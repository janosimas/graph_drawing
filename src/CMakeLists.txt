find_package(Magnum REQUIRED
                    Sdl2Application
                    Shaders)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

file(GLOB_RECURSE READER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/reader/*.cpp)
file(GLOB_RECURSE READER_HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/reader/*.hpp)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(app ${SRC_FILES} ${HDR_FILES} ${READER_SRC_FILES} ${READER_HDR_FILES})
target_link_libraries(app
                      Magnum::Application
                      Magnum::Magnum
                      Magnum::Shaders)
