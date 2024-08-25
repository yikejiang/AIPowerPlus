#include "appsettings.h"

#include <utility>

#include <QSizePolicy>
#include <Qt>
#include <QIcon>
#include <QStringList>
#include <QDir>
#include <QStandardPaths>
#include <QFileDialog>
#include <QFileInfo>

AppSettings::AppSettings() : QDialog() {
    this -> setGeometry(0, 0, 900, 600);

    this -> setWindowIcon(QIcon(":/resources/logo.ico"));

    font.setPointSize(11);

    this -> setLayout(settingsLayout);

    layoutLeft -> setAlignment(Qt::AlignTop);
    settingsLayout -> addLayout(layoutLeft);

    layoutLeft -> addLayout(layoutLeftUpper);

    layoutLeftUpperFirst -> setAlignment(Qt::AlignLeft);
    layoutLeftUpper -> addLayout(layoutLeftUpperFirst);

    layoutLeftUpperSecond -> setAlignment(Qt::AlignLeft);
    layoutLeftUpper -> addLayout(layoutLeftUpperSecond);

    layoutLeftUpperThird -> setAlignment(Qt::AlignLeft);
    layoutLeftUpper -> addLayout(layoutLeftUpperThird);

    layoutLeftUpperFourth -> setAlignment(Qt::AlignLeft);
    layoutLeftUpper -> addLayout(layoutLeftUpperFourth);

    containerRight -> setFixedWidth(400);
    containerRight -> setLayout(layoutRight);
    settingsLayout -> addWidget(containerRight);

    layoutRight -> setAlignment(Qt::AlignTop);

    layoutRight -> setContentsMargins(20, 0, 0, 0);
    layoutRight -> addLayout(layoutRightUpper);

    layoutRightUpperFirst -> setAlignment(Qt::AlignLeft);
    layoutRightUpper -> addLayout(layoutRightUpperFirst);

    layoutRightUpperSecond -> setAlignment(Qt::AlignLeft);
    layoutRightUpper -> addLayout(layoutRightUpperSecond);

    layoutRightUpperThird -> setAlignment(Qt::AlignLeft);
    layoutRightUpper -> addLayout(layoutRightUpperThird);

    layoutRightUpperFourth -> setAlignment(Qt::AlignLeft);
    layoutRightUpper -> addLayout(layoutRightUpperFourth);

    layoutRightCenter -> setContentsMargins(0, 20, 0, 0);
    layoutRight -> addLayout(layoutRightCenter);

    layoutRightCenter -> addLayout(layoutRightCenterLeft);

    layoutRightLower -> setContentsMargins(0, 20, 0, 0);
    layoutRight -> addLayout(layoutRightLower);

    layoutLeftUpperFirst -> addWidget(labelAIModelConfiguration);

    layoutLeftUpperSecond -> addWidget(labelAIRole);
    comboboxAIRole -> setFixedWidth(150);
    layoutLeftUpperSecond -> addWidget(comboboxAIRole);

    layoutLeftUpperThird -> addWidget(labelAIModelTemperature);
    lineeditAIModelTemperature -> setFixedWidth(40);
    layoutLeftUpperThird -> addWidget(lineeditAIModelTemperature);

    layoutLeftUpperThird -> addWidget(labelTTSAudioFileName);
    lineeditTTSAudioFileBasename -> setFixedWidth(120);
    layoutLeftUpperThird -> addWidget(lineeditTTSAudioFileBasename);
    comboboxTTSAudioFileSuffix -> setFixedWidth(80);
    layoutLeftUpperThird -> addWidget(comboboxTTSAudioFileSuffix);

    layoutLeftUpperFourth -> addWidget(labelTTSAudioFileFolder);
    buttonSetTTSAudioFileFolder -> setFixedSize(60, 25);
    layoutLeftUpperFourth -> addWidget(buttonSetTTSAudioFileFolder);
    lineeditTTSAudioFileFolderPath -> setFixedWidth(200);
    lineeditTTSAudioFileFolderPath -> setReadOnly(true);
    layoutLeftUpperFourth -> addWidget(lineeditTTSAudioFileFolderPath);

    containerAIRoleDescription -> setLayout(layoutLeftCenter);
    containerAIRequirements -> setLayout(layoutLeftLower);

    layoutLeft -> addWidget(splitterAIGuidelines);

    splitterAIGuidelines -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitterAIGuidelines -> setOrientation(Qt::Vertical);

    splitterAIGuidelines -> addWidget(containerAIRoleDescription);
    splitterAIGuidelines -> addWidget(containerAIRequirements);

    splitterAIGuidelines -> setChildrenCollapsible(false);

    int heightSplitterAIGuidelines = splitterAIGuidelines -> height();
    splitterAIGuidelines -> setSizes({int(heightSplitterAIGuidelines * 0.2), int(heightSplitterAIGuidelines * 0.8)});

    layoutLeftCenter -> setContentsMargins(0, 0, 0, 0);
    layoutLeftCenter -> addWidget(labelAIRoleDescription);

    texteditAIRoleDescription -> setFont(font);
    texteditAIRoleDescription -> setAcceptRichText(false);
    layoutLeftCenter -> addWidget(texteditAIRoleDescription);

    layoutLeftLower -> setContentsMargins(0, 0, 0, 0);
    layoutLeftLower -> addWidget(labelAIRequirements);

    texteditAIRequirements -> setFont(font);
    texteditAIRequirements -> setAcceptRichText(false);
    layoutLeftLower -> addWidget(texteditAIRequirements);

    layoutRightUpperFirst -> addWidget(labelAIModels);

    layoutRightUpperSecond -> addWidget(labelAIModelCustomName);

    comboboxAIModel -> setFixedWidth(180);
    layoutRightUpperSecond -> addWidget(comboboxAIModel);

    lineeditAIModelCustomName -> setFixedWidth(180);
    layoutRightUpperSecond -> addWidget(lineeditAIModelCustomName);
    layoutRightUpperSecond -> addWidget(labelNoticeAIModelCustomName);

    layoutRightUpperThird -> addWidget(buttonModifyAIModel);
    layoutRightUpperThird -> addWidget(buttonRemoveAIModel);
    layoutRightUpperThird -> addWidget(buttonAddAIModel);
    layoutRightUpperThird -> addWidget(buttonSaveAIModel);
    layoutRightUpperThird -> addWidget(buttonCancelModifyingOrAddingAIModel);

    layoutRightUpperFourth -> addWidget(labelAIModelName);

    lineeditAIModelName -> setFixedWidth(180);
    layoutRightUpperFourth -> addWidget(lineeditAIModelName);
    layoutRightUpperFourth -> addWidget(labelNoticeAIModelName);

    layoutRightCenterLeft -> addWidget(labelAPIKeys);

    comboboxAPIKeyName -> setFixedWidth(180);
    layoutRightCenter -> addWidget(comboboxAPIKeyName);

    lineeditAPIKey -> setFixedWidth(200);
    layoutRightCenter -> addWidget(lineeditAPIKey);

    buttonSaveAPIKey -> setFixedSize(80, 25);
    layoutRightCenter -> addWidget(buttonSaveAPIKey);

    buttonModifyAPIKey -> setFixedSize(80, 25);
    layoutRightCenter -> addWidget(buttonModifyAPIKey);

    layoutRightCenter -> addWidget(labelAPIKeyStatus);

    layoutRightLower -> addWidget(labelAppVersion);

    layoutRightLower -> addWidget(labelAppNote);

    labelAppWebsite -> setText("<a href=\"https://www.aipowerplus.com\">https://www.aipowerplus.com</a>");
    labelAppWebsite -> setOpenExternalLinks(true);
    layoutRightLower -> addWidget(labelAppWebsite);

    // Signals and slots
    connect(comboboxAIRole, &QComboBox::currentIndexChanged, this, &AppSettings::whenAIRoleIsChanged);
    connect(lineeditAIModelTemperature, &QLineEdit::textChanged, this, &AppSettings::saveAIModelTemperature);
    connect(lineeditTTSAudioFileBasename, &QLineEdit::textChanged, this, &AppSettings::saveTTSAudioFilePath);
    connect(comboboxTTSAudioFileSuffix, &QComboBox::currentIndexChanged, this, &AppSettings::whenTTSAudioFileSuffixIsChanged);
    connect(buttonSetTTSAudioFileFolder, &QPushButton::clicked, this, &AppSettings::setTTSAudioFileFolder);
    connect(texteditAIRoleDescription, &QTextEdit::textChanged, this, &AppSettings::saveAIRoleDescription);
    connect(texteditAIRequirements, &QTextEdit::textChanged, this, &AppSettings::saveAIRequirements);

    connect(comboboxAIModel, &QComboBox::currentIndexChanged, this, &AppSettings::whenAIModelIsChanged);
    connect(buttonModifyAIModel, &QPushButton::clicked, this, &AppSettings::modifyAIModel);
    connect(buttonRemoveAIModel, &QPushButton::clicked, this, &AppSettings::removeAIModel);
    connect(buttonAddAIModel, &QPushButton::clicked, this, &AppSettings::addAIModel);
    connect(buttonSaveAIModel, &QPushButton::clicked, this, &AppSettings::saveAIModel);
    connect(buttonCancelModifyingOrAddingAIModel, &QPushButton::clicked, this, &AppSettings::cancelModifyingOrAddingAIModel);

    connect(comboboxAPIKeyName, &QComboBox::currentIndexChanged, this, &AppSettings::whenAPIKeyNameIsChanged);
    connect(buttonSaveAPIKey, &QPushButton::clicked, this, &AppSettings::saveAPIKey);
    connect(buttonModifyAPIKey, &QPushButton::clicked, this, &AppSettings::modifyAPIKey);

    // Initialization
    initializeParameters();
}

