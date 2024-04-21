#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

enum class IHttpStatus
{
    // 1XX
    CONTINUE_100                            = 100,
    SWITCH_PROTOCOLS_101                    = 101,
    PROCESSING_102                          = 102,
    EARLY_HINTS_103                         = 103,

    // 2XX
    OK_200                                  = 200,
    CREATED_201                             = 201,
    ACCEPTED_202                            = 202,
    NON_AUTHORITATIVE_INFORMATION_203       = 203,
    NO_CONTENT_204                          = 204,
    RESET_CONTENT_205                       = 205,
    PARTIAL_CONTENT_206                     = 206,
    MULTI_STATUS_207                        = 207,
    ALREADY_REPORTED_208                    = 208,
    IM_USED_226                             = 226,

    // 3XX
    MULTIPLE_CHOICE_300                     = 300,
    MOVED_PERMANENTLY_301                   = 301,
    FOUND_302                               = 302,
    SEE_OTHER_303                           = 303,
    NOT_MODIFIED_304                        = 304,
    USE_PROXY_305                           = 305,
    UNUSED_306                              = 306, //unused, see https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#redirection_messages
    TEMPORARY_REDIRECT_307                  = 307,
    PERMANENT_REDIRECT_308                  = 308,

    // 4XX
    BAD_REQUEST_400                         = 400,
    UNAUTHORIZED_401                        = 401,
    PAYMENT_REQURIED_402                    = 402,
    FORBIDDEN_403                           = 403,
    NOT_FOUND_404                            = 404,
    METHOD_NOT_ALLOWED_405                  = 405,
    NOT_ACCEPTABLE_406                      = 406,
    PROXY_AUTHENTICATION_REQUIRED_407       = 407,
    REQUEST_TIMEOUT_408                     = 408,
    CONFLICT_409                            = 409,
    GONE_410                                = 410,
    LENGTH_REQUIRED_411                     = 411,
    PRECODITION_FAILED_412                  = 412,
    PAYLOAD_TOO_LARGE_413                   = 413,
    URI_TOO_LONG_414                        = 414,
    UNSUPPORTED_MEDIA_TYPE_415              = 415,
    RANGE_NOT_SATISFIABLE_416               = 416,
    EXPECTATION_FAILED_417                  = 417,
    I_AM_A_TEAPOT_418                       = 418,
    MISDIRECTED_REQUEST_421                 = 421,
    UNPROCESSABLE_ENTITY_422                = 422,
    LOCKED_423                              = 423,
    FAILED_DEPENDENCY_424                   = 424,
    TOO_EARLY_425                           = 425,
    UPGRADE_REQUIRED_426                    = 426,
    PRECONDITION_REQUIRED_428               = 428,
    TOO_MANY_REQUESTS_429                   = 429,
    REQUEST_HEADER_FIELDS_TOO_LARGE_431     = 431,
    UNAVAILABLE_FOR_LEGAL_REASON_451        = 451,

    //5XX
    INTERNAL_SERVER_ERROR_500               = 500,
    NOT_IMPLEMENTED_501                     = 501,
    BAD_GATEWAY_502                         = 502,
    SERVICE_UNAVAILABLE_503                 = 503,
    GATEWAT_TIMEOUT_504                     = 504,
    HTTP_VERSION_NOT_SUPPORTED              = 505,
    VARIANT_ALSO_NEGOTITAES_505             = 506,
    INSUFFICIENT_STORAGE_506                = 507,
    LOOP_DETECTED_508                       = 508,
    NOT_EXTENDEND_510                       = 510,
    NETWORK_AUTHENTICATION_REQUIRED_511     = 511,

    // other
    UNKNOWN                                 = 1024
};

namespace IHttpStatusHelper {
    QString toString(const IHttpStatus);
    QString toStringDescription(IHttpStatus);
    QString getDescription(IHttpStatus);
    IHttpStatus toStatus(int);
    IHttpStatus toStatus(const QString&);
    const QMap<int, QString> &getStatusDescription();
}

$PackageWebCoreEnd
