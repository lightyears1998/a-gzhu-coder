/* GZHUOJ1002 Word Counting */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main()
{
    char a[10005];
//! while (fgets(a, sizeof(a), stdin))
    while (scanf("%[^#]", a) == 1)
    {
//!     getchar(); getchar(); getchar(); getchar();
        int s = 0, start = 0;
        for (int i = 0; i < strlen(a) - 1; i++)
        {
            if (isspace(a[i])) start = 0;
            else if (isalpha(a[i]) || isdigit(a[i]))
            {
                if (!start) {
                    start = 1;
                    s++;
                }
            }
            else if(ispunct(a[i])) {
                s++;
                start = 0;
            }
        }
        printf("%d\n",s);
        scanf("%[#\n]", a);
    }
}
