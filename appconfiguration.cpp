#include "appconfiguration.h"

#include <QStringList>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

AppConfiguration::AppConfiguration() {
}

QString AppConfiguration::readAppConfigFolderPath() {
    QString pathAppConfigFolder = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    QDir dir(pathAppConfigFolder);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return pathAppConfigFolder;
}

QString AppConfiguration::readAppConfigFilePath() {
    QString pathAppConfigFolder = readAppConfigFolderPath();
    QDir dir(pathAppConfigFolder);

    QString pathAppConfigFile = dir.filePath("AIPowerPlus.ini");

    return pathAppConfigFile;
}

QString AppConfiguration::readConfig(const QString &appConfigName) {
    QString pathAppConfigFile = readAppConfigFilePath();

    QFile fileAppConfig(pathAppConfigFile);

    if (fileAppConfig.exists()) {
        fileAppConfig.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&fileAppConfig);

        QString line;

        while (!in.atEnd()) {
            line = in.readLine();
            QStringList lineParts = line.split("=");
            if (lineParts.length() == 2) {
                QString linePartI = lineParts.at(0).trimmed();
                QString linePartII = lineParts.at(1).trimmed();

                if (linePartI == appConfigName) {
                    fileAppConfig.close();
                    return linePartII;
                }
            }
        }

        fileAppConfig.close();
    }

    return QString();
}

void AppConfiguration::saveConfig(const QString &appConfigName, const QString &appConfigValue) {
    QString pathAppConfigFile = readAppConfigFilePath();

    QFile fileAppConfig(pathAppConfigFile);

    QString fileNewContent;

    if (fileAppConfig.exists()) {
        fileAppConfig.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&fileAppConfig);
        QString fileContent = in.readAll();

        QStringList listFileLines = fileContent.split("\n");

        QStringList listNewFileLines;

        if (fileContent.contains(appConfigName)) {
            for (const QString &line : listFileLines) {
                if (!line.isEmpty()) {
                    QStringList lineParts = line.split("=");
                    if (lineParts.length() == 2) {
                        QString linePartI = lineParts.at(0).trimmed();
                        QString linePartII = lineParts.at(1).trimmed();

                        if (linePartI == appConfigName) {
                            linePartII = appConfigValue;
                        }

                        listNewFileLines.append(linePartI + " = " + linePartII);
                    }
                }
            }
        } else {
            listNewFileLines = listFileLines;
            listNewFileLines.append(appConfigName + " = " + appConfigValue);
        }

        fileAppConfig.close();

        fileNewContent = listNewFileLines.join("\n");
    } else {
        fileNewContent = appConfigName + " = " + appConfigValue;
    }

    fileAppConfig.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&fileAppConfig);
    out << fileNewContent;

    fileAppConfig.close();
}

void AppConfiguration::addAIModel(const QString &aiModelCustomName, const QString &aiModelName) {
    QString aiModelCustomNames = readConfig("ai_model_custom_names");
    QString aiModelNames = readConfig("ai_model_names");

    if (!aiModelCustomNames.isEmpty()) {
        aiModelCustomNames = aiModelCustomNames + "," + aiModelCustomName;
    } else {
        aiModelCustomNames = aiModelCustomName;
    }

    if (!aiModelNames.isEmpty()) {
        aiModelNames = aiModelNames + "," + aiModelName;
    } else {
        aiModelNames = aiModelName;
    }

    saveConfig("ai_model_custom_names", aiModelCustomNames);
    saveConfig("ai_model_names", aiModelNames);
}

std::pair<QStringList, QStringList> AppConfiguration::readAIModels() {
    QString aiModelCustomNames = readConfig("ai_model_custom_names");
    QString aiModelNames = readConfig("ai_model_names");

    if (!aiModelCustomNames.isEmpty()) {
        QStringList listAIModelCustomNames = aiModelCustomNames.split(",");
        QStringList listAIModelNames = aiModelNames.split(",");
        return std::make_pair(listAIModelCustomNames, listAIModelNames);
    } else {
        return std::make_pair(QStringList(), QStringList());
    }
}

QString AppConfiguration::readAIModelName(const int &indexAIModel) {
    std::pair<QStringList, QStringList> pairAIModels = readAIModels();
    QStringList listAIModelNames = pairAIModels.second;
    QString aiModelName = listAIModelNames.at(indexAIModel);
    return aiModelName;
}

