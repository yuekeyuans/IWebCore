#ifdef _MSC_VER

    #pragma once

    #include <QtCore>
    #include <QtXml>
    #include <QtNetwork>
    #include <QtSql>
    #include "package/IPackagePreProcessor.h"
    #include "assertion/IAssertInfoList.h"

#else

    #ifndef __IHEADUTIL__
    #define __IHEADUTIL__

        #include <QtCore>
        #include <QtXml>
        #include <QtNetwork>
        #include <QtSql>
        #include "package/IPackagePreProcessor.h"

    #endif

#endif
