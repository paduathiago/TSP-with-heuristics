#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include <cmath>
#include "Node.h"

class DistanceMeasure
{
public:
    virtual double distance(const Node& n1, const Node& n2) const = 0;
    virtual ~DistanceMeasure() = default;
};

class EuclideanDistance : public DistanceMeasure
{
public:
    double distance(const Node& n1, const Node& n2) const override
    {
        return std::sqrt((n2.x - n1.x) * (n2.x - n1.x) + (n2.y - n1.y) * (n2.y - n1.y));
    }
};

class PseudoEuclideanDistance : public DistanceMeasure
{
public:
    double distance(const Node& n1, const Node& n2) const override
    {
        double dx = n2.x - n1.x;
        double dy = n2.y - n1.y;
        double rij = std::sqrt(dx * dx + dy * dy);
        return std::round(rij); // rounds to the nearest integer
    }
};

#endif // DISTANCEMEASURE_H
