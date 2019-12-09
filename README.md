# Disease-Modeling

Simple model of disease transmission. Model is written in C++. Analysis and plots are generated with Python notebooks.

### Instructions

Compile:

```g++ ./main.cpp```

Run:

```./.a.exe```

### Output files

```output.txt``` contains data output from Experiment 1. Each line represents a trial with a certain probability of infection. Each line contains a timeseries where data point i represents the size of the population at day i.

```outputWithVaccintation.txt``` contains data output from Experiment 2. Each line represents a trial with a certain amount of vaccinations. Each line contains a timeseries where data point i represents the size of the population at day i.

### Report

```GenerateReport.ipynb``` is used to read in data and generate plots. The plots and summary are contained in ```Report.pdf```.