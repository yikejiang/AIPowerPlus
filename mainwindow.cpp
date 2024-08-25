#include "mainwindow.h"

#include <tuple>
#include <utility>

#include <Qt>
#include <QSizePolicy>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QIcon>
#include <QFile>

#include "appcommunication.h"
#include "appmultimedia.h"
#include "appcommands.h"

MainWindow::MainWindow() : QMainWindow() {
    QRect screenGeometry = QGuiApplication::primaryScreen() -> geometry();
    appXStart = (screenGeometry.width() - 1280) / 2;
    appYStart = (screenGeometry.height() - 960) / 2;

    this -> setGeometry(appXStart, appYStart, 1280, 960);

    this -> setWindowIcon(QIcon(":/resources/logo.ico"));

    font.setPointSize(11);

    this -> setCentralWidget(centralWidget);

    appLayout -> setAlignment(Qt::AlignTop);
    centralWidget -> setLayout(appLayout);

    layoutTopRight -> setAlignment(Qt::AlignRight);
    layoutTop -> addLayout(layoutTopRight);
    containerTop -> setLayout(layoutTop);
    appLayout -> addWidget(containerTop);

    splitterMain -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitterMain -> setOrientation(Qt::Horizontal);
    appLayout -> addWidget(splitterMain);

    splitterLeft -> setOrientation(Qt::Vertical);
    splitterRight -> setOrientation(Qt::Vertical);

    splitterMain -> addWidget(splitterLeft);
    splitterMain -> addWidget(splitterRight);

    containerMainLeftUpper -> setLayout(layoutMainLeftUpper);
    containerMainLeftLower -> setLayout(layoutMainLeftLower);

    splitterLeft -> addWidget(containerMainLeftUpper);
    splitterLeft -> addWidget(containerMainLeftLower);

    containerMainRightUpper -> setLayout(layoutMainRightUpper);

    containerMainRightLower -> setLayout(layoutMainRightLower);

    splitterRight -> addWidget(containerMainRightUpper);
    splitterRight -> addWidget(containerMainRightLower);

    layoutMainLeftUpper -> addLayout(layoutMainLeftUpperTop);

    layoutMainLeftUpperTopLeft -> setAlignment(Qt::AlignLeft);
    layoutMainLeftUpperTop -> addLayout(layoutMainLeftUpperTopLeft);

    layoutMainLeftUpperTopRight -> setAlignment(Qt::AlignRight);
    layoutMainLeftUpperTop -> addLayout(layoutMainLeftUpperTopRight);

    layoutMainRightUpper -> addLayout(layoutMainRightUpperTop);

    layoutMainRightUpperTopLeft -> setAlignment(Qt::AlignLeft);
    layoutMainRightUpperTop -> addLayout(layoutMainRightUpperTopLeft);

    layoutMainRightUpperTopRight -> setAlignment(Qt::AlignRight);
    layoutMainRightUpperTop -> addLayout(layoutMainRightUpperTopRight);

    layoutMainRightLower -> addLayout(layoutMainRightLowerTop);

    layoutMainRightLowerTopLeft -> setAlignment(Qt::AlignLeft);
    layoutMainRightLowerTop -> addLayout(layoutMainRightLowerTopLeft);

    layoutMainRightLowerTopRight -> setAlignment(Qt::AlignRight);
    layoutMainRightLowerTop -> addLayout(layoutMainRightLowerTopRight);

    labelAIRole -> setFixedHeight(30);
    layoutTopRight -> addWidget(labelAIRole);

    comboboxAIRole -> setFixedWidth(150);
    layoutTopRight -> addWidget(comboboxAIRole);

    layoutTopRight -> addWidget(labelInterfaceLanguage);

    comboboxInterfaceLanguage -> setFixedWidth(90);
    layoutTopRight -> addWidget(comboboxInterfaceLanguage);

    layoutTopRight -> addWidget(labelAIModel);

    comboboxAIModel -> setFixedWidth(180);
    layoutTopRight -> addWidget(comboboxAIModel);

    buttonSettings -> setFixedWidth(90);
    layoutTopRight -> addWidget(buttonSettings);

    labelUserText -> setFixedHeight(30);
    layoutMainLeftUpperTopLeft -> addWidget(labelUserText);

    labelBlackboard -> setFixedHeight(30);
    layoutMainLeftUpperTopLeft -> addWidget(labelBlackboard);

    layoutMainLeftUpperTopRight -> addWidget(labelTTSVoice);

    comboboxTTSVoice -> setFixedWidth(90);
    layoutMainLeftUpperTopRight -> addWidget(comboboxTTSVoice);

    buttonProcessTTS -> setFixedWidth(90);
    layoutMainLeftUpperTopRight -> addWidget(buttonProcessTTS);

    buttonPlayAudio -> setFixedWidth(90);
    layoutMainLeftUpperTopRight -> addWidget(buttonPlayAudio);

    layoutMainLeftUpperTopRight -> addWidget(labelTranslationLanguage);

    comboboxTranslationLanguage -> setFixedWidth(90);
    layoutMainLeftUpperTopRight -> addWidget(comboboxTranslationLanguage);

    texteditUserText -> setAcceptRichText(false);
    texteditUserText -> setFont(font);
    layoutMainLeftUpper -> addWidget(texteditUserText);

    texteditBlackboard -> setAcceptRichText(false);
    texteditBlackboard -> setFont(font);
    layoutMainLeftUpper -> addWidget(texteditBlackboard);

    labelAIText -> setFixedHeight(30);
    layoutMainLeftLower -> addWidget(labelAIText);

    labelTeacherExplanation -> setFixedHeight(30);
    layoutMainLeftLower -> addWidget(labelTeacherExplanation);

    texteditAIText -> setAcceptRichText(false);
    texteditAIText -> setFont(font);
    layoutMainLeftLower -> addWidget(texteditAIText);

    texteditTeacherExplanation -> setAcceptRichText(false);
    texteditTeacherExplanation -> setFont(font);
    layoutMainLeftLower -> addWidget(texteditTeacherExplanation);

    labelUserMessage -> setFixedHeight(30);
    layoutMainRightUpperTopLeft -> addWidget(labelUserMessage);

    layoutMainRightUpperTopRight -> addWidget(labelChatContext);

    checkboxChatContext -> setChecked(false);
    layoutMainRightUpperTopRight -> addWidget(checkboxChatContext);

    buttonSubmit -> setFixedWidth(90);
    layoutMainRightUpperTopRight -> addWidget(buttonSubmit);

    texteditUserMessage -> setAcceptRichText(false);
    texteditUserMessage -> setFont(font);
    layoutMainRightUpper -> addWidget(texteditUserMessage);

    labelAIExplanation -> setFixedHeight(30);
    layoutMainRightLowerTopLeft -> addWidget(labelAIExplanation);

    labelChatHistory -> setFixedHeight(30);
    layoutMainRightLowerTopLeft -> addWidget(labelChatHistory);

    buttonExplanationOrHistory -> setFixedWidth(120);
    layoutMainRightLowerTopLeft -> addWidget(buttonExplanationOrHistory);

    buttonClearChatHistory -> setFixedWidth(100);
    layoutMainRightLowerTopRight -> addWidget(buttonClearChatHistory);

    texteditAIExplanation -> setFont(font);
    texteditAIExplanation -> setReadOnly(true);
    layoutMainRightLower -> addWidget(texteditAIExplanation);

    texteditChatHistory -> setReadOnly(true);
    texteditChatHistory -> setFont(font);
    layoutMainRightLower -> addWidget(texteditChatHistory);

    // Signals and slots
    connect(comboboxAIRole, &QComboBox::currentIndexChanged, this, &MainWindow::changeAIRole);
    connect(comboboxInterfaceLanguage, &QComboBox::currentIndexChanged, this, &MainWindow::changeInterfaceLanguage);
    connect(comboboxAIModel, &QComboBox::currentIndexChanged, this, &MainWindow::changeAIModel);
    connect(buttonSettings, &QPushButton::clicked, this, &MainWindow::showSettings);
    connect(comboboxTranslationLanguage, &QComboBox::currentIndexChanged, this, &MainWindow::changeTranslationLanguage);
    connect(comboboxTTSVoice, &QComboBox::currentIndexChanged, this, &MainWindow::changeTTSVoice);
    connect(buttonProcessTTS, &QPushButton::clicked, this, &MainWindow::processTTS);
    connect(buttonPlayAudio, &QPushButton::clicked, this, &MainWindow::playAudio);
    connect(texteditUserText, &QTextEdit::textChanged, this, &MainWindow::whenUserTextIsChanged);
    connect(checkboxChatContext, &QCheckBox::checkStateChanged, this, &MainWindow::setChatContextOption);
    connect(buttonSubmit, &QPushButton::clicked, this, &MainWindow::submitRequest);
    connect(texteditUserMessage, &QTextEdit::textChanged, this, &MainWindow::whenUserMessageIsChanged);
    connect(buttonExplanationOrHistory, &QPushButton::clicked, this, &MainWindow::showExplanationOrHistory);
    connect(buttonClearChatHistory, &QPushButton::clicked, this, &MainWindow::clearChatHistory);

    connect(this, &MainWindow::signalChangeAIRole, &appSettings, &AppSettings::changeAIRole);
    connect(this, &MainWindow::signalChangeInterfaceLanguage, &appSettings, &AppSettings::changeInterfaceLanguage);

    connect(&appSettings, &AppSettings::signalReloadAIModels, this, &MainWindow::loadAIModels);

    // Initialization
    initializeParameters();
}

