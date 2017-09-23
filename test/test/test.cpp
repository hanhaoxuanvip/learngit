
#include <stdio.h>
#include<stdlib.h>
#include <string.h>                                                                    
#include "cJSON.h"
#include <windows.h>
using namespace std;


char *get_json_data(char*adress)

{
	FILE *f_json = NULL;

	long json_size;

	char *json_data = NULL;
	
	f_json = fopen(adress, "r");

	fseek(f_json, 0, SEEK_END);//将指针移动到文件尾部

	json_size = ftell(f_json);//当前指针位置相对于文件首部偏移的字节数

	fseek(f_json, 0, SEEK_SET);//将指针移动到文件首部

	json_data = (char *)malloc(json_size + 1);//向系统申请分配指定size个字节的内存空间
	//free(json_data);
	memset(json_data, 0, json_size + 1);    //内存空间初始化
	fread((void *)json_data, json_size, 1, f_json);//将f_json中的数据读入中json_data中，1个数据项
	//FILE *f_json
	fclose(f_json);

	f_json = NULL;

	return(json_data);
}
////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

	char key;
	char*get_json_data(char*adress);

	char file_head[30] = "F:\\media_out\\";//F:/media_out/
	char filename[40];
	const int filecount = 221;//文件数
	int count;
	cJSON* hand_right_keypoints;
	printf("please press A or Q\n");
	key = getchar();
	getchar();
	while (key != 'A')
	{
		if (key == 'Q')
			exit(0);
		else
		{
			
			printf("please press A or Q\n");
			key = getchar();
			getchar();	
		}

	}
	for (count = 0; count <= 220; count++)

	{

		sprintf(filename, "%s%.12d_keypoints.json", file_head, count);//生成了一个FILENAME，filename---jsonfile	
		puts(filename);
		char *p = get_json_data(filename);
		cJSON * pArray = NULL;
		cJSON * root = NULL;
		root = cJSON_Parse(p);//json结构体
		//cJSON * pSub = cJSON_GetArrayItem(root, 1);//第二个序号
		cJSON * pSub = cJSON_GetObjectItem(root, "people");
		int j = 0;
		int flag = 0;
		pArray = cJSON_GetArrayItem(pSub, 0);  

		hand_right_keypoints = cJSON_GetObjectItem(pArray, "hand_right_keypoints");
		//hand_right_keypoints = cJSON_GetArrayItem(pArray, 3);
		int iSize = cJSON_GetArraySize(hand_right_keypoints);
		printf("this is NO.%d\n", count + 1);
		for (int iCnt = 0; iCnt < iSize; iCnt++)
		{
			cJSON * pSub = cJSON_GetArrayItem(hand_right_keypoints, iCnt);
			if (NULL == pSub)
			{
				continue;
			}
			float iValue = pSub->valuefloat;

			if ((iCnt + 1) % 3 == 0)
				continue;
			else
			{
				printf("%.3f", iValue);
				if (flag == 0)
				{
					printf(",");
					flag = 1;
				}
				else
				{
					printf("\n");
					flag = 0;
				}
			}
		}
		Sleep(1000);
	}
}

