# Oniguruma

<div style="margin-block: -1em 2em">
  🔠 The regular expression library that powered Ruby & PHP
</div>

<div align=center style="margin-block: 1em">
  <img src="https://i.imgur.com/OXD1kgW.png">
</div>

<div align=center style="margin-block: 1em">
  <a href="https://oniguruma.org/oniguruma/">Docs website</a>
  | <a href="https://oniguruma.org/oniguruma/en/oniguruma_8h.html">oniguruma.h API</a>
  | <a href="https://github.com/oniguruma/oniguruma#readme">GitHub</a>
  | <a href="https://github.com/oniguruma">More Oniguruma projects</a>
</div>

<!-- prettier-ignore -->
💎 Used as the regex engine in [Ruby] 2<br>
🐘 Used as the regex engine in [PHP] 5<br>
😎 Written in everyone's favorite C language<br>
🍰 Uses standard [CMake] for the build system<br>
🐸 Installable via [Conan] dependency manager<br>
📦 Installable via [Vcpkg] package manager

## Installation

![Conan](https://img.shields.io/static/v1?style=for-the-badge&message=Conan&color=6699CB&logo=Conan&logoColor=FFFFFF&label=)
![Vcpkg](https://img.shields.io/static/v1?style=for-the-badge&message=Vcpkg&color=5C2D91&logo=Visual+Studio&logoColor=FFFFFF&label=)
![APT](https://img.shields.io/static/v1?style=for-the-badge&message=APT&color=A81D33&logo=Debian&logoColor=FFFFFF&label=)
![pacman](https://img.shields.io/static/v1?style=for-the-badge&message=pacman&color=1793D1&logo=Arch+Linux&logoColor=FFFFFF&label=)
![CMake](https://img.shields.io/static/v1?style=for-the-badge&message=CMake&color=064F8C&logo=CMake&logoColor=FFFFFF&label=)

You can install this library using [Conan] or [Vcpkg] like this:

```sh
# conanfile.txt
[requires]
oniguruma/6.9.8
```

```sh
vcpkg install oniguruma
```

ℹ The `oniguruma` Vcpkg port in is maintained by Microsoft community
contributors. If any issues arise specific to Vcpkg, please direct them to the
[microsoft/vcpkg] project.

<details><summary>This library is also available through a number of system package managers</summary>

| OS            | Install command               |
| ------------- | ----------------------------- |
| Fedora        | `dnf install oniguruma-devel` |
| RHEL/CentOS   | `yum install oniguruma`       |
| Debian/Ubuntu | `apt install libonig5`        |
| Arch          | `pacman -S oniguruma`         |
| openSUSE      | `zypper install oniguruma`    |

</details>

<details><summary>Manual build instructions for users</summary>

```sh
cmake -Bbuild
cmake --build build
cp -r include build/lib* /workspaces/awesome-project/
```

💻 These steps work on Windows, macOS, and Linux. Make sure you have a good
version of [CMake] installed. You can [download CMake] from [CMake.org] or via
[webinstall.dev/cmake].

</details>

## Usage

After installing, you can get started with a simple program like this. It prints
out whether or not the example `text` matches the `regex` variable.

```c
#include <stdio.h>
#include <oniguruma.h>

int main() {
    OnigEncoding enc;
    OnigRegex regex;
    OnigPosition start, end;
    OnigRegion* region;
    UChar* pattern = (UChar*) "hello";
    UChar* str = (UChar*) "Hello world!";
    int r;

    r = onig_initialize(&enc, ONIG_ENCODING_UTF8, ONIG_ENCODING_UTF8);
    if (r != ONIG_NORMAL) {
        printf("Error: onig_initialize\n");
        return 1;
    }

    r = onig_new(&regex, pattern, pattern + strlen((char*)pattern),
                 ONIG_OPTION_IGNORECASE, enc, ONIG_SYNTAX_DEFAULT, NULL);
    if (r != ONIG_NORMAL) {
        printf("Error: onig_new\n");
        onig_end();
        return 1;
    }

    region = onig_region_new();

    r = onig_search(regex, str, str + strlen((char*)str),
                    str, str + strlen((char*)str), region, ONIG_OPTION_NONE);
    if (r >= 0) {
        printf("Match found!\n");
    } else if (r == ONIG_MISMATCH) {
        printf("No match found.\n");
    } else {
        printf("Error: onig_search (return code %d)\n", r);
    }

    onig_region_free(region, 1);
    onig_free(regex);
    onig_end();

    return 0;
}
```

If you're interested in seeing some more examples, check out the [Examples page]
on the [documentation website]!

## Development

This project uses CMake as its build system. The source `*.c` files are all in
`src/`. Any public header files that users of the library could
`#include <lib.h>` are in the `include/` folder. This library offers two main
targets: a shared library (usually `libonig.so`) and a static library (usually
`libonig.a`). These targets are named `libonig-shared` and `libonig-static` if
you want to build them individually via `cmake --build build --target <target>`.

To get started, run these commands after cloning this repository:

```sh
cmake -Bbuild
cmake --build build
```

The `-Bbuild` flag tells CMake to put the generated build tree (`Makefile`, `.o`
files, etc.) into a parallel `build/` folder instead of the current directory.
We then use the `--build` flag to run the Ninja, Make, VS project, or other
build system commands in the `build/` folder that was just generated. After the
initial generation you don't need to rerun the `cmake -Bbuild` command since the
build tooling will already be there. Instead just run `cmake --build build`.

There's also a `test` target that can used to build and run the tests. There's
not currently a test runner that we use, so we roll our own. To run the tests,
use this:

```sh
cmake --build build --target test
```

| File                | Description                                              |
| :------------------ | :------------------------------------------------------- |
| oniguruma.h         | Oniguruma API header file (public)                       |
| onig-config.in      | configuration check program template                     |
| regenc.h            | character encodings framework header file                |
| regint.h            | internal definitions                                     |
| regparse.h          | internal definitions for regparse.c and regcomp.c        |
| regcomp.c           | compiling and optimization functions                     |
| regenc.c            | character encodings framework                            |
| regerror.c          | error message function                                   |
| regext.c            | extended API functions (deluxe version API)              |
| regexec.c           | search and match functions                               |
| regparse.c          | parsing functions.                                       |
| regsyntax.c         | pattern syntax functions and built-in syntax definitions |
| regtrav.c           | capture history tree data traverse functions             |
| regversion.c        | version info function                                    |
| st.h                | hash table functions header file                         |
| st.c                | hash table functions                                     |
| oniggnu.h           | GNU regex API header file (public)                       |
| reggnu.c            | GNU regex API functions                                  |
| onigposix.h         | POSIX API header file (public)                           |
| regposerr.c         | POSIX error message function                             |
| regposix.c          | POSIX API functions                                      |
| mktable.c           | character type table generator                           |
| ascii.c             | ASCII encoding                                           |
| euc_jp.c            | EUC-JP encoding                                          |
| euc_tw.c            | EUC-TW encoding                                          |
| euc_kr.c            | EUC-KR, EUC-CN encoding                                  |
| sjis.c              | Shift_JIS encoding                                       |
| big5.c              | Big5 encoding                                            |
| gb18030.c           | GB18030 encoding                                         |
| koi8.c              | KOI8 encoding                                            |
| koi8_r.c            | KOI8-R encoding                                          |
| cp1251.c            | CP1251 encoding                                          |
| iso8859_1.c         | ISO-8859-1 (Latin-1)                                     |
| iso8859_2.c         | ISO-8859-2 (Latin-2)                                     |
| iso8859_3.c         | ISO-8859-3 (Latin-3)                                     |
| iso8859_4.c         | ISO-8859-4 (Latin-4)                                     |
| iso8859_5.c         | ISO-8859-5 (Cyrillic)                                    |
| iso8859_6.c         | ISO-8859-6 (Arabic)                                      |
| iso8859_7.c         | ISO-8859-7 (Greek)                                       |
| iso8859_8.c         | ISO-8859-8 (Hebrew)                                      |
| iso8859_9.c         | ISO-8859-9 (Latin-5 or Turkish)                          |
| iso8859_10.c        | ISO-8859-10 (Latin-6 or Nordic)                          |
| iso8859_11.c        | ISO-8859-11 (Thai)                                       |
| iso8859_13.c        | ISO-8859-13 (Latin-7 or Baltic Rim)                      |
| iso8859_14.c        | ISO-8859-14 (Latin-8 or Celtic)                          |
| iso8859_15.c        | ISO-8859-15 (Latin-9 or West European with Euro)         |
| iso8859_16.c        | ISO-8859-16 (Latin-10)                                   |
| utf8.c              | UTF-8 encoding                                           |
| utf16_be.c          | UTF-16BE encoding                                        |
| utf16_le.c          | UTF-16LE encoding                                        |
| utf32_be.c          | UTF-32BE encoding                                        |
| utf32_le.c          | UTF-32LE encoding                                        |
| unicode.c           | common codes of Unicode encoding                         |
| unicode_fold_data.c | Unicode folding data                                     |
| windows/testc.c     | Test program for Windows (VC++)                          |

[conan]: https://conan.io/
[vcpkg]: https://vcpkg.io/
[php]: https://www.php.net/
[ruby]: https://www.ruby-lang.org/
[cmake]: https://cmake.org/
[download cmake]: https://cmake.org/download/
[cmake.org]: https://cmake.org/
[webinstall.dev/cmake]: https://webinstall.dev/cmake
[microsoft/vcpkg]: https://github.com/microsoft/vcpkg
