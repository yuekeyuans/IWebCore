#pragma once

#include "core/util/IPreProcessorUtil.h"

// NOTE: this writing will be greatly improve in cpp20 latter
#define $PackageBegin_1(name1) \
inline namespace name1 {

#define $PackageBegin_2(name1, name2) \
inline namespace name1 {   \
    inline namespace name2 {

#define $PackageBegin_3(name1, name2, name3) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3

#define $PackageBegin_4(name1, name2, name3, name4) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4

#define $PackageBegin_5(name1, name2, name3, name4, name5) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5

#define $PackageBegin_6(name1, name2, name3, name4, name5, name6) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6

#define $PackageBegin_7(name1, name2, name3, name4, name5, name6, name7) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7

#define $PackageBegin_8(name1, name2, name3, name4, name5, name6, name7, name8) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7 \
                            inline namespace name8

#define $PackageBegin_9(name1, name2, name3, name4, name5, name6, name7, name8, name9) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7 \
                            inline namespace name8 \
                                inline namespace name9

#define $PackageBegin_(N) $PackageBegin_##N
#define $PackageBegin_EVAL(N) $PackageBegin_(N)
#define $PackageBegin(...) PP_EXPAND( $PackageBegin_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


// $PackageEnd
#define $PackageEnd_1(name1) \
}

#define $PackageEnd_2(name1, name2) \
    }   \
}

#define $PackageEnd_3(name1, name2, name3) \
        }   \
    }   \
}

#define $PackageEnd_4(name1, name2, name3, name4) \
            }   \
        }   \
    }   \
}

#define $PackageEnd_5(name1, name2, name3, name4, name5) \
                }   \
            }   \
        }   \
    }   \
}

#define $PackageEnd_6(name1, name2, name3, name4, name5, name6) \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $PackageEnd_7(name1, name2, name3, name4, name5, name6, name7) \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $PackageEnd_8(name1, name2, name3, name4, name5, name6, name7, name8) \
                            }   \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $PackageEnd_9(name1, name2, name3, name4, name5, name6, name7, name8, name9) \
                                }   \
                            }   \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $PackageEnd_(N) $PackageEnd_##N
#define $PackageEnd_EVAL(N) $PackageEnd_(N)
#define $PackageEnd(...) PP_EXPAND( $PackageEnd_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $PackageUsing_1(name1) \
    using namespace name1;

#define $PackageUsing_2(name1, name2) \
    using namespace name1::name2;

#define $PackageUsing_3(name1, name2, name3) \
    using namespace name1::name2::name3;

#define $PackageUsing_4(name1, name2, name3, name4) \
    using namespace name1::name2::name3::name4;

#define $PackageUsing_5(name1, name2, name3, name4, name5) \
    using namespace name1::name2::name3::name4::name5;

#define $PackageUsing_6(name1, name2, name3, name4, name5, name6) \
    using namespace name1::name2::name3::name4::name5::name6;

#define $PackageUsing_7(name1, name2, name3, name4, name5, name6, name7) \
    using namespace name1::name2::name3::name4::name5::name6::name7;

#define $PackageUsing_8(name1, name2, name3, name4, name5, name6, name7, name8) \
    using namespace name1::name2::name3::name4::name5::name6::name7::name8;

#define $PackageUsing_9(name1, name2, name3, name4, name5, name6, name7, name8, name9) \
    using namespace name1::name2::name3::name4::name5::name6::name7::name8::name9;

#define $PackageUsing_(N) $PackageUsing_##N
#define $PackageUsing_EVAL(N) $PackageUsing_(N)
#define $PackageUsing(...) PP_EXPAND( $PackageUsing_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__))

#define $PackageWebCoreBegin \
    $PackageBegin(IWebCore)

#define $PackageWebCoreEnd \
    $PackageEnd(IWebCore)

#define $PackageWebCoreName "IWebCore"
