#include "ISqlQuery.h"
#include "core/util/IConvertUtil.h"
#include "core/config/IContextManage.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

ISqlQuery &ISqlQuery::operator=(const ISqlQuery &other)
{
    QSqlQuery::operator=(other);
    this->m_parameters = other.m_parameters;
    return *this;
}

ISqlQuery::~ISqlQuery()
{
    if(isEnableSqlPrint()){
        IOrmManage::logQuery(*this);
    }
}

bool ISqlQuery::exec(const QString &sql)
{
    bindExecParameters();
    return QSqlQuery::exec(sql);
}

bool ISqlQuery::exec()
{
    bindExecParameters();
    return QSqlQuery::exec();
}

void ISqlQuery::bindExecParameters()
{
    if(m_parameters.isEmpty()){
        return;
    }

    //! @note 这里的boundValues 有一点bug
    const auto& boundParameters = boundValues();
    const auto& bounded = boundValues().keys();
    auto keys = m_parameters.keys();
    for(const auto& key : keys){
        if(bounded.indexOf(key) == -1 || !boundParameters[key].isValid()){
            QSqlQuery::bindValue(key, m_parameters[key]);
        }
    }
}

// TODO: 这个也不动，这个应该是 Profile 来处理
bool ISqlQuery::isEnableSqlPrint()
{
    static bool isEnabled = true;

    static std::once_flag flag;
    std::call_once(flag, [](){
        bool ok;
        auto value = IContextManage::instance()->getConfig("ENABLE_SQL_PRINT_INFO", ok);
        if(!ok || !value.isBool()){
            isEnabled = true;
        }else{
            isEnabled = value.toBool();
        }
    });

    return isEnabled;
}


void ISqlQuery::binParameter(const QString &key, const QVariant &value)
{
    m_parameters[key] = value;
}

void ISqlQuery::bindParameters(const QMap<QString, QVariant> &map)
{
    // NOTE:  这里调用的multiInsert, 但应该也没啥问题
    m_parameters.unite(map);
}

$PackageWebCoreEnd
