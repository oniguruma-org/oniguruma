# Regular Expression Match Example 🧩

// Example of a simple regular expression match
OnigRegex regex = onig_new_simple("\\d+");
int result = onig_search(regex, "123", 0, 3);
printf("Match result: %d\n", result); // Outputs: Match result: 0

// You can find the source code for these functions at:
// https://github.com/oniguruma-org/oniguruma/blob/main/src/oniguruma.c

// Here's another example, this time we're looking for any word characters:
OnigRegex regex2 = onig_new_simple("\\w+");
int result2 = onig_search(regex2, "Hello, World!", 0, 13);
printf("Match result: %d\n", result2); // Outputs: Match result: 0
