# Introduce

## original packages



## repackages


## repackages-portable

    

# Installation

1.Clone this project to your computer by running:

    git clone https://github.com/moskensoap/MUR-packages.git

2.Prepare build enviroment, See the [MSYS2 new package guide](https://www.msys2.org/dev/new-package/) and run

    pacman -S --needed base-devel

3.To build the package, start a shell in an environment you want to build for, change the working directory to the directory of the PKGBUILD.

For mingw_arch, run:

    makepkg-mingw --cleanbuild --syncdeps --force --noconfirm

For none_mingw_arch, run:

    makepkg --cleanbuild --syncdeps --force --noconfirm

To solve CRLF error, you may run:

    dos2unix PKGBUILD

4.To install the package, run:

    pacman -U *.pkg.tar.zst

# Contributing

Contributions are welcome! Please submit pull requests or open issues for any improvements or bug fixes.

# License

This project is licensed under the MIT License - see the LICENSE file for details.