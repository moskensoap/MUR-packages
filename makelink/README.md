# Instruction
Create make.exe linking to mingw32-make.exe in the ucrt64, mingw32, mingw64, clang32, clang64, and clangarm64 sub-environments of MSYS2. This project will help you create a local pacman package to install, setting `make.exe` as an alias of `mingw32-make.exe` to build a common environment between Windows and Linux.

# Installation
1.Clone this project to your computer by running:

    git clone https://github.com/moskensoap/makelink.git

2.Prepare build enviroment, See the [MSYS2 new package guide](https://www.msys2.org/dev/new-package/) and run

    pacman -S --needed base-devel

3.To build the package, start a shell in an environment you want to build for, change the working directory to the directory of the PKGBUILD(i.e. run `cd makelink`), and run:

    makepkg-mingw --cleanbuild --syncdeps --force --noconfirm

To solve CRLF error, you may run:

    dos2unix PKGBUILD

4.You should check the downloaded source code files, `./src/makelink-version/main.c` and `./src/makelink-version/Makefile`, to ensure everything is correct.

5.To install the package, run:

    pacman -U *.pkg.tar.zst

# Contributing
Contributions are welcome! Please submit pull requests or open issues for any improvements or bug fixes.

# License
This project is licensed under the MIT License - see the LICENSE file for details.
