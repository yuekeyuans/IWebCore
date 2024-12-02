INCLUDEPATH += $$PWD

QT += sql xml testlib

CONFIG += c++17

include($$PWD/core/package/package.pri)

PRECOMPILED_HEADER = $$PWD/core/util/IHeaderUtil.h

HEADERS += \
    $$PWD/IHttp/IHttpControllerInterface \
    $$PWD/core/abort/IAbortInterface.h \
    $$PWD/core/abort/IAbortPreProcessor.h \
    $$PWD/core/abort/IGlobalAbort.h \
    $$PWD/core/application/IApplicationAnnomacro.h \
    $$PWD/core/application/IApplicationInterface.h \
    $$PWD/core/application/IAsioApplication.h \
    $$PWD/core/application/IAsioManage.h \
    $$PWD/core/application/IQtApplication.h \
    $$PWD/core/base/IString.h \
    $$PWD/core/base/IStringViewStash.h \
    $$PWD/core/bean/IBeanAbort.h \
    $$PWD/core/bean/IBeanTraitInterface.h \
    $$PWD/core/task/default/IRegisterBaseTypeTask.h \
    $$PWD/core/test/ITestTaskInterface.h \
    $$PWD/core/test/IUnitTestCatagory.h \
    $$PWD/core/trait/IExceptionTrait.h \
    $$PWD/core/unit/IClassNameUnit.h \
    $$PWD/core/unit/ITraceUnit.h \
    $$PWD/core/util/ICodecUtil.h \
    $$PWD/core/util/IConstantUtil.h \
    $$PWD/core/util/IConvertUtil.h \
    $$PWD/core/util/IFileUtil.h \
    $$PWD/core/util/IHeaderUtil.h \
    $$PWD/core/util/IJsonUtil.h \
    $$PWD/core/util/IMetaUtil.h \
    $$PWD/core/util/IPackageUtil.h \
    $$PWD/core/util/IPreProcessorUtil.h \
    $$PWD/core/util/ISpawnUtil.h \
    $$PWD/core/util/IStringUtil.h \
    $$PWD/core/util/ITicTacUtil.h \
    $$PWD/core/util/IToeUtil.h \
    $$PWD/core/util/ITraitUtil.h \
    $$PWD/core/bean/IBeanInterface.h \
    $$PWD/core/bean/IBeanPreProcessor.h \
    $$PWD/core/bean/IBeanTypeManage.h \
    $$PWD/core/bean/IBeanWare.h \
    $$PWD/core/config/IConfigAbort.h \
    $$PWD/core/config/IConfigAnnomacro.h \
    $$PWD/core/config/IConfigImportInterface.h \
    $$PWD/core/config/IConfigManageInterface.h \
    $$PWD/core/config/IConfigPreProcessor.h \
    $$PWD/core/config/IConfigTaskCatagory.h \
    $$PWD/core/config/IContextImport.h \
    $$PWD/core/config/IContextManage.h \
    $$PWD/core/config/IContextTaskInterface.h \
    $$PWD/core/config/IProfileImport.h \
    $$PWD/core/config/IProfileManage.h \
    $$PWD/core/config/IProfileTaskInterface.h \
    $$PWD/core/config/default/IContextJsonProfileTask.h \
    $$PWD/core/config/default/IContextSystemVariableTask.h \
    $$PWD/core/config/default/IContextTomlProfileTask.h \
    $$PWD/core/config/default/ILoadProfileFileUnit.h \
    $$PWD/core/core.h \
    $$PWD/core/base/IResult.h \
    $$PWD/core/base/IStringView.h \
    $$PWD/core/task/ITaskCatagory.h \
    $$PWD/core/task/ITaskCatagoryInterface.h \
    $$PWD/core/task/ITaskPreProcessor.h \
    $$PWD/core/task/default/IBannerTask.h \
    $$PWD/core/task/default/IEndupTaskCatagory.h \
    $$PWD/core/task/default/IEndupTaskInterface.h \
    $$PWD/core/task/default/IInitializationTaskCatagory.h \
    $$PWD/core/task/default/IInitializationTaskInterface.h \
    $$PWD/core/task/default/IStartupTaskCatagory.h \
    $$PWD/core/task/default/IStartupTaskInterface.h \
    $$PWD/core/task/ITaskManage.h \
    $$PWD/core/task/ITaskWare.h \
    $$PWD/core/task/unit/ITaskCatagoryUnit.h \
    $$PWD/core/task/unit/ITaskInstantUnit.h \
    $$PWD/core/task/unit/ITaskWareUnit.h \
    $$PWD/core/test/IUnitTestInterface.h \
    $$PWD/core/test/IUnitTestManage.h \
    $$PWD/core/test/IUnitTestTask.h \
    $$PWD/core/unit/INoConstructUnit.h \
    $$PWD/core/unit/IOrderUnit.h  \
    $$PWD/core/unit/IRegisterMetaTypeUnit.h \
    $$PWD/core/unit/ISingletonUnit.h \
    $$PWD/core/unit/IStackObjectUnit.h \
    $$PWD/core/util/detail/IJsonUtil_fromJson.h \
    $$PWD/core/util/detail/IJsonUtil_toJson.h \
    $$PWD/http/IHttpAnnomacro.h \
    $$PWD/http/IHttpManage.h \
    $$PWD/http/IHttpTaskCatagory.h \
    $$PWD/http/base/IArgumentType.h \
    $$PWD/http/base/IMethodParameterManage.h \
    $$PWD/http/base/IReturnType.h \
    $$PWD/http/biscuits/IHttpAttribute.h \
    $$PWD/http/controller/IHttpControllerAbort.h \
    $$PWD/http/controller/IHttpControllerAction.h \
    $$PWD/http/controller/IHttpControllerInterface.h \
    $$PWD/http/controller/IHttpControllerNode.h \
    $$PWD/http/controller/IHttpPathFunctorValidatorInterface.h \
    $$PWD/http/controller/detail/IHttpControllerBeanParameter.h \
    $$PWD/http/controller/detail/IHttpControllerParameter.h \
    $$PWD/http/controller/detail/IHttpControllerParameterTask.h \
    $$PWD/http/controller/detail/IHttpUrl.h \
    $$PWD/http/controller/detail/IHttpUrlFragment.h \
    $$PWD/http/core/defaultTask/IHttpDefaultProfileTask.h \
    $$PWD/http/core/defaultTask/IHttpFileServiceTask.h \
    $$PWD/http/core/defaultTask/IHttpPrintTraceTask.h \
    $$PWD/http/core/defaultTask/IHttpUrlPathValidatorTask.h \
    $$PWD/http/core/unit/IRegisterResponseUnit.h \
    $$PWD/http/invalid/IHttpBadRequestInvalid.h \
    $$PWD/http/invalid/IHttpInternalErrorInvalid.h \
    $$PWD/http/invalid/IHttpInvalidHandlerInterface.h \
    $$PWD/http/invalid/IHttpInvalidInterface.h \
    $$PWD/http/invalid/IHttpInvalidWare.h \
    $$PWD/http/invalid/IHttpNotFoundInvalid.h \
    $$PWD/http/invalid/IHttpRequestHeaderFieldTooLargeInvalid.h \
    $$PWD/http/invalid/IHttpRequestTimeoutInvalid.h \
    $$PWD/http/mappings/IHttpAction.h \
    $$PWD/http/mappings/IHttpActionInterface.h \
    $$PWD/http/mappings/IHttpBadRequestAction.h \
    $$PWD/http/mappings/IHttpControllerMapping.h \
    $$PWD/http/mappings/IHttpInternalErrorAction.h \
    $$PWD/http/mappings/IHttpMappingInterface.h \
    $$PWD/http/mappings/IHttpMappingWare.h \
    $$PWD/http/mappings/IHttpNotFoundAction.h \
    $$PWD/http/net/IRequestManage.h \
    $$PWD/http/net/impl/IRequestRaw.h \
    $$PWD/http/net/impl/IResponseHeader.h \
    $$PWD/http/net/impl/IResponseRaw.h \
    $$PWD/http/response/content/IFileResponseContent.h \
