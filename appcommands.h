#ifndef APPCOMMANDS_H
#define APPCOMMANDS_H

#include <QString>

class AppCommands
{
public:
    AppCommands();
    static QString getRandomString(const int &randomStringLength);
    static QString getCurrentTime();
};

#endif // APPCOMMANDS_H