MainWindow::~MainWindow() {
}

void MainWindow::initializeParameters() {
    // The command refreshes the size of centralWidget and splitterMain.
    this -> show();

    statusPlayAgain = false;
    statusAIExplanation = true;

    loadInterfaceLanguages();
    loadAIRoles();
    loadAIModels();
    loadTTSVoices();
    loadTranslationLanguages();

    setLang();
}

void MainWindow::loadInterfaceLanguages() {
    bool statusInt;

    QList<QString> listInterfaceLanguage = appLang.listInterfaceLanguage;
    indexInterfaceLanguage = QString(appConfiguration.readConfig("interface_language_index")).toInt(&statusInt);

    if (statusInt) {
        if (indexInterfaceLanguage >= listInterfaceLanguage.length() || indexInterfaceLanguage < 0) {
            indexInterfaceLanguage = 0;
        }
    } else {
        indexInterfaceLanguage = 0;
    }

    if (!listInterfaceLanguage.isEmpty()) {
        interfaceLanguage = listInterfaceLanguage.at(indexInterfaceLanguage);
    }

    comboboxInterfaceLanguage -> clear();
    statusInitializationComboboxInterfaceLanguage = true;
    comboboxInterfaceLanguage -> addItems(listInterfaceLanguage);
    comboboxInterfaceLanguage -> setCurrentIndex(indexInterfaceLanguage);
}