AppSettings::~AppSettings() {
}

void AppSettings::initializeParameters() {
    indexAIRole = 0;
    indexInterfaceLanguage = 0;
    indexAIModel = 0;
    indexAPIKeyName = 0;

    statusModifyAIModel = false;
    statusAddAIModel = false;
    statusRemoveAIModel = false;

    statusOpenAIAPIKey = false;
    statusModifyOpenAIAPIKey = false;
    statusClaudeAIAPIKey = false;
    statusModifyClaudeAIAPIKey = false;
    statusGeminiAPIKey = false;
    statusModifyGeminiAPIKey = false;

    checkAPIKeys();
    loadAIRoles();
    adjustAIModelConfigurationInterface();
    readAIGuidelines(aiRole);
    loadTTSAudioSettings();
    loadAIModels();
    loadAPIKeyNames();
    adjustLayoutAPIKeys();
    setLang();
}

std::tuple<bool, bool, bool> AppSettings::checkAPIKeys() {
    QString openAIAPIKey = appConfiguration.readConfig("openai_api_key");
    if (openAIAPIKey.isEmpty()) {
        statusOpenAIAPIKey = false;
    } else {
        statusOpenAIAPIKey = true;
    }

    QString claudeAIAPIKey = appConfiguration.readConfig("claude_ai_api_key");
    if (claudeAIAPIKey.isEmpty()) {
        statusClaudeAIAPIKey = false;
    }
    else {
        statusClaudeAIAPIKey = true;
    }

    QString geminiAPIKey = appConfiguration.readConfig("gemini_api_key");
    if (geminiAPIKey.isEmpty()) {
        statusGeminiAPIKey = false;
    }
    else {
        statusGeminiAPIKey = true;
    }

    return std::make_tuple(statusOpenAIAPIKey, statusClaudeAIAPIKey, statusGeminiAPIKey);
}

