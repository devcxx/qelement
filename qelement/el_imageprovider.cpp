#include "el_imageprovider.h"
#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardPaths>

EL_BEGIN_NAMESPACE

ImageRunnable::ImageRunnable(const QString& url, const QString& fileName)
    : _url(url)
    , _fileName(fileName)
{
}

void ImageRunnable::run()
{
    emit taskStart(_url, _fileName);

    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(_url));

    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply* reply = manager.get(request);
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Download Failed at {}\n"
                 << _url;
    }

    QFile file(_fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to write " << _fileName;
    }
    file.write(reply->readAll());
    file.flush();
    file.close();
    qDebug() << "Download compeleted: " << _fileName;

    emit taskEnd(_url, _fileName);
}

ImageProvider::ImageProvider(QObject* parent)
    : QObject { parent }
{
    _pool = new QThreadPool(this);
    QString appDataDir = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).first();
    _cacheDir = appDataDir + "/imagecached";
    QDir dir(_cacheDir);
    if (!dir.exists()) {
        dir.mkpath(_cacheDir);
    }
}

ImageProvider::~ImageProvider()
{
    _pool->clear();
    _pool->waitForDone();
}

void ImageProvider::getNetworkImage(const QString& url)
{
    QString id = generateId(url);
    QString filePath = _cacheDir + "/" + id;
    if (QFile::exists(filePath)) {
        emit imageReady(url, filePath);
        return;
    }
    ImageRunnable* runnable = new ImageRunnable(url, filePath);
    runnable->setAutoDelete(true);
    connect(runnable, &ImageRunnable::taskEnd, this, &ImageProvider::imageReady);
    _pool->start(runnable);
}

QString ImageProvider::generateId(const QString& url)
{
    return QString(QCryptographicHash::hash(url.toUtf8(), QCryptographicHash::Md5).toHex());
}

EL_END_NAMESPACE