void MainWindow::loadAIRoles() {
    bool statusInt;

    QList<QString> listComboboxItemsAIRole = appLang.readComboboxItemsAIRole(indexInterfaceLanguage);
    indexAIRole = QString(appConfiguration.readConfig("ai_role_index")).toInt(&statusInt);

    if (statusInt) {
        if (indexAIRole >= listComboboxItemsAIRole.length() || indexAIRole < 0) {
            indexAIRole = 0;
        }
    } else {
        indexAIRole = 0;
    }

    aiRole = appLang.readAIRole(indexAIRole);

    comboboxAIRole -> clear();
    statusInitializationComboboxAIRole = true;
    comboboxAIRole -> addItems(listComboboxItemsAIRole);
    comboboxAIRole -> setCurrentIndex(indexAIRole);
}

void MainWindow::loadAIModels() {
    std::tuple<bool, bool, bool> statusAPIKeys = appSettings.checkAPIKeys();
    bool statusOpenAIAPIKey = std::get<0>(statusAPIKeys);
    bool statusClaudeAIAPIKey = std::get<1>(statusAPIKeys);
    bool statusGeminiAPIKey = std::get<2>(statusAPIKeys);

    std::pair<QStringList, QStringList> pairAIModels = appConfiguration.readAIModels();
    QStringList listAIModelCustomNames = pairAIModels.first;
    QStringList listAIModelNames = pairAIModels.second;

    QStringList listAvailableAIModelCustomNames;
    QStringList listAvailableAIModelNames;

    if (!listAIModelNames.isEmpty()) {
        for (const QString &item : listAIModelNames) {
            if (statusOpenAIAPIKey) {
                if (item.contains("gpt")) {
                    listAvailableAIModelNames.append(item);
                    int indexItem = listAIModelNames.indexOf(item);
                    listAvailableAIModelCustomNames.append(listAIModelCustomNames.at(indexItem));
                }
            }

            if (statusClaudeAIAPIKey) {
                if (item.contains("claude")) {
                    listAvailableAIModelNames.append(item);
                    int indexItem = listAIModelNames.indexOf(item);
                    listAvailableAIModelCustomNames.append(listAIModelCustomNames.at(indexItem));
                }
            }

            if (statusGeminiAPIKey) {
                if (item.contains("gemini")) {
                    listAvailableAIModelNames.append(item);
                    int indexItem = listAIModelNames.indexOf(item);
                    listAvailableAIModelCustomNames.append(listAIModelCustomNames.at(indexItem));
                }
            }
        }
    }

    bool statusInt;
    indexAIModel = QString(appConfiguration.readConfig("ai_model_index")).toInt(&statusInt);

    if (statusInt) {
        if (indexAIModel >= listAvailableAIModelNames.length() || indexAIModel < 0) {
            indexAIModel = 0;
        }
    } else {
        indexAIModel = 0;
    }

    if (!listAvailableAIModelNames.isEmpty()) {
        aiModel = listAvailableAIModelNames.at(indexAIModel);
    }

    comboboxAIModel -> clear();
    statusInitializationComboboxAIModel = true;
    comboboxAIModel -> addItems(listAvailableAIModelCustomNames);
    comboboxAIModel -> setCurrentIndex(indexAIModel);

    adjustAIRoleInterface();
}

void MainWindow::loadTTSVoices() {
    bool statusInt;

    QList<QString> listItemsTTSVoice = appLang.readComboboxItemsTTSVoice();
    indexTTSVoice = QString(appConfiguration.readConfig("tts_voice_index")).toInt(&statusInt);
    if (statusInt) {
        if (indexTTSVoice >= listItemsTTSVoice.length() || indexTTSVoice < 0) {
            indexTTSVoice = 0;
        }
    } else {
        indexTTSVoice = 0;
    }

    ttsVoice = appLang.readTTSVoice(indexTTSVoice);

    comboboxTTSVoice -> clear();
    statusInitializationComboboxTTSVoice = true;
    comboboxTTSVoice -> addItems(listItemsTTSVoice);
    comboboxTTSVoice -> setCurrentIndex(indexTTSVoice);
}

void MainWindow::loadTranslationLanguages() {
    bool statusInt;

    QList<QString> listTranslationLanguage = appLang.listTranslationLanguage;
    indexTranslationLanguage = QString(appConfiguration.readConfig("translation_language_index")).toInt(&statusInt);
    if (statusInt) {
        if (indexTranslationLanguage >= listTranslationLanguage.length() || indexTranslationLanguage < 0) {
            indexTranslationLanguage = 0;
        }
    } else {
        indexTranslationLanguage = 0;
    }

    if (!listTranslationLanguage.isEmpty()) {
        translationLanguage = listTranslationLanguage.at(indexTranslationLanguage);
    }

    comboboxTranslationLanguage -> clear();
    statusInitializationComboboxTranslationLanguage = true;
    comboboxTranslationLanguage -> addItems(listTranslationLanguage);
    comboboxTranslationLanguage -> setCurrentIndex(indexTranslationLanguage);
}

