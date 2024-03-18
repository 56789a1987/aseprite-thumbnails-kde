#include "aseprite_thumbnails.h"

#include <QCryptographicHash>
#include <QFile>
#include <QImage>
#include <QProcess>
#include <QStringList>
#include <QtGlobal>

#include <KPluginFactory>
K_PLUGIN_CLASS_WITH_JSON(AsepriteThumbnails, "aseprite_thumbnails.json")

AsepriteThumbnails::AsepriteThumbnails(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

KIO::ThumbnailResult AsepriteThumbnails::create(const KIO::ThumbnailRequest &request)
{
    QProcess process;
    QStringList args;

    QSize size = request.targetSize();
    QString path = request.url().toLocalFile();
    QString hash = QString::fromLatin1(QCryptographicHash::hash(path.toLocal8Bit(), QCryptographicHash::Md5).toHex());

    QString tempFile = QStringLiteral("/tmp/Aseprite/") + hash + QStringLiteral(".png");
    QString sizeStr = QString::number(size.width()) + QStringLiteral(",") + QString::number(size.width());

    args << QStringLiteral("-b")
         << QStringLiteral("--frame-range")
         << QStringLiteral("0,0")
         << path
         << QStringLiteral("--shrink-to")
         << sizeStr
         << QStringLiteral("--sheet")
         << tempFile;

    process.start(QStringLiteral("aseprite"), args);
    if (!process.waitForFinished())
    {
        return KIO::ThumbnailResult::fail();
    }

    QImage image(tempFile);
    if (image.isNull())
    {
        QFile::remove(tempFile);
        return KIO::ThumbnailResult::fail();
    }

    QFile::remove(tempFile);
    return KIO::ThumbnailResult::pass(image);
}

#include "aseprite_thumbnails.moc"
