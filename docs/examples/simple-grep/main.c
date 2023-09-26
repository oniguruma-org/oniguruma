#include <stdio.h>
#include <string.h>
#include <oniguruma.h>

int main(int argc, char *argv[]) {
    OnigRegex regex;
    OnigErrorInfo einfo;

    UChar* pattern = (UChar*)argv[1];
    int r = onig_new(&regex, pattern, pattern + strlen((const char*)pattern),
                     ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);

    if (r != ONIG_NORMAL) {
        UChar ebuf[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(ebuf, r, &einfo);
        fprintf(stderr, "Error: %s\n", ebuf);
        return 2;
    }

    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        if (onig_search(regex, (UChar*)line, (UChar*)line + strlen(line),
                        (UChar*)line, (UChar*)line + strlen(line), NULL, 0, ONIG_OPTION_NONE) >= 0) {
            printf("%s", line);
        }
    }

    onig_free(regex);
    return 0;
}
