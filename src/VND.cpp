#include "VND.h"

VND::VND(std::string inputFile)
{
    initialNN.solve(inputFile);

    distanceMeasure = initialNN.getDistanceMeasure();
    solution = initialNN.getSolution();
    totalDistance = initialNN.getTotalDistance();

    twoOpt = TwoOpt(distanceMeasure);
}

void VND::run()
{
    solution = twoOpt.run(totalDistance, solution);
    totalDistance = twoOpt.getTotalDistance();
}
