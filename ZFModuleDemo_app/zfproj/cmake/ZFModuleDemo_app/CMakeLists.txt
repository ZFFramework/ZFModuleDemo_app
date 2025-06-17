cmake_minimum_required(VERSION 3.16)
project(ZFModuleDemo_app)
set(ZF_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../../ZFFramework")
include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE TRUE)
    execute_process(COMMAND "${ZF_ROOT_PATH}\\tools\\release\\release_cmake.bat" 1)
else()
    execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/release/release_cmake.sh" 1)
endif()

file(GLOB_RECURSE ZF_SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/cmake_main.cpp"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c"
    "${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp"
    )
if(COMMAND zfprojConfigBefore_ZFModuleDemo_app)
    zfprojConfigBefore_ZFModuleDemo_app(ZFModuleDemo_app ZF_SRC_FILES)
endif()
add_executable(ZFModuleDemo_app ${ZF_SRC_FILES})
zfprojStripFILE(ZFModuleDemo_app)
set_target_properties(ZFModuleDemo_app PROPERTIES LINKER_LANGUAGE CXX)
if(COMMAND zfprojConfigAfter_ZFModuleDemo_app)
    zfprojConfigAfter_ZFModuleDemo_app(ZFModuleDemo_app)
endif()

target_include_directories(ZFModuleDemo_app PRIVATE "${PROJECT_SOURCE_DIR}/../../../zfsrc")

function(ZFAddLib ZF_LIB_NAME_)
    target_include_directories(ZFModuleDemo_app PRIVATE "${ZF_ROOT_PATH}/_release/cmake/all/include")

    target_link_directories(ZFModuleDemo_app PUBLIC "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib")
    target_link_libraries(ZFModuleDemo_app ${ZF_LIB_NAME_})

    install(
        DIRECTORY "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/"
        DESTINATION "${PROJECT_BINARY_DIR}/zfdist"
        PATTERN "*.lib" EXCLUDE
        )
    if(WIN32)
        execute_process(COMMAND "${ZF_ROOT_PATH}\\tools\\util\\copy_res.bat" "${ZF_ROOT_PATH}\\_release\\cmake\\module\\${ZF_LIB_NAME_}\\zfres\\" "${PROJECT_BINARY_DIR}\\zfdist\\zfres")
    else()
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/util/copy_res.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/zfres/" "${PROJECT_BINARY_DIR}/zfdist/zfres")
    endif()
endfunction()

ZFAddLib(ZFCore)
ZFAddLib(ZFAlgorithm)
ZFAddLib(ZFUtility)
ZFAddLib(ZFUIKit)
ZFAddLib(ZFUIWidget)
ZFAddLib(ZFNet)
ZFAddLib(ZF_impl)
ZFAddLib(ZFCore_impl)
ZFAddLib(ZFAlgorithm_impl)
ZFAddLib(ZFUIKit_impl)
ZFAddLib(ZFModuleDemo_lib)
ZFAddLib(ZFModuleDemo_impl)

if(APPLE)
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "@loader_path")
elseif(WIN32)
else()
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "\\\$ORIGIN;$ORIGIN")
endif()

install(
    TARGETS ZFModuleDemo_app
    DESTINATION "${PROJECT_BINARY_DIR}/zfdist"
    )

file(GLOB_RECURSE SDL_LIBS_
    "${ZF_ROOT_PATH}/_release/cmake/SDL/lib/*SDL3*.*"
    )
foreach(SDL_LIB_ ${SDL_LIBS_})
    if(NOT (SDL_LIB_ MATCHES "_release/cmake/SDL/lib/cmake|_release/cmake/SDL/lib/pkgconfig"))
        if(NOT (SDL_LIB_ MATCHES "SDL3[^/]*\\.a|SDL3[^/]*\\.lib"))
            install(FILES ${SDL_LIB_} DESTINATION "${PROJECT_BINARY_DIR}/zfdist")
        endif()
    endif()
endforeach()

file(GLOB_RECURSE SDL_LIBS_
    "${ZF_ROOT_PATH}/_release/cmake/SDL/bin/*.dll"
    )
foreach(SDL_LIB_ ${SDL_LIBS_})
    install(FILES ${SDL_LIB_} DESTINATION "${PROJECT_BINARY_DIR}/zfdist")
endforeach()

