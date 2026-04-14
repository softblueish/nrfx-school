# School assignments involving the nRF-series of chips

<img width="1480" height="224" alt="image" src="https://github.com/user-attachments/assets/a5f10781-f853-4f7e-9eca-f13b9e2f43e8" />

<img width="1353" height="227" alt="image" src="https://github.com/user-attachments/assets/193e8c98-399b-49ff-9e4d-d405e1fa9c68" />


# Below is the README for nrfx

## Overview

nrfx is a standalone set of drivers for peripherals present in Nordic
Semiconductor's SoCs and SiPs. It originated as an extract from the nRF5 SDK.
The intention was to provide drivers that can be used in various environments
without the necessity to integrate other parts of the SDK into them.
For the user's convenience, the drivers come with the MDK package. This package
contains definitions of register structures and bitfields for all supported
SoCs, as well as startup and initialization files for them.

## Supported SoCs and SiPs

* nRF51 Series
* nRF52805
* nRF52810
* nRF52811
* nRF52820
* nRF52832
* nRF52833
* nRF52840
* nRF5340
* nRF9131
* nRF9160
* nRF9161

## Directories

```
 .
 ├── doc             # Project documentation files
 ├── drivers         # nrfx driver files
 │   ├── include     # nrfx driver headers
 │   └── src         # nrfx driver sources
 ├── hal             # Hardware Access Layer files
 ├── haly            # Extended Hardware Access Layer files
 ├── helpers         # nrfx driver helper files
 ├── mdk             # nRF MDK files
 ├── soc             # SoC specific files
 └── templates       # Templates of nrfx integration files
```

## Generating documentation

nrfx documentation is available in the `doc\html` folder of the release package.

Refer to [this guide](doc/README.md) for more details.
