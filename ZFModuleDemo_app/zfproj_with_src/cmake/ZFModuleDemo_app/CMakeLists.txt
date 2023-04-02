cmake_minimum_required(VERSION 3.0.0)
set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../ZFFramework)
include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)
include("${ZF_ROOT_PATH}/ZF/ZF_impl/zfproj/cmake/ZF_impl/zfprojConfig.cmake")
if(COMMAND zfprojConfigGlobal_ZFModuleDemo_app)
    zfprojConfigGlobal_ZFModuleDemo_app()
endif()
if(COMMAND zfprojConfigGlobal_ZF_impl)
    zfprojConfigGlobal_ZF_impl()
endif()
project(ZFModuleDemo_app)
message("Build with type: ${CMAKE_BUILD_TYPE}, path: ${PROJECT_SOURCE_DIR}")

include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")

if(WIN32)
    execute_process(COMMAND "${ZF_ROOT_PATH}/zfsetup.bat")
else()
    execute_process(COMMAND sh "${ZF_ROOT_PATH}/zfsetup.sh")
endif()

function(ZFAddSrc srcfiles PROJ_PATH_)
    file(GLOB_RECURSE srcfiles RELATIVE ${PROJECT_SOURCE_DIR}
        ${PROJ_PATH_}/zfsrc/*.c
        ${PROJ_PATH_}/zfsrc/*.cpp
        ${PROJ_PATH_}/zfsrc_ext/*.c
        ${PROJ_PATH_}/zfsrc_ext/*.cpp
        )
    set(${srcfiles} ${${srcfiles}} ${srcfiles} PARENT_SCOPE)

    include_directories(${PROJ_PATH_}/zfsrc)

    if(WIN32)
        execute_process(COMMAND "${ZF_ROOT_PATH}/tools/util/copy_res.bat" "${PROJ_PATH_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    else()
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/util/copy_res.sh" "${PROJ_PATH_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    endif()
endfunction(ZFAddSrc)

ZFAddSrc(srcfiles ${PROJECT_SOURCE_DIR}/../../..)

ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFCore)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFAlgorithm)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFUtility)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFUIKit)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFUIWidget)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZF_impl)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFCore_impl)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFAlgorithm_impl)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/ZF/ZFUIKit_impl)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/../ZFModule/ZF/ZFModuleDemo_lib)
ZFAddSrc(srcfiles ${ZF_ROOT_PATH}/../ZFModule/ZF/ZFModuleDemo_impl)

if(COMMAND zfprojConfigBefore_ZFModuleDemo_app)
    zfprojConfigBefore_ZFModuleDemo_app(ZFModuleDemo_app srcfiles)
endif()
if(COMMAND zfprojConfigBefore_ZF_impl)
    zfprojConfigBefore_ZF_impl(ZFModuleDemo_app srcfiles)
endif()
add_executable(ZFModuleDemo_app ${srcfiles})
zfprojStripFILE(ZFModuleDemo_app)
set_target_properties(ZFModuleDemo_app PROPERTIES LINKER_LANGUAGE CXX)
if(COMMAND zfprojConfigAfter_ZF_impl)
    zfprojConfigAfter_ZF_impl(ZFModuleDemo_app)
endif()
if(COMMAND zfprojConfigAfter_ZFModuleDemo_app)
    zfprojConfigAfter_ZFModuleDemo_app(ZFModuleDemo_app)
endif()

