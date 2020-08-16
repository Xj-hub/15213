#include "stdio.h"
#include <string.h>
//#include <string>
//#include <cstring>
//使用string和cstring时会报错，具体原因不明，可能是和当前是进行c编译，无法使用c++库函数的原因，
//所以在c语言中，若想使用字符串的操作，需要的头文件应该是string.h
void main()
{
	char *my_test = "abc";//指针指向静态存储区的一段内存
	printf("%s\n", my_test);//abc
	printf("%c\n", my_test);//0
	printf("%d\n", my_test);//打印的是指针的地址值
	printf("%d\n", *my_test);//ascii a-01100001十进制值97 b-01100010 c - 01100011 \0-0000 0000 
	
	int char_len = sizeof(my_test);
	printf("%d\n", char_len);//输出结果为4
 
	char_len = strlen(my_test);//当头文件中不包含string.h时，strlen函数无法使用
	printf("%d\n", char_len);//输出结果为3
    
	my_test = "why";
	printf("%s\n", my_test);//why
 
	printf("%c\n%c\n%c\n", my_test[0], my_test[1], my_test[2]);
 
	//my_test[1] = 'c';出错
	//memcpy(my_test ,"c", 1);出错
 
	char my_test_buff[20] = "hello!";//申请了一段buffer，是存储在栈中
	printf("%s\n", my_test_buff);//hello!
	printf("%d\n", my_test_buff);//地址值,不固定
	printf("%c\n", my_test_buff);//和地址值有关，不固定
	printf("%d\n", *my_test_buff);//ascii字符h的十进制值104
	printf("%c\n", my_test_buff[0]);//h
 
	printf("%d\n", strlen(my_test_buff));//6
	printf("%d\n", sizeof(my_test_buff));//20
	my_test_buff[1] = 'p';
	printf("%s\n", my_test_buff);//hpllo!
 
	char*p_my = my_test_buff;
	p_my[2] = 'k';
	printf("%s-%s\n", my_test_buff, p_my);//hpklo!- hpklo!
 
	memcpy(p_my, "n", 1);
	printf("%s-%s\n", my_test_buff, p_my);//npklo!- npklo!
 
	memcpy(p_my+3, "wx", 2);
	printf("%s-%s\n", my_test_buff, p_my); //npkwx!- npkwx!
 
 

	printf("%d\n", sizeof(""));//change!


	char str1[20] = "123";
	char * str2 = "456";
	strncat(str1, str2, 1);
	printf("%s\n", str1);//change!
	strstr("23", str1);

	printf("%d\n", sizeof(int)-6);//change!
}