#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $SetHttpIp(value)    \
    PP_PROFILE_CONFIG(SetHttpIpAddress, /http/ip, value)

#define $SetHttpPort(value)   \
    PP_PROFILE_CONFIG(SetHttpIpPort, /http/port, value)


#define $EnableWebPrintTrace(boolValue) \
    PP_PROFILE_CONFIG(EnableWebPrintTrace, http.printTrace, boolValue)

//#define $SetFileServiceMapping_(N) $SetFileServiceMapping_##N
//#define $SetFileServiceMapping_EVAL(N) $SetFileServiceMapping_(N)
//#define $SetFileServiceMapping(...) PP_EXPAND( $SetFileServiceMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

//#define $SetFileServiceMapping_1(path_) \
//    PP_PROFILE_CONFIG(SetFileServiceMapping_location, http.fileService.path, path_) \
//    PP_PROFILE_CONFIG(SetFileServiceMapping_url, http.fileService.mapping, "/")

//#define $SetFileServiceMapping_2(path_, mapping_) \
//    PP_PROFILE_CONFIG(SetFileServiceMapping_location, http.fileService.path, path_) \
//    PP_PROFILE_CONFIG(SetFileServiceMapping_url, http.fileService.url, mapping_)

//// SetFileServiceAttachmentSuffix
//#define $SetFileServiceAttachmentSuffix_(N) $SetFileServiceAttachmentSuffix_##N
//#define $SetFileServiceAttachmentSuffix_EVAL(N) $SetFileServiceAttachmentSuffix_(N)
//#define $SetFileServiceAttachmentSuffix(...) PP_EXPAND( $SetFileServiceAttachmentSuffix_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

//#define $SetFileServiceAttachmentSuffix_1(suffix1) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_1, http.fileService.contentDisposition.suffixes.@$, suffix1)

//#define $SetFileServiceAttachmentSuffix_2(suffix1, suffix2) \
//    $SetFileServiceAttachmentSuffix_1(suffix1) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_2, http.fileService.contentDisposition.suffixes.@$, suffix2)

//#define $SetFileServiceAttachmentSuffix_3(suffix1, suffix2, suffix3) \
//    $SetFileServiceAttachmentSuffix_2(suffix1, suffix2) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_3, http.fileService.contentDisposition.suffixes.@$, suffix3)

//#define $SetFileServiceAttachmentSuffix_4(suffix1, sufix2, suffix3, suffix4) \
//    $SetFileServiceAttachmentSuffix_3(suffix1, suffix2, suffix3) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_4, http.fileService.contentDisposition.suffixes.@$, suffix4)

//#define $SetFileServiceAttachmentSuffix_5(suffix1, suffix2, suffix3, suffix4, suffix5) \
//    $SetFileServiceAttachmentSuffix_4(suffix1, suffix2, suffix3, suffix4) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_5, http.fileService.contentDisposition.suffixes.@$, suffix5)

//#define $SetFileServiceAttachmentSuffix_6(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6) \
//    $SetFileServiceAttachmentSuffix_5(suffix1, suffix2, suffix3, suffix4, suffix5) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_6, http.fileService.contentDisposition.suffixes.@$, suffix6)

//#define $SetFileServiceAttachmentSuffix_7(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6, suffix7) \
//    $SetFileServiceAttachmentSuffix_6(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_7, http.fileService.contentDisposition.suffixes.@$, suffix7)

//#define $SetFileServiceAttachmentSuffix_8(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6, suffix7, suffix8) \
//    $SetFileServiceAttachmentSuffix_7(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6, suffix7) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_8, http.fileService.contentDisposition.suffixes.@$, suffix8)

//#define $SetFileServiceAttachmentSuffix_9(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6, suffix7, suffix8, suffix9) \
//    $SetFileServiceAttachmentSuffix_8(suffix1, suffix2, suffix3, suffix4, suffix5, suffix6, suffix7, suffix8) \
//    PP_PROFILE_CONFIG(SetFileServiceAttachmentSuffix_9, http.fileService.contentDisposition.suffixes.@$, suffix9)

//#define $EnableFileServiceStaticMapping(value)  \
//    PP_PROFILE_CONFIG(EnableFileServiceStaticMapping, http.fileService.staticMapping, value)

//#define $EnableFileServiceContentDisposition(value)  \
//    PP_PROFILE_CONFIG(EnableFileServiceContentDisposition, http.fileService.contentDisposition.enabled, value)

//#define $SetNodyTemplateFolder(path) \
//    PP_PROFILE_CONFIG(SetNodyTemplateFolder, http.templates.nody.templateFolder, path)

//#define $SetFileServiceFolderHandled(value)  \
//    PP_PROFILE_CONFIG(SetFileServiceFolderHandled, http.fileService.folderHandled, value)
