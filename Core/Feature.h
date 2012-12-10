#ifndef FEATURE_H
#define FEATURE_H

#include <QPoint>

#include "IntegralImage.h"

class Feature
{
public:
    Feature();
    virtual ~Feature();

    virtual qint64 evaluate(const IntegralImage& image,
                            const QPoint& origin,
                            qreal scale);
};

#endif // FEATURE_H
