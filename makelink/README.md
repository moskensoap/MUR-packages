# Introduction

**makelink**: Creat make.exe linking to mingw32-make.exe (mingw-w64)

Ways to run __mingw32-make__:

1.Directly run __mingw32-make__, or __mingw32-make.exe__.

2.Set alias in .bashrc:
```
alias make=mingw32-make
alias make.exe='mingw32-make.exe'
```
This allows you to run __make__ as if you were running __mingw32-make__, but two issues arise: (1) It is not useful in CMD and Powershell; (2) It prevents the native MSYS/__make__ from being run in Bash.

3.Install __makelink__, which requires no alias and allows you to run __make__ to invoke MSYS/__make__ in the MSYS shell, and __make__ to invoke __mingw32-make__ in other shells.