void AppSettings::loadAIRoles() {
    QList<QString> listComboboxItemsAIRole = appLang.readComboboxItemsAIRole(indexInterfaceLanguage);

    comboboxAIRole -> clear();
    statusInitializationComboboxAIRole = true;
    comboboxAIRole -> addItems(listComboboxItemsAIRole);
    comboboxAIRole -> setCurrentIndex(indexAIRole);

    aiRole = appLang.readAIRole(indexAIRole);
}

void AppSettings::adjustAIModelConfigurationInterface() {
    if (aiRole != "speaker") {
        labelAIModelTemperature -> setVisible(true);
        lineeditAIModelTemperature -> setVisible(true);

        labelTTSAudioFileName -> setVisible(false);
        lineeditTTSAudioFileBasename -> setVisible(false);
        comboboxTTSAudioFileSuffix -> setVisible(false);
        labelTTSAudioFileFolder -> setVisible(false);
        buttonSetTTSAudioFileFolder -> setVisible(false);
        lineeditTTSAudioFileFolderPath -> setVisible(false);

        splitterAIGuidelines -> setVisible(true);
    } else {
        labelAIModelTemperature -> setVisible(false);
        lineeditAIModelTemperature -> setVisible(false);

        labelTTSAudioFileName -> setVisible(true);
        lineeditTTSAudioFileBasename -> setVisible(true);
        comboboxTTSAudioFileSuffix -> setVisible(true);
        labelTTSAudioFileFolder -> setVisible(true);
        buttonSetTTSAudioFileFolder -> setVisible(true);
        lineeditTTSAudioFileFolderPath -> setVisible(true);

        splitterAIGuidelines -> setVisible(false);
    }
}

