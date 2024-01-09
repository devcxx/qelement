#ifndef EL_IMAGEPROVIDER_H
#define EL_IMAGEPROVIDER_H

#include <QObject>
#include <QRunnable>
#include <QThreadPool>

#include "el_global.h"

EL_BEGIN_NAMESPACE

class ImageRunnable : public QObject, public QRunnable {
    Q_OBJECT
public:
    ImageRunnable(const QString& url, const QString& fileName);
    void run();

signals:
    void taskStart(QString, QString);
    void taskEnd(QString, QString);

private:
    QString _url;
    QString _fileName;
};

class ImageProvider : public QObject {
    Q_OBJECT
public:
    explicit ImageProvider(QObject* parent = nullptr);
    ~ImageProvider();
    void getNetworkImage(const QString& url);
    QString generateId(const QString& url);

signals:
    void imageReady(QString url, QString filePath);

private:
    QThreadPool* _pool = nullptr;
    QString _cacheDir;
};

EL_END_NAMESPACE

#endif // EL_IMAGEPROVIDER_H
