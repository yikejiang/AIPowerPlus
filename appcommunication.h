#ifndef APPCOMMUNICATION_H
#define APPCOMMUNICATION_H

#include <QThread>
#include <QString>

#include "appconfiguration.h"

class AppCommunication : public QThread
{
    Q_OBJECT

public:
    struct DataCommunication {
        QString aiRole;
        QString aiModel;
        QString interfaceLanguage;
        QString translationLanguage;
        QString ttsVoice;
        QString userText;
        QString userMessage;
        QString chatContext;
    };

    explicit AppCommunication(const DataCommunication &dataCommunication);

signals:
    void communicationResult(QString aiRole, QString aiOutput, QString aiExplanation);

protected:
    void run() override;

private:
    AppConfiguration appConfiguration;

    QString aiRole;
    QString aiModel;
    QString interfaceLanguage;
    QString translationLanguage;
    QString ttsVoice;
    QString userText;
    QString userMessage;
    QString chatContext;

    QString replyType;

    QString apiKey;
};

#endif // APPCOMMUNICATION_H