void AppSettings::readAIGuidelines(const QString &aiRole) {
    std::pair<QString, QString> aiGuidelines = appConfiguration.readAIGuidelines(aiRole);
    QString aiRoleDescription = aiGuidelines.first;
    QString aiRequirements = aiGuidelines.second;

    QString aiModelTemperature = appConfiguration.readAIRoleConfig(aiRole, "ai_model_temperature");

    if (aiModelTemperature.isEmpty()) {
        lineeditAIModelTemperature -> setText("0.0");
    } else {
        lineeditAIModelTemperature -> setText(aiModelTemperature);
    }

    texteditAIRoleDescription -> setText(aiRoleDescription);
    texteditAIRequirements -> setText(aiRequirements);
}

void AppSettings::loadTTSAudioSettings() {
    std::pair<QString, QString> pairTTSAudioFilePath = appConfiguration.readTTSAudioFilePath();
    QString pathTTSAudioFile = pairTTSAudioFilePath.first;
    QFileInfo file(pathTTSAudioFile);
    QString pathTTSAudioFileFolder = file.absolutePath();
    QString ttsAudioFileBasename = file.baseName();
    QString ttsAudioFileType = file.suffix();

    lineeditTTSAudioFileBasename -> setText(ttsAudioFileBasename);

    QList<QString> listTTSAudioFileSuffix = appLang.listTTSAudioFileSuffix;
    indexTTSAudioFileSuffix = listTTSAudioFileSuffix.indexOf("." + ttsAudioFileType);
    comboboxTTSAudioFileSuffix -> clear();
    statusInitializationComboboxTTSAudioFileSuffix = true;
    comboboxTTSAudioFileSuffix -> addItems(listTTSAudioFileSuffix);
    comboboxTTSAudioFileSuffix -> setCurrentIndex(indexTTSAudioFileSuffix);

    lineeditTTSAudioFileFolderPath -> setText(pathTTSAudioFileFolder);
}

void AppSettings::loadAIModels() {
    std::pair<QStringList, QStringList> pairAIModels = appConfiguration.readAIModels();
    QStringList listAIModelCustomNames = pairAIModels.first;
    QStringList listAIModelNames = pairAIModels.second;

    comboboxAIModel -> clear();
    statusInitializationComboboxAIModel = true;
    comboboxAIModel -> addItems(listAIModelCustomNames);

    if (statusModifyAIModel) {
        indexAIModel = indexModifyAIModel;
        statusModifyAIModel = false;
    }

    if (statusAddAIModel) {
        indexAIModel = indexAddAIModel;
        statusAddAIModel = false;
    }

    if (statusRemoveAIModel) {
        indexAIModel = indexRemoveAIModel - 1;
        statusRemoveAIModel = false;
    }

    comboboxAIModel -> setCurrentIndex(indexAIModel);

    if (!listAIModelCustomNames.isEmpty() && !listAIModelNames.isEmpty()) {
        lineeditAIModelCustomName -> setText(listAIModelCustomNames.at(indexAIModel));
        lineeditAIModelName -> setText(listAIModelNames.at(indexAIModel));

        comboboxAIModel -> setVisible(true);

        labelAIModelCustomName -> setVisible(false);
        lineeditAIModelCustomName -> setVisible(false);

        labelAIModelName -> setVisible(true);
        lineeditAIModelName -> setVisible(true);
        lineeditAIModelName -> setReadOnly(true);

        buttonModifyAIModel -> setVisible(true);
        buttonRemoveAIModel -> setVisible(true);
        buttonAddAIModel -> setVisible(true);
        buttonSaveAIModel -> setVisible(false);
        buttonCancelModifyingOrAddingAIModel -> setVisible(false);
    } else {
        comboboxAIModel -> setVisible(true);

        labelAIModelCustomName -> setVisible(false);
        lineeditAIModelCustomName -> setVisible(false);

        labelAIModelName -> setVisible(false);
        lineeditAIModelName -> setVisible(false);

        buttonModifyAIModel -> setVisible(false);
        buttonRemoveAIModel -> setVisible(false);
        buttonAddAIModel -> setVisible(true);
        buttonSaveAIModel -> setVisible(false);
        buttonCancelModifyingOrAddingAIModel -> setVisible(false);
    }

    emit signalReloadAIModels();
}

