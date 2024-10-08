cmake_minimum_required(VERSION 3.4.1)
project(ZFModuleDemo_app)
set(ZF_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../../ZFFramework")
include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../../../../_tmp/cmake/ZFModuleDemo_app/app")

execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/release/release_cmake.sh" 1)

file(GLOB_RECURSE ZF_SRC_FILES RELATIVE ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.c
    ${PROJECT_SOURCE_DIR}/../../../zfsrc/*.cpp
    ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.c
    ${PROJECT_SOURCE_DIR}/../../../zfsrc_ext/*.cpp
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

include_directories(${PROJECT_SOURCE_DIR}/../../../zfsrc)
include_directories(${ZF_ROOT_PATH}/_release/cmake/all/include)

function(ZFAddLib ZF_LIB_TARGETS_ ZF_LIB_NAME_)
    add_library(${ZF_LIB_NAME_} SHARED IMPORTED)
    file(GLOB_RECURSE libPath "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/*${ZF_LIB_NAME_}*")
    if(NOT libPath)
        message(FATAL_ERROR "unable to find lib ${ZF_LIB_NAME_}")
        return()
    endif()
    set_target_properties(${ZF_LIB_NAME_} PROPERTIES IMPORTED_LOCATION ${libPath})
    set(${ZF_LIB_TARGETS_} ${${ZF_LIB_TARGETS_}} ${ZF_LIB_NAME_} PARENT_SCOPE)

    if(WIN32)
        execute_process(COMMAND "${ZF_ROOT_PATH}/tools/common/copy_check.bat" "${libPath}" "${CMAKE_INSTALL_PREFIX}/.")
        execute_process(COMMAND "${ZF_ROOT_PATH}/tools/util/copy_res.bat" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    else()
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/common/copy_check.sh" "${libPath}" "${CMAKE_INSTALL_PREFIX}/.")
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/util/copy_res.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    endif()
endfunction(ZFAddLib)

ZFAddLib(ZF_LIB_TARGETS ZFCore)
ZFAddLib(ZF_LIB_TARGETS ZFAlgorithm)
ZFAddLib(ZF_LIB_TARGETS ZFUtility)
ZFAddLib(ZF_LIB_TARGETS ZFUIKit)
ZFAddLib(ZF_LIB_TARGETS ZFUIWidget)
ZFAddLib(ZF_LIB_TARGETS ZFNet)
ZFAddLib(ZF_LIB_TARGETS ZF_impl)
ZFAddLib(ZF_LIB_TARGETS ZFCore_impl)
ZFAddLib(ZF_LIB_TARGETS ZFAlgorithm_impl)
ZFAddLib(ZF_LIB_TARGETS ZFUIKit_impl)
ZFAddLib(ZF_LIB_TARGETS ZFModuleDemo_lib)
ZFAddLib(ZF_LIB_TARGETS ZFModuleDemo_impl)

target_link_libraries(ZFModuleDemo_app PRIVATE ${ZF_LIB_TARGETS})
if(APPLE)
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "@loader_path")
elseif(WIN32)
else()
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "\\\$ORIGIN;$ORIGIN")
endif()