void MainWindow::changeAIRole(const int &index) {
    if (!statusInitializationComboboxAIRole && index != -1) {
        indexAIRole = index;
        appConfiguration.saveConfig("ai_role_index", QString::number(indexAIRole));
        aiRole = appLang.readAIRole(indexAIRole);
        emit signalChangeAIRole(indexAIRole);
        adjustAIRoleInterface();
    }

    if (statusInitializationComboboxAIRole) {
        statusInitializationComboboxAIRole = false;
    }
}

void MainWindow::changeInterfaceLanguage(const int &index) {
    if (!statusInitializationComboboxInterfaceLanguage && index != -1) {
        indexInterfaceLanguage = index;
        appConfiguration.saveConfig("interface_language_index", QString::number(indexInterfaceLanguage));
        interfaceLanguage = appLang.readInterfaceLanguage(indexInterfaceLanguage);
        emit signalChangeInterfaceLanguage(indexInterfaceLanguage);
        setLang();
    }

    if (statusInitializationComboboxInterfaceLanguage) {
        statusInitializationComboboxInterfaceLanguage = false;
    }
}

void MainWindow::changeAIModel(const int &index) {
    if (!statusInitializationComboboxAIModel && index != -1) {
        indexAIModel = index;
        appConfiguration.saveConfig("ai_model_index", QString::number(indexAIModel));
        aiModel = appConfiguration.readAIModelName(indexAIModel);
    }

    if (statusInitializationComboboxAIModel) {
        statusInitializationComboboxAIModel = false;
    }
}

void MainWindow::showSettings() {
    QRect appGeometry = this -> geometry();
    appXStart = appGeometry.x();
    appYStart = appGeometry.y();
    appWidth = appGeometry.width();
    appHeight = appGeometry.height();

    appXEnd = appXStart + appWidth;

    settingsXStart = int(appXStart + (appWidth - 900) / 2);
    settingsYStart = int(appYStart + (appHeight - 600) / 2);

    appSettings.move(settingsXStart, settingsYStart);
    appSettings.show();
}

void MainWindow::changeTTSVoice(const int &index) {
    if (!statusInitializationComboboxTTSVoice && index != -1) {
        indexTTSVoice = index;
        appConfiguration.saveConfig("tts_voice_index", QString::number(indexTTSVoice));
        ttsVoice = appLang.readTTSVoice(indexTTSVoice);
    }

    if (statusInitializationComboboxTTSVoice) {
        statusInitializationComboboxTTSVoice = false;
    }
}

void MainWindow::processTTS() {
    buttonProcessTTS->setEnabled(false);
    requestCommunication();
}

bool MainWindow::checkAudio() {
    std::pair<QString, QString> pairTTSAudioFilePath = appConfiguration.readTTSAudioFilePath();
    QString pathTTSAudioFile = pairTTSAudioFilePath.first;
    QFile fileTTSAudio(pathTTSAudioFile);

    bool statusAudio = fileTTSAudio.exists();

    return statusAudio;
}

void MainWindow::playAudio() {
    std::pair<QString, QString> pairTTSAudioFilePath = appConfiguration.readTTSAudioFilePath();
    QString pathTTSAudioFile = pairTTSAudioFilePath.first;

    if (checkAudio()) {
        statusPlayAgain = true;
        setLangPlayAudio();

        AppMultimedia *appMultimedia = new AppMultimedia(pathTTSAudioFile);
        connect(appMultimedia, &AppMultimedia::finished, appMultimedia, &AppMultimedia::deleteLater);
        appMultimedia -> start();
    }
}

void MainWindow::changeTranslationLanguage(const int &index) {
    if (!statusInitializationComboboxTranslationLanguage && index != -1) {
        indexTranslationLanguage = index;
        appConfiguration.saveConfig("translation_language_index", QString::number(indexTranslationLanguage));
        translationLanguage = appLang.readTranslationLanguage(indexTranslationLanguage);
    }

    if (statusInitializationComboboxTranslationLanguage) {
        statusInitializationComboboxTranslationLanguage = false;
    }
}

void MainWindow::whenUserTextIsChanged() {
    resetSubmitButtonStatus();
}

void MainWindow::setChatContextOption() {
    if (checkboxChatContext -> isChecked()) {
        statusChatContext = true;
    } else {
        statusChatContext = false;
    }
}

void MainWindow::submitRequest() {
    chatContext = texteditChatHistory -> toPlainText();

    if (!chatContext.isEmpty()) {
        texteditChatHistory -> append("\n");
    }

    texteditChatHistory -> append(QString("User (%1):\n\n%2").arg(AppCommands::getCurrentTime(), texteditUserMessage -> toPlainText()));

    requestCommunication();
}

