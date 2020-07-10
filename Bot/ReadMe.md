## Contract Bridge Playing Bot

This code uses modified version of Bo haguland's DDS and Thomas Andrews Deal for Monte Carlo Simulation of Declarers play.

**Prerequisites :**
- Deal Generator used in the project needs python>=3.6

**Files :**
- `mcsolver.cpp` : Game code.
- `SolverBoardPBN` : DDS Executable.
- `bridgebot` : Game Executable.

**Instructions :**
1. Run `./install.sh` to install necessary packages.
2. Run `make clean` to clean the directory.
2. Run `make`.
3. Run `./bridgebot` to start playing the game.

**Example :**
- Trump Suit: 4
- First Hand: 1
- Declarer:   2
- Deal in PBN format: .63.AKQ987.A9732 A8654.KQ5.T.QJT6 J973.J98742.3.K4 KQT2.AT.J6542.85


**Deal Generator :**
https://github.com/anntzer/redeal

**DDS :**
https://github.com/dds-bridge/dds

