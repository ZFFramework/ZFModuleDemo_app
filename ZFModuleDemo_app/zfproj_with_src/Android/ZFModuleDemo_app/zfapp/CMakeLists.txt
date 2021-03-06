cmake_minimum_required(VERSION 3.4.1)

set(ZF_ROOT_PATH ${PROJECT_SOURCE_DIR}/../../../../../../ZFFramework)

if(WIN32)
    execute_process(COMMAND ${ZF_ROOT_PATH}/zfsetup.bat)
else()
    execute_process(COMMAND ${ZF_ROOT_PATH}/zfsetup.sh)
endif()

function(ZFAddSrc ZF_SRC_FILES_ PROJ_PATH_)
    file(GLOB_RECURSE srcfiles RELATIVE ${PROJECT_SOURCE_DIR}
        ${PROJ_PATH_}/zfsrc/*.c
        ${PROJ_PATH_}/zfsrc/*.cpp
        ${PROJ_PATH_}/zfsrc_ext/*.c
        ${PROJ_PATH_}/zfsrc_ext/*.cpp
        )
    set(${ZF_SRC_FILES_} ${${ZF_SRC_FILES_}} ${srcfiles} PARENT_SCOPE)

    include_directories(${PROJ_PATH_}/zfsrc)
endfunction(ZFAddSrc)


ZFAddSrc(ZF_SRC_FILES ${PROJECT_SOURCE_DIR}/../../../..)

ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFCore)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFAlgorithm)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUtility)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIKit)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIWidget)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZF_impl)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFCore_impl)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFAlgorithm_impl)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIKit_impl)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/../ZFModule/ZF/ZFModuleDemo_lib)
ZFAddSrc(ZF_SRC_FILES ${ZF_ROOT_PATH}/../ZFModule/ZF/ZFModuleDemo_impl)

add_library(ZFModuleDemo_app SHARED ${ZF_SRC_FILES})
set_target_properties(ZFModuleDemo_app PROPERTIES LINKER_LANGUAGE CXX)
find_library(log-lib log)
find_library(android-lib android)
target_link_libraries(ZFModuleDemo_app ${android-lib} ${log-lib})