void MainWindow::requestCommunication() {
    buttonSubmit -> setEnabled(false);
    buttonProcessTTS -> setEnabled(false);

    AppCommunication::DataCommunication dataCommunication;

    dataCommunication.aiRole = aiRole;
    dataCommunication.aiModel = aiModel;
    dataCommunication.interfaceLanguage = interfaceLanguage;
    dataCommunication.translationLanguage = translationLanguage;
    dataCommunication.ttsVoice = ttsVoice;
    dataCommunication.userText = texteditUserText -> toPlainText();
    dataCommunication.userMessage = texteditUserMessage -> toPlainText();

    if (statusChatContext) {
        dataCommunication.chatContext = chatContext;
    } else {
        dataCommunication.chatContext = "";
    }

    AppCommunication *appCommunication = new AppCommunication(dataCommunication);
    connect(appCommunication, &AppCommunication::communicationResult, this, &MainWindow::receiveCommunicationResult);
    connect(appCommunication, &AppCommunication::finished, appCommunication, &AppCommunication::deleteLater);
    appCommunication -> start();
}

void MainWindow::receiveCommunicationResult(const QString &aiRoleResult, const QString &aiOutput, const QString &aiExplanation) {
    if (aiRoleResult == "speaker") {
        buttonProcessTTS -> setEnabled(true);

        if (checkAudio()) {
            buttonPlayAudio -> setEnabled(true);
            buttonPlayAudio -> setVisible(true);
        } else {
            buttonPlayAudio -> setEnabled(false);
            buttonPlayAudio -> setVisible(false);
        }
    } else {
        buttonSubmit -> setEnabled(true);

        QString currentTime = AppCommands::getCurrentTime();

        if (texteditChatHistory -> toPlainText() != "") {
            texteditChatHistory -> append("\n");
        }

        if (aiRoleResult == "translator" || aiRoleResult == "writing_helper" || aiRoleResult == "writer") {
            texteditAIText -> setText(aiOutput);
            texteditAIExplanation -> setText(aiExplanation);
            texteditChatHistory -> append(
                QString("AI (%1):\n\n"
                        "%2%3:\n\n"
                        "%4\n\n"
                        "%5:\n\n"
                        "%6").arg(
                        currentTime,
                        appLang.readLangEntry(indexInterfaceLanguage, "here_is_my"),
                        appLang.readLangEntry(indexInterfaceLanguage, appConfiguration.readAITextType(aiRoleResult)),
                        aiOutput,
                        appLang.readLangEntry(indexInterfaceLanguage, "here_is_my_explanation"),
                        aiExplanation
                        )
                );
        }

        if (aiRoleResult == "teacher") {
            texteditBlackboard -> setText(aiOutput);
            texteditTeacherExplanation -> setText(aiExplanation);
            texteditChatHistory -> append(
                QString("AI (%1):\n\n"
                        "%2:\n\n"
                        "%3\n\n"
                        "%4:\n\n"
                        "%5").arg(
                        currentTime,
                        appLang.readLangEntry(indexInterfaceLanguage, "watch_blackboard"),
                        aiOutput,
                        appLang.readLangEntry(indexInterfaceLanguage, "here_is_my_explanation"),
                        aiExplanation
                        )
                );
        }

        if (aiRoleResult == "programmer" || aiRoleResult == "custom_role") {
            texteditChatHistory -> append(QString("AI (%1):\n\n%2").arg(currentTime, aiOutput));
        }
    }
}

void MainWindow::whenUserMessageIsChanged() {
    resetSubmitButtonStatus();
}

void MainWindow::showExplanationOrHistory() {
    if (statusAIExplanation) {
        labelAIExplanation -> setVisible(false);
        texteditAIExplanation -> setVisible(false);
        labelChatHistory -> setVisible(true);
        buttonClearChatHistory -> setVisible(true);
        texteditChatHistory -> setVisible(true);
        statusAIExplanation = false;
    } else {
        labelAIExplanation -> setVisible(true);
        texteditAIExplanation -> setVisible(true);
        labelChatHistory -> setVisible(false);
        buttonClearChatHistory -> setVisible(false);
        texteditChatHistory -> setVisible(false);
        statusAIExplanation = true;
    }

    setLangExplanationOrHistory();
}

void MainWindow::clearChatHistory() {
    texteditChatHistory -> clear();
}

