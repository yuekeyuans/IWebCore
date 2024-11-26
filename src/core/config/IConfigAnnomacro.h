#pragma once

#include "IConfigPreProcessor.h"

// catagory
#define $EnableCatagory(catagoryName) \
    PP_NORMAL_CONTEXT_CONFIG(EnableCatagory_##catagoryName, /CATAGORY_ENABLE_STATE_##catagoryName, true)

#define $DisableCatagory(catagoryName) \
    PP_NORMAL_CONTEXT_CONFIG(DisableCatagory_##catagoryName, /CATAGORY_ENABLE_STATE_##catagoryName, false)

#define $EnableTask(catagoryName, taskName) \
    PP_NORMAL_CONTEXT_CONFIG(EnableTask_##catagoryName##_##taskName, /TASK_ENABLE_STATE_##catagoryName##_##taskName, true)

#define $DisableTask(catagoryName, taskName) \
    PP_NORMAL_CONTEXT_CONFIG(DisableTask_##catagoryName##_##taskName, /TASK_ENABLE_STATE_##catagoryName##_##taskName, false)

// below is config files anomacro
#define $EnableConfigFiles(value)    \
    PP_NORMAL_CONTEXT_CONFIG(EnableConfigFiles, /config/enableConfigFiles, value)

#define $SetConfigFileFilters_(N) $SetConfigFileFilters_##N
#define $SetConfigFileFilters_EVAL(N) $SetConfigFileFilters_(N)
#define $SetConfigFileFilters(...) PP_EXPAND( $SetConfigFileFilters_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $SetConfigFileFilters_1(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_1, /config/configFileFilters/1, path1_)

#define $SetConfigFileFilters_2(path1_, path2_) \
    $SetConfigFileFilters_1(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_2, /config/configFileFilters/2, path2_)

#define $SetConfigFileFilters_3(path1_, path2_, path3_) \
    $SetConfigFileFilters_2(path1_, path2_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_3, /config/configFileFilters/3, path3_)

#define $SetConfigFileFilters_4(path1_, path2_, path3_, path4_) \
    $SetConfigFileFilters_3(path1_, path2_, path3_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_4, /config/configFileFilters/4, path4_)

#define $SetConfigFileFilters_5(path1_, path2_, path3_, path4_, path5_) \
    $SetConfigFileFilters_4(path1_, path2_, path3_, path4_) \
   PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_5, /config/configFileFilters/5, path5_)

#define $SetConfigFileFilters_6(path1_, path2_, path3_, path4_, path5_, path6_) \
    $SetConfigFileFilters_5(path1_, path2_, path3_, path4_, path5_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_6, /config/configFileFilters/6, path6_)

#define $SetConfigFileFilters_7(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    $SetConfigFileFilters_6(path1_, path2_, path3_, path4_, path5_, path6_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_7, /config/configFileFilters/7, path7_)

#define $SetConfigFileFilters_8(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    $SetConfigFileFilters_7(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_8, /config/configFileFilters/8, path8_)

#define $SetConfigFileFilters_9(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_, path9_) \
    $SetConfigFileFilters_8(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFileFilters_9, /config/configFileFilters/9, path9_)

#define $SetConfigFilePaths_(N) $SetConfigFilePaths_##N
#define $SetConfigFilePaths_EVAL(N) $SetConfigFilePaths_(N)
#define $SetConfigFilePaths(...) PP_EXPAND( $SetConfigFilePaths_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $SetConfigFilePaths_1(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_1, /config/configFilePaths/1, path1_)

#define $SetConfigFilePaths_2(path1_, path2_) \
    $SetConfigFilePaths_1(path1_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_2, /config/configFilePaths/2, path2_)

#define $SetConfigFilePaths_3(path1_, path2_, path3_) \
    $SetConfigFilePaths_2(path1_, path2_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_3, /config/configFilePaths/3, path3_)

#define $SetConfigFilePaths_4(path1_, path2_, path3_, path4_) \
    $SetConfigFilePaths_3(path1_, path2_, path3_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_4, /config/configFilePaths/4, path4_)

#define $SetConfigFilePaths_5(path1_, path2_, path3_, path4_, path5_) \
    $SetConfigFilePaths_4(path1_, path2_, path3_, path4_) \
   PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_5, /config/configFilePaths/5, path5_)

#define $SetConfigFilePaths_6(path1_, path2_, path3_, path4_, path5_, path6_) \
    $SetConfigFilePaths_5(path1_, path2_, path3_, path4_, path5_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_6, config/configFilePaths/6, path6_)

#define $SetConfigFilePaths_7(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    $SetConfigFilePaths_6(path1_, path2_, path3_, path4_, path5_, path6_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_7, /config/configFilePaths/7, path7_)

#define $SetConfigFilePaths_8(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    $SetConfigFilePaths_7(path1_, path2_, path3_, path4_, path5_, path6_, path7_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_8, config/configFilePaths/8, path8_)

#define $SetConfigFilePaths_9(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_, path9_) \
    $SetConfigFilePaths_8(path1_, path2_, path3_, path4_, path5_, path6_, path7_, path8_) \
    PP_NORMAL_CONTEXT_CONFIG(SetConfigFilePaths_9, /config/configFilePaths/9, path9_)

#define $EnableDefaultConfigFiles   \
    $EnableConfigFiles(true)   \
    $SetConfigFileFilters("*.json")    \
    $SetConfigFilePaths(":/config/")