void AppSettings::loadAPIKeyNames() {
    QList<QString> listComboboxItemsAPIKeyName = appLang.readComboboxItemsAPIKeyName(indexInterfaceLanguage);
    comboboxAPIKeyName -> clear();
    statusInitializationComboboxAPIKeyName = true;
    comboboxAPIKeyName -> addItems(listComboboxItemsAPIKeyName);
    comboboxAPIKeyName -> setCurrentIndex(indexAPIKeyName);
}

void AppSettings::adjustLayoutAPIKeys() {
    apiKeyName = appLang.readAPIKeyName(indexAPIKeyName);

    if (apiKeyName == "openai_api_key") {
        if (statusOpenAIAPIKey) {
            lineeditAPIKey -> setVisible(false);
            buttonSaveAPIKey -> setVisible(false);
            buttonModifyAPIKey -> setVisible(true);
        } else {
            lineeditAPIKey -> setVisible(true);
            buttonSaveAPIKey -> setVisible(true);
            buttonModifyAPIKey -> setVisible(false);
        }
    }

    if (apiKeyName == "claude_ai_api_key") {
        if (statusClaudeAIAPIKey) {
            lineeditAPIKey -> setVisible(false);
            buttonSaveAPIKey -> setVisible(false);
            buttonModifyAPIKey -> setVisible(true);
        } else {
            lineeditAPIKey -> setVisible(true);
            buttonSaveAPIKey -> setVisible(true);
            buttonModifyAPIKey -> setVisible(false);
        }
    }

    if (apiKeyName == "gemini_api_key") {
        if (statusGeminiAPIKey) {
            lineeditAPIKey -> setVisible(false);
            buttonSaveAPIKey -> setVisible(false);
            buttonModifyAPIKey -> setVisible(true);
        } else {
            lineeditAPIKey -> setVisible(true);
            buttonSaveAPIKey -> setVisible(true);
            buttonModifyAPIKey -> setVisible(false);
        }
    }
}

void AppSettings::changeInterfaceLanguage(const int &index) {
    indexInterfaceLanguage = index;
    setLang();
}

void AppSettings::changeAIRole(const int &index) {
    indexAIRole = index;

    comboboxAIRole -> setCurrentIndex(indexAIRole);
    whenAIRoleIsChanged(indexAIRole);
}

void AppSettings::whenAIRoleIsChanged(const int &index) {
    if (!statusInitializationComboboxAIRole && index != -1) {
        indexAIRole = index;
        aiRole = appLang.readAIRole(indexAIRole);

        adjustAIModelConfigurationInterface();
        if (aiRole != "speaker") {
            readAIGuidelines(aiRole);
        } else {
            loadTTSAudioSettings();
        }
    }

    if (statusInitializationComboboxAIRole) {
        statusInitializationComboboxAIRole = false;
    }
}

void AppSettings::whenTTSAudioFileSuffixIsChanged(const int &index) {
    if (!statusInitializationComboboxTTSAudioFileSuffix && index != -1) {
        saveTTSAudioFilePath();
    }

    if (statusInitializationComboboxTTSAudioFileSuffix) {
        statusInitializationComboboxTTSAudioFileSuffix = false;
    }
}

