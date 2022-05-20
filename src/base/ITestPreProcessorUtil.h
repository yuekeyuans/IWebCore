#pragma once

#define $ITestBegin \
    QCoreApplication app(argc, argv); \
    app.setAttribute(Qt::AA_Use96Dpi, true);

#define $ITestClass(TestObject) \
    TESTLIB_SELFCOVERAGE_START(#TestObject) \
    QT_PREPEND_NAMESPACE(QTest::Internal::callInitMain)<TestObject>(); \
    TestObject m_##TestObject; \
    QTest::qExec(&m_##TestObject, argc, argv);

#define $ITestEnd \
    return 0;
