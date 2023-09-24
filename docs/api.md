# API Documentation 📚

// Example 1: Simple Regular Expression Match
OnigRegex regex = onig_new_simple("\\d+");
int result = onig_search(regex, "123", 0, 3);
printf("Match result: %d\n", result); // Outputs: Match result: 0
// Source code: https://github.com/oniguruma-org/oniguruma/blob/main/src/oniguruma.c

// Example 2: Regular Expression Match for Word Characters
OnigRegex regex2 = onig_new_simple("\\w+");
int result2 = onig_search(regex2, "Hello, World!", 0, 13);
printf("Match result: %d\n", result2); // Outputs: Match result: 0
// Source code: https://github.com/oniguruma-org/oniguruma/blob/main/src/oniguruma.c
...
