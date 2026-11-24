# Third-party components

| Path | Project | License |
|---|---|---|
| vendor/tinycc | TinyCC (mob branch), patched for Symbian ARM | LGPL-2.1-or-later |
| vendor/unshield | unshield 1.6.2 | MIT |
| vendor/zlib | zlib 1.3.1 | zlib |
| sdk/targets/*/include, lib, tools | Nokia S60 SDKs (2nd Ed FP3, 3rd Ed, 3.1, 3.2, 5th Ed) | Nokia SDK EULA |
| sdk/gcce | Symbian GCCE toolchain (GCC 3.4.3 based) | GPL-2.0+ with runtime exception |

The S60 SDK archives are official Nokia installers; `tools/sdkimport.sh` unpacks them with
unshield and copies the header, import-library and tool subsets. Redistribution of those files is
governed by Nokia's EULA, not by this repository's MIT license.

`vendor/tinycc/tccelf.c` carries one local change: ARM `e_flags` are set to `0x04000010`
(EABI v4) instead of EABI v5 so objects match the S60 link libraries.