void AppConfiguration::modifyAIModel(const int &indexAIModel, const QString &aiModelCustomName, const QString &aiModelName) {
    std::pair<QStringList, QStringList> pairAIModels = readAIModels();
    QStringList listAIModelCustomNames = pairAIModels.first;
    QStringList listAIModelNames = pairAIModels.second;

    listAIModelCustomNames[indexAIModel] = aiModelCustomName;
    listAIModelNames[indexAIModel] = aiModelName;

    QString aiModelCustomNames = listAIModelCustomNames.join(",");
    QString aiModelNames = listAIModelNames.join(",");
    saveConfig("ai_model_custom_names", aiModelCustomNames);
    saveConfig("ai_model_names", aiModelNames);
}

void AppConfiguration::removeAIModel(const int &indexAIModel) {
    std::pair<QStringList, QStringList> pairAIModels = readAIModels();
    QStringList listAIModelCustomNames = pairAIModels.first;
    QStringList listAIModelNames = pairAIModels.second;

    listAIModelCustomNames.removeAt(indexAIModel);
    listAIModelNames.removeAt(indexAIModel);

    QString aiModelCustomNames = listAIModelCustomNames.join(",");
    QString aiModelNames = listAIModelNames.join(",");
    saveConfig("ai_model_custom_names", aiModelCustomNames);
    saveConfig("ai_model_names", aiModelNames);
}

QString AppConfiguration::readAIRoleConfigFilePath(const QString &aiRole) {
    QString pathAppConfigFolder = readAppConfigFolderPath();
    QDir dir(pathAppConfigFolder);

    QString pathAIRoleConfigFile = dir.filePath(QString("%1_config.ini").arg(aiRole));
    return pathAIRoleConfigFile;
}

QString AppConfiguration::readAIRoleConfig(const QString &aiRole, const QString &aiRoleConfigName) {
    QString pathAIRoleConfigFile = readAIRoleConfigFilePath(aiRole);

    QFile fileAIRoleConfig(pathAIRoleConfigFile);

    if (fileAIRoleConfig.exists()) {
        fileAIRoleConfig.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&fileAIRoleConfig);
        QString line;

        while (!in.atEnd()) {
            line = in.readLine();
            QStringList lineParts = line.split("=");
            QString linePartI = lineParts.at(0).trimmed();
            QString linePartII = lineParts.at(1).trimmed();

            if (linePartI == aiRoleConfigName) {
                fileAIRoleConfig.close();
                return linePartII;
            }
        }

        fileAIRoleConfig.close();
    }

    return QString();
}

void AppConfiguration::saveAIRoleConfig(const QString &aiRole, const QString &aiRoleConfigName, const QString &aiRoleConfigValue) {
    QString pathAIRoleConfigFile = readAIRoleConfigFilePath(aiRole);
    QFile fileAIRoleConfig(pathAIRoleConfigFile);

    QString fileNewContent;

    if (fileAIRoleConfig.exists()) {
        fileAIRoleConfig.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&fileAIRoleConfig);
        QString fileContent = in.readAll();
        QStringList listFileLines = fileContent.split("\n");

        QStringList listNewFileLines;

        if (fileContent.contains(aiRoleConfigName)) {
            for (const QString &line : listFileLines) {
                if (!line.isEmpty()) {
                    QStringList lineParts = line.split("=");
                    if (lineParts.length() == 2) {
                        QString linePartI = lineParts.at(0).trimmed();
                        QString linePartII = lineParts.at(1).trimmed();

                        if (linePartI == aiRoleConfigName) {
                            linePartII = aiRoleConfigValue;
                        }

                        listNewFileLines.append(linePartI + " = " + linePartII);
                    }
                }
            }
        } else {
            listNewFileLines = listFileLines;
            listNewFileLines.append(aiRoleConfigName + " = " + aiRoleConfigValue);
        }

        fileAIRoleConfig.close();

        fileNewContent = listNewFileLines.join("\n");
    } else {
        fileNewContent = aiRoleConfigName + " = " + aiRoleConfigValue;
    }

    fileAIRoleConfig.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&fileAIRoleConfig);
    out << fileNewContent;

    fileAIRoleConfig.close();
}

