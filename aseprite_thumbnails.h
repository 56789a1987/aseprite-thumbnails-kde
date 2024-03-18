#ifndef _ASEPRITE_THUMBNAILS_H_
#define _ASEPRITE_THUMBNAILS_H_
#pragma once

#include <QObject>
#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(LOG_ASEPRITE_THUMBNAILS)

#include <KIO/ThumbnailCreator>

class AsepriteThumbnails : public KIO::ThumbnailCreator
{
public:
    AsepriteThumbnails(QObject *parent, const QVariantList &args);
    KIO::ThumbnailResult create(const KIO::ThumbnailRequest &request) override;
};

#endif