void AppSettings::setLang() {
    if (indexInterfaceLanguage == 0) {
        labelAIRole -> setFixedWidth(45);
        labelAIModelTemperature -> setFixedWidth(80);
        labelTTSAudioFileName -> setFixedWidth(120);
        labelTTSAudioFileFolder -> setFixedWidth(120);
        labelAIModelCustomName -> setFixedWidth(135);
        labelAIModelName -> setFixedWidth(90);
    }

    if (indexInterfaceLanguage == 1) {
        labelAIRole -> setFixedWidth(45);
        labelAIModelTemperature -> setFixedWidth(80);
        labelTTSAudioFileName -> setFixedWidth(140);
        labelTTSAudioFileFolder -> setFixedWidth(120);
        labelAIModelCustomName -> setFixedWidth(195);
        labelAIModelName -> setFixedWidth(100);
    }

    if (indexInterfaceLanguage == 2) {
        labelAIRole -> setFixedWidth(45);
        labelAIModelTemperature -> setFixedWidth(35);
        labelTTSAudioFileName -> setFixedWidth(120);
        labelTTSAudioFileFolder -> setFixedWidth(120);
        labelAIModelCustomName -> setFixedWidth(95);
        labelAIModelName -> setFixedWidth(60);
    }

    this -> setWindowTitle(appLang.readLangEntry(indexInterfaceLanguage, "settings"));

    labelAIModelConfiguration -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_model_configuration"));

    labelAIRole -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_role"));

    loadAIRoles();

    labelAIModelTemperature -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_model_temperature"));

    labelTTSAudioFileName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "tts_audio_file_name"));
    labelTTSAudioFileFolder -> setText(appLang.readLangEntry(indexInterfaceLanguage, "folder_to_save_file"));
    buttonSetTTSAudioFileFolder -> setText(appLang.readLangEntry(indexInterfaceLanguage, "set"));

    labelAIRoleDescription -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_role_description"));
    labelAIRequirements -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_requirements"));

    labelAIModels -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_models"));
    labelAIModelCustomName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_model_custom_name"));
    labelAIModelName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_model_name"));

    buttonModifyAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "modify"));
    buttonRemoveAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "remove"));
    buttonAddAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "add"));
    buttonSaveAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "save"));
    buttonCancelModifyingOrAddingAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "cancel"));

    labelAPIKeys -> setText(appLang.readLangEntry(indexInterfaceLanguage, "api_keys"));

    loadAPIKeyNames();

    buttonSaveAPIKey -> setText(appLang.readLangEntry(indexInterfaceLanguage, "save"));
    buttonModifyAPIKey -> setText(appLang.readLangEntry(indexInterfaceLanguage, "modify"));

    labelAppVersion -> setText("AI Power Plus 1.1\n");
    labelAppNote -> setText(appLang.readLangEntry(indexInterfaceLanguage, "software_note"));

    setLangAPIKeys();
}

void AppSettings::setLangAPIKeys() {
    apiKeyName = appLang.readAPIKeyName(indexAPIKeyName);

    if (apiKeyName == "openai_api_key") {
        if (!statusOpenAIAPIKey) {
            labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "openai_api_key_is_not_found"));
        } else {
            if (!statusModifyOpenAIAPIKey) {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "openai_api_key_is_saved"));
            } else {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "input_new_openai_api_key"));
            }
        }
    }

    if (apiKeyName == "claude_ai_api_key") {
        if (!statusClaudeAIAPIKey) {
            labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "claudeai_api_key_is_not_found"));
        } else {
            if (!statusModifyClaudeAIAPIKey) {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "claudeai_api_key_is_saved"));
            } else {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "input_new_claudeai_api_key"));
            }
        }
    }

    if (apiKeyName == "gemini_api_key") {
        if (!statusGeminiAPIKey) {
            labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "gemini_api_key_is_not_found"));
        } else {
            if (!statusModifyGeminiAPIKey) {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "gemini_api_key_is_saved"));
            } else {
                labelAPIKeyStatus -> setText(appLang.readLangEntry(indexInterfaceLanguage, "input_new_gemini_api_key"));
            }
        }
    }
}

void AppSettings::saveAIModelTemperature() {
    QString aiModelTemperature = lineeditAIModelTemperature -> text();
    appConfiguration.saveAIRoleConfig(aiRole, "ai_model_temperature", aiModelTemperature);
}

void AppSettings::saveAIRoleDescription() {
    QString aiRoleDescription = texteditAIRoleDescription -> toPlainText();
    appConfiguration.saveAIGuidelines(aiRole, "role_description", aiRoleDescription);
}

void AppSettings::saveAIRequirements() {
    QString aiRequirements = texteditAIRequirements -> toPlainText();
    appConfiguration.saveAIGuidelines(aiRole, "requirements", aiRequirements);
}

