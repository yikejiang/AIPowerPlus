#include "appmultimedia.h"

#include <QUrl>

AppMultimedia::AppMultimedia(const QString &path) : QThread() {
    pathTTSAudioFile = path;
}

void AppMultimedia::run() {
    audioPlayer -> setAudioOutput(audioOutput);
    audioPlayer -> setSource(QUrl::fromLocalFile(pathTTSAudioFile));
    audioPlayer -> play();
}
