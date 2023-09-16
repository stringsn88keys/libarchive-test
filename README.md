# libarchive-test
Two C projects to test linkage to [libarchive/libarchive](https://github.com/libarchive/libarchive/) and general example on static vs. dynamic linking

# Prequisites

##  a package manager install of libarchive

### macOS example

Install:
```sh 
    brew install libarchive
```

Use
```sh
    brew info libarchive 
    
    # produces
    export LDFLAGS="-L/opt/homebrew/opt/libarchive/lib"
    export CPPFLAGS="-I/opt/homebrew/opt/libarchive/include"
```

## a libarchive build from source or release folder

The [GitHub release page](https://github.com/libarchive/libarchive/releases) for `libarchive`
