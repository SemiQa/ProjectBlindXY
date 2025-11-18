# BlindWatch

BlindWatch is an assistive device for the visually impaired that helps with navigation.

## Setup for VSCode

* Install ModusToolbox Setup from
https://softwaretools.infineon.com/tools/com.ifx.tb.tool.modustoolboxsetup

* Using ModusToolbox Setup install Arm GNU Toolchain, ModusToolbox Tools Package and ModusToolbox Programming tools

* Install make

* Install the ModusToolbox Assistant extension in VSCode




* Clone the repository

* CD into the repository

* Run
```console
make getlibs
```

* Run 
```console
make vscode
```

* Open the project with VSCode

* To build, clean, program, erase etc. use tasks defined in the .vscode folder

* Debugging procedure is defined in the launch.json file in the .vscode folder

## Hardware

This firmware is meant to run on the PSoC6 AI Evaluation Kit by Infineon (CY8CKIT-062S2-AI)

## Setup for tests

* Install python

* Install meson and ninja through pip

* Install needed components through MSYS2

```console
pacman -S mingw-w64-x86_64-clang
pacman -S mingw-w64-x86_64-gtest
pacman -S mingw-w64-x86_64-pkg-config
pacman -S mingw-w64-x86_64-compiler-rt
```

* Add MSYS2 mingw64 bin folder to environmental variables

* Install gcovr through pip

* In project directory run

```console
meson setup -Db_coverage=true --native-file=llvm.ini out/UT
```

* To test run 
```console
ninja test -C out/UT
```
#### Model note
Please note that this repository, due to licensing, lacks model weights, review the provided README.md file with instruction on how to generate model.


#### Instalation note for ModusToolbox when doing remote development
Sometimes (in fishshell)when connected through ssh enviromental variables for modustoolbox location can not set causing `make` to fail.
Below is temporary fix,(for default location) add this line to `Makefile`
```
CY_TOOLS_PATHS+=/opt/Tools/ModusToolbox/tools_*
```

## License

The BlindWatch application code (navigation logic, message system, threads and
other files under `Sources/` except third-party drivers and generated machine
learning models) is licensed under the GNU General Public License, version 3
or (at your option) any later version. See `LICENSE-GPL-3.0`.

This GPL licensing applies **only** to code authored for BlindWatch in this
repository. It does **not** change the licenses of any third-party or vendor
components that are included or used by the build.

This project depends on the Infineon/Cypress ModusToolbox ecosystem, including
board support packages (BSP), hardware abstraction layers (HAL/PDL), and other
platform-specific components. Those components are **not** licensed under
GPL-3.0; they remain under the Cypress (Infineon) End User License Agreement
or Apache-2.0 as provided by the vendor. See `LICENSE` in this repository and
the license files within `mtb_shared/`.

Additional third-party libraries (for example FreeRTOS, CMSIS-DSP, BMI270
SensorAPI, and XENSIV BGT60TRXX drivers) are brought in via `.mtb` dependency
files in `deps/`. Their respective licenses are provided in the corresponding
directories under `mtb_shared/` or in the upstream repositories. You must
comply with those licenses when using or redistributing BlindWatch.