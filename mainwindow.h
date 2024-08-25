#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QTextEdit>

#include "appconfiguration.h"
#include "applang.h"
#include "appsettings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

signals:
    void signalChangeInterfaceLanguage(const int &index);
    void signalChangeAIRole(const int &index);

private slots:
    void loadAIModels();
    void showSettings();
    void changeAIRole(const int &index);
    void changeInterfaceLanguage(const int &index);
    void changeAIModel(const int &index);
    void changeTTSVoice(const int &index);
    void processTTS();
    void playAudio();
    void changeTranslationLanguage(const int &index);
    void whenUserTextIsChanged();
    void setChatContextOption();
    void submitRequest();
    void whenUserMessageIsChanged();
    void showExplanationOrHistory();
    void clearChatHistory();
    void receiveCommunicationResult(const QString &aiRoleResult, const QString &aiOutput, const QString &aiExplanation);

private:
    void initializeParameters();
    void loadAIRoles();
    void loadInterfaceLanguages();
    void loadTranslationLanguages();
    void loadTTSVoices();
    void setLang();
    void setLangPlayAudio();
    void setLangExplanationOrHistory();
    void adjustAIRoleInterface();
    void requestCommunication();
    void resetSubmitButtonStatus();
    void adjustAvailableFunctions();
    bool checkAudio();

    AppConfiguration appConfiguration;
    AppSettings appSettings;
    AppLang appLang;

    int appXStart;
    int appYStart;
    int appWidth;
    int appHeight;
    int appXEnd;
    int settingsXStart;
    int settingsYStart;
    int indexAIRole;
    int indexInterfaceLanguage;
    int indexAIModel;
    int indexTranslationLanguage;
    int indexTTSVoice;

    bool statusInitializationComboboxAIRole;
    bool statusInitializationComboboxInterfaceLanguage;
    bool statusInitializationComboboxAIModel;
    bool statusInitializationComboboxTTSVoice;
    bool statusInitializationComboboxTranslationLanguage;
    bool statusPlayAgain;
    bool statusChatContext;
    bool statusAIExplanation;

    QString pathAppLogoFilePath;
    QString aiRole;
    QString aiModel;
    QString interfaceLanguage;
    QString ttsVoice;
    QString translationLanguage;
    QString userText;
    QString userMessage;
    QString chatContext;

    QFont font;

    // app's layout
    QWidget *centralWidget  = new QWidget;
    QVBoxLayout *appLayout = new QVBoxLayout;

    // layout of the app's top
    QHBoxLayout *layoutTop = new QHBoxLayout;
    QWidget *containerTop = new QWidget;
    QHBoxLayout *layoutTopRight = new QHBoxLayout;

    // splitter of the app's main area
    QSplitter *splitterMain = new QSplitter;

    // left splitter and right splitter in the app's main area
    QSplitter *splitterLeft = new QSplitter;
    QSplitter *splitterRight = new QSplitter;

    // layout of the left side in the app's main area
    QVBoxLayout *layoutMainLeftUpper = new QVBoxLayout;
    QWidget *containerMainLeftUpper = new QWidget;
    QVBoxLayout *layoutMainLeftLower = new QVBoxLayout;
    QWidget *containerMainLeftLower = new QWidget;

    // layout of the right side in the app's main area
    QVBoxLayout *layoutMainRightUpper = new QVBoxLayout;
    QWidget *containerMainRightUpper = new QWidget;
    QVBoxLayout *layoutMainRightLower = new QVBoxLayout;
    QWidget *containerMainRightLower = new QWidget;

    // layout for the top of the left upper area in the app's main area
    QHBoxLayout *layoutMainLeftUpperTop = new QHBoxLayout;
    QHBoxLayout *layoutMainLeftUpperTopLeft = new QHBoxLayout;
    QHBoxLayout *layoutMainLeftUpperTopRight = new QHBoxLayout;

    // layout for the top of the right upper area in the app's main area
    QHBoxLayout *layoutMainRightUpperTop = new QHBoxLayout;
    QHBoxLayout *layoutMainRightUpperTopLeft = new QHBoxLayout;
    QHBoxLayout *layoutMainRightUpperTopRight = new QHBoxLayout;

    // layout for the top of the right lower area in the app's main area
    QHBoxLayout *layoutMainRightLowerTop = new QHBoxLayout;
    QHBoxLayout *layoutMainRightLowerTopLeft = new QHBoxLayout;
    QHBoxLayout *layoutMainRightLowerTopRight = new QHBoxLayout;

    // components of the app's top
    QLabel *labelAIRole = new QLabel;
    QComboBox *comboboxAIRole = new QComboBox;

    QLabel *labelInterfaceLanguage = new QLabel;
    QComboBox *comboboxInterfaceLanguage = new QComboBox;

    QLabel *labelAIModel = new QLabel;
    QComboBox *comboboxAIModel = new QComboBox;

    QPushButton *buttonSettings = new QPushButton;

    // area of user's input text
    QLabel *labelUserText = new QLabel;

    QLabel *labelTTSVoice = new QLabel;
    QComboBox *comboboxTTSVoice = new QComboBox;
    QPushButton *buttonProcessTTS = new QPushButton;
    QPushButton *buttonPlayAudio = new QPushButton;

    QLabel *labelTranslationLanguage = new QLabel;
    QComboBox *comboboxTranslationLanguage = new QComboBox;

    QTextEdit *texteditUserText = new QTextEdit;

    // area of AI's teacher role
    QLabel *labelBlackboard = new QLabel;
    QTextEdit *texteditBlackboard = new QTextEdit;

    QLabel *labelTeacherExplanation = new QLabel;
    QTextEdit *texteditTeacherExplanation = new QTextEdit;

    // area of AI's output text
    QLabel *labelAIText = new QLabel;
    QTextEdit *texteditAIText = new QTextEdit;

    // area of user's message
    QLabel *labelUserMessage = new QLabel;
    QLabel *labelChatContext = new QLabel;
    QCheckBox *checkboxChatContext = new QCheckBox;
    QPushButton *buttonSubmit = new QPushButton;
    QTextEdit *texteditUserMessage = new QTextEdit;

    // area of AI's explanation
    QLabel *labelAIExplanation = new QLabel;

    // area of chat history
    QLabel *labelChatHistory = new QLabel;
    QPushButton *buttonExplanationOrHistory = new QPushButton;
    QPushButton *buttonClearChatHistory = new QPushButton;

    QTextEdit *texteditAIExplanation = new QTextEdit;
    QTextEdit *texteditChatHistory = new QTextEdit;
};
#endif // MAINWINDOW_H
