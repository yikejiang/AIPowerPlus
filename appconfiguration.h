#ifndef APPCONFIGURATION_H
#define APPCONFIGURATION_H

#include <utility>

#include <QString>

#include "applang.h"

class AppConfiguration
{
public:
    AppConfiguration();

    QString readAppConfigFolderPath();
    QString readAppConfigFilePath();

    QString readConfig(const QString &appConfigName);
    void saveConfig(const QString &appConfigName, const QString &appConfigValue);

    void addAIModel(const QString &aiModelCustomName, const QString &aiModelName);
    std::pair<QStringList, QStringList> readAIModels();
    QString readAIModelName(const int &indexAIModel);
    void modifyAIModel(const int &indexAIModel, const QString &aiModelCustomName, const QString &aiModelName);
    void removeAIModel(const int &indexAIModel);

    QString readAIRoleConfigFilePath(const QString &aiRole);

    void saveAIRoleConfig(const QString &aiRole, const QString &aiRoleConfigName, const QString &aiRoleConfigValue);
    QString readAIRoleConfig(const QString &aiRole, const QString &aiRoleConfigName);

    std::pair<QString, QString> readAIGuidelinesFilePath(const QString &aiRole);

    std::pair<QString, QString> readAIGuidelines(const QString &aiRole);
    void saveAIGuidelines(const QString &aiRole, const QString &aiGuidelinesType, const QString &aiGuidelinesValue);

    std::pair<QString, QString> readTTSAudioFilePath();

    QString readAITextType(const QString &aiRole);

private:
    AppLang appLang;
};

#endif // APPCONFIGURATION_H