#    $$PWD/http/response/content/IHtmlResponseContent.h \
    $$PWD/http/response/content/IInvalidReponseContent.h \
#    $$PWD/http/response/content/IJsonResponseContent.h \
#    $$PWD/http/response/content/IQByteArrayResponseContent.h \
#    $$PWD/http/response/content/IQStringResponseContent.h \
    $$PWD/http/response/content/IResponseContentWare.h \
#    $$PWD/http/response/content/IStdStringResponseContent.h \
    $$PWD/http/response/content/IStringResponseContent.h \
#    $$PWD/http/response/content/IStrinigViewResponseContent.h \
    $$PWD/http/server/IHttpConnection.h \
    $$PWD/http/server/IHttpServer.h \
    $$PWD/http/server/ITcpConnection.h \
    $$PWD/http/server/ITcpConnectionData.h \
    $$PWD/http/server/ITcpConnectionManage.h \
    $$PWD/http/server/ITcpResolverInterface.h \
    $$PWD/http/server/ITcpResolverManage.h \
    $$PWD/http/base/IHttpParameterRestrictInterface.h \
    $$PWD/http/base/IHttpParameterRestrictManage.h \
    $$PWD/http/response/IStatusResponse.h \
    $$PWD/orm/IOrmAbort.h \
#    $$PWD/orm/IOrmAssert.h \
    $$PWD/orm/IOrmManage.h \
    $$PWD/orm/IOrmTaskCatagory.h \
    $$PWD/orm/IOrmUtil.h \
    $$PWD/orm/database/IOrmDataSource.h \
    $$PWD/orm/database/IOrmDatabaseInterface.h \
    $$PWD/orm/database/IOrmDatabaseWare.h \
    $$PWD/orm/dialect/IOrmDialectInterface.h \
    $$PWD/orm/dialect/IOrmDialectWare.h \
    $$PWD/orm/model/IOrmEntityModeWare.h \
    $$PWD/orm/model/IOrmTableModelInterface.h \
    $$PWD/orm/model/IOrmViewModelInterface.h \
    $$PWD/orm/pp/IOrmPreProcessor.h \
    $$PWD/orm/pp/IOrmTablePreProcessor.h \
    $$PWD/orm/pp/IOrmViewPreProcessor.h \
    $$PWD/orm/private/IOrmConditionImpl.h \
    $$PWD/orm/ISqlQuery.h \
    $$PWD/orm/clause/IOrmClause.h \
    $$PWD/orm/clause/IOrmCondition.h \
    $$PWD/orm/clause/IOrmQueryClause.h \
    $$PWD/orm/dialect/IOrmMySqlDialect.h \
    $$PWD/orm/dialect/IOrmSqliteDialect.h \
    $$PWD/orm/private/IOrmDatabaseWareImpl.h \
    $$PWD/orm/tableview/IOrmEntityInfoWare.h \
    $$PWD/orm/tableview/IOrmEntityWare.h \
    $$PWD/orm/tableview/IOrmTableInfo.h \
    $$PWD/orm/tableview/IOrmTableInterface.h \
    $$PWD/orm/tableview/IOrmTableWare.h \
    $$PWD/orm/tableview/IOrmViewInfo.h \
    $$PWD/orm/tableview/IOrmViewInterface.h \
    $$PWD/orm/tableview/IOrmViewWare.h \
    $$PWD/http/biscuits/IHttpHeader.h \
    $$PWD/http/biscuits/IHttpMethod.h \
    $$PWD/http/biscuits/IHttpMime.h \
    $$PWD/http/biscuits/IHttpStatus.h \
    $$PWD/http/biscuits/IHttpVersion.h \
    $$PWD/http/controller/IHttpPathRegexpValidatorInterface.h \
    $$PWD/http/net/ICookieJar.h \
    $$PWD/http/net/ICookiePart.h \
    $$PWD/http/net/IHeaderJar.h \
    $$PWD/http/net/IJarUnit.h \
    $$PWD/http/net/IMultiPart.h \
    $$PWD/http/net/IMultiPartJar.h \
    $$PWD/http/net/ISessionJar.h \
    $$PWD/http/net/IRequest.h \
    $$PWD/http/net/IResponse.h \
