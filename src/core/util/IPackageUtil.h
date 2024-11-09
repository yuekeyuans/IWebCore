#pragma once

#include "core/util/IPreProcessorUtil.h"

// NOTE: this writing will be greatly improve in cpp20 latter
#define $IPackageBegin_1(name1) \
inline namespace name1 {

#define $IPackageBegin_2(name1, name2) \
inline namespace name1 {   \
    inline namespace name2 {

#define $IPackageBegin_3(name1, name2, name3) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3

#define $IPackageBegin_4(name1, name2, name3, name4) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4

#define $IPackageBegin_5(name1, name2, name3, name4, name5) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5

#define $IPackageBegin_6(name1, name2, name3, name4, name5, name6) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6

#define $IPackageBegin_7(name1, name2, name3, name4, name5, name6, name7) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7

#define $IPackageBegin_8(name1, name2, name3, name4, name5, name6, name7, name8) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7 \
                            inline namespace name8

#define $IPackageBegin_9(name1, name2, name3, name4, name5, name6, name7, name8, name9) \
inline namespace name1 {   \
    inline namespace name2 {   \
        inline namespace name3 \
            inline namespace name4 \
                inline namespace name5 \
                    inline namespace name6 \
                        inline namespace name7 \
                            inline namespace name8 \
                                inline namespace name9

#define $IPackageBegin_(N) $IPackageBegin_##N
#define $IPackageBegin_EVAL(N) $IPackageBegin_(N)
#define $IPackageBegin(...) PP_EXPAND( $IPackageBegin_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $IPackageEnd_1(name1) \
}

#define $IPackageEnd_2(name1, name2) \
    }   \
}

#define $IPackageEnd_3(name1, name2, name3) \
        }   \
    }   \
}

#define $IPackageEnd_4(name1, name2, name3, name4) \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_5(name1, name2, name3, name4, name5) \
                }   \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_6(name1, name2, name3, name4, name5, name6) \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_7(name1, name2, name3, name4, name5, name6, name7) \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_8(name1, name2, name3, name4, name5, name6, name7, name8) \
                            }   \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_9(name1, name2, name3, name4, name5, name6, name7, name8, name9) \
                                }   \
                            }   \
                        }   \
                    }   \
                }   \
            }   \
        }   \
    }   \
}

#define $IPackageEnd_(N) $IPackageEnd_##N
#define $IPackageEnd_EVAL(N) $IPackageEnd_(N)
#define $IPackageEnd(...) PP_EXPAND( $IPackageEnd_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


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

#define $PackageWebCoreBegin  $IPackageBegin(IWebCore)

#define $PackageWebCoreEnd    $IPackageEnd(IWebCore)

#define $PackageDetailBegin   $IPackageBegin(detail)

#define $PackageDetailEnd     $IPackageEnd(detail)


#define $PackageWebCoreName "IWebCore"
