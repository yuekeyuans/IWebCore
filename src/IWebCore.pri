INCLUDEPATH += $$PWD

QT += sql xml testlib

CONFIG += c++17


#CONFIG += console release  # 允许在 release 模式下输出到控制台
#CONFIG -= app_bundle       # 禁用 Windows GUI 应用，仅控制台
#DEFINES += QT_MESSAGELOGCONTEXT  # 保留文件名、行号等上下文信息
#QMAKE_CXXFLAGS_RELEASE += -Zi  # 生成 PDB 调试符号
#QMAKE_LFLAGS_RELEASE += /DEBUG  # 保留 PDB 调试符号文件
#LIBS += -ldbghelp  # 链接 dbghelp 库以支持 MiniDump

msvc {
    debug {
        QMAKE_CXXFLAGS += /bigobj
    }
}

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
    $$PWD/core/bean/IBeanContainerInterface.h \
    $$PWD/core/bean/IBeanRegisterTypeUnit.h \
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
    $$PWD/core/unit/IObjectMemoryPoolUnit.h \
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
    $$PWD/http/IHttpServer.h \
    $$PWD/http/IHttpTaskCatagory.h \
    $$PWD/http/callable/IArgumentType.h \
    $$PWD/http/callable/IArgumentTypeDetail.h \
    $$PWD/http/callable/IMethodParameterManage.h \
    $$PWD/http/callable/IReturnType.h \
    $$PWD/http/biscuits/IHttpAttribute.h \
    $$PWD/http/controller/IHttpControllerAbort.h \
    $$PWD/http/controller/IHttpControllerAction.h \
    $$PWD/http/controller/IHttpControllerInterface.h \
    $$PWD/http/controller/IHttpControllerNode.h \
    $$PWD/http/controller/IHttpPath.h \
    $$PWD/http/controller/IHttpPathValidatorInterface.h \
    $$PWD/http/controller/detail/IHttpControllerInterfaceDetail.h \
    $$PWD/http/controller/detail/IHttpPathDetail.h \
    $$PWD/http/controller/detail/IHttpPathFragmentDetail.h \
    $$PWD/http/controller/detail/IHttpPathValidatorsTask.h \
    $$PWD/http/detail/task/IHttpDefaultProfileTask.h \
    $$PWD/http/detail/task/IHttpFileServiceTask.h \
    $$PWD/http/detail/task/IHttpPrintTraceTask.h \
    $$PWD/http/detail/task/IHttpResolverFactory.h \
    $$PWD/http/invalid/IHttpBadRequestInvalid.h \
    $$PWD/http/invalid/IHttpInternalErrorInvalid.h \
    $$PWD/http/invalid/IHttpInvalidHandlerInterface.h \
    $$PWD/http/invalid/IHttpInvalidInterface.h \
    $$PWD/http/invalid/IHttpInvalidWare.h \
    $$PWD/http/invalid/IHttpNotFoundInvalid.h \
    $$PWD/http/action/IHttpAction.h \
    $$PWD/http/action/IHttpActionInterface.h \
    $$PWD/http/action/IHttpBadRequestAction.h \
    $$PWD/http/action/IHttpControllerMapping.h \
    $$PWD/http/action/IHttpInternalErrorAction.h \
    $$PWD/http/action/IHttpInvalidRequestAction.h \
    $$PWD/http/action/IHttpNotFoundAction.h \
    $$PWD/http/action/IHttpOptionsMethodAction.h \
    $$PWD/http/detail/IRequestRaw.h \
#    $$PWD/http/detail/IResponseHeader.h \
    $$PWD/http/detail/IResponseRaw.h \
    $$PWD/http/mapping/IHttpMappingInterface.h \
    $$PWD/http/mapping/IHttpMappingWare.h \
    $$PWD/http/midware/IHttpFirstLineResolverFilterInterface.h \
    $$PWD/http/midware/IHttpResolverFilterWare.h \
    $$PWD/http/response/content/IFileResponseContent.h \
    $$PWD/http/response/content/IInvalidReponseContent.h \
    $$PWD/http/response/content/IResponseContent.h \
#    $$PWD/http/server/IHttpConnection.h \
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
    $$PWD/http/ICookieJar.h \
    $$PWD/http/ICookiePart.h \
    $$PWD/http/IHeaderJar.h \
    $$PWD/http/IJarUnit.h \
    $$PWD/http/IMultiPart.h \
    $$PWD/http/IMultiPartJar.h \
    $$PWD/http/ISessionJar.h \
    $$PWD/http/IRequest.h \
    $$PWD/http/IResponse.h \
#    $$PWD/http/detail/IRequestAssert.h \
    $$PWD/http/detail/IRequestImpl.h \
    $$PWD/http/callable/IMethodNode.h \
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
    $$PWD/http/session/ISessionWare.h \
    $$PWD/tcp/ITcpAnnomarco.h \
    $$PWD/tcp/ITcpConnection.h \
    $$PWD/tcp/ITcpConnectionData.h \
    $$PWD/tcp/ITcpManage.h \
    $$PWD/tcp/ITcpResolver.h \
    $$PWD/tcp/ITcpResolverFactoryInterface.h \
    $$PWD/tcp/ITcpResolverFactoryWare.h \
    $$PWD/tcp/ITcpServer.h \
    $$PWD/tcp/ITcpSocketFilterInterface.h \
    $$PWD/tcp/ITcpTaskCatagory.h

