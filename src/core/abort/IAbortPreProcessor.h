#pragma once

#include "core/util/IPreProcessorUtil.h"

#define PP_ABORT_FUNC(name) \
    static void abort ## name(ISourceLocation location){    \
        instance()->abort(name, location);    \
    }   \
    static void abort ## name(const QString& description = {}, ISourceLocation location = {}){  \
        instance()->abort(name, description, location);     \
    }

#define PP_ABORT_EXPAND_1(arg_0)  \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_2(arg_0, arg_1)  \
    PP_ABORT_EXPAND_1(arg_1) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_3(arg_0, arg_1, arg_2)  \
    PP_ABORT_EXPAND_2(arg_1, arg_2) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_4(arg_0, arg_1, arg_2, arg_3)  \
    PP_ABORT_EXPAND_3(arg_1, arg_2, arg_3) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_5(arg_0, arg_1, arg_2, arg_3, arg_4)  \
    PP_ABORT_EXPAND_4(arg_1, arg_2, arg_3, arg_4) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_6(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5)  \
    PP_ABORT_EXPAND_5(arg_1, arg_2, arg_3, arg_4, arg_5) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_7(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6)  \
    PP_ABORT_EXPAND_6(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_8(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7)  \
    PP_ABORT_EXPAND_7(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_9(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8)  \
    PP_ABORT_EXPAND_8(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_10(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9)  \
    PP_ABORT_EXPAND_9(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_11(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10)  \
    PP_ABORT_EXPAND_10(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_12(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11) \
    PP_ABORT_EXPAND_11(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_13(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11, arg_12) \
    PP_ABORT_EXPAND_12(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, arg_11, arg_12) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_14(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13) \
    PP_ABORT_EXPAND_13(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_15(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14) \
    PP_ABORT_EXPAND_14(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_16(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15) \
    PP_ABORT_EXPAND_15(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_17(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16) \
    PP_ABORT_EXPAND_16(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_18(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17) \
    PP_ABORT_EXPAND_17(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_19(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18) \
    PP_ABORT_EXPAND_18(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_20(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19) \
    PP_ABORT_EXPAND_19(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_21(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20) \
    PP_ABORT_EXPAND_20(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_22(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21) \
    PP_ABORT_EXPAND_21(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_23(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22) \
    PP_ABORT_EXPAND_22(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_24(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23) \
    PP_ABORT_EXPAND_23(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_25(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24) \
    PP_ABORT_EXPAND_24(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_26(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25) \
    PP_ABORT_EXPAND_25(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_27(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26) \
    PP_ABORT_EXPAND_26(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_28(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27) \
    PP_ABORT_EXPAND_27(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_29(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28) \
    PP_ABORT_EXPAND_28(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_30(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29) \
    PP_ABORT_EXPAND_29(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_31(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30) \
    PP_ABORT_EXPAND_30(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_32(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31) \
    PP_ABORT_EXPAND_31(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_33(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32) \
    PP_ABORT_EXPAND_32(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_34(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33) \
    PP_ABORT_EXPAND_33(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_35(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34) \
    PP_ABORT_EXPAND_34(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_36(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35) \
    PP_ABORT_EXPAND_35(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_37(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36) \
    PP_ABORT_EXPAND_36(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_38(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37) \
    PP_ABORT_EXPAND_37(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_39(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38) \
    PP_ABORT_EXPAND_38(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_40(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39, arg_40) \
    PP_ABORT_EXPAND_39(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_41(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                       arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                       arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                       arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                       arg_37, arg_38, arg_39, arg_40) \
PP_ABORT_EXPAND_40(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39, arg_40) \
PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_42(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                       arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                       arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                       arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                       arg_37, arg_38, arg_39, arg_40, arg_41) \
PP_ABORT_EXPAND_41(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39, arg_40, arg_41) \
PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_43(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                       arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                       arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                       arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                       arg_37, arg_38, arg_39, arg_40, arg_41, arg_42) \
PP_ABORT_EXPAND_42(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39, arg_40, arg_41, arg_42) \
PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_44(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                       arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                       arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                       arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                       arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43) \
PP_ABORT_EXPAND_43(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                   arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                   arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                   arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                   arg_38, arg_39, arg_40, arg_41, arg_42, arg_43) \
PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_45(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                       arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                       arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                       arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                       arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44) \
    PP_ABORT_EXPAND_44(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_46(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45) \
    PP_ABORT_EXPAND_45(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_47(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, \
                           arg_46) \
    PP_ABORT_EXPAND_46(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, arg_46) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_48(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, \
                           arg_46, arg_47) \
    PP_ABORT_EXPAND_47(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, arg_46, \
                       arg_47) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_49(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, arg_46, arg_47, arg_48) \
    PP_ABORT_EXPAND_48(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, arg_46, \
                       arg_47, arg_48) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_50(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, \
                           arg_10, arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, \
                           arg_19, arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, \
                           arg_28, arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, \
                           arg_37, arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, \
                           arg_46, arg_47, arg_48, arg_49) \
    PP_ABORT_EXPAND_49(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9, arg_10, \
                       arg_11, arg_12, arg_13, arg_14, arg_15, arg_16, arg_17, arg_18, arg_19, \
                       arg_20, arg_21, arg_22, arg_23, arg_24, arg_25, arg_26, arg_27, arg_28, \
                       arg_29, arg_30, arg_31, arg_32, arg_33, arg_34, arg_35, arg_36, arg_37, \
                       arg_38, arg_39, arg_40, arg_41, arg_42, arg_43, arg_44, arg_45, arg_46, \
                       arg_47, arg_48, arg_49) \
    PP_ABORT_FUNC(arg_0)


#define PP_ABORT_EXPAND_(N) PP_ABORT_EXPAND_##N
#define PP_ABORT_EXPAND_EVAL(N) PP_ABORT_EXPAND_(N)
#define PP_ABORT_EXPAND(...) PP_EXPAND( PP_ABORT_EXPAND_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $AsAbort(...)   \
    template<typename T>    \
    friend class IAbortInterface;   \
protected: \
    enum Type{__VA_ARGS__, EndTag}; \
    \
public:     \
    PP_ABORT_EXPAND(__VA_ARGS__)    \
private:
