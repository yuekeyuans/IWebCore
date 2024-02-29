#pragma once

#include "IConfigPreProcessor.h"

// begin task
#define $EnableCatagory(catagoryName) \
    PP_NORMAL_CONTEXT_CONFIG(EnableCatagory_##catagoryName, CATAGORY_ENABLE_STATE_##catagoryName, true)

#define $DisableCatagory(catagoryName) \
    PP_NORMAL_CONTEXT_CONFIG(DisableCatagory_##catagoryName, CATAGORY_ENABLE_STATE_##catagoryName, false)

#define $EnableTask(catagoryName, taskName) \
    PP_NORMAL_CONTEXT_CONFIG(EnableTask_##catagoryName##_##taskName, TASK_ENABLE_STATE_##catagoryName##_##taskName, true)

#define $DisableTask(catagoryName, taskName) \
    PP_NORMAL_CONTEXT_CONFIG(DisableTask_##catagoryName##_##taskName, TASK_ENABLE_STATE_##catagoryName##_##taskName, false)
// end task

// begin test
#define $EnableTest_(N) $EnableTest_##N
#define $EnableTest_EVAL(N) $EnableTest_(N)
#define $EnableTest(...) PP_EXPAND( $EnableTest_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $EnableTest_1(testKlass1) \
    $EnableTask(Test, testKlass1)

#define $EnableTest_2(testKlass1, testKlass2) \
    $EnableTest(testKlass1) \
    $EnableTask(Test, testKlass2)

#define $EnableTest_3(testKlass1, testKlass2, testKlass3) \
    $EnableTest(testKlass1, testKlass2) \
    $EnableTask(Test, testKlass3)

#define $EnableTest_4(testKlass1, testKlass2, testKlass3, testKlass4) \
    $EnableTest(testKlass1, testKlass2, testKlass3) \
    $EnableTask(Test, testKlass4)

#define $EnableTest_5(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5) \
    $EnableTest(testKlass1, testKlass2, testKlass3, testKlass4) \
    $EnableTask(Test, testKlass5)

#define $EnableTest_6(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6) \
    $EnableTest(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5) \
    $EnableTask(Test, testKlass6)

#define $EnableTest_7(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7) \
    $EnableTest(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6) \
    $EnableTask(Test, testKlass7)

#define $EnableTest_8(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8) \
    $EnableTest(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7) \
    $EnableTask(Test, testKlass8)

#define $EnableTest_9(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8, testKlass9) \
    $EnableTest(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8) \
    $EnableTask(Test, testKlass9)

// enable taskManage to output something. default do not output anything
#define $EnableTaskOutput \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableTaskOutputSettingKlass, SYSTEM_ENABLE_TASK_OUTPUT, true)


#define $DisableTest_(N) $DisableTest_##N
#define $DisableTest_EVAL(N) $DisableTest_(N)
#define $DisableTest(...) PP_EXPAND( $DisableTest_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $DisableTest_1(testKlass1) \
    $DisableTask(Test, testKlass1)

#define $DisableTest_2(testKlass1, testKlass2) \
    $DisableTest_1(testKlass1) \
    $DisableTask(Test, testKlass2)

#define $DisableTest_3(testKlass1, testKlass2, testKlass3) \
    $DisableTest_2(testKlass1, testKlass2) \
    $DisableTask(Test, testKlass3)

#define $DisableTest_4(testKlass1, testKlass2, testKlass3, testKlass4) \
    $DisableTest_3(testKlass1, testKlass2, testKlass3) \
    $DisableTask(Test, testKlass4)

#define $DisableTest_5(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5) \
    $DisableTest_4(testKlass1, testKlass2, testKlass3, testKlass4) \
    $DisableTask(Test, testKlass5)

#define $DisableTest_6(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6) \
    $DisableTest_5(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5) \
    $DisableTask(Test, testKlass6)

#define $DisableTest_7(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7) \
    $DisableTest_6(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6) \
    $DisableTask(Test, testKlass7)

#define $DisableTest_8(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8) \
    $DisableTest_7(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7) \
    $DisableTask(Test, testKlass8)

#define $DisableTest_9(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8, testKlass9) \
    $DisableTest_8(testKlass1, testKlass2, testKlass3, testKlass4, testKlass5, testKlass6, testKlass7, testKlass8) \
    $DisableTask(Test, testKlass9)
// end test

// below is config files anomacro
#define $EnableConfigFiles(value)    \
    PP_NORMAL_CONTEXT_CONFIG(EnableConfigFiles, config.enableConfigFiles, value)

#define $EnableExternalConfigFiles(value)    \
    PP_NORMAL_CONTEXT_CONFIG(EnableExternalConfigFiles, config.enableExternalConfigFiles, value)

#define $SetConfigFilesFilter(value)    \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilesFilter, config.configFilesFilter, value)

// SetConfigFilesPath
#define $SetConfigFilespath_(N) $SetConfigFilespath_##N
#define $SetConfigFilespath_EVAL(N) $SetConfigFilespath_(N)
#define $SetConfigFilesPath(...) PP_EXPAND( $SetConfigFilespath_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $SetConfigFilespath_1(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_1, config.configFilePaths.path1, path1_)

#define $SetConfigFilespath_2(path1_, path2_) \
    $SetConfigFilesPath(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_2, config.configFilePaths.path2, path2_)

#define $SetConfigFilespath_3(path1_, path2_, path3_) \
    $SetConfigFilesPath(path1_, path2_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_3, config.configFilePaths.path3, path3_)

#define $SetConfigFilespath_4(path1_, path2_, path3_, path4_) \
    $SetConfigFilesPath(path1_, path2_, path3_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_4, config.configFilePaths.path4, path4_)

#define $SetConfigFilespath_5(path1_, path2_, path3_, path4_, path5_) \
    $SetConfigFilesPath(path1_, path2_, path3_, path4_) \
   PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_5, config.configFilePaths.path5, path5_)

#define $SetConfigFilespath_6(path1_, path2_, path3_, path4_, path5_, path6_) \
    $SetConfigFilesPath(path1_, path2_, path3_, path4_, path5_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_6, config.configFilePaths.path6, path6_)

#define $SetConfigFilespath_7(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    $SetConfigFilesPath(path1_, path2_, path3_, path4_, path5_, path6_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_7, config.configFilePaths.path7, path7_)

#define $SetConfigFilespath_8(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    $SetConfigFilesPath(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_8, config.configFilePaths.path8, path8_)

#define $SetConfigFilespath_9(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_, path9_) \
    $SetConfigFilesPath(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilespath_9, config.configFilePaths.path9, path9_)

#define $EnableDefaultConfigFiles   \
    $EnableConfigFiles(true)   \
    $SetConfigFilesPath(":/config/")    \
    $SetConfigFilesFilter("*.yaml")
