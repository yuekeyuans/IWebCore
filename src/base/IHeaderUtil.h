#ifdef _MSC_VER

    #pragma once

    #include <QtCore>
    #include <QtXml>
    #include <QtNetwork>
    #include <QtSql>
    #include "base/IPackageUtil.h"
    #include "assertion/IAssertInfoList.h"

    #define $PackageWebCoreBegin \
        $PackageBegin(IWebCore)

    #define $PackageWebCoreEnd \
        $PackageEnd(IWebCore)

    #define $PackageWebCoreUsing \
        $PackageUsing(IWebCore)

    #define $PackageWebCoreName "IWebCore"

#else

    #ifndef __IHEADUTIL__
    #define __IHEADUTIL__

        #include <QtCore>
        #include <QtXml>
        #include <QtNetwork>
        #include <QtSql>
        #include "base/IPackagePreProcessor.h"

        // IWebCore about
        #define $PackageWebCoreBegin \
            $PackageBegin(IWebCore)

        #define $PackageWebCoreEnd \
            $PackageEnd(IWebCore)

        #define $PackageWebCoreUsing \
            $PackageUsing(IWebCore)

        #define $PackageWebCoreName ("IWebCore")

    #endif


#endif
