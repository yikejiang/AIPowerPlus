#ifndef APPMULTIMEDIA_H
#define APPMULTIMEDIA_H

#include <QThread>
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

class AppMultimedia : public QThread
{
    Q_OBJECT

public:
    explicit AppMultimedia(const QString &path);

protected:
    void run() override;

private:
    QString pathTTSAudioFile;

    QMediaPlayer *audioPlayer = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
};

#endif // APPMULTIMEDIA_H
