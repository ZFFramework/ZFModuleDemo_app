#include "ZFCore.h"
#include "ZFUIKit.h"
#include "ZFUIWidget.h"
#include "ZFModuleDemo_lib.h"
#include "ZFImpl/default/ZFImpl_default_ZFModuleDemo_impl.h"

static void myTestCode(void);

ZFMAIN_ENTRY() {
    // TODO: add your code here
    myTestCode();
}

static void myTestCode(void) {
    zfobj<ZFUIWindow> window;
    window->windowShow();

    zfobj<ZFUITextView> textView;
    window->childAdd(textView)->c_alignCenter();
    textView->text(demoFunc());

    ZFLog() << demoFunc();
    ZFLog() << demoFuncFromImpl();
}