void AppSettings::setTTSAudioFileFolder() {
    const char *stringSetFolder;
    stringSetFolder = appLang.readLangEntry(indexInterfaceLanguage, "set_folder").toUtf8().constData();

    QString defaultFilePath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString pathTTSAudioFolder = QFileDialog::getExistingDirectory(this,
                                                                 tr(stringSetFolder),
                                                                 defaultFilePath,
                                                                 QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!pathTTSAudioFolder.isEmpty()) {
        lineeditTTSAudioFileFolderPath -> setText(pathTTSAudioFolder);
        saveTTSAudioFilePath();
    }
}

void AppSettings::saveTTSAudioFilePath() {
    int indexTTSAudioFileSuffix = comboboxTTSAudioFileSuffix -> currentIndex();

    if (!statusInitializationComboboxTTSAudioFileSuffix && indexTTSAudioFileSuffix != -1) {
        QString ttsAudioFileBasename = lineeditTTSAudioFileBasename -> text();
        QString ttsAudioFileSuffix = comboboxTTSAudioFileSuffix -> currentText();
        QString pathTTSAudioFileFolder = lineeditTTSAudioFileFolderPath -> text();

        if (!ttsAudioFileBasename.isEmpty() && !ttsAudioFileSuffix.isEmpty() && !pathTTSAudioFileFolder.isEmpty()) {
            QString ttsAudioFileName = ttsAudioFileBasename + ttsAudioFileSuffix;
            QDir dir(pathTTSAudioFileFolder);
            QString pathTTSAudioFile = dir.filePath(ttsAudioFileName);

            appConfiguration.saveConfig("tts_audio_file_path", pathTTSAudioFile);
        }
    }
}

void AppSettings::whenAIModelIsChanged(const int &index) {
    if (!statusInitializationComboboxAIModel && index != -1) {
        std::pair<QStringList, QStringList> pairAIModels = appConfiguration.readAIModels();
        QStringList listAIModelCustomNames = pairAIModels.first;
        QStringList listAIModelNames = pairAIModels.second;

        indexAIModel = index;

        lineeditAIModelCustomName -> setText(listAIModelCustomNames.at(indexAIModel));
        lineeditAIModelName -> setText(listAIModelNames.at(indexAIModel));
    }

    if (statusInitializationComboboxAIModel) {
        statusInitializationComboboxAIModel = false;
    }
}

void AppSettings::modifyAIModel() {
    statusModifyAIModel = true;
    indexModifyAIModel = comboboxAIModel -> currentIndex();

    comboboxAIModel -> setVisible(false);

    labelAIModelCustomName -> setVisible(true);
    lineeditAIModelCustomName -> setVisible(true);

    lineeditAIModelName -> setReadOnly(false);

    buttonModifyAIModel -> setVisible(false);
    buttonRemoveAIModel -> setVisible(false);
    buttonAddAIModel -> setVisible(false);

    buttonSaveAIModel -> setVisible(true);
    buttonCancelModifyingOrAddingAIModel -> setVisible(true);
}

void AppSettings::removeAIModel() {
    statusRemoveAIModel = true;
    indexRemoveAIModel = comboboxAIModel -> currentIndex();

    appConfiguration.removeAIModel(indexRemoveAIModel);

    loadAIModels();
}

void AppSettings::addAIModel() {
    statusAddAIModel = true;
    indexAddAIModel = comboboxAIModel -> count();

    lineeditAIModelCustomName -> clear();
    lineeditAIModelName -> clear();

    comboboxAIModel -> setVisible(false);
    labelAIModelCustomName -> setVisible(true);

    lineeditAIModelCustomName -> setVisible(true);

    labelAIModelName -> setVisible(true);
    lineeditAIModelName -> setVisible(true);
    lineeditAIModelName -> setReadOnly(false);

    buttonModifyAIModel -> setVisible(false);
    buttonRemoveAIModel -> setVisible(false);
    buttonAddAIModel -> setVisible(false);
    buttonSaveAIModel -> setVisible(true);
    buttonCancelModifyingOrAddingAIModel -> setVisible(true);
}

