cmake_minimum_required(VERSION 3.16)
project(ZFModuleDemo_app)
set(ZF_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../../ZFFramework")
include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE TRUE)
endif()

zfprojExec("${PROJECT_SOURCE_DIR}/../../../../zfsetup")

set(ZF_SRC_FILES ${ZF_SRC_FILES} "${PROJECT_SOURCE_DIR}/cmake_main.cpp")

function(ZFAddSrc ZF_LIB_NAMES_ LIB_NAME_ ZF_SRC_FILES_ PROJ_PATH_)
    set(${ZF_LIB_NAMES_} ${${ZF_LIB_NAMES_}} ${LIB_NAME_} PARENT_SCOPE)
    if(NOT "${ARGV4}" STREQUAL "")
        include("${ARGV4}/zfprojConfig.cmake" OPTIONAL)
    else()
        include("${PROJ_PATH_}/zfproj/cmake/${LIB_NAME_}/zfprojConfig.cmake" OPTIONAL)
    endif()
    zfprojSrcFiles(
        ZF_SRC_FILES_TMP
        "${CMAKE_BINARY_DIR}/zfgensrc/zfgensrc_${LIB_NAME_}.cpp"
        "${ZF_ROOT_PATH}"
        "${PROJECT_SOURCE_DIR}"
        "${PROJ_PATH_}"
        )
    set(${ZF_SRC_FILES_} ${${ZF_SRC_FILES_}} ${ZF_SRC_FILES_TMP} PARENT_SCOPE)
    include_directories("${PROJ_PATH_}/zfsrc")
    zfprojExec("${ZF_ROOT_PATH}/tools/util/copy_res" "${PROJ_PATH_}/zfres/" "${CMAKE_INSTALL_PREFIX}/bin/zfres")
endfunction()

ZFAddSrc(ZF_LIB_NAMES ZFModuleDemo_app ZF_SRC_FILES ${PROJECT_SOURCE_DIR}/../../.. ${PROJECT_SOURCE_DIR})

ZFAddSrc(ZF_LIB_NAMES ZFCore ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFCore)
ZFAddSrc(ZF_LIB_NAMES ZFAlgorithm ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFAlgorithm)
ZFAddSrc(ZF_LIB_NAMES ZFUtility ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUtility)
ZFAddSrc(ZF_LIB_NAMES ZFUIKit ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIKit)
ZFAddSrc(ZF_LIB_NAMES ZFUIWidget ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIWidget)
ZFAddSrc(ZF_LIB_NAMES ZF_impl ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZF_impl)
ZFAddSrc(ZF_LIB_NAMES ZFCore_impl ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFCore_impl)
ZFAddSrc(ZF_LIB_NAMES ZFAlgorithm_impl ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFAlgorithm_impl)
ZFAddSrc(ZF_LIB_NAMES ZFUIKit_impl ZF_SRC_FILES ${ZF_ROOT_PATH}/ZF/ZFUIKit_impl)
ZFAddSrc(ZF_LIB_NAMES ZFModuleDemo_lib ZF_SRC_FILES ${ZF_ROOT_PATH}/ZFModule/ZFModuleDemo_lib)
ZFAddSrc(ZF_LIB_NAMES ZFModuleDemo_impl ZF_SRC_FILES ${ZF_ROOT_PATH}/ZFModule/ZFModuleDemo_impl)

include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)
if(COMMAND zfprojConfigBefore_ZFModuleDemo_app)
    zfprojConfigBefore_ZFModuleDemo_app(ZFModuleDemo_app ZF_SRC_FILES)
endif()
foreach(LIB_NAME_ ${ZF_LIB_NAMES})
    if(COMMAND zfprojConfigBefore_${LIB_NAME_})
        cmake_language(CALL zfprojConfigBefore_${LIB_NAME_} ZFModuleDemo_app ZF_SRC_FILES)
    endif()
endforeach()
add_executable(ZFModuleDemo_app ${ZF_SRC_FILES})
target_compile_options(ZFModuleDemo_app PRIVATE "$<$<CONFIG:DEBUG>:-DDEBUG>")
zfprojStripFILE(ZFModuleDemo_app)
set_target_properties(ZFModuleDemo_app PROPERTIES LINKER_LANGUAGE CXX)
foreach(LIB_NAME_ ${ZF_LIB_NAMES})
    if(COMMAND zfprojConfigAfter_${LIB_NAME_})
        cmake_language(CALL zfprojConfigAfter_${LIB_NAME_} ZFModuleDemo_app)
    endif()
endforeach()
if(COMMAND zfprojConfigAfter_ZFModuleDemo_app)
    zfprojConfigAfter_ZFModuleDemo_app(ZFModuleDemo_app)
endif()

# dllimport not work for app with all src, disable it explicitly
foreach(LIB_NAME_ ${ZF_LIB_NAMES})
    target_compile_definitions(ZFModuleDemo_app PUBLIC ZFLIB_${LIB_NAME_}=)
endforeach()

if(APPLE)
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "@loader_path")
elseif(WIN32)
else()
    set_target_properties(ZFModuleDemo_app PROPERTIES INSTALL_RPATH "\\\$ORIGIN;$ORIGIN")
endif()

install(
    TARGETS ZFModuleDemo_app
    DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    )

file(GLOB AppIconPath "${PROJECT_SOURCE_DIR}/AppIcon.png")
if(NOT "${AppIconPath}" STREQUAL "")
    install(FILES ${AppIconPath} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/zfres/ZFUIKit_impl/sys_SDL")
endif()

