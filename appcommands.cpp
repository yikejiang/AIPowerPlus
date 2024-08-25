#include "appcommands.h"

#include <string>
#include <random>

#include <QDateTime>
#include <QTimeZone>

AppCommands::AppCommands() {
}

QString AppCommands::getRandomString(const int &randomStringLength) {
    const std::string characterRange = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characterRange.size() - 1);
    std::string randomString;
    for (int i = 0; i < randomStringLength; ++i) {
        randomString += characterRange[distribution(generator)];
    }
    return QString::fromStdString(randomString);
}

QString AppCommands::getCurrentTime() {
    QDateTime currentLocalTime = QDateTime::currentDateTime();
    QTimeZone currentTimeZone = currentLocalTime.timeZone();
    QString currentTime = currentLocalTime.toString("yyyy-MM-dd HH:mm:ss") + " " + currentTimeZone.displayName(currentLocalTime, QTimeZone::OffsetName);

    return currentTime;
}
