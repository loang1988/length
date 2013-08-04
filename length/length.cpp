// length.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <map>
#include <string>

using namespace std;

#define BUFFSIZE 1024
int _tmain(int argc, _TCHAR* argv[])
{
	std::map<string,double> _map;
	FILE *fileOpen= NULL;
	FILE *fileWrite= NULL;
	char buf[BUFFSIZE];
	if((fileOpen = fopen("..\\input.txt", "r")) == NULL)
	{
		printf("fopen error\n");
		return 0;
	}
	if((fileWrite = fopen("..\\output.txt", "w")) == NULL)
	{
		printf("fopen error\n");
		fclose(fileOpen);
		return 0;
	}
	while(fgets(buf, BUFFSIZE, fileOpen))
	{
		if (strlen(buf)==1)
		{
			break;
		}
		double m1;
		double m2;
		char *token = strtok(buf, " ");
		m1=atof(token);
		token= strtok(NULL, " ");
		string strUnit1 = token;
		token= strtok(NULL, " ");
		token= strtok(NULL, " ");
		m2=atof(token);
		token= strtok(NULL, " ");
		string strUnit2 = token;
		if (strUnit1.compare("m")==0)   // 1 m = 20 miles
		{
			m1=m1/m2;
			strUnit1=strUnit2;
		}else{                        // 1 mile =20 m
			m1=m2/m1;
		}
		_map.insert(std::make_pair(strUnit1,m1));
		if (strUnit1.substr(strUnit1.length()-2,strUnit1.length())=="ch")
		{
			strUnit1=strUnit1+"es";
		}else if (strUnit1=="foot")
		{
			strUnit1="feet";
		}else 
		{
			strUnit1=strUnit1+"s";
		}
		_map.insert(std::make_pair(strUnit1,m1));
	}
	sprintf(buf,"loang1988@gmail.com\n");
	fwrite(buf,strlen(buf),1,fileWrite);
	while(fgets(buf, BUFFSIZE, fileOpen)){
		if (strlen(buf)==1)
		{
			break;
		}
		double total=0.0;
		char *token = strtok(buf, " ");
		while (token)
		{
			int bAdd=1;
			double m1;
			if (strcmp(token,"-")==0)
			{
				bAdd=0;
				token = strtok(NULL, " ");
			}else if (strcmp(token,"+")==0)
			{
				token = strtok(NULL, " ");
			}
			m1=atof(token);
			token = strtok(NULL, " \n");
			//string str=token;
			//str=str.substr(0,str.length()-1);
			std::map<string,double>::iterator iter = _map.find(token);

			if (bAdd)
			{
				total+=iter->second*m1;
			}else
				total-=iter->second*m1;
			
			token = strtok(NULL, " ");


		}
		//if (total+0.005>1)
		//{
		sprintf(buf,"\n%.2lf m",total+0.005);
		//}else
		//{
		//	sprintf(buf,"%.2lf meter\n",total+0.005);
		//}
		
		fwrite(buf,strlen(buf),1,fileWrite);
	
	}
	fflush(fileWrite);
	fclose(fileWrite);
	fclose(fileOpen);

	return 0;
}

