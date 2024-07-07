# Introduction

**gradlelink**: Creat /usr/bin/gradle.exe linking to /usr/share/java/gradle/bin/gradle

The file tree of official **gradle**:


    /etc/profile.d/gradle.sh
    /usr/bin/
    /usr/share/java/gradle/LICENSE
    /usr/share/java/gradle/NOTICE
    /usr/share/java/gradle/bin/gradle
    /usr/share/java/gradle/bin/gradle.bat
    /usr/share/java/gradle/lib/*

If you __cat /etc/profile.d/gradle.sh__, you'll see:

    #!/usr/bin/env sh
    export GRADLE_HOME=/usr/share/java/gradle
    export PATH=$PATH:$GRADLE_HOME/bin

This ensures that you can run __gradle__ in MSYS2/MSYS or MSYS/UCRT64 or MSYS/* shells.

However, /etc/profile.d/\* scripts are not sourced in CMD and POWERSHELL, if you prefer add MSYS2's /usr/bin or /ucrt64/bin or /\*/bin to your user PATH in WINDOWS, and run __gradle__ in CMD or POWERSHELL, there are two ways to do it.

---
Way 1:

1.Run __msys2_shell.cmd__

2.Run __gradle__

---
Way 2:

1.Install __gradlelink__ in this repo

2.Add MSYS's /opt/bin to your user PATH

3.Run __gradle__ anywhere

---