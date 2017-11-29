#include "player.h"
#include "recorder.h"
#include "adapter.h"

const int LEN = 100;

int main()
{
    char buf[LEN];

    // 读取用户的字符串
    play("[PLEASE GIVE ME SOME INPUT]", true);
    play(">> "); record(buf, LEN);
    play("[YOUR INPUT]", true);
    play("<< "); play(buf, true);

    // 读取用户指定的字符
    char ch;
    play("[PLEASE GIVE ME ONE CHARACTER] ");
    play(">> "); record(ch);
    play("[YOUR INPUT] ");
    play(ch, true);

    // 在字符串中删去字符
    play("[PROCEEDING...]", true);
    adapt(buf, ch);

    // 输出修改后的字符串
    play("<< "); play(buf, true);
    play("[Goodbye~] : )", true);
}
