# Introduce

**gradlelink**: Creat /usr/bin/gradle.exe linking to /usr/share/java/gradle/bin/gradle

The file tree of official **gradle**:


    /etc/profile.d/gradle.sh
    /usr/bin/
    /usr/share/java/gradle/LICENSE
    /usr/share/java/gradle/NOTICE
    /usr/share/java/gradle/bin/gradle
    /usr/share/java/gradle/bin/gradle.bat
    /usr/share/java/gradle/lib/*

If you cat /etc/profile.d/gradle.sh, you'll find out:

    #!/usr/bin/env sh
    export GRADLE_HOME=/usr/share/java/gradle
    export PATH=$PATH:$GRADLE_HOME/bin

It ensure you can run gradle in MSYS2/MSYS or MSYS/UCRT64 or MSYS/* shells.

For /etc/profile.d/\* will not be sourced in CMD and POWERSHELL, if you prefer add MSYS2's /usr/bin or /ucrt64/bin or /\*/bin into your user PATH in WINDOWS, and run gradle in CMD or POWERSHELL, there are two ways to go.

---
way 1:

1.run __msys2_shell.cmd__

2.run __gradle__

---
way 2:

1.install __gradlelink__ in this repo

2.add MSYS's /opt/bin into your user PATH

3.run __gradle__ anywhere

---