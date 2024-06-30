# Functions

**gradle**: Creat /usr/bin/gradle.exe linking to /usr/share/java/gradle/bin/gradle

**helix**: Creat MINGW_PREFIX/bin/hx.exe linking to MINGW_PREFIX/lib/helix/hx.exe (mingw-w64)

**jdk-openjdk**: OpenJDK Java development kit

**lua-language-server**: A language server that offers Lua language support - programmed in Lua

**makelink**: Creat make.exe linking to mingw32-make.exe (mingw-w64)

**marksman**: Write Markdown with code assist and intelligence in the comfort of your favourite editor.

**omnisharp-roslyn**: OmniSharp server (HTTP, STDIO) based on Roslyn workspaces

**omnisharp-roslyn-net6.0**: OmniSharp server (HTTP, STDIO) based on Roslyn workspaces (net6.0)

**pandoc**: Universal markup converter.

**zig**: General-purpose programming language and toolchain for maintaining robust, optimal, and reusable software.

**zls**: A Zig language server supporting Zig developers with features like autocomplete and goto definition
    

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