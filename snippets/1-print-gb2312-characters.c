/**
 * 以接近底层的方式输出GB2312字符
 *
 * 时间：17-08-18
 *
 * 提示：
 * 如果你直接从仓库下载这份代码，它是以UTF8编码保存的
 * 仅在GB2312字符集环境中能得到有意义的输出，典型的GB2312字符集环境是Windows简体中文版的命令行工具环境。
 */

/**
 * GB2312码表参考：
 * [千千秀字](http://www.qqxiuzi.cn/zh/hanzi-gb2312-bianma.php) 
 * [国家标准化管理委员会](http://www.gb688.cn/bzgk/gb/newGbInfo?hcno=5664A728BD9D523DE3B99BC37AC7A2CC)
 *
 * “高字节”在前先于低字节输出
 * 
 * 注意
 */

#include <stdio.h>

int main(void){
	char characters[5][2];		// 字符编码
	int offset = 0xA0;			// 偏移量
	
	// 多 区位码2264
	characters[0][0] = 22+offset;
	characters[0][1] = 64+offset;
	
	// 莉
	characters[1][0] = 32+offset;
	characters[1][1] = 82+offset;
	
	// 你
	characters[2][0] = 36+offset;
	characters[2][1] = 67+offset;
	
	// 好
	characters[3][0] = 26+offset;
	characters[3][1] = 35+offset;
	
	// ！（全角字符）
	characters[4][0] = 3+offset;
	characters[4][1] = 1+offset;
	
	// GB2312兼容ASCII
	printf("(GB2313)");
	
	for(int i=0; i<5; i++){
		printf("%c", characters[i][0]);
		printf("%c", characters[i][1]);
	}
	
//! 在Windows命令行工具中，你可以用 chcp 65001; 来切换到UTF8环境，尝试下面的语句
//! 如果你直接从仓库下载，则下面的中文字符是UTF8编码的；UTF8兼容ASCII，不兼容GB2312
//!	printf("(取决于文件编码)多莉你好！");
//!	printf("(UTF8)%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 
//!		0xE5, 0xA4, 0x9A, 0xE8, 0x8E, 0x89, 0xE4, 0xBD,
//!		0xA0, 0xE5, 0xA5, 0xBD, 0xEF, 0xBC, 0x81);
	
	return 0;
}