void MainWindow::setLang() {
    this -> setWindowTitle(appLang.readLangEntry(indexInterfaceLanguage, "app_name"));

    labelAIRole -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_role"));

    loadAIRoles();

    labelInterfaceLanguage -> setText(appLang.readLangEntry(indexInterfaceLanguage, "interface_language"));

    labelAIModel -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_model"));

    buttonSettings -> setText(appLang.readLangEntry(indexInterfaceLanguage, "settings"));

    labelUserText -> setText(appLang.readLangEntry(indexInterfaceLanguage, "user_text"));

    labelBlackboard -> setText(appLang.readLangEntry(indexInterfaceLanguage, "blackboard"));

    labelTTSVoice -> setText(appLang.readLangEntry(indexInterfaceLanguage, "tts_voice"));

    buttonProcessTTS -> setText(appLang.readLangEntry(indexInterfaceLanguage, "process"));

    setLangPlayAudio();

    labelTranslationLanguage -> setText(appLang.readLangEntry(indexInterfaceLanguage, "translation_language"));

    labelAIText -> setText(appLang.readLangEntry(indexInterfaceLanguage, "ai_text"));

    labelTeacherExplanation -> setText(appLang.readLangEntry(indexInterfaceLanguage, "explanation"));

    labelChatContext -> setText(appLang.readLangEntry(indexInterfaceLanguage, "chat_context"));

    buttonSubmit -> setText(appLang.readLangEntry(indexInterfaceLanguage, "submit"));

    labelUserMessage -> setText(appLang.readLangEntry(indexInterfaceLanguage, "user_message"));

    setLangExplanationOrHistory();

    buttonClearChatHistory -> setText(appLang.readLangEntry(indexInterfaceLanguage, "clear"));

    labelAIExplanation -> setText(appLang.readLangEntry(indexInterfaceLanguage, "explanation"));

    labelChatHistory -> setText(appLang.readLangEntry(indexInterfaceLanguage, "chat_history"));
}

void MainWindow::setLangPlayAudio() {
    if (!statusPlayAgain) {
        buttonPlayAudio -> setText(appLang.readLangEntry(indexInterfaceLanguage, "play_audio"));
    } else {
        if (indexInterfaceLanguage == 1) {
            buttonPlayAudio -> setFixedWidth(120);
        } else {
            buttonPlayAudio -> setFixedWidth(90);
        }

        buttonPlayAudio -> setText(appLang.readLangEntry(indexInterfaceLanguage, "play_again"));
    }
}

void MainWindow::setLangExplanationOrHistory() {
    if (statusAIExplanation) {
        buttonExplanationOrHistory -> setText(appLang.readLangEntry(indexInterfaceLanguage, "show_chat_history"));
    } else {
        buttonExplanationOrHistory -> setText(appLang.readLangEntry(indexInterfaceLanguage, "show_explanation"));
    }
}

void MainWindow::resetSubmitButtonStatus() {
    userText = texteditUserText -> toPlainText();

    if (aiRole == "translator" || aiRole == "writing_helper" || aiRole == "writer") {
        if (!userText.isEmpty()) {
            buttonSubmit -> setEnabled(true);
        } else {
            buttonSubmit -> setEnabled(false);
        }
    }

    userMessage = texteditUserMessage -> toPlainText();

    if (aiRole == "teacher" || aiRole == "programmer" || aiRole == "custom_role") {
        if (!userMessage.isEmpty()) {
            buttonSubmit -> setEnabled(true);
        } else {
            buttonSubmit -> setEnabled(false);
        }
    }

    if (aiRole == "speaker") {
        if (!userText.isEmpty()) {
            buttonProcessTTS -> setEnabled(true);
        } else {
            buttonProcessTTS -> setEnabled(false);
        }
    }
}