#    $$PWD/http/net/impl/IRequestAssert.h \
    $$PWD/http/net/impl/IRequestImpl.h \
    $$PWD/http/base/IMethodNode.h \
    $$PWD/http/response/IByteArrayResponse.h \
    $$PWD/http/response/IFileResponse.h \
    $$PWD/http/response/IHtmlResponse.h \
    $$PWD/http/response/IJsonResponse.h \
    $$PWD/http/response/IPlainTextResponse.h \
    $$PWD/http/response/IRedirectResponse.h \
    $$PWD/http/response/IResponseInterface.h \
    $$PWD/http/response/IResponseManage.h \
    $$PWD/http/response/IResponsePreProcessor.h \
    $$PWD/http/response/IResponseTemplateRenderer.h \
    $$PWD/http/response/IResponseWare.h \
    $$PWD/http/controller/pp/IControllerPreProcessor.h \
    $$PWD/http/controller/pp/IDeleteMappingPreProcessor.h \
    $$PWD/http/controller/pp/IGetMappingPreProcessor.h \
    $$PWD/http/controller/pp/IPatchMappingPreProcessor.h \
    $$PWD/http/controller/pp/IPostMappingPreProcessor.h \
    $$PWD/http/controller/pp/IPutMappingPreProcessor.h \
    $$PWD/http/session/ISessionInterface.h \
    $$PWD/http/session/ISessionManager.h \
    $$PWD/http/session/ISessionWare.h