void AppSettings::saveAIModel() {
    std::pair<QStringList, QStringList> pairAIModels = appConfiguration.readAIModels();
    QStringList listAIModelCustomNames = pairAIModels.first;
    QStringList listAIModelNames = pairAIModels.second;

    QString aiModelCustomName = lineeditAIModelCustomName -> text();
    QString aiModelName = lineeditAIModelName -> text();

    QStringList listAIModelCustomNamesExcept = listAIModelCustomNames;
    if (!listAIModelCustomNamesExcept.isEmpty()) {
        listAIModelCustomNamesExcept.remove(indexAIModel);
    }

    QStringList listAIModelNamesExcept = listAIModelNames;
    if (!listAIModelNamesExcept.isEmpty()) {
        listAIModelNamesExcept.remove(indexAIModel);
    }

    if (statusAddAIModel) {
        if (listAIModelCustomNames.contains(aiModelCustomName)) {
            labelNoticeAIModelCustomName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "name_exists"));
        } else if (listAIModelNames.contains(aiModelName)) {
            labelNoticeAIModelName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "name_exists"));
        } else {
            appConfiguration.addAIModel(aiModelCustomName, aiModelName);

            lineeditAIModelCustomName -> clear();
            lineeditAIModelName -> clear();

            labelNoticeAIModelCustomName -> clear();
            labelNoticeAIModelName -> clear();

            loadAIModels();
        }
    }

    if (statusModifyAIModel) {
        if (listAIModelCustomNamesExcept.contains(aiModelCustomName)) {
            labelNoticeAIModelCustomName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "name_exists"));
        } else if (listAIModelNamesExcept.contains(aiModelName)) {
            labelNoticeAIModelName -> setText(appLang.readLangEntry(indexInterfaceLanguage, "name_exists"));
        } else {
            appConfiguration.modifyAIModel(indexModifyAIModel, aiModelCustomName, aiModelName);

            lineeditAIModelCustomName -> clear();
            lineeditAIModelName -> clear();

            labelNoticeAIModelCustomName -> clear();
            labelNoticeAIModelName -> clear();

            loadAIModels();
        }
    }
}

void AppSettings::cancelModifyingOrAddingAIModel() {
    statusModifyAIModel = false;
    statusAddAIModel = false;

    loadAIModels();
}

void AppSettings::whenAPIKeyNameIsChanged(const int &index) {
    if (!statusInitializationComboboxAPIKeyName && index != -1) {
        indexAPIKeyName = index;
        apiKeyName = appLang.readAPIKeyName(indexAPIKeyName);

        if (statusModifyOpenAIAPIKey) {
            statusModifyOpenAIAPIKey = false;
        }

        if (statusModifyClaudeAIAPIKey) {
            statusModifyClaudeAIAPIKey = false;
        }

        if (statusModifyGeminiAPIKey) {
            statusModifyGeminiAPIKey = false;
        }

        adjustLayoutAPIKeys();
        setLangAPIKeys();
    }

    if (statusInitializationComboboxAPIKeyName) {
        statusInitializationComboboxAPIKeyName = false;
    }
}

void AppSettings::saveAPIKey() {
    QString apiKey = lineeditAPIKey -> text();
    appConfiguration.saveConfig(apiKeyName, apiKey);

    lineeditAPIKey -> clear();

    checkAPIKeys();
    adjustLayoutAPIKeys();
    setLangAPIKeys();

    emit signalReloadAIModels();
}

void AppSettings::modifyAPIKey() {
    apiKeyName = appLang.readAPIKeyName(indexAPIKeyName);

    if (apiKeyName == "openai_api_key") {
        statusModifyOpenAIAPIKey = true;

        statusModifyClaudeAIAPIKey = false;
        statusModifyGeminiAPIKey = false;
    }

    if (apiKeyName == "claude_ai_api_key") {
        statusModifyClaudeAIAPIKey = true;

        statusModifyOpenAIAPIKey = false;
        statusModifyGeminiAPIKey = false;
    }

    if (apiKeyName == "gemini_api_key") {
        statusModifyGeminiAPIKey = true;

        statusModifyOpenAIAPIKey = false;
        statusModifyClaudeAIAPIKey = false;
    }

    lineeditAPIKey -> setVisible(true);
    buttonSaveAPIKey -> setVisible(true);
    buttonModifyAPIKey -> setVisible(false);

    setLangAPIKeys();
}
