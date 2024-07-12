# Introduction

**helixlink**: Creat \${MINGW_PREFIX}/bin/hx.exe linking to \${MINGW_PREFIX}/lib/helix/hx.exe (mingw-w64)

The file tree of official **helix** in ucrt64:

    /ucrt64/bin/helix
    /ucrt64/lib/helix/hx.exe
    /ucrt64/lib/helix/runtime/*
    /ucrt64/share/bash-completion/completions/helix
    /ucrt64/share/doc/helix/html/*
    /ucrt64/share/fish/vendor_completions.d/helix.fish
    /ucrt64/share/licenses/helix/LICENSE
    /ucrt64/share/zsh/site-functions/_
    /ucrt64/var/lib/helix/runtime*
    
if you see the its [PKGBUILD](https://github.com/msys2/MINGW-packages/blob/master/mingw-w64-helix/PKGBUILD) in offcial repo, you will findout /ucrt64/var/lib/helix/runtime* are just copies of /ucrt64/lib/helix/runtime/*.

If you cat /ucrt64/bin/helix, you'll see:

    #!/usr/bin/env sh

    HELIX_RUNTIME=${MINGW_PREFIX}/var/lib/helix/runtime exec ${MINGW_PREFIX}/lib/helix/hx.exe "$@"

This script uses ${MINGW_PREFIX} meaning it can only work in ucrt64 shell where you installed it, otherwise, no hx.exe will be found.

You can run two commands below to compare them, and find this script is irrelevant, for by default, `\\?\C:\msys64\ucrt64\lib\helix\runtime` is already in Runtime directories.

```MSYS/UCRT64
username@computername UCRT64 ~
$ hxlix --heallth
Config file: default
Language file: default
Log file: C:\Users\username\AppData\Local\helix\helix.log
Runtime directories: C:\Users\username\AppData\Roaming\helix\runtime;C:/msys64/ucrt64/var/lib/helix/runtime;
\\?\C:\msys64\ucrt64\lib\helix\runtime
Runtime directory does not exist: C:\Users\username\AppData\Roaming\helix\runtime
Clipboard provider: clipboard-win
System clipboard provider: clipboard-win
```

```MSYS/UCRT64
username@computername UCRT64 ~
$ /ucrt64/lib/helix/hx.exe --health
Config file: default
Language file: default
Log file: C:\Users\username\AppData\Local\helix\helix.log
Runtime directories: C:\Users\username\AppData\Roaming\helix\runtime;
\\?\C:\msys64\ucrt64\lib\helix\runtime
Runtime directory does not exist: C:\Users\username\AppData\Roaming\helix\runtime
Clipboard provider: clipboard-win
System clipboard provider: clipboard-win
```

Thus, directly running __\${MINGW_PREFIX}/lib/helix/hx.exe__ is fine, and __helixlink__ creats \${MINGW_PREFIX}/bin/hx.exe for you to run more conveniently.