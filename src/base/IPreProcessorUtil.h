#pragma once

#define PP_EXPAND(X) X    // for MSVC10 compatibility
#define PP_JOIN(X, Y) X##Y
#define PP_STRING(X) #X

#define PP_NARG(...) PP_EXPAND( PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) )
#define PP_NARG_(...) PP_EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define PP_RSEQ_N() 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define $UseInstance(klassName) \
public: \
    static klassName* instance(){ \
        static klassName m_instance; \
        return &m_instance; \
    } \
private:

#define $UseDataPtr(klass)   \
private:    \
    Q_DECLARE_PRIVATE(klass);    \
    std::shared_ptr<klass##Private> d_ptr {nullptr};

#define $AsWare \
private:    \
    virtual void pureVirtualWare() = 0;

#define $UseWare \
private:    \
    virtual void pureVirtualWare() override {};

#define $AsCatagory(klassName)  $UseInstance(klassName)

#define $UseMetaRegistration(klassName) \
public:     \
static void web_core_init_registerMetaType() {  \
    QString baseName = #klassName ; \
    QString fullName = IMetaUtil::getMetaClassName(staticMetaObject);  \
    IMetaUtil::registerMetaType<klassName>(baseName, fullName); \
}   \
private:

#define $UseGadget(klassName)   \
public:\
    virtual const QString& className() const final {    \
        static const QString clsName = staticMetaObject.className();    \
        return clsName; \
    }   \
    virtual QMetaObject getMetaObject() const final{    \
        return staticMetaObject;    \
    }   \
    virtual const QVector<QMetaMethod>& getMetaMethods() const final{  \
        static auto methods =  IMetaUtil::getMetaMethods(staticMetaObject); \
        return methods; \
    }   \
    virtual const QMap<QString, QString>& getMetaClassInfos() const final{ \
        static auto clsInfos = IMetaUtil::getMetaClassInfoMap(staticMetaObject);    \
        return clsInfos;    \
    }   \
    virtual QMetaProperty getMetaProperty(const QString& name) const final {   \
        return IMetaUtil::getMetaPropertyByName(staticMetaObject, name);    \
    }   \
    virtual const QVector<QMetaProperty>& getMetaProperties() const final {    \
        static auto props = IMetaUtil::getMetaProperties(staticMetaObject);  \
        return props;   \
    }   \
    virtual QVariant getFieldValue(const QString& name) const final {   \
        const auto& property = getMetaProperty(name);  \
        return IMetaUtil::readProperty(property, this); \
    }   \
    virtual void setFieldValue(const QString& name, const QVariant& value) final{     \
        const auto& property = getMetaProperty(name);  \
        IMetaUtil::writeProperty(property, this, value);    \
    }   \
    virtual QJsonObject toJson() const final{   \
        auto map = IMetaUtil::toVariantMap(this, staticMetaObject); \
        return IConvertUtil::toJsonObject(map); \
    }   \
    virtual QMap<QString, QVariant> toVariantMap() const final{ \
        return IMetaUtil::toVariantMap(this, staticMetaObject); \
    }   \
    virtual const QStringList& getIgnorableFieldNames() const override{ \
        static QStringList ignoredFields = IMetaUtil::getIgnoredFields(staticMetaObject);   \
        return ignoredFields;   \
    }   \
    virtual const QVector<int>& getIgnorableFieldIndexes() const override{  \
        static QVector<int> ignoredFields = IMetaUtil::getIgnoredFieldIndexes(staticMetaObject);   \
        return ignoredFields;   \
    }   \
    virtual bool isIgnorableField(const QString& name) const override{  \
        static const QStringList ignoredFields = getIgnorableFieldNames();  \
        return ignoredFields.contains(name);    \
    }   \
    virtual bool isIgnorableField(int index) const override{    \
        static const QVector<int> ignoredFields = getIgnorableFieldIndexes();   \
        return ignoredFields.contains(index);   \
    }   \
    virtual const QStringList& getMetaFieldNames() const override{  \
        static QStringList fieldNames = IMetaUtil::getMetaPropertyNames(staticMetaObject);  \
        return fieldNames;  \
    }   \
private:


// create on stack only
#define Q_CREATE_ON_STACK_ONLY \
private:    \
    void* operator new(size_t) noexcept {return nullptr;};  \
    void operator delete(void*){};  \

