#pragma once

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>

namespace IWebCore {

#define $UseCloneClause(klassName)  \
    virtual klassName * klassName::clone() final  \
    {   \
        auto node = new klassName(*this);   \
        node->INody::clone();   \
        return node;    \
    }

struct INody
{
public:
    virtual ~INody() = default;
    virtual INody* clone();

    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) = 0;         // 使用引用，因为传递不需要拷贝，但是如果在函数内改变该内容了，则是需要拷贝备份的。
    virtual void computeNody(){}
protected:
    QJsonValue getValue(const QString& path, const QJsonObject& root, const QMap<QString, QJsonValue>& map);

private:
    QJsonValue getValue(const QString& path, const QJsonObject&);
    QJsonValue getValue(const QString& path, const QMap<QString, QJsonValue>&);
};

struct INodyWithChildren
{
    QList<INody*> m_children;
    virtual ~INodyWithChildren();
};

struct INodyWithChild
{
    INody* m_child{};
    virtual ~INodyWithChild();
};

struct INodyWithTwins
{
    INody* m_elder{};
    INody* m_younger{};
    virtual ~INodyWithTwins();
};

struct IUnionNody : public INody, public INodyWithChildren
{
    $UseCloneClause(IUnionNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
};

struct IHtmlNody : public INody
{
    QString m_html; 
    $UseCloneClause(IHtmlNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
};

struct IVariableNody : public INody
{
    QString m_path;
    $UseCloneClause(IVariableNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
};

struct IfNody : public INody, INodyWithTwins
{
    QString m_path;
    $UseCloneClause(IfNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
};

struct IForNody : public INody, public INodyWithChild
{
    QString m_var;
    QString m_path;
    $UseCloneClause(IForNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
};

struct IWithNody : public INody, public INodyWithChild
{
    QString m_var;
    QString m_path;
    $UseCloneClause(IWithNody)
    virtual QString execute(const QJsonObject &, const QMap<QString, QJsonValue> &) final;
};

struct IIncludeNody : public INody, public INodyWithChild
{
    QString m_path;
    $UseCloneClause(IIncludeNody)
    virtual QString execute(const QJsonObject&, const QMap<QString, QJsonValue>&) final;
    virtual void computeNody() final;
};

struct IBlockNody : public INody, public INodyWithChild
{
    QString m_name;
    $UseCloneClause(IBlockNody)
    virtual QString execute(const QJsonObject &, const QMap<QString, QJsonValue> &) final;
};

struct IExtendNody : public INody, public INodyWithChild, public INodyWithChildren
{
    QString m_path;
    $UseCloneClause(IExtendNody)
    virtual QString execute(const QJsonObject &, const QMap<QString, QJsonValue> &) final;
    virtual void computeNody() final;

private:
    void replaceBlock(INody* node, QMap<QString, IBlockNody*> map);
};

struct IFunNody : public INody, public INodyWithChild
{
    QString m_funName;
    $UseCloneClause(IFunNody)
    virtual QString execute(const QJsonObject &, const QMap<QString, QJsonValue> &);
};

class INodyException : std::exception
{
public:
    INodyException(const QString& error, const QString& content);
    virtual const char *what() const final;

public:
    void addTrace(const QString& error, const QString& content);
    QString getTraces();

private:
    QString makeTrace(const QString& error, const QString& content);

private:
    QStringList m_error;
};

}


