#include "VND.h"

VND::VND(std::string inputFile)
{
    initialNN.solve(inputFile);

    distanceMeasure = initialNN.getDistanceMeasure();
    solution = initialNN.getSolution();
    totalDistance = initialNN.getTotalDistance();

    twoOpt = TwoOpt(distanceMeasure);
    threeOpt = ThreeOpt(distanceMeasure);
}

double VND::computeTotalDistance()
{
    double dist = 0.0;
    for (int i = 0; i < int(solution.size() - 1); i++)
    {
        dist += distanceMeasure->distance(solution[i], solution[i + 1]);
    }
    dist += distanceMeasure->distance(solution[solution.size() - 1], solution[0]);
    return dist;
}

void VND::run()
{
    runN1();
}

void VND::runN1()
{
    solution = twoOpt.run(totalDistance, solution);
    totalDistance = twoOpt.getTotalDistance();
    runN2();
}

void VND::runN2()
{
    double initalDistance = totalDistance;
    solution = threeOpt.run(totalDistance, solution);

    totalDistance = threeOpt.getTotalDistance();
    if (totalDistance < initalDistance)
    {
        runN1();
    }
}