SOURCES += \
    $$PWD/core/abort/IGlobalAbort.cpp \
    $$PWD/core/application/IApplicationInterface.cpp \
    $$PWD/core/application/IAsioApplication.cpp \
    $$PWD/core/application/IAsioManage.cpp \
    $$PWD/core/application/IQtApplication.cpp \
    $$PWD/core/base/IString.cpp \
    $$PWD/core/base/IStringViewStash.cpp \
    $$PWD/core/task/default/IRegisterBaseTypeTask.cpp \
    $$PWD/core/util/ICodecUtil.cpp \
    $$PWD/core/util/IConvertUtil.cpp \
    $$PWD/core/util/IFileUtil.cpp \
    $$PWD/core/util/IHeaderUtil.cpp \
    $$PWD/core/util/IMetaUtil.cpp \
    $$PWD/core/util/IPreProcessorUtil.cpp \
    $$PWD/core/util/IStringUtil.cpp \
    $$PWD/core/util/ITicTacUtil.cpp \
    $$PWD/core/util/IToeUtil.cpp \
    $$PWD/core/bean/IBeanTypeManage.cpp \
    $$PWD/core/config/IConfigManageInterface.cpp \
    $$PWD/core/config/IProfileManage.cpp \
    $$PWD/core/config/default/IContextJsonProfileTask.cpp \
    $$PWD/core/config/default/IContextSystemVariableTask.cpp \
    $$PWD/core/config/default/IContextTomlProfileTask.cpp \
#    $$PWD/core/config/default/IContextYamlProfileTask.cpp \
    $$PWD/core/config/default/ILoadProfileFileUnit.cpp \
    $$PWD/core/base/IStringView.cpp \
    $$PWD/core/task/ITaskCatagory.cpp \
    $$PWD/core/task/default/IBannerTask.cpp \
    $$PWD/core/task/ITaskManage.cpp \
    $$PWD/core/task/ITaskWare.cpp \
    $$PWD/core/test/IUnitTestManage.cpp \
    $$PWD/core/test/IUnitTestTask.cpp \
    $$PWD/core/unit/ISingletonUnit.cpp \
