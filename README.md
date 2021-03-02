<h1 align="center">
    telekom pxt-ki-in-schulen
</h1>

<p align="center">
    <a href="https://github.com/telekom/pxt-ki-in-schulen/commits/" title="Last Commit"><img src="https://img.shields.io/github/last-commit/telekom/pxt-ki-in-schulen?style=flat"></a>
    <a href="https://github.com/telekom/pxt-ki-in-schulen/issues" title="Open Issues"><img src="https://img.shields.io/github/issues/telekom/pxt-ki-in-schulen?style=flat"></a>
    <a href="https://github.com/telekom/pxt-ki-in-schulen/blob/master/LICENSE" title="License"><img src="https://img.shields.io/badge/License-MIT-green.svg?style=flat"></a>
</p>

This project implements KI (neural networks) extension blocks for the Calliope Mini MakeCode Editor.

## Infos for Developers

* https://makecode.com/extensions/getting-started/vscode
* https://makecode.com/extensions/getting-started/simple-extension
* https://learn.sparkfun.com/tutorials/how-to-create-a-makecode-package-for-microbit/all
* https://github.com/sparkfun/pxt-gator-light
* https://forum.calliope.cc/t/makecode-erweiterungen-fuer-groove-sensoren-in-c/1363

## build

### prerequisite

see: https://makecode.com/cli

install NodeJS: https://nodejs.org/
12.17.0 LTS

npm install -g pxt

install CMake: https://cmake.org/download/
https://github.com/Kitware/CMake/releases/download/v3.17.3/cmake-3.17.3-win64-x64.msi

install ninja: https://github.com/martine/ninja/releases/download/v1.5.3/ninja-win.zip

install cpp  arm-none-eabi-gcc cross compiler: https://launchpad.net/gcc-arm-embedded
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads

install srecord
https://sourceforge.net/projects/srecord/files/srecord-win32/1.64/

### install microbit

install pxt-microbit, runs server, create project, modify project and build from cli:

```
(yotta) E:\CALLIOPE>mkdir pxt-microbit
(yotta) E:\CALLIOPE>cd pxt-microbit
(yotta) E:\CALLIOPE\pxt-microbit>pxt target microbit
        ... downloads ...

(yotta) E:\CALLIOPE\pxt-microbit>pxt serve
        ... create project "nntest2", edit files, exit browser, <Ctrl>-'C' ...

(yotta) E:\CALLIOPE\pxt-microbit>cd projects\nntest2
(yotta) E:\CALLIOPE\pxt-microbit\projects\nntest2>pxt install
Using target microbit with build engine yotta
  target: v3.0.1 E:\CALLIOPE\pxt-microbit\node_modules\pxt-microbit
  pxt-core: v5.37.83 E:\CALLIOPE\pxt-microbit\node_modules\pxt-core
installing dependencies...

(yotta) E:\CALLIOPE\pxt-microbit\projects\nntest2>pxt build
Using target microbit with build engine yotta
  target: v3.0.1 E:\CALLIOPE\pxt-microbit\node_modules\pxt-microbit
  pxt-core: v5.37.83 E:\CALLIOPE\pxt-microbit\node_modules\pxt-core
building E:\CALLIOPE\pxt-microbit\projects\nntest2

(yotta) E:\CALLIOPE\pxt-microbit\projects\nntest2>copy built\binary.hex G:\
        1 Datei(en) kopiert.
        ... calliope mini runs newest code ...
```

Remark: when using pxt-calliope as target the build fails with the message file "device.h" not found.

### build from fresh checkout



```
(yotta) E:\CALLIOPE\pxt-microbit\projects>git clone https://github.com/ferenc-hechler/pxt-nntest.git

(yotta) E:\CALLIOPE\pxt-microbit\projects>cd pxt-nntest

(yotta) E:\CALLIOPE\pxt-microbit\projects\pxt-nntest>pxt install
Using target microbit with build engine yotta
  target: v3.0.1 E:\CALLIOPE\pxt-microbit\node_modules\pxt-microbit
  pxt-core: v5.37.83 E:\CALLIOPE\pxt-microbit\node_modules\pxt-core
installing dependencies...

(yotta) E:\CALLIOPE\pxt-microbit\projects\pxt-nntest>pxt build
Using target microbit with build engine yotta
  target: v3.0.1 E:\CALLIOPE\pxt-microbit\node_modules\pxt-microbit
  pxt-core: v5.37.83 E:\CALLIOPE\pxt-microbit\node_modules\pxt-core
building E:\CALLIOPE\pxt-microbit\projects\pxt-nntest
polling C++ build https://makecode.com/compile/f60db3bb2519ae8c63ba832606daf5a8ced182d2a852e30de65bf9046491946b.json
polling C++ build https://makecode.com/compile/f60db3bb2519ae8c63ba832606daf5a8ced182d2a852e30de65bf9046491946b.json
build log https://makecode.com/compile/f60db3bb2519ae8c63ba832606daf5a8ced182d2a852e30de65bf9046491946b.log
fetching https://pxt.azureedge.net/compile/f60db3bb2519ae8c63ba832606daf5a8ced182d2a852e30de65bf9046491946b.hex

(yotta) E:\CALLIOPE\pxt-microbit\projects\pxt-nntest>copy built\binary.hex g:\
        1 Datei(en) kopiert.
```



## Supported targets

* for PXT/microbit
* for PXT/calliope


## Sources

the initial sources for creating a MakeCode Extension have been taken form the repository 
https://github.com/sparkfun/pxt-gator-light


## Licensing

Copyright (c) 2020 Deutsche Telekom AG.
Copyright (c) 2017 SparkFun Electronics (see above **Sources**).


Licensed under the **MIT License** (the "License"); you may not use this file except in compliance with the License.

You may obtain a copy of the License by reviewing the file [LICENSE](./LICENSE) in the repository.

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the [LICENSE](./LICENSE) for the specific language governing permissions and limitations under the License.



