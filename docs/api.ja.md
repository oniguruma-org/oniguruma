# Regular Expression Match Example

// Example of a simple regular expression match
OnigRegex regex = onig_new_simple("\\d+");
int result = onig_search(regex, "123", 0, 3);
printf("Match result: %d\n", result); // Outputs: Match result: 0