#    $$PWD/http/IHttpAssert.cpp \
#    $$PWD/core/util/detail/IConvertUtilBaseTypeDetail.cpp \
    $$PWD/core/util/detail/IJsonUtil_fromJson.cpp \
    $$PWD/http/IHttpManage.cpp \
    $$PWD/http/base/IArgumentType.cpp \
    $$PWD/http/base/IMethodParameterManage.cpp \
    $$PWD/http/base/IReturnType.cpp \
    $$PWD/http/biscuits/IHttpAttribute.cpp \
    $$PWD/http/biscuits/IHttpHeader.cpp \
    $$PWD/http/controller/IHttpControllerAction.cpp \
    $$PWD/http/controller/IHttpControllerInterface.cpp \
    $$PWD/http/controller/IHttpControllerNode.cpp \
    $$PWD/http/controller/IHttpPathFunctorValidatorInterface.cpp \
    $$PWD/http/controller/IHttpPathRegexpValidatorInterface.cpp \
    $$PWD/http/controller/detail/IHttpControllerBeanParameter.cpp \
    $$PWD/http/controller/detail/IHttpControllerParameter.cpp \
    $$PWD/http/controller/detail/IHttpControllerParameterTask.cpp \
    $$PWD/http/controller/detail/IHttpUrl.cpp \
    $$PWD/http/controller/detail/IHttpUrlFragment.cpp \
    $$PWD/http/core/defaultTask/IHttpDefaultProfileTask.cpp \
    $$PWD/http/core/defaultTask/IHttpFileServiceTask.cpp \
    $$PWD/http/core/defaultTask/IHttpPrintTraceTask.cpp \
    $$PWD/http/core/defaultTask/IHttpUrlPathValidatorTask.cpp \
#    $$PWD/http/core/test/IHttpTestTool.cpp \
    $$PWD/http/invalid/IHttpBadRequestInvalid.cpp \
    $$PWD/http/invalid/IHttpInternalErrorInvalid.cpp \
    $$PWD/http/invalid/IHttpInvalidWare.cpp \
    $$PWD/http/invalid/IHttpNotFoundInvalid.cpp \
    $$PWD/http/invalid/IHttpRequestHeaderFieldTooLargeInvalid.cpp \
    $$PWD/http/invalid/IHttpRequestTimeoutInvalid.cpp \
    $$PWD/http/mappings/IHttpAction.cpp \
    $$PWD/http/mappings/IHttpActionInterface.cpp \
    $$PWD/http/mappings/IHttpBadRequestAction.cpp \
    $$PWD/http/mappings/IHttpControllerMapping.cpp \
    $$PWD/http/mappings/IHttpInternalErrorAction.cpp \
    $$PWD/http/mappings/IHttpMappingWare.cpp \
    $$PWD/http/mappings/IHttpNotFoundAction.cpp \
    $$PWD/http/net/IRequestManage.cpp \
    $$PWD/http/net/impl/IResponseHeader.cpp \
    $$PWD/http/net/impl/IResponseRaw.cpp \
    $$PWD/http/response/content/IFileResponseContent.cpp \
#    $$PWD/http/response/content/IHtmlResponseContent.cpp \
    $$PWD/http/response/content/IInvalidReponseContent.cpp \
#    $$PWD/http/response/content/IJsonResponseContent.cpp \
#    $$PWD/http/response/content/IQByteArrayResponseContent.cpp \
#    $$PWD/http/response/content/IQStringResponseContent.cpp \
    $$PWD/http/response/content/IResponseContentWare.cpp \
#    $$PWD/http/response/content/IStdStringResponseContent.cpp \
    $$PWD/http/response/content/IStringResponseContent.cpp \
#    $$PWD/http/response/content/IStrinigViewResponseContent.cpp \
    $$PWD/http/server/IHttpConnection.cpp \
    $$PWD/http/server/IHttpServer.cpp \
    $$PWD/http/server/ITcpConnection.cpp \
    $$PWD/http/server/ITcpConnectionData.cpp \
    $$PWD/http/server/ITcpConnectionManage.cpp \
    $$PWD/http/server/ITcpResolverInterface.cpp \
    $$PWD/http/server/ITcpResolverManage.cpp \
    $$PWD/http/base/IHttpParameterRestrictManage.cpp \
    $$PWD/http/response/IStatusResponse.cpp \