std::pair<QString, QString> AppConfiguration::readAIGuidelinesFilePath(const QString &aiRole) {
    QString pathAppConfigFolder = readAppConfigFolderPath();
    QDir dir(pathAppConfigFolder);

    QString pathAIRoleDescriptionFile = dir.filePath(QString("%1_role_description.ini").arg(aiRole));
    QString pathAIRequirementsFile = dir.filePath(QString("%1_requirements.ini").arg(aiRole));
    return std::make_pair(pathAIRoleDescriptionFile, pathAIRequirementsFile);
}

std::pair<QString, QString> AppConfiguration::readAIGuidelines(const QString &aiRole) {
    std::pair<QString, QString> aiGuidelinesFilePath = readAIGuidelinesFilePath(aiRole);
    QString pathAIRoleDescriptionFile = aiGuidelinesFilePath.first;
    QString pathAIRequirementsFile = aiGuidelinesFilePath.second;

    QFile fileAIRoleDescription(pathAIRoleDescriptionFile);
    QFile fileAIRequirements(pathAIRequirementsFile);

    QString aiRoleDescription;
    QString aiRequirements;

    if (fileAIRoleDescription.exists()) {
        fileAIRoleDescription.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fileAIRoleDescription);

        aiRoleDescription = in.readAll();

        fileAIRoleDescription.close();
    }

    if (fileAIRequirements.exists()) {
        fileAIRequirements.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fileAIRequirements);

        aiRequirements = in.readAll();

        fileAIRequirements.close();
    }

    return std::make_pair(aiRoleDescription, aiRequirements);
}

void AppConfiguration::saveAIGuidelines(const QString &aiRole, const QString &aiGuidelinesType, const QString &aiGuidelinesValue) {
    std::pair<QString, QString> aiGuidelinesFilePath = readAIGuidelinesFilePath(aiRole);
    QString pathAIRoleDescriptionFile = aiGuidelinesFilePath.first;
    QString pathAIRequirementsFile = aiGuidelinesFilePath.second;

    QFile fileAIRoleDescription(pathAIRoleDescriptionFile);
    QFile fileAIRequirements(pathAIRequirementsFile);

    if (aiGuidelinesType == "role_description") {
        fileAIRoleDescription.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&fileAIRoleDescription);

        out << aiGuidelinesValue;

        fileAIRoleDescription.close();
    }

    if (aiGuidelinesType == "requirements") {
        fileAIRequirements.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&fileAIRequirements);

        out << aiGuidelinesValue;

        fileAIRequirements.close();
    }
}

std::pair<QString, QString> AppConfiguration::readTTSAudioFilePath() {
    QString pathTTSAudioFile = readConfig("tts_audio_file_path");

    QString ttsAudioFileType;

    if (pathTTSAudioFile.isEmpty()) {
        QString pathDownloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        pathTTSAudioFile = QDir(pathDownloadsFolder).filePath("tts_audio.mp3");
    } else {
        QString pathTTSAudioFileFolder;

        if (QFileInfo(pathTTSAudioFile).isDir()) {
            pathTTSAudioFileFolder = pathTTSAudioFile;
            pathTTSAudioFile = QDir(pathTTSAudioFileFolder).filePath("tts_audio.mp3");
        } else {
            QFileInfo file(pathTTSAudioFile);

            pathTTSAudioFileFolder = file.absolutePath();
            QString ttsAudioFileBasename = file.baseName();
            ttsAudioFileType = file.suffix();

            if (!QDir(pathTTSAudioFileFolder).exists()) {
                pathTTSAudioFileFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
            }

            if (ttsAudioFileBasename.isEmpty()) {
                ttsAudioFileBasename = "tts_audio";
            }

            QList<QString> listTTSAudioFileSuffix = appLang.listTTSAudioFileSuffix;
            if (!listTTSAudioFileSuffix.contains("." + ttsAudioFileType)) {
                ttsAudioFileType = "mp3";
            }

            pathTTSAudioFile = QDir(pathTTSAudioFileFolder).filePath(ttsAudioFileBasename + "." + ttsAudioFileType);
        }
    }

    ttsAudioFileType = QFileInfo(pathTTSAudioFile).suffix();

    return std::make_pair(pathTTSAudioFile, ttsAudioFileType);
}

QString AppConfiguration::readAITextType(const QString &aiRole) {
    QString aiTextType;

    if (aiRole == "translator") {
        aiTextType = "translation";
    }
    if (aiRole == "writing_helper") {
        aiTextType = "modified text";
    }
    if (aiRole == "writer") {
        aiTextType = "written text";
    }

    return aiTextType;
}
