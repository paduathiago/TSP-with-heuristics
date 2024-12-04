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

void VND::run()
{
    runN1();
}

void VND::runN1()
{
    solution = twoOpt.run(totalDistance, solution);
    totalDistance = twoOpt.getTotalDistance();
    std::cout << "Total distance after N1: " << totalDistance << std::endl;
    runN2();
}

void VND::runN2()
{
    double initalDistance = totalDistance;
    solution = threeOpt.run(totalDistance, solution);
    std::cout << "------------------------------------" << std::endl;
    totalDistance = threeOpt.getTotalDistance();
    if (totalDistance < initalDistance)
    {
        std::cout << "back to N1" << std::endl;
        runN1();
    }
    else
        std::cout << "*done*" << std::endl;
}
