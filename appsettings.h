#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <tuple>

#include <QDialog>
#include <QWidget>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include "appconfiguration.h"
#include "applang.h"

class AppSettings : public QDialog
{
    Q_OBJECT

public:
    AppSettings();
    ~AppSettings();

    std::tuple<bool, bool, bool> checkAPIKeys();

signals:
    void signalReloadAIModels();

public slots:
    void changeInterfaceLanguage(const int &index);
    void changeAIRole(const int &index);

private slots:
    void whenAIRoleIsChanged(const int &index);
    void whenTTSAudioFileSuffixIsChanged(const int &index);
    void saveAIModelTemperature();
    void saveAIRoleDescription();
    void saveAIRequirements();
    void setTTSAudioFileFolder();
    void saveTTSAudioFilePath();
    void whenAIModelIsChanged(const int &index);
    void modifyAIModel();
    void removeAIModel();
    void addAIModel();
    void saveAIModel();
    void cancelModifyingOrAddingAIModel();
    void whenAPIKeyNameIsChanged(const int &index);
    void saveAPIKey();
    void modifyAPIKey();

private:
    void initializeParameters();
    void setLang();
    void setLangAPIKeys();
    void loadAIRoles();
    void adjustAIModelConfigurationInterface();
    void readAIGuidelines(const QString &aiRole);
    void loadTTSAudioSettings();
    void loadAIModels();
    void loadAPIKeyNames();
    void adjustLayoutAPIKeys();

    AppLang appLang;
    AppConfiguration appConfiguration;

    bool statusInitializationComboboxAIRole;
    bool statusInitializationComboboxTTSAudioFileSuffix;
    bool statusInitializationComboboxAIModel;
    bool statusInitializationComboboxAPIKeyName;
    bool statusModifyAIModel;
    bool statusAddAIModel;
    bool statusRemoveAIModel;
    bool statusOpenAIAPIKey;
    bool statusModifyOpenAIAPIKey;
    bool statusClaudeAIAPIKey;
    bool statusModifyClaudeAIAPIKey;
    bool statusGeminiAPIKey;
    bool statusModifyGeminiAPIKey;

    QList<QString> listAIRole;

    int indexInterfaceLanguage;
    int indexAIRole;
    int indexTTSAudioFileSuffix;
    int indexAIModel;
    int indexModifyAIModel;
    int indexAddAIModel;
    int indexRemoveAIModel;
    int indexAPIKeyName;

    QString aiRole;
    QString apiKeyName;

    QFont font;

    // layout of settings
    QHBoxLayout *settingsLayout = new QHBoxLayout;

    // layout of the left area
    QVBoxLayout *layoutLeft = new QVBoxLayout;

    // layout of the top area in the left area
    QVBoxLayout *layoutLeftUpper = new QVBoxLayout;

    // layout of the first line of the top area in the left area
    QHBoxLayout *layoutLeftUpperFirst = new QHBoxLayout;

    // layout of the second line of the top area in the left area
    QHBoxLayout *layoutLeftUpperSecond = new QHBoxLayout;

    // layout of the third line of the top area in the left area
    QHBoxLayout *layoutLeftUpperThird = new QHBoxLayout;

    // layout of the fourth line of the top area in the left area
    QHBoxLayout *layoutLeftUpperFourth = new QHBoxLayout;

    // splitter and containers for the center area and the lower area in the left area
    QSplitter *splitterAIGuidelines = new QSplitter;
    QWidget *containerAIRoleDescription = new QWidget;
    QWidget *containerAIRequirements = new QWidget;

    // layout of the center area in the left area
    QVBoxLayout *layoutLeftCenter = new QVBoxLayout;

    // layout of the lower area in the left area
    QVBoxLayout *layoutLeftLower = new QVBoxLayout;

    // container of the right area
    QWidget *containerRight = new QWidget;

    // layout of the right area
    QVBoxLayout *layoutRight = new QVBoxLayout;

    // layout of the top area in the right area
    QVBoxLayout *layoutRightUpper = new QVBoxLayout;

    // layout of the first line of the top area in the right area
    QHBoxLayout *layoutRightUpperFirst = new QHBoxLayout;

    // layout of the second line of the top area in the right area
    QHBoxLayout *layoutRightUpperSecond = new QHBoxLayout;

    // layout of the third line of the top area in the right area
    QHBoxLayout *layoutRightUpperThird = new QHBoxLayout;

    // layout of the fourth line of the top area in the right area
    QHBoxLayout *layoutRightUpperFourth = new QHBoxLayout;

    // layout of the center area in the right area
    QVBoxLayout *layoutRightCenter = new QVBoxLayout;

    // layout of the left side of the center area in the right area
    QHBoxLayout *layoutRightCenterLeft = new QHBoxLayout;

    // layout of the lower area in the right area
    QVBoxLayout *layoutRightLower = new QVBoxLayout;

    // AI model's configuration
    QLabel *labelAIModelConfiguration = new QLabel;

    QLabel *labelAIRole = new QLabel;
    QComboBox *comboboxAIRole = new QComboBox;

    QLabel *labelAIModelTemperature = new QLabel;
    QLineEdit *lineeditAIModelTemperature = new QLineEdit;

    QLabel *labelTTSAudioFileName = new QLabel;
    QLineEdit *lineeditTTSAudioFileBasename = new QLineEdit;
    QComboBox *comboboxTTSAudioFileSuffix = new QComboBox;
    QLabel *labelTTSAudioFileFolder = new QLabel;
    QPushButton *buttonSetTTSAudioFileFolder = new QPushButton;
    QLineEdit *lineeditTTSAudioFileFolderPath = new QLineEdit;

    QLabel *labelAIRoleDescription = new QLabel;
    QTextEdit *texteditAIRoleDescription = new QTextEdit;

    QLabel *labelAIRequirements = new QLabel;
    QTextEdit *texteditAIRequirements = new QTextEdit;

    // set AI models
    QLabel *labelAIModels = new QLabel;

    QLabel *labelAIModelCustomName = new QLabel;

    QComboBox *comboboxAIModel = new QComboBox;

    QLineEdit *lineeditAIModelCustomName = new QLineEdit;

    QLabel *labelNoticeAIModelCustomName = new QLabel;

    QPushButton *buttonModifyAIModel = new QPushButton;
    QPushButton *buttonRemoveAIModel = new QPushButton;
    QPushButton *buttonAddAIModel = new QPushButton;

    QPushButton *buttonSaveAIModel = new QPushButton;
    QPushButton *buttonCancelModifyingOrAddingAIModel = new QPushButton;

    QLabel *labelAIModelName = new QLabel;
    QLineEdit *lineeditAIModelName = new QLineEdit;
    QLabel *labelNoticeAIModelName = new QLabel;

    // set API keys
    QLabel *labelAPIKeys = new QLabel;

    QComboBox *comboboxAPIKeyName = new QComboBox;

    QLineEdit *lineeditAPIKey = new QLineEdit;

    QPushButton *buttonSaveAPIKey = new QPushButton;
    QPushButton *buttonModifyAPIKey = new QPushButton;

    QLabel *labelAPIKeyStatus = new QLabel;

    // app's description
    QTextEdit *texteditAppDescription = new QTextEdit;
};

#endif // APPSETTINGS_H
