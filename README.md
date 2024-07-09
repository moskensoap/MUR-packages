# Introduction

Just as the [AUR (Arch User Repository)](https://aur.archlinux.org) is a community-maintained repository for [Arch Linux](https://archlinux.org), the MUR (MSYS2 User Repository) is a community-driven space for [MSYS2](https://archlinux.org) users.

The MUR helps users access official packages by providing simple __executable links__. This makes it easy to run these packages directly from the command line (CMD, PowerShell, Bash, Zsh, Fish, and more).

The MUR also repackages software from their official sources, providing __executable wrappers__ to make these packages easy to use while maintaining their Windows file structure and allowing installation in MSYS2.

Additionally, the MUR offers tools developed by the community.

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
The version config file is stored in `/home/.mur/setversion/jdk-openjdk.txt`. You need to manually remove it when uninstalling jdk-openjdk.
```
PS C:\Users\username> javalatest --version
openjdk 22 2024-03-19
OpenJDK Runtime Environment (build 22+36-2370)
OpenJDK 64-Bit Server VM (build 22+36-2370, mixed mode, sharing)
PS C:\Users\username> java17 --version
openjdk 17 2021-09-14
OpenJDK Runtime Environment (build 17+35-2724)
OpenJDK 64-Bit Server VM (build 17+35-2724, mixed mode, sharing)
PS C:\Users\username> java --version
openjdk 22 2024-03-19
OpenJDK Runtime Environment (build 22+36-2370)
OpenJDK 64-Bit Server VM (build 22+36-2370, mixed mode, sharing)
PS C:\Users\username> setversion-jdk 17
PS C:\Users\username> java --version
openjdk 17 2021-09-14
OpenJDK Runtime Environment (build 17+35-2724)
OpenJDK 64-Bit Server VM (build 17+35-2724, mixed mode, sharing)
PS C:\Users\username> setversion-jdk latest
PS C:\Users\username> java --version
openjdk 22 2024-03-19
OpenJDK Runtime Environment (build 22+36-2370)
OpenJDK 64-Bit Server VM (build 22+36-2370, mixed mode, sharing)
```
__jdtls__: Java language server

__lua-language-server__: A language server that offers Lua language support - programmed in Lua

__marksman__: Write Markdown with code assist and intelligence in the comfort of your favourite editor.

__marktext__: A simple and elegant markdown editor, available for Linux, macOS and Windows.

Note: 1.type `WINDOWS` key 2.input `marktext` 3.type `ENTER` key

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
The version config file is stored in `/home/.mur/setversion/php.txt`. You need to manually remove it when uninstalling php.

Scan this dir for additional .ini files => /opt/share/mur__php/conf.d:/home/.mur/php
/home/.mur/php is convenient for users.
Note: .ini scan dir of php8.0 => /opt/share/mur__php8.0/conf.d:/home/.mur/php8.0
```
PS C:\Users\username> phplatest --version
PHP 8.2.20 (cli) (built: Jun  4 2024 17:50:12) (ZTS Visual C++ 2019 x64)
Copyright (c) The PHP Group
Zend Engine v4.2.20, Copyright (c) Zend Technologies
    with Zend OPcache v8.2.20, Copyright (c), by Zend Technologies
    with Xdebug v3.3.2, Copyright (c) 2002-2024, by Derick Rethans
PS C:\Users\username> php8.0 --version
PHP 8.0.30 (cli) (built: Sep  1 2023 14:15:38) ( ZTS Visual C++ 2019 x64 )
Copyright (c) The PHP Group
Zend Engine v4.0.30, Copyright (c) Zend Technologies
    with Zend OPcache v8.0.30, Copyright (c), by Zend Technologies
    with Xdebug v3.3.2, Copyright (c) 2002-2024, by Derick Rethans
PS C:\Users\username> php --version
PHP 8.2.20 (cli) (built: Jun  4 2024 17:50:12) (ZTS Visual C++ 2019 x64)
Copyright (c) The PHP Group
Zend Engine v4.2.20, Copyright (c) Zend Technologies
    with Zend OPcache v8.2.20, Copyright (c), by Zend Technologies
    with Xdebug v3.3.2, Copyright (c) 2002-2024, by Derick Rethans
PS C:\Users\username> setversion-php 8.0
PS C:\Users\username> php --version
PHP 8.0.30 (cli) (built: Sep  1 2023 14:15:38) ( ZTS Visual C++ 2019 x64 )
Copyright (c) The PHP Group
Zend Engine v4.0.30, Copyright (c) Zend Technologies
    with Zend OPcache v8.0.30, Copyright (c), by Zend Technologies
    with Xdebug v3.3.2, Copyright (c) 2002-2024, by Derick Rethans
PS C:\Users\username> setversion-php latest
PS C:\Users\username> php --version
PHP 8.2.20 (cli) (built: Jun  4 2024 17:50:12) (ZTS Visual C++ 2019 x64)
Copyright (c) The PHP Group
Zend Engine v4.2.20, Copyright (c) Zend Technologies
    with Zend OPcache v8.2.20, Copyright (c), by Zend Technologies
    with Xdebug v3.3.2, Copyright (c) 2002-2024, by Derick Rethans
```

__xdebug__: Xdebug — Step Debugger and Debugging Aid for PHP

__zig__: General-purpose programming language and toolchain for maintaining robust, optimal, and reusable software.

__zls__: A Zig language server supporting Zig developers with features like autocomplete and goto definition

# Contributing

Contributions are welcome! Please submit pull requests or open issues for any improvements or bug fixes.

Adding new package: fork this program, add 

# License

This project is licensed under the MIT License - see the LICENSE file for details.