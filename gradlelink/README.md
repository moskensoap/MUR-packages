# Installation
1.Clone this project to your computer by running:

    git clone https://github.com/moskensoap/gradlelink.git

2.Prepare build enviroment, See the [MSYS2 new package guide](https://www.msys2.org/dev/new-package/) and run

    pacman -S --needed base-devel

3.To build the package, start a shell in an environment you want to build for, change the working directory to the directory of the PKGBUILD(i.e. run `cd zls-PKGBUILD`), and run:

    makepkg --cleanbuild --syncdeps --force --noconfirm

To solve CRLF error, you may run:

    dos2unix PKGBUILD

4.To install the package, run:

    pacman -U *.pkg.tar.zst