SOURCES += \
    $$PWD/core/abort/IGlobalAbort.cpp \
    $$PWD/core/application/IApplicationInterface.cpp \
    $$PWD/core/application/IAsioApplication.cpp \
    $$PWD/core/application/IAsioManage.cpp \
    $$PWD/core/application/IQtApplication.cpp \
    $$PWD/core/base/IString.cpp \
    $$PWD/core/base/IStringViewStash.cpp \
    $$PWD/core/base/IStringView_value.cpp \
    $$PWD/core/base/IString_value.cpp \
    $$PWD/core/task/default/IRegisterBaseTypeTask.cpp \
    $$PWD/core/util/ICodecUtil.cpp \
    $$PWD/core/util/IConstantUtil.cpp \
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
    $$PWD/http/IHttpManage.cpp \
    $$PWD/http/IHttpServer.cpp \
    $$PWD/http/callable/IArgumentTypeDetail.cpp \
    $$PWD/http/callable/IMethodParameterManage.cpp \
    $$PWD/http/callable/IReturnType.cpp \
    $$PWD/http/callable/IReturnTypeDetail.cpp \
    $$PWD/http/biscuits/IHttpAttribute.cpp \
    $$PWD/http/biscuits/IHttpHeader.cpp \
    $$PWD/http/controller/IHttpControllerAction.cpp \
    $$PWD/http/controller/IHttpControllerNode.cpp \
    $$PWD/http/controller/IHttpPath.cpp \
    $$PWD/http/controller/IHttpPathFunctorValidatorInterface.cpp \
    $$PWD/http/controller/detail/IHttpControllerInterfaceDetail.cpp \
    $$PWD/http/controller/detail/IHttpPathDetail.cpp \
    $$PWD/http/controller/detail/IHttpPathFragmentDetail.cpp \
    $$PWD/http/controller/detail/IHttpPathValidatorsTask.cpp \
    $$PWD/http/detail/task/IHttpDefaultProfileTask.cpp \
    $$PWD/http/detail/task/IHttpFileServiceTask.cpp \
    $$PWD/http/detail/task/IHttpPrintTraceTask.cpp \
    $$PWD/http/detail/task/IHttpResolverFactory.cpp \
    $$PWD/http/invalid/IHttpBadRequestInvalid.cpp \
    $$PWD/http/invalid/IHttpInternalErrorInvalid.cpp \
    $$PWD/http/invalid/IHttpInvalidWare.cpp \
    $$PWD/http/invalid/IHttpNotFoundInvalid.cpp \
    $$PWD/http/action/IHttpBadRequestAction.cpp \
    $$PWD/http/action/IHttpControllerMapping.cpp \
    $$PWD/http/action/IHttpInternalErrorAction.cpp \
    $$PWD/http/action/IHttpInvalidRequestAction.cpp \
    $$PWD/http/action/IHttpNotFoundAction.cpp \
    $$PWD/http/action/IHttpOptionsMethodAction.cpp \
#    $$PWD/http/detail/IResponseHeader.cpp \
    $$PWD/http/detail/IResponseRaw.cpp \
    $$PWD/http/mapping/IHttpMappingWare.cpp \
    $$PWD/http/response/content/IFileResponseContent.cpp \
    $$PWD/http/response/content/IInvalidReponseContent.cpp \
    $$PWD/http/response/content/IResponseContent.cpp \
    $$PWD/http/response/IStatusResponse.cpp \
#    $$PWD/http/server/IHttpConnection.cpp \
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
    $$PWD/http/ICookieJar.cpp \
    $$PWD/http/ICookiePart.cpp \
    $$PWD/http/IHeaderJar.cpp \
    $$PWD/http/IMultiPart.cpp \
    $$PWD/http/IMultiPartJar.cpp \
    $$PWD/http/ISessionJar.cpp \
    $$PWD/http/IRequest.cpp \
    $$PWD/http/IResponse.cpp \
    $$PWD/http/detail/IRequestImpl.cpp \
    $$PWD/http/callable/IMethodNode.cpp \
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
    $$PWD/http/session/ISessionWare.cpp \
    $$PWD/tcp/ITcpConnection.cpp \
    $$PWD/tcp/ITcpConnectionData.cpp \
    $$PWD/tcp/ITcpManage.cpp \
    $$PWD/tcp/ITcpServer.cpp

HEADERS += \
    $$PWD/IWebCore   \
    $$PWD/ICore/IApplication \
    $$PWD/ICore/IContext \
    $$PWD/ICore/IProfile \
    $$PWD/ICore/IUnitTestInterface \
    $$PWD/IWeb/IHttpInvalidInterface \
    $$PWD/IWeb/HttpRequest

RESOURCES += \
    $$PWD/http/webresource.qrc
