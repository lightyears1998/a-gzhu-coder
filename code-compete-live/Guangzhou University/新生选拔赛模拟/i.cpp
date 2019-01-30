#include <cstdio>

int main()
{
    int i, j;
    while (scanf("%d%d", &i, &j) == 2)
    {
        switch (i) {
            case 1: {
                if (j >= 20) printf("Aquarius\n");
                else printf("Capricorn\n");
                break;
            }
            case 2: {
                if (j >= 19) printf("Pisces\n");
                else printf("Aquarius\n");
                break;
            }
            case 3: {
                if (j >= 21) printf("Aries\n");
                else printf("Pisces\n");
                break;
            }
            case 4: {
                if (j >= 20) printf("Taurus\n");
                else printf("Aries\n");
                break;
            }
            case 5: {
                if (j >= 21) printf("Gemini\n");
                else printf("Taurus\n");
                break;
            }
            case 6: {
                if (j >= 22) printf("Cancer\n");
                else printf("Gemini\n");
                break;
            }
            case 7: {
                if (j >= 23) printf("Leo\n");
                else printf("Cancer\n");
                break;
            }
            case 8: {
                if (j >= 23) printf("Virgo\n");
                else printf("Leo\n");
                break;
            }
            case 9: {
                if (j >= 23) printf("Libra\n");
                else printf("Virgo\n");
                break;
            }
            case 10: {
                if (j >= 24) printf("Scorpio\n");
                else printf("Libra\n");
                break;
            }
            case 11: {
                if (j >= 23) printf("Sagittarius\n");
                else printf("Scorpio\n");
                break;
            }
            case 12: {
                if (j >= 22) printf("Capricorn\n");
                else printf("Sagittarius\n");
                break;
            }
        }
    }
}
