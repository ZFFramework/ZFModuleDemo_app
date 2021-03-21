#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFModuleDemo_lib.h"
#include "ZFImpl/default/ZFImpl_default_ZFModuleDemo_impl.h"

static void myTestCode(void);

ZFMAIN_ENTRY()
{
    // TODO: add your code here
    myTestCode();
}

static void myTestCode(void)
{
    zfblockedAlloc(ZFUIWindow, window);
    window->windowShow();

    zfblockedAlloc(ZFUITextView, textView);
    window->childAdd(textView);
    textView->layoutParam()->layoutAlign(ZFUIAlign::e_Center);
    textView->text(demoFunc());

    zfLogT() << demoFunc();
    zfLogT() << demoFuncFromImpl();
}

