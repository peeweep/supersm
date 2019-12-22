# SuperSM
Super Symlink Manager.

| LICENSE                                                                                                                            | Language                                                                            | Activities                                                                       |
|------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|
| [![GitHub license](https://img.shields.io/github/license/peeweep/SuperSM)](https://github.com/peeweep/SuperSM/blob/master/LICENSE) | ![GitHub top language](https://img.shields.io/github/languages/top/peeweep/SuperSM) | ![GitHub last commit](https://img.shields.io/github/last-commit/peeweep/SuperSM) |

### Required

C++ 17, boost-libs

### Features

This software looks like [GNU Stow](https://www.gnu.org/software/stow/), but something different:

1. Don't need `--no-folding` anymore.
    Only symlink files, not folder.
2. Don't need `--adopt`anymore.
    If symlink's path already exist file, we will force delete it.

OPTIONS:

```text
Super Symlinks Manager.
Allowed options:
  -v [ --version ]                      version message
  -h [ --help ]                         help message
  -s [ --SuperSM ] arg                  SuperSM project
  -u [ --undo ] arg                     undo SuperSM
  -t [ --target ] arg                   set target
```

* `--target` will use current path's parent directory if not specified.(absolute path)
