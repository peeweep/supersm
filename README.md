# SuperSM
Super Symlinks Manager.

| LICENSE                                                                                                                            | Language                                                                            | Activities                                                                       |
|------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------|----------------------------------------------------------------------------------|
| [![GitHub license](https://img.shields.io/github/license/peeweep/SuperSM)](https://github.com/peeweep/SuperSM/blob/master/LICENSE) | ![GitHub top language](https://img.shields.io/github/languages/top/peeweep/SuperSM) | ![GitHub last commit](https://img.shields.io/github/last-commit/peeweep/SuperSM) |

### Features

This software looks like [GNU Stow](https://www.gnu.org/software/stow/), but somethings different:

1. Don't need `--no-folding` anymore.
    Only symlink files, not folder.
2. Don't need `--adopt`anymore.
    If target already exist file, we will force delete it.

OPTIONS:

```text
Super Symlinks Manager.
Allowed options:
  -v [ --version ]                      version message
  -s [ --SuperSM ] arg                  SuperSM project
  -h [ --help ]                         help message
  -t [ --target ] arg                   set target
```
