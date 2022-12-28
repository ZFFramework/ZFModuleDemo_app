
include("${ZF_ROOT_PATH}/ZF/ZF_impl/zfproj/cmake/ZF_impl/zfprojConfig.cmake")

function(zfprojConfigBefore_ZFModuleDemo_app projName srcfiles)
    if(COMMAND zfprojConfigBefore_ZF_impl)
        zfprojConfigBefore_ZF_impl(${projName} ${srcfiles})
    endif()
endfunction(zfprojConfigBefore_ZFModuleDemo_app)

function(zfprojConfigAfter_ZFModuleDemo_app projName)
    if(COMMAND zfprojConfigAfter_ZF_impl)
        zfprojConfigAfter_ZF_impl(${projName})
    endif()
endfunction(zfprojConfigAfter_ZFModuleDemo_app)

