cmake_minimum_required(VERSION 3.4.1)
project(ZFModuleDemo_app)
set(ZF_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../../ZFFramework")
include("${ZF_ROOT_PATH}/tools/spec/cmake/util.cmake")
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

include("${PROJECT_SOURCE_DIR}/zfprojConfig.cmake" OPTIONAL)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/../../../../_tmp/cmake/ZFModuleDemo_app/app")

execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/release/release_cmake.sh" 1)

file(GLOB_RECURSE ZF_SRC_FILES RELATIVE "${PROJECT_SOURCE_DIR}"
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

    target_link_directories(ZFModuleDemo_app PUBLIC "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/")
    target_link_libraries(ZFModuleDemo_app PUBLIC ${ZF_LIB_NAME_})

    if(WIN32)
        execute_process(COMMAND call "${ZF_ROOT_PATH}\\tools\\common\\copy_check.bat" "${ZF_ROOT_PATH}\\_release\\cmake\\module\\${ZF_LIB_NAME_}\\lib\\" "${CMAKE_INSTALL_PREFIX}\\.")
        execute_process(COMMAND call "${ZF_ROOT_PATH}\\tools\\util\\copy_res.bat" "${ZF_ROOT_PATH}\\_release\\cmake\\module\\${ZF_LIB_NAME_}\\zfres\\" "${PROJECT_BINARY_DIR}\\zfres")
    else()
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/common/copy_check.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/lib/" "${CMAKE_INSTALL_PREFIX}/.")
        execute_process(COMMAND sh "${ZF_ROOT_PATH}/tools/util/copy_res.sh" "${ZF_ROOT_PATH}/_release/cmake/module/${ZF_LIB_NAME_}/zfres/" "${PROJECT_BINARY_DIR}/zfres")
    endif()
endfunction(ZFAddLib)

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

install(TARGETS ZFModuleDemo_app EXPORT ZFModuleDemo_app
    LIBRARY DESTINATION "${PROJECT_BINARY_DIR}"
    ARCHIVE DESTINATION "${PROJECT_BINARY_DIR}"
    RUNTIME DESTINATION "${PROJECT_BINARY_DIR}"
    )

