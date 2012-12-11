#include "SimpleClassifier.h"

#include <QtDebug>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

SimpleClassifier::SimpleClassifier(const QSharedPointer<Feature> &feat, int polarity, qint64 threshold) :
    _feature(feat), _threshold(threshold)
{
    this->setPolarity(polarity);

    if (_feature.isNull())
        qWarning() << "SimpleClassifier given null feature pointer. Will always classify \"false\" in this case";
}

SimpleClassifier::~SimpleClassifier()
{
}

//Copy Constructor
SimpleClassifier::SimpleClassifier(const SimpleClassifier &other)
{
    _feature = other.feature();
    _polarity = other.polarity();
    _threshold = other.threshold();
}

//Assignment Operator
SimpleClassifier &SimpleClassifier::operator =(const SimpleClassifier &other)
{
    //Always check for self-assignment!
    if (&other == this)
        return *this;

    _feature = other.feature();
    _polarity = other.polarity();
    _threshold = other.threshold();
    return *this;
}

//virtual from Classifier
bool SimpleClassifier::classify(const IntegralImage &image, const QPoint &origin, qreal scale)
{
    if (_feature.isNull())
        return false;

    int p = this->polarity();

    const QSharedPointer<Feature>& f = this->feature();
    qint64 val = f->evaluate(image, origin, scale);

    return (p*val < p*this->threshold());
}

const QSharedPointer<Feature> &SimpleClassifier::feature() const
{
    return _feature;
}

void SimpleClassifier::setFeature(const QSharedPointer<Feature> &nFeat)
{
    if (nFeat.isNull())
    {
        qWarning() << "SimpleClassifier setFeature given null feature. Will not set.";
        return;
    }

    _feature = nFeat;
}

int SimpleClassifier::polarity() const
{
    return _polarity;
}

void SimpleClassifier::setPolarity(int nPol)
{
    _polarity = sgn<int>(nPol);

    if (_polarity == 0)
    {
        qWarning() << "SimpleClassifier given polarity of 0. Must be -1 or 1. Assuming 1.";
        _polarity = 1;
    }
}

qint64 SimpleClassifier::threshold() const
{
    return _threshold;
}

void SimpleClassifier::setThreshold(qint64 nThresh)
{
    _threshold = nThresh;
}
