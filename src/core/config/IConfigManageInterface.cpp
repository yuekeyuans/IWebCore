#include "IConfigManageInterface.h"
#include "core/abort/IAbortInterface.h"
#include "core/config/IConfigAbort.h"

$PackageWebCoreBegin

namespace detail{
    std::vector<std::string> splitPath(const std::string& path) {
        std::vector<std::string> keys;
        std::stringstream ss(path);
        std::string key;

        while (std::getline(ss, key, '/')) {
            if (!key.empty()) {
                keys.push_back(key);
            }
        }

        return keys;
    }

    void recursiveMerge(IJson& target, const IJson& value) {
        if (target.is_object() && value.is_object()) {
            for (auto it = value.begin(); it != value.end(); ++it) {
                const std::string& key = it.key();
                if (target.contains(key) && target[key].is_object() && it.value().is_object()) {
                    recursiveMerge(target[key], it.value());
                }else if (target.contains(key) && target[key].is_array() && it.value().is_array()) {
                    for (size_t i = 0; i < it.value().size(); ++i) {
                        if (i < target[key].size()) {
                            if (target[key][i].is_object() && it.value()[i].is_object()) {
                                recursiveMerge(target[key][i], it.value()[i]);
                            } else {
                                target[key][i] = it.value()[i];
                            }
                        } else {
                            target[key].push_back(it.value()[i]);
                        }
                    }
                } else {
                    target[key] = it.value();
                }
            }
        }  else if (target.is_array() && value.is_array()) {
            for (size_t i = 0; i < value.size(); ++i) {
                if (i < target.size()) {
                    if (target[i].is_object() && value[i].is_object()) {
                        recursiveMerge(target[i], value[i]);
                    } else {
                        target[i] = value[i];
                    }
                } else {
                    target.push_back(value[i]);
                }
            }
        } else {
            target = value;
        }
    }

    void mergeJson(IJson& target, const IJson& value, const std::string& path) {
        if (path.empty()) {
            return recursiveMerge(target, value);
        }

        std::vector<std::string> keys = splitPath(path);

        IJson* current = &target;
        for (size_t i = 0; i < keys.size(); ++i) {
            const std::string& key = keys[i];

            if (i == keys.size() - 1) {
                if (current->contains(key)) {
                    recursiveMerge((*current)[key], value);
                } else {
                    (*current)[key] = value;
                }
            } else {
                if (!current->contains(key) || !(*current)[key].is_object()) {
                    (*current)[key] = IJson::object();
                }
                current = &(*current)[key];
            }
        }
    }
}


void IConfigManageInterface::addConfig(const IJson &value, const std::string& path)
{
    detail::mergeJson(m_configs, value, path);
}

IJson IConfigManageInterface::getConfig(const QString &path)
{
    return getConfig(path.toStdString());
}

IJson IConfigManageInterface::getConfig(const std::string &path)
{
    if(path.empty()){
        return nullptr;
    }
    if(path.find_first_of('.') != std::string::npos || path[0] != '/'){
        std::string newPath = path[0] == '/' ? path : "/" + path;
        std::replace(newPath.begin(), newPath.end(), '.', '/');
        IJson::json_pointer p(path);
        if(m_configs.contains(p)){
            return m_configs[p];
        }
    }else{
        IJson::json_pointer p(path);
        if(m_configs.contains(p)){
            return m_configs[p];
        }
    }
    return nullptr;
}

$PackageWebCoreEnd