#    $$PWD/orm/IOrmAssert.cpp \
    $$PWD/orm/IOrmManage.cpp \
    $$PWD/orm/IOrmUtil.cpp \
    $$PWD/orm/database/IOrmDataSource.cpp \
    $$PWD/orm/database/IOrmDatabaseInterface.cpp \
    $$PWD/orm/database/IOrmDatabaseWare.cpp \
    $$PWD/orm/dialect/IOrmDialectInterface.cpp \
    $$PWD/orm/dialect/IOrmDialectWare.cpp \
    $$PWD/orm/model/IOrmEntityModeWare.cpp \
    $$PWD/orm/model/IOrmTableModelInterface.cpp \
    $$PWD/orm/model/IOrmViewModelInterface.cpp \
    $$PWD/orm/private/IOrmConditionImpl.cpp \
    $$PWD/orm/ISqlQuery.cpp \
    $$PWD/orm/clause/IOrmClause.cpp \
    $$PWD/orm/clause/IOrmCondition.cpp \
    $$PWD/orm/clause/IOrmQueryClause.cpp \
    $$PWD/orm/dialect/IOrmMySqlDialect.cpp \
    $$PWD/orm/dialect/IOrmSqliteDialect.cpp \
    $$PWD/orm/private/IOrmDatabaseWareImpl.cpp \
    $$PWD/orm/tableview/IOrmEntityInfoWare.cpp \
    $$PWD/orm/tableview/IOrmEntityWare.cpp \
    $$PWD/orm/tableview/IOrmTableInfo.cpp \
    $$PWD/orm/tableview/IOrmTableWare.cpp \
    $$PWD/orm/tableview/IOrmViewInfo.cpp \
    $$PWD/orm/tableview/IOrmViewWare.cpp \
    $$PWD/http/biscuits/IHttpMethod.cpp \
    $$PWD/http/biscuits/IHttpMime.cpp \
    $$PWD/http/biscuits/IHttpStatus.cpp \
    $$PWD/http/biscuits/IHttpVersion.cpp \
    $$PWD/http/net/ICookieJar.cpp \
    $$PWD/http/net/ICookiePart.cpp \
    $$PWD/http/net/IHeaderJar.cpp \
    $$PWD/http/net/IJarUnit.cpp \
    $$PWD/http/net/IMultiPart.cpp \
    $$PWD/http/net/IMultiPartJar.cpp \
    $$PWD/http/net/ISessionJar.cpp \
    $$PWD/http/net/IRequest.cpp \
    $$PWD/http/net/IResponse.cpp \
    $$PWD/http/net/impl/IRequestImpl.cpp \
    $$PWD/http/base/IMethodNode.cpp \
    $$PWD/http/response/IByteArrayResponse.cpp \
    $$PWD/http/response/IFileResponse.cpp \
    $$PWD/http/response/IHtmlResponse.cpp \
    $$PWD/http/response/IJsonResponse.cpp \
    $$PWD/http/response/IPlainTextResponse.cpp \
    $$PWD/http/response/IRedirectResponse.cpp \
    $$PWD/http/response/IResponseManage.cpp \
    $$PWD/http/response/IResponseTemplateRenderer.cpp \
    $$PWD/http/response/IResponseWare.cpp \
    $$PWD/http/session/ISessionInterface.cpp \
    $$PWD/http/session/ISessionManager.cpp \
    $$PWD/http/session/ISessionWare.cpp

HEADERS += \
    $$PWD/IWebCore   \
    $$PWD/ICore/IApplication \
    $$PWD/ICore/IContext \
    $$PWD/ICore/IProfile \
    $$PWD/ICore/IUnitTestInterface \
#    $$PWD/IWeb/IHttpTestInterface   \
    $$PWD/IWeb/IHttpInvalidInterface \
    $$PWD/IWeb/HttpRequest

DISTFILES +=

RESOURCES += \
    $$PWD/http/webresource.qrc




