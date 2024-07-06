# Introduce

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

If you cat /ucrt64/bin/helix, you'll find out:

    #!/usr/bin/env sh

    HELIX_RUNTIME=${MINGW_PREFIX}/var/lib/helix/runtime exec ${MINGW_PREFIX}/lib/helix/hx.exe "$@"