void MainWindow::adjustAIRoleInterface() {
    int heightSplitterMain = splitterMain -> height();
    int widthSplitterMain = splitterMain -> width();

    if (aiRole == "translator") {
        splitterMain -> setCollapsible(0, false);
        splitterMain -> setCollapsible(1, false);
        splitterLeft -> setCollapsible(0, false);
        splitterLeft -> setCollapsible(1, false);
        splitterRight -> setCollapsible(0, false);
        splitterRight -> setCollapsible(1, false);

        splitterMain -> setHandleWidth(2);
        splitterLeft -> setHandleWidth(2);
        splitterRight -> setHandleWidth(2);

        splitterLeft -> setSizes({int(heightSplitterMain * 0.4), int(heightSplitterMain * 0.6)});
        splitterRight -> setSizes({int(heightSplitterMain * 0.3), int(heightSplitterMain * 0.7)});
        splitterMain -> setSizes({int(widthSplitterMain * 0.55), int(widthSplitterMain * 0.45)});

        labelUserText -> setVisible(true);
        texteditUserText -> setVisible(true);

        labelTranslationLanguage -> setVisible(true);
        comboboxTranslationLanguage -> setVisible(true);

        labelTTSVoice -> setVisible(false);
        comboboxTTSVoice -> setVisible(false);
        buttonProcessTTS -> setVisible(false);
        buttonPlayAudio -> setVisible(false);

        labelAIText -> setVisible(true);
        texteditAIText -> setVisible(true);

        labelBlackboard -> setVisible(false);
        texteditBlackboard -> setVisible(false);
        labelTeacherExplanation -> setVisible(false);
        texteditTeacherExplanation -> setVisible(false);

        labelUserMessage -> setVisible(true);
        texteditUserMessage -> setVisible(true);

        labelChatContext -> setVisible(true);
        checkboxChatContext -> setVisible(true);

        buttonSubmit -> setVisible(true);

        buttonExplanationOrHistory -> setVisible(true);

        if (statusAIExplanation) {
            buttonClearChatHistory -> setVisible(false);
            labelAIExplanation -> setVisible(true);
            texteditAIExplanation -> setVisible(true);
            labelChatHistory -> setVisible(false);
            texteditChatHistory -> setVisible(false);
        } else {
            buttonClearChatHistory -> setVisible(true);
            labelAIExplanation -> setVisible(false);
            texteditAIExplanation -> setVisible(false);
            labelChatHistory -> setVisible(true);
            texteditChatHistory -> setVisible(true);
        }
    }

    if (aiRole == "writing_helper" || aiRole == "writer") {
        splitterMain -> setCollapsible(0, false);
        splitterMain -> setCollapsible(1, false);
        splitterLeft -> setCollapsible(0, false);
        splitterLeft -> setCollapsible(1, false);
        splitterRight -> setCollapsible(0, false);
        splitterRight -> setCollapsible(1, false);

        splitterMain -> setHandleWidth(2);
        splitterLeft -> setHandleWidth(2);
        splitterRight -> setHandleWidth(2);

        splitterLeft -> setSizes({int(heightSplitterMain * 0.4), int(heightSplitterMain * 0.6)});
        splitterRight -> setSizes({int(heightSplitterMain * 0.3), int(heightSplitterMain * 0.7)});
        splitterMain -> setSizes({int(widthSplitterMain * 0.55), int(widthSplitterMain * 0.45)});

        labelUserText -> setVisible(true);
        texteditUserText -> setVisible(true);

        labelTranslationLanguage -> setVisible(false);
        comboboxTranslationLanguage -> setVisible(false);

        labelTTSVoice -> setVisible(false);
        comboboxTTSVoice -> setVisible(false);
        buttonProcessTTS -> setVisible(false);
        buttonPlayAudio -> setVisible(false);

        labelAIText -> setVisible(true);
        texteditAIText -> setVisible(true);

        labelBlackboard -> setVisible(false);
        texteditBlackboard -> setVisible(false);
        labelTeacherExplanation -> setVisible(false);
        texteditTeacherExplanation -> setVisible(false);

        labelUserMessage -> setVisible(true);
        texteditUserMessage -> setVisible(true);

        labelChatContext -> setVisible(true);
        checkboxChatContext -> setVisible(true);

        buttonSubmit -> setVisible(true);

        buttonExplanationOrHistory -> setVisible(true);

        if (statusAIExplanation) {
            buttonClearChatHistory -> setVisible(false);
            labelAIExplanation -> setVisible(true);
            texteditAIExplanation -> setVisible(true);
            labelChatHistory -> setVisible(false);
            texteditChatHistory -> setVisible(false);
        } else {
            buttonClearChatHistory -> setVisible(true);
            labelAIExplanation -> setVisible(false);
            texteditAIExplanation -> setVisible(false);
            labelChatHistory -> setVisible(true);
            texteditChatHistory -> setVisible(true);
        }
    }

    if (aiRole == "teacher") {
        splitterMain -> setCollapsible(0, false);
        splitterMain -> setCollapsible(1, false);
        splitterLeft -> setCollapsible(0, false);
        splitterLeft -> setCollapsible(1, false);
        splitterRight -> setCollapsible(0, false);
        splitterRight -> setCollapsible(1, false);

        splitterMain -> setHandleWidth(2);
        splitterLeft -> setHandleWidth(2);
        splitterRight -> setHandleWidth(2);

        splitterLeft -> setSizes({int(heightSplitterMain * 0.4), int(heightSplitterMain * 0.6)});
        splitterRight -> setSizes({int(heightSplitterMain * 0.3), int(heightSplitterMain * 0.7)});
        splitterMain -> setSizes({int(widthSplitterMain * 0.6), int(widthSplitterMain * 0.4)});

        labelUserText -> setVisible(false);
        texteditUserText -> setVisible(false);

        labelTranslationLanguage -> setVisible(false);
        comboboxTranslationLanguage -> setVisible(false);

        labelTTSVoice -> setVisible(false);
        comboboxTTSVoice -> setVisible(false);
        buttonProcessTTS -> setVisible(false);
        buttonPlayAudio -> setVisible(false);

        labelAIText -> setVisible(false);
        texteditAIText -> setVisible(false);

        labelBlackboard -> setVisible(true);
        texteditBlackboard -> setVisible(true);
        labelTeacherExplanation -> setVisible(true);
        texteditTeacherExplanation -> setVisible(true);

        labelUserMessage -> setVisible(true);
        texteditUserMessage -> setVisible(true);

        labelChatContext -> setVisible(true);
        checkboxChatContext -> setVisible(true);

        buttonSubmit -> setVisible(true);

        buttonExplanationOrHistory -> setVisible(false);

        buttonClearChatHistory -> setVisible(true);
        labelAIExplanation -> setVisible(false);
        texteditAIExplanation -> setVisible(false);
        labelChatHistory -> setVisible(true);
        texteditChatHistory -> setVisible(true);
    }

    if (aiRole == "programmer" || aiRole == "custom_role") {
        splitterMain -> setCollapsible(0, true);
        splitterMain -> setCollapsible(1, false);
        splitterLeft -> setCollapsible(0, true);
        splitterLeft -> setCollapsible(1, true);
        splitterRight -> setCollapsible(0, false);
        splitterRight -> setCollapsible(1, false);

        splitterMain -> setHandleWidth(0);
        splitterRight -> setHandleWidth(2);

        splitterMain -> setSizes({0, widthSplitterMain});
        splitterRight -> setSizes({int(heightSplitterMain * 0.2), int(heightSplitterMain * 0.8)});

        labelUserText -> setVisible(false);
        texteditUserText -> setVisible(false);

        labelTranslationLanguage -> setVisible(false);
        comboboxTranslationLanguage -> setVisible(false);

        labelTTSVoice -> setVisible(false);
        comboboxTTSVoice -> setVisible(false);
        buttonProcessTTS -> setVisible(false);
        buttonPlayAudio -> setVisible(false);

        labelAIText -> setVisible(false);
        texteditAIText -> setVisible(false);

        labelBlackboard -> setVisible(false);
        texteditBlackboard -> setVisible(false);
        labelTeacherExplanation -> setVisible(false);
        texteditTeacherExplanation -> setVisible(false);

        labelUserMessage -> setVisible(true);
        texteditUserMessage -> setVisible(true);

        labelChatContext -> setVisible(true);
        checkboxChatContext -> setVisible(true);

        buttonSubmit -> setVisible(true);

        buttonExplanationOrHistory -> setVisible(false);

        buttonClearChatHistory -> setVisible(true);
        labelAIExplanation -> setVisible(false);
        texteditAIExplanation -> setVisible(false);
        labelChatHistory -> setVisible(true);
        texteditChatHistory -> setVisible(true);
    }

    if (aiRole == "speaker") {
        splitterMain -> setCollapsible(0, false);
        splitterMain -> setCollapsible(1, true);
        splitterLeft -> setCollapsible(0, false);
        splitterLeft -> setCollapsible(1, true);
        splitterRight -> setCollapsible(0, true);
        splitterRight -> setCollapsible(1, true);

        splitterMain -> setHandleWidth(0);
        splitterLeft -> setHandleWidth(0);

        splitterMain -> setSizes({widthSplitterMain, 0});
        splitterLeft -> setSizes({heightSplitterMain, 0});

        labelUserText -> setVisible(true);
        texteditUserText -> setVisible(true);

        labelTranslationLanguage -> setVisible(false);
        comboboxTranslationLanguage -> setVisible(false);

        labelTTSVoice -> setVisible(true);
        comboboxTTSVoice -> setVisible(true);
        buttonProcessTTS -> setVisible(true);

        if (checkAudio()) {
            buttonPlayAudio -> setEnabled(true);
            buttonPlayAudio -> setVisible(true);
        } else {
            buttonPlayAudio -> setEnabled(false);
            buttonPlayAudio -> setVisible(false);
        }

        labelAIText -> setVisible(false);
        texteditAIText -> setVisible(false);

        labelBlackboard -> setVisible(false);
        texteditBlackboard -> setVisible(false);
        labelTeacherExplanation -> setVisible(false);
        texteditTeacherExplanation -> setVisible(false);

        labelUserMessage -> setVisible(false);
        texteditUserMessage -> setVisible(false);

        labelChatContext -> setVisible(false);
        checkboxChatContext -> setVisible(false);

        buttonSubmit -> setVisible(false);

        buttonExplanationOrHistory -> setVisible(false);

        buttonClearChatHistory -> setVisible(false);
        labelAIExplanation -> setVisible(false);
        texteditAIExplanation -> setVisible(false);
        labelChatHistory -> setVisible(false);
        texteditChatHistory -> setVisible(false);
    }

    adjustAvailableFunctions();
}

