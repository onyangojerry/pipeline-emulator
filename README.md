# Pipeline Emulator

A lightweight CPU pipeline emulator written in C++. This project simulates the behavior of a pipelined processor, enabling step-by-step inspection of instruction execution, hazards, forwarding, and control flow. It is intended for educational use in computer architecture courses or as a foundation for more advanced CPU modeling.

## Features

- Instruction Fetch–Decode–Execute pipeline with support for multi-stage execution
- Single-cycle, multi-cycle, and pipelined processor models
- Hazard detection and forwarding logic to handle data dependencies
- Branch and control hazard handling
- Flexible instruction memory loading from test programs
- Modular design to allow incremental development and testing of each stage

## Repository Structure

```text
pipeline-emulator/
├── src/                # Core source code for processor components and pipeline stages
├── solutions/          # Example implementations or reference solutions
├── test-progs/         # Test programs to run on the emulator
├── Makefile            # Build instructions
└── ask-vbisc-oracle.py # Utility script (likely for querying instruction behavior)

'''

# Clone the repository
git clone https://github.com/onyangojerry/pipeline-emulator.git
cd pipeline-emulator

# Build using Makefile
make


