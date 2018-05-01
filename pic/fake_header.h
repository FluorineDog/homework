void error(char*);
typedef char* string;
int string_length(string s);                    /* number of characters in s */
string string_join(string a, string b);         /* concatenate a and b */
string string_sub(string a, int start, int end) /* substring a[start..end) */
    //@requires 0 <= start && start <= end && end <= string_length(a);
    ;

/* lexicographic comparison; less than (-1), equal (0), greater than (1) */
int string_compare(string a, string b)
    //@ensures -1 <= \result && \result <= 1;
    ;

string string_fromint(int i);
string string_frombool(bool b);
string string_fromchar(char c)
    //@requires c != '\0';
    ;