| Style | Unit Tests | Code Size |
| ----- | ---------- | --------- |
| [![Build status](https://badge.buildkite.com/c07c5d06b8f75b27f3b2a13ed6ab44981e73a564cb60fef9ac.svg?branch=development)](https://buildkite.com/blue-white-inc/code-style) | [![Build status](https://badge.buildkite.com/4b3ad3e6ffbe2f1c7730627a1bac115c0b54d2e0b1931e31fb.svg?branch=development)](https://buildkite.com/blue-white-inc/s6-unit-tests) | [![Build status](https://badge.buildkite.com/dd9b48201b00eb33e9c7a611c6d6783773bf50ffd2df9e2aad.svg?branch=development)](https://buildkite.com/blue-white-inc/s6-code-size) |

# S6 Chemical Flow Sensor

The S6 Chemical Flow Sensor is designed to accurately verify and measure chemical injection. This code base will encompassed various models of the S6 product line. Detailed functionality of the S6 platform can be found [Functional Spec : Error Handling](https://github.com/blue-white-inc/s6/wiki/document.pdf)

## Getting Started

You will need the toolchain installed, an `S6` circuit board, a USB to RS-232 adaptor that connects to `J9`, a Modifed Programmer Board setup correctly and a configured target in the `platformio.ini` for you environment.

### Toolchain

 - [PlatformIO](http://docs.platformio.org/en/latest/ide/atom.html#installation) either `ATOM` or `VSCode` can be used as an IDE.
 - [ARM Mbed](https://www.mbed.com/en/) using a custom target for the [STM32 MCU L072rb](http://www.st.com/en/microcontrollers/stm32l072rb.html)
 - Code is written in C++

### USB to RS-232 Adaptor

Using a standard USB to RS-232 adaptor work with another developer on the team to copy a DB-9 connector for the S6 board to connect to `J9` on the board.

### Modified Programmer Board

A copper wire was soldered on the back of the nucleo_f411re from SWD's pin-1 (top most pin) to the VCC pin on the mini USB port. This is done in order to transfer power from the nucleo_f411re onto the GP30 microcontroller.

![Soldering on the nucleo_f411re](https://gist.githubusercontent.com/jdinh1/68359bf68abc53b40daa15864d63e560/raw/5cbfda0069f84d4909b696780246b8b16d0be1ee/20171003_111221.jpg)

### Installing

A step by step guide for getting a development env running.

#### Install the PlatformIO IDE for Atom

[PlatformIO for Atom](http://docs.platformio.org/en/latest/ide/atom.html#installation).

#### Install the PlatformIO IDE for VSCode

[PlatformIO for VSCode](http://docs.platformio.org/en/latest/ide/vscode.html#installation).

#### Create a PIO account

From the command line:

```
# Create PIO Account
pio account register

# Login with credentials (will be sent to your e-mail)
pio account login

# Change temporary password (from e-mail) to permanent
pio account password
```

Once you have an account created, please work with Norm to gain a `Pro` license so that you can run unit tests.

#### Extra steps for Windows

 - Install [Git for Windows](https://git-scm.com/download/win).
 - Install [ST-LINK USB DRIVER](http://www.st.com/en/development-tools/stsw-link009.html).
 - (Optional) Upgrade [ST-LINK Firmware](http://www.st.com/en/development-tools/stsw-link007.html).

#### Setting up the Custom target

 - Add [platform ststm32-bw](https://github.com/blue-white-inc/platform-ststm32) into project. (A PIO account is needed for this step)

#### Adding SSH key to SSH-Agent
  An SSH key might be required to install the framework mbed for Blue-White's stm32-bw platform. Follow the link below for instructions on setting up an SSH key.
 - https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/

#### PlatformIO Target for your Environment

PlatformIO heavily makes use of a serial port connected to the target circuit board to upload code, run test and debug the system. Since the device names are different for each developer, it's easier to add a specfic target for your environment. An example target looks like:

```
[env:generic_l072rb]
platform = ststm32-bw
board = generic_l072rb
framework = mbed
build_flags = -DS6_V1
test_port = /dev/cu.usbserial-A504XIT9
upload_port = /Volumes/NODE_F411RE/
```

## Running the tests

From the command line not limiting any tests:

```pio test -e generic_l072rb```

From the command line limiting the tests to only the GP30 suite of tests:

```pio test -e generic_l072rb -f GP30```


### Coding style

A clang-format profile is used for formatting C++ codes. The coding style used is based on LLVM C++ style with a few minor adjustments.

Specific code formating can be found in:

```
.clang-format
```

On rare occasions ```// clang-format off``` tags will be used to manually format areas of the code the auto formatting does a particually poor job with. This should be the expection vs the rule.

Optionally the `clang-format` package can be installed for Atom for in IDE formating.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/blue-white-inc/s6/tags).

## Build Flags

We currently have two environments that we target:

### nucleo_f746zg

```
#ifdef S6_SHEILD
// Code for the nucleo_f746zg
#endif
```

### L072RB

```
#ifdef S6_V1
// Code for the L072RB
#endif
```
