# Covert-Channel Attacks on RISC-V BOOM Core Branch Predictor

This repository contains multiple side-channel attacks performed on different configurations of the branch predictor available in the BOOM core.

## List of Implemented Attacks

- **Branch Direct (BRAD-a and BRAD-b) Attack**
- **Pointer-based Indirect jump with Known targets (PINK) Attack**
- **Predictive Loop (PLoop) Attack**

## Building the Binaries

Before building the binaries, it is essential to have the necessary dependencies installed, as we are cross-compiling the binaries on the host machine. For detailed steps on setting up the required environment and dependencies, refer to the Chipyard Initial Repository Setup documentation: [Initial Repo Setup](https://chipyard.readthedocs.io/en/1.6.2/Chipyard-Basics/Initial-Repo-Setup.html)

First, clone our repository to your workspace, which contains all the source files for the attacks:

`git clone https://github.com/RutvikC/BOOM_BPU_attack.git`

**Note:** The repo [BOOM Speculative Attacks](https://github.com/riscv-boom/boom-attacks/tree/master?tab=readme-ov-file#boom-speculative-attacks) was used to verify the susceptibility of the BOOM core to Spectre attacks. We are using some of the include files from this repository to get the cycle count for our attacks. The repository has already been added as a submodule in our repository, so you only need to pull it and build the binaries:

`cd BOOM_BPU_attack\`

`git submodule update --init`

`make all`

This will compile all the binaries into the bin/ directory.

## Configuration Files

The repository also includes configuration files for different Branch Prediction Unit (BPU) configurations. These files are located in the main branch of the Chipyard repository ([1.6.2](https://github.com/ucb-bar/chipyard/tree/1.6.2)):

* config-mixings.scala
    * Location: `chipyard/generators/boom/src/main/scala/common/config-mixins.scala`
    * Contains class definitions for all possible Branch Prediction configurations.

* BoomConfigs.scala
    * Location: `chipyard/generators/chipyard/src/main/scala/config/BoomConfigs.scala`
    * Incorporates all the BPU configurations from the above file into an actual core tile.

* Configs.scala
    * Location: `chipyard/fpga/src/main/scala/vcu118/Configs.scala`
    * Calls the core tile configurations and applies the necessary tweaks for the VCU118 FPGA. This file can be used to generate the bitstream that runs on the FPGA.

## Running binaries on Verilator

*(Assuming the Initial Chipyard Repo setup has been completed)*
Once the necessary configs are in place in the `BoomConfigs.scala` file, the following command can be run under `sims/verilator` directory:

`make CONFIG=SmallBoomConfigNLP0 run-binary BINARY=<LOCATION_OF_BINARY_FILE> -j8`

## Generating a Bitstream

FPGA prototyping resources are located in the `fpga` directory of the Chipyard project. This includes the `fpga-shells` submodule and the `src` directory with Scala, TCL, and other files. To initialize the `fpga-shells` submodule, run the provided script:

`chipyard/scripts/init-fpga.sh`

To generate a bitstream using Vivado, run this command in the fpga directory:

`make SUB_PROJECT=vcu118 CONFIG=FPGABoomConfigNLP0 bitstream -j8`

The generated bitstream will located at: `generated-src/<LONG_NAME>/obj/*.bit`

## Running Attacks on VCU118 FPGA

We booted Buildroot Linux from an SD card on the VCU118 FPGA, with one partition for Linux and another for the attack binaries. After booting, we ran the attack binaries from the second partition. For setup details, see the [VCU118 Prototyping Guide](https://chipyard.readthedocs.io/en/1.6.2/Prototyping/VCU118.html).