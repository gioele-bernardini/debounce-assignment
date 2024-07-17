# Debounce Assignment

This repository contains the source code for the Debounce Assignment, completed as part of the hiring process at Bytem.

## Structure

```
.
├── ButtonBounce.ino
├── plotter
│   ├── DebouncePlotter.ino
│   ├── main.cpp
│   ├── Makefile
│   └── NoDebouncePlotter.ino
├── README.md
├── Report.pdf
└── solutions
    ├── DebouncePostChange.ino
    ├── DebouncePreChange.ino
    ├── DebounceStableReadings.ino
    └── estimation
        └── DebounceEstimate.ino
```

### Folder Details

#### Root Directory

- **ButtonBounce.ino**: Contains the standard code to configure the Arduino to read the button and turn on the LED accordingly. The button debounce is not handled in any way.
- **README.md**: This file, providing an overview of the project.
- **Report.pdf**: Contains the circuit schematic as well as the considerations and observations made during the execution of the project.

#### plotter/

- **DebouncePlotter.ino**: Contains code to plot debounce behavior. It involves collecting and plotting the readings of a button press to visualize debounce.
- **main.cpp**: The main source file for the plotter application. Contains the core logic and entry point for the plotting application.
- **Makefile**: Contains build instructions for the project. It defines how to compile and link the application.
- **NoDebouncePlotter.ino**: Contains code to plot the behavior of a button press without debounce, similar to what happens with the DebouncePlotter.ino file. However, in this file, the debounce logic is handled.

#### solutions/

- **DebouncePostChange.ino**: Implements a debounce solution that is applied after a change is detected. This approach involves waiting for a period of stability after an initial change before confirming the new state.
- **DebouncePreChange.ino**: Implements a debounce solution that is applied before a change is detected. This approach involves checking for stability before acknowledging a change has occurred.
- **DebounceStableReadings.ino**: Implements a debounce solution based on stable readings. The implementation involves reading a digital input multiple times to ensure the value is stable before accepting it as an input change.
- **estimation/**
  - **DebounceEstimate.ino**: Implements an estimation method for debounce. It involves measuring the time between input changes to estimate the debounce period and adjust the debounce logic accordingly.

## Additional Branches

### Alternative Debounce Algorithm

There is an additional branch named `estimate-dev` where an alternative algorithm for `DebounceEstimate.ino` has been tested. Due to time costraints it is *not* fully working, but it might be a good starting point for what will come next.
To explore this alternative implementation, you can check out the branch using the following commands:

```sh
git checkout estimate-dev
```

In this branch, the `DebounceEstimate.ino` file contains a different approach to debounce estimation, which you can compare with the main implementation.

## Getting Started

To get started with this project, you can clone the repository and navigate to the respective directories to explore the code. Make sure you have the necessary tools and dependencies installed to run the scripts and compile the code.

### Prerequisites

- Arduino IDE for .ino files
- GCC or any C++ compiler for .cpp files
- Make for running the Makefile

### Installation

1. Clone the repository:
   ```sh
   git clone hgit@github.com:gioele-bernardini/debounce-assignment.git
   cd debounce-assignment
   ```

2. Navigate to the `plotter` directory and build the application:
   ```sh
   cd plotter
   make
   ```

### Usage

Before running the code, make sure to set up the circuit correctly as shown in the `report.pdf` file. This file will provide the schematic for the breadboard setup, which is crucial for the correct functioning of the debounce logic.

- **ButtonBounce.ino**: Upload this file to your Arduino to test basic button debounce.
- **plotter**: Use the scripts and executables in this directory to visualize debounce behavior.
- **solutions**: Explore different debounce solutions and choose the one that best fits your needs.

## Acknowledgments

This project was completed as part of the hiring process at Bytem.
Special thanks to the Bytem team for the opportunity and guidance.

