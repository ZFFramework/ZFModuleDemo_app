#include "ZFImpl/sys_Qt/ZFMainEntry_sys_Qt.h"

int main(int argc, char **argv) {
    ZFImpl_sys_Qt_requireLib(ZFCore)
    ZFImpl_sys_Qt_requireLib(ZFAlgorithm)
    ZFImpl_sys_Qt_requireLib(ZFUtility)
    ZFImpl_sys_Qt_requireLib(ZFUIKit)
    ZFImpl_sys_Qt_requireLib(ZFUIWidget)
    ZFImpl_sys_Qt_requireLib(ZFNet)
    ZFImpl_sys_Qt_requireLib(ZF_impl)
    ZFImpl_sys_Qt_requireLib(ZFCore_impl)
    ZFImpl_sys_Qt_requireLib(ZFAlgorithm_impl)
    ZFImpl_sys_Qt_requireLib(ZFUIKit_impl)
    ZFImpl_sys_Qt_requireLib(ZFModuleDemo_lib)
    ZFImpl_sys_Qt_requireLib(ZFModuleDemo_impl)
    return ZFMainEntry_sys_Qt(argc, argv);
}

