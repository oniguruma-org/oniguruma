# https://webinstall.dev/cmake/
cmake_minimum_required(VERSION 3.25)
# https://oniguruma.org/oniguruma
project(oniguruma VERSION 6.9.8)

# https://cmake.org/cmake/help/latest/module/CMakePrintHelpers.html
include(CMakePrintHelpers)

# file(GLOB_RECURSE my_src_files CONFIGURE_DEPENDS "src/*.c")
set(my_src_files
src/regint.h src/regparse.h src/regenc.h src/st.h src/regerror.c src/regparse.c
src/regext.c src/regcomp.c src/regexec.c src/reggnu.c src/regenc.c
src/regsyntax.c src/regtrav.c src/regversion.c src/st.c src/onig_init.c
src/unicode.c src/ascii.c src/utf8.c src/utf16_be.c src/utf16_le.c
src/utf32_be.c src/utf32_le.c src/euc_jp.c src/sjis.c src/iso8859_1.c
src/iso8859_2.c src/iso8859_3.c src/iso8859_4.c src/iso8859_5.c
src/iso8859_6.c src/iso8859_7.c src/iso8859_8.c src/iso8859_9.c
src/iso8859_10.c src/iso8859_11.c src/iso8859_13.c src/iso8859_14.c
src/iso8859_15.c src/iso8859_16.c src/euc_tw.c src/euc_kr.c src/big5.c
src/gb18030.c src/koi8_r.c src/cp1251.c src/euc_jp_prop.c src/sjis_prop.c
src/unicode_unfold_key.c src/unicode_fold1_key.c src/unicode_fold2_key.c
src/unicode_fold3_key.c
)
cmake_print_variables(my_src_files)

configure_file(${PROJECT_SOURCE_DIR}/src/config.h.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# Default to C23 for all targets
set(CMAKE_C_STANDARD 23)

add_library(oniguruma STATIC ${my_src_files})
target_include_directories(oniguruma PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(oniguruma PRIVATE ${CMAKE_CURRENT_BINARY_DIR})