#include "IConstantUtil.h"

namespace IConstantUtil{

extern const char ServerName[] = "IWebCore";
const char MasterServer[] = "masterServer";


}

namespace IConstantHelper {

void deprecateWarning(){
    using namespace IConstantUtil;

    Q_UNUSED(ServerName)
    Q_UNUSED(MasterServer);
}
}