void MainWindow::adjustAvailableFunctions() {
    if (aiModel.isEmpty()) {
        texteditUserText -> setEnabled(false);
        buttonProcessTTS -> setEnabled(false);
        buttonPlayAudio -> setEnabled(false);
        texteditAIText -> setEnabled(false);
        texteditUserMessage -> setEnabled(false);
        checkboxChatContext -> setEnabled(false);
        buttonSubmit -> setEnabled(false);
        buttonExplanationOrHistory -> setEnabled(false);
        buttonClearChatHistory -> setEnabled(false);
        texteditAIExplanation -> setEnabled(false);
        texteditChatHistory -> setEnabled(false);
        texteditBlackboard -> setEnabled(false);
        texteditTeacherExplanation -> setEnabled(false);
    } else {
        texteditUserText -> setEnabled(true);
        texteditAIText -> setEnabled(true);
        texteditUserMessage -> setEnabled(true);
        checkboxChatContext -> setEnabled(true);
        buttonSubmit -> setEnabled(true);
        buttonExplanationOrHistory -> setEnabled(true);
        buttonClearChatHistory -> setEnabled(true);
        texteditAIExplanation -> setEnabled(true);
        texteditChatHistory -> setEnabled(true);
        texteditBlackboard -> setEnabled(true);
        texteditTeacherExplanation -> setEnabled(true);

        std::tuple<bool, bool, bool> statusAPIKeys = appSettings.checkAPIKeys();
        bool statusOpenAIAPIKey = std::get<0>(statusAPIKeys);
        if (statusOpenAIAPIKey) {
            buttonProcessTTS -> setEnabled(true);

            if (checkAudio()) {
                buttonPlayAudio -> setEnabled(true);
            } else {
                buttonPlayAudio -> setEnabled(false);
            }
        } else {
            buttonProcessTTS -> setEnabled(false);
            buttonPlayAudio -> setEnabled(false);
        }

        resetSubmitButtonStatus();
    }
}
