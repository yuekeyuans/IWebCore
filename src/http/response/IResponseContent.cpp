//#include "IResponseContent.h"
//#include "core/util/IFileUtil.h"
//#include "core/util/IConstantUtil.h"
//#include "core/abort/IAbortInterface.h"
//#include "content/IQByteArrayResposneContent.h"
//#include "content/IQStringResponseContent.h"

//$PackageWebCoreBegin

//void IResponseContent::setContent(QString &&content)
//{
//    m_contents.push_back(new IQStringResponseContent(std::move(content)));
//}

//void IResponseContent::setContent(const QString &content)
//{
//    m_contents.push_back(new IQStringResponseContent(content));
//}

//void IResponseContent::setContent(QByteArray &&content)
//{
//    m_contents.push_back(new IQByteArrayResposneContent(std::move(content)));
//}

//void IResponseContent::setContent(const QByteArray &content)
//{
//    m_contents.push_back(new IQByteArrayResposneContent(content));
//}

//void IResponseContent::setContent(const char *content)
//{
//    m_contents.push_back(new IQByteArrayResposneContent(content));
//}

//void IResponseContent::setContent(IHttpInvalidWare ware)
//{
////    type = Type::Invalid;
////    contentString = ware.description;
////    if(ware.m_function){
////        invalidFunction = ware.m_function;
////    }
//}

//void IResponseContent::setFileContent(const QString &path)
//{
//    // TODO:
//}

//IStringView IResponseContent::getContent()
//{
//    if(m_contents.empty()){
//        return IStringView{};
//    }
//    return m_contents.back()->getContent();
//}

//$PackageWebCoreEnd
