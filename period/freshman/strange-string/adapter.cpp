#include <cstring>
#include <algorithm>

// 删除str中指定位置的字符，并将字符串中删除字符后的字符前移
void trim(char * pos)
{
    *pos = '\0';
    while (*++pos != '\0') {
        std::swap(*pos, *(pos - 1));
    }
}

int adapt(char * str, char ch)
{
    int cnt = 0; char * pos;
    while ((pos = strchr(str, ch)) != NULL) {
        trim(pos);
        cnt++;
    }
    return cnt;
}
