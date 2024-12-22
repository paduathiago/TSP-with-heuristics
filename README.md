# TSP-with-heuristics
This repo implements a series of heuristics to solve TSP from different perspectives, in c++.

## Heuristics implemented
- Nearest Neighbour (constructive heuristic)
- VND (Variable Neighbourhood Descent) with 2-opt and 3-opt
- ILS (Iterated Local Search) with 3-opt and a boltzmann distribution based acceptance criterion

A full report of the project is available in the file `report.ipynb`. The report contains a detailed explanation of the implemented heuristics, the results obtained and a discussion of the results. It is written in a Jupyter notebook, so you can run it in your local machine if you have Jupyter installed. The language used in the report is Portuguese.

To run the code, a makefile is provided. You can run the following command to compile the code:
```bash
make
```
To run the code, you can use the following command:
```bash
./heuristic <input_file> <chosen_heuristic>
```
if you want to run the code with the Iterated Local Search metaheuristic, you can use the following command:
```bash
./heuristic <input_file> ILS <initial_temperature> <cooling_rate>
```
The folder `instances` contains some instances that you can use to test the code.
