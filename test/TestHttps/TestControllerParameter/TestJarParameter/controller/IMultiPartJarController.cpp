#include "IMultiPartJarController.h"

QString IMultiPartJarController::testFileMultiPartJar(IMultiPartJar jar)
{
    auto fileParts = jar.getRequestFileMultiParts ();

    int count{0};
    for(const auto& filePart : fileParts){ 
        if(filePart.fileName == "main.py"){
            auto size = jar["main.py"].content.toInt ();
            if(filePart.content.size () != size){
                break;      // this will cause error assert
            }
            count ++;
        }

        if(filePart.fileName == "test_multiPartJarController.py"){
            auto size = jar["test_multiPartJarController.py"].content.toInt ();
            if(filePart.content.size () != size){
                break;      // this will cause error assert
            }
            count ++;
        }
    }
    return QString::number (count);
}

QString IMultiPartJarController::testFileMultiPartJarNotExist(IMultiPartJar jar)
{
    const auto& part = jar.getRequestMultiPart ("hello");
    if(!part.isValid ()){
        return "error";
    }
    return "success";
}

QString IMultiPartJarController::testFileMultiPartNames(IMultiPartJar jar)
{
    auto names = jar.getRequestMultiPartNames ();
    return IConvertUtil::toString (names);
}

QString IMultiPartJarController::testFileMultiPart(IMultiPart file_1)
{
    return QString::number (file_1.content.size ());
}
