#ifndef APPLANG_H
#define APPLANG_H

#include <QString>
#include <QList>
#include <QMap>
#include <QVariantMap>

class AppLang
{
public:
    AppLang();
    QString readLangEntry(const int &indexInterfaceLanguage, const QString &nameLangEntry);
    QString readInterfaceLanguage(const int &indexInterfaceLanguage);
    QString readTranslationLanguage(const int &indexTranslationLanguage);
    QList<QString> readComboboxItemsAIRole(const int &indexInterfaceLanguage);
    QString readAIRole(const int &indexAIRole);
    QList<QString> readComboboxItemsTTSVoice();
    QString readTTSVoice(const int &indexTTSVoice);
    QList<QString> readComboboxItemsAPIKeyName(const int &indexInterfaceLanguage);
    QString readAPIKeyName(const int &indexAPIKeyName);

    QString appVersion;

    QList<QString> listInterfaceLanguage;
    QList<QString> listTranslationLanguage;
    QList<QString> listAIRole;
    QList<QString> listTTSAudioFileSuffix;
    QList<QString> listAPIKeyName;

private:
    QMap<QString, QString> mapTTSVoice;

    QVariantMap mapLangEntry;
};

#endif // APPLANG_H
