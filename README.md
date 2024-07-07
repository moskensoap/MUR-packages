# Introduction
Just as the [AUR (Arch User Repository)](https://aur.archlinux.org) is a community-maintained repository for [Arch Linux](https://archlinux.org), the MUR (MSYS2 User Repository) serves as an analogous community-driven space for [MSYS2](https://archlinux.org) users.

The MUR aims to address the issue of hidden or deeply nested official package entry points, providing executable wrappers or linkers that simplify the execution of these packages directly from the command line (CMD, PowerShell, or Bash Bash, Zsh, Fish, and more).

Additionally, the MUR houses community-developed tools and repackaged versions of software officially distributed from other sources. These contributions complement the official MSYS2 packages, offering users a more extensive selection of utilities and applications tailored to their specific needs and preferences. By creating executable files that encapsulate the necessary commands to invoke hidden or complex scripts, the MUR makes it easier for users to access and utilize these resources without having to navigate through complex file paths or manual setup processes.

# How to use

## Rules of this repository

1.Package Name of this repository begins with `mur__`.

2.Repackaged binaries are stored in /opt/bin.

3.The original directory structure of repackaged packages is preserved in /opt/share/${pkgname}.

4.Packages which depends or makedepends on repackaged packages, are installed in /opt.

5.Executable linkers are located in appropriate bin directories within the build system structure.

6.Fully compiled original packages, sourced from various repositories or categories, are installed in /usr/local.


## Integrating PATH for Global Access (Optional but Recommended)  
  
By default, binaries in `/opt/bin` and other MSYS2 directories are only accessible within the MSYS2 shell. To make these binaries accessible globally within Windows (e.g., from the Command Prompt or PowerShell), follow these steps to add them to your Windows PATH environment variable:  

1. Navigate to System Properties > Advanced System Settings > Environment Variables.  
2. Under "User Variables" (or "System Variables" if you want the change to apply to all users), select the "Path" variable and click "Edit".  
3. Append the following paths, separated by semicolons (;), to the end of the list:

```
C:\msys64\ucrt64\bin
C:\msys64\mingw64\bin
C:\msys64\mingw32\bin
C:\msys64\clang64\bin
C:\msys64\clang32\bin
C:\msys64\clangarm64\bin
C:\msys64\usr\local\bin
C:\msys64\usr\bin
C:\msys64\bin
C:\msys64\opt\bin
```

**Note**: Adjust the paths as necessary if your MSYS2 installation is located in a different directory.  
 
4. Click "OK" to save your changes and close the dialog boxes.  
 
Additionally, to ensure that MSYS2 can inherit the Windows PATH (e.g., to access Windows programs within MSYS2), you can set the `MSYS2_PATH_TYPE` environment variable to `inherit`.


## Installation

1.Clone this project to your computer by running:

    git clone https://github.com/moskensoap/MUR-packages.git

2.Prepare build enviroment, See the [MSYS2 new package guide](https://www.msys2.org/dev/new-package/) and run

    pacman -S --needed base-devel

3.To build the package, start a shell in an environment you want to build for, change the working directory to the directory of the PKGBUILD.

For mingw_arch, run:

    makepkg-mingw --cleanbuild --syncdeps --force --noconfirm

For msys_arch(no __mingw_arch__ in its PKGBUILD), run:

    makepkg --cleanbuild --syncdeps --force --noconfirm

To solve CRLF error, you may run:

    dos2unix PKGBUILD

4.To install the package, run:

    pacman -U *.pkg.tar.zst

# Packages

## Todo list
- [ ] murpkg: MUR package manager.
- [ ] jdk21-openjdk
- [ ] jdk11-openjdk
- [ ] jdk8-openjdk
- [ ] jre-openjdk
- [ ] jre21-openjdk
- [ ] jre17-openjdk
- [ ] jre11-openjdk
- [ ] jre8-openjdk
- [ ] php8.1
- [ ] php7.3
- [ ] php7.2
- [ ] php7.1
- [ ] php7.0
- [ ] php5.6
- [ ] xdebug8.1
- [ ] xdebug7.3
- [ ] xdebug7.2
- [ ] xdebug7.1
- [ ] xdebug7.0
- [ ] xdebug5.6

## Original packages

[**gradlelink**](./gradlelink/README.md): Creat /usr/bin/gradle.exe linking to /usr/share/java/gradle/bin/gradle

[**helixlink**](./helixlink/README.md): Creat \${MINGW_PREFIX}/bin/hx.exe linking to \${MINGW_PREFIX}/lib/helix/hx.exe (mingw-w64)

[**makelink**](./makelink/README.md): Creat make.exe linking to mingw32-make.exe (mingw-w64)

**murclean**: List and clean up cache, logs, and other files not owned by any package.
```
Usage:
        murclean list [argument]: cache, logs, and other files not owned by any package.
        murclean clean [argument]: remove cache, logs, and other files not owned by any package.
argument:
        clang32 clang64 clangarm64
        mingw32 mingw64 ucrt64
        usr     opt     tmp
        all (for all above if default)
```
**optfirst**: Locally sets PATH to /opt/bin:$PATH and runs \<command\> with the provided arguments.
```
Usage: optfirst <command> [args...]
This program locally sets PATH to /opt/bin:$PATH and runs <command> with the provided arguments.
```
```
usr
└── local
    ├── bin
    │   ├── clang32first.exe
    │   ├── clang64first.exe
    │   ├── clangarm64first.exe
    │   ├── mingw32first.exe
    │   ├── mingw64first.exe
    │   ├── optfirst.exe
    │   ├── ucrt64first.exe
    │   ├── usrfirst.exe
    │   └── usrlocalfirst.exe
    └── share
        └── licenses
            └── mur__optfirst
                └── LICENSE
```
Note: Nested calls are allowed.

## repackaged package

__composer__: Dependency Manager for PHP

__jdk-openjdk__: OpenJDK Java development kit

Note:
```
Usage:
        setversion-jdk <version>
version:
        jdk<version>-openjdk you installed form MUR-PACKAGES
        latest for jdk-openjdk
example:
        setversion-jdk 8
        setversion-jdk 11
        setversion-jdk 17
        setversion-jdk 21
        setversion-jdk latest
```
__jdtls__: Java language server

__lua-language-server__: A language server that offers Lua language support - programmed in Lua

__marksman__: Write Markdown with code assist and intelligence in the comfort of your favourite editor.

__omnisharp-roslyn__: OmniSharp server (HTTP, STDIO) based on Roslyn workspaces

__omnisharp-roslyn-net6.0__: OmniSharp server (HTTP, STDIO) based on Roslyn workspaces (net6.0)

__pandoc__: Universal markup converter.

__php__: php for Windows x64 Thread Safe

Note:
```
Usage:
        setversion-php <version>
version:
        php<version> you installed form MUR-PACKAGES
        latest for php
example:
        setversion-php 5.6
        setversion-php 7.0
        setversion-php 7.4
        setversion-php 8.0
        setversion-php latest
```

__xdebug__: Xdebug — Step Debugger and Debugging Aid for PHP

__zig__: General-purpose programming language and toolchain for maintaining robust, optimal, and reusable software.

__zls__: A Zig language server supporting Zig developers with features like autocomplete and goto definition

# Contributing

Contributions are welcome! Please submit pull requests or open issues for any improvements or bug fixes.

Adding new package: fork this program, add 

# License

This project is licensed under the MIT License - see the LICENSE file for details.