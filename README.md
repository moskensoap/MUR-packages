# Introduction

## Overview

Based on [MSYS2](https://www.msys2.org) and its pacman, MUR (MSYS2 User Repository) installs and provides rolling upgrades for packages on Windows.

MUR focuses on development tools that cannot be compiled via MSYS2 from source code yet.

MUR builds `executable wrappers` to run binaries of repackaged packages from their official sites while maintaining their Windows file structure and installing them in MSYS2.

## Classes:

1.Programming Languages:

Java (and version control), PHP (and version control), Python (and version control), Zig.

2.LSP (Language Server Protocol):

jdtls, lua-language-server, marksman, omnisharp-roslyn, zls.

3.Development Tools:

composer, lf, marktext (GUI), pandoc, xdebug.

4.Utilities:

gradlelink, helixlink, makelink, murclean, murpkg, optfirst.

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
  
### murpkg  
  
[murpkg](https://github.com/moskensoap/murpkg) is the package manager for this repository. It can add other GitHub repositories if their PKGBUILD files' `pkgname` contains `__`.  
  
Using murpkg to automatically install, remove, and upgrade packages is recommended. Additionally, murpkg itself is available in this repository and can be upgraded using murpkg.

First, you should manually install murpkg by following the steps below.

### Manual Installation

1.Clone this project to your computer by running:

    git clone https://github.com/moskensoap/MUR-packages.git

2.Prepare build enviroment, See the [MSYS2 new package guide](https://www.msys2.org/dev/new-package/) and run

    pacman -S --needed base-devel

3.To build the package, start a shell in an environment you want to build for, change the working directory to the directory of the PKGBUILD. (Note: murpkg belongs to msys2_arch, and you should open a MSYS shell to build)

* Convert CRLF to LF by running:
```
    find . -maxdepth 1 -type f -exec dos2unix {} +
```
* For mingw_arch, run:
```
    makepkg-mingw --cleanbuild --syncdeps --force --noconfirm
```
* For msys_arch(no __mingw_arch__ in its PKGBUILD), run:
```
    makepkg --cleanbuild --syncdeps --force --noconfirm
```
To solve CRLF error, you may run:
```
    dos2unix PKGBUILD
```
4.To install the package, run:

    pacman -U *.pkg.tar.zst

# Packages

## Todo list
- [x] murpkg: MUR package manager.
- [x] jdk-openjdk
- [x] jdk21-openjdk
- [x] jdk17-openjdk
- [x] jdk11-openjdk
- [x] jdk8-openjdk
- [x] jre-openjdk
- [x] jre21-openjdk
- [x] jre17-openjdk
- [x] jre11-openjdk
- [x] jre8-openjdk
- [x] php
- [x] php8.1
- [x] php8.0
- [x] php7.4
- [x] php7.3
- [x] php7.2
- [x] php7.1
- [x] php7.0
- [x] php5.6
- [x] xdebug8.1
- [x] xdebug7.3
- [x] xdebug7.2
- [x] xdebug7.1
- [x] xdebug7.0
- [x] xdebug5.6
- [x] pythonembed
- [x] pythonembed311
- [x] pythonembed310
- [x] pythonembed39
- [x] pythonembed38



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
**murpkg**: MUR-package manager
```
Usage:

        murpkg command [arguments]

The commands are:

        repo init       Initialize a new repository.
        repo list       List all available repositories.
        repo add        Add a new repository.
        repo remove     Remove an existing repository.
        update          Update the package database.
        list            List all installed packages.
        search          Search for a package in the repositories.
        show            Show detailed information about a package.
        install         Install a package.
        reinstall       Reinstall a package.
        upgrade         Upgrade all installed packages to the latest version.
        remove          Remove a package.
        autoremove      Automatically remove unneeded packages.
        clean           Clean up the package cache.
        help            Show this help message.
        version         Show the version of murpkg.
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
        jdk<version>-openjdk you installed from MUR-PACKAGES
        <jreversion>-openjdk you installed from MUR-PACKAGES
        latest for jdk-openjdk
        jrelatest for jre-openjdk
example:
        setversion-jdk 8
        setversion-jdk 11
        setversion-jdk 17
        setversion-jdk 21
        setversion-jdk latest
        setversion-jdk jre8
        setversion-jdk jre11
        setversion-jdk jre17
        setversion-jdk jre21
        setversion-jdk jrelatest
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

__lf__: Terminal file manager

Note: Modified the `start file` command to `less file` when opening a file in `lf`.

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
        php<version> you installed from MUR-PACKAGES
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

__pythonembed__: Python is a programming language that lets you work more quickly and integrate your systems more effectively.

Repackaged on official [embeded python zip](https://www.python.org/downloads/windows/), with `ensurepip` extracted form [github.com/python/cpython](https://github.com/python/cpython), supporting the installation and use of `virtualenv`.

The version config file is stored in /home/.mur/setversion/pythonembed.txt. You need to manually remove it when uninstalling pythonembed. Additionally, it is better to install `murclean` and run `murclean clean opt` to automatically remove all packages installed by pip.

Basic Usage:
```
setversion-python latest
optfirst which python
optfirst python --version
optfirst which pip
optfirst pip --version
optfirst pip install virtualenv
optfirst which virtualenv
setversion-python latest
optfirst which virtualenv
optfirst virtualenv path/to/myenv
```

Note: Do not add /opt/share/python/mur__pythonembed/Scripts/ to your PATH, `setversion-python` will automatically handle it and other mur__pythonembed\<version\>/Scripts/.

```
PS C:\Users\username> setversion-python
Usage:
        setversion-python <version>
version:
        pythonembed<version> you installed from MUR-PACKAGES
        latest for python-embed
example:
        setversion-python 38
        setversion-python 39
        setversion-python 310
        setversion-python 311
        setversion-python latest
```

1.How to install pip: 

run `setversion-python <version>`

2.How to add pip installed package executables into `/opt/bin`: 

run `setversion-python <version>`

3.How to switch Python version, pip version, or use a different group of package executables: 

run `setversion-python <version>`

Examples:
```
PS C:\Users\username> setversion-python 311
Looking in links: c:\Users\username\AppData\Local\Temp\tmpxl6acd1_
Requirement already satisfied: setuptools in c:\msys64\opt\share\python\mur__pythonembed311\lib\site-packages (65.5.0)
Requirement already satisfied: pip in c:\msys64\opt\share\python\mur__pythonembed311\lib\site-packages (24.0)
success: /usr/bin/rm -rf /home/.mur/tmp/pythonembed/*
success: /usr/bin/cp /opt/share/python/linkmakefile /home/.mur/tmp/pythonembed/makefile
success: for file in $(/usr/bin/ls /opt/share/python/mur__pythonembed311/Scripts | /usr/bin/grep .exe | /usr/bin/sed 's/\.exe$/.c/'); do /usr/bin/cp /opt/share/python/pip_installed_exe_link.c /home/.mur/tmp/pythonembed/$file; done
success: /usr/bin/find /home/.mur/tmp/pythonembed/ -type f -name '*.c' -exec /usr/bin/sed -i '1s/.*/#define pkgver "311"/' {} +
make: Entering directory '/home/.mur/tmp/pythonembed'
usrfirst gcc -o pip.exe pip.c -O3 -s
usrfirst gcc -o pip3.11.exe pip3.11.c -O3 -s
usrfirst gcc -o pip3.exe pip3.c -O3 -s
usrfirst gcc -o pyi-archive_viewer.exe pyi-archive_viewer.c -O3 -s
usrfirst gcc -o pyi-bindepend.exe pyi-bindepend.c -O3 -s
usrfirst gcc -o pyi-grab_version.exe pyi-grab_version.c -O3 -s
usrfirst gcc -o pyi-makespec.exe pyi-makespec.c -O3 -s
usrfirst gcc -o pyi-set_version.exe pyi-set_version.c -O3 -s
usrfirst gcc -o pyinstaller.exe pyinstaller.c -O3 -s
All Done
make: Leaving directory '/home/.mur/tmp/pythonembed'
success: /usr/bin/make -C /home/.mur/tmp/pythonembed/
success: /usr/bin/find /opt/bin/ -exec /usr/bin/pacman -Qo {} + 2>&1 | /usr/bin/grep "error: No package owns" | /usr/bin/cut -d' ' -f5- | /usr/bin/tr '\n' '\0' | /usr/bin/xargs -r -0 -- /usr/bin/rm -rf --
success: for file in "/home/.mur/tmp/pythonembed/"*.exe; do target_file="/opt/bin/${file#/home/.mur/tmp/pythonembed/}"; if [ ! -e "$target_file" ]; then /usr/bin/cp "$file" "$target_file"; fi; done
success: /usr/bin/rm -rf /home/.mur/tmp/pythonembed/*
```
```
PS C:\Users\username> setversion-python latest
Looking in links: c:\Users\username\AppData\Local\Temp\tmpuhv814f7
Requirement already satisfied: pip in c:\msys64\opt\share\python\mur__pythonembed\lib\site-packages (24.0)
success: /usr/bin/rm -rf /home/.mur/tmp/pythonembed/*
success: /usr/bin/cp /opt/share/python/linkmakefile /home/.mur/tmp/pythonembed/makefile
success: for file in $(/usr/bin/ls /opt/share/python/mur__pythonembed/Scripts | /usr/bin/grep .exe | /usr/bin/sed 's/\.exe$/.c/'); do /usr/bin/cp /opt/share/python/pip_installed_exe_link.c /home/.mur/tmp/pythonembed/$file; done
success: /usr/bin/find /home/.mur/tmp/pythonembed/ -type f -name '*.c' -exec /usr/bin/sed -i '1s/.*/#define pkgver "latest"/' {} +
make: Entering directory '/home/.mur/tmp/pythonembed'
usrfirst gcc -o findent.exe findent.c -O3 -s
usrfirst gcc -o pip.exe pip.c -O3 -s
usrfirst gcc -o pip3.12.exe pip3.12.c -O3 -s
usrfirst gcc -o pip3.exe pip3.c -O3 -s
All Done
make: Leaving directory '/home/.mur/tmp/pythonembed'
success: /usr/bin/make -C /home/.mur/tmp/pythonembed/
success: /usr/bin/find /opt/bin/ -exec /usr/bin/pacman -Qo {} + 2>&1 | /usr/bin/grep "error: No package owns" | /usr/bin/cut -d' ' -f5- | /usr/bin/tr '\n' '\0' | /usr/bin/xargs -r -0 -- /usr/bin/rm -rf --
success: for file in "/home/.mur/tmp/pythonembed/"*.exe; do target_file="/opt/bin/${file#/home/.mur/tmp/pythonembed/}"; if [ ! -e "$target_file" ]; then /usr/bin/cp "$file" "$target_file"; fi; done
success: /usr/bin/rm -rf /home/.mur/tmp/pythonembed/*
```

__xdebug__: Xdebug — Step Debugger and Debugging Aid for PHP

__zig__: General-purpose programming language and toolchain for maintaining robust, optimal, and reusable software.

__zls__: A Zig language server supporting Zig developers with features like autocomplete and goto definition

# Contributing

Contributions are welcome! Please submit pull requests or open issues for any improvements or bug fixes.

# License

This project is licensed under the MIT License - see the [LICENSE file](./LICENSE) for details.