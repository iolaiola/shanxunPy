#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>    
#include <string.h>  
typedef int (*CAC_FUNC)(char*, int,char*,int);
int my_atoi(char *str){
	int result = 0;
	int signal = 1;
	if((*str>='0'&&*str<='9')||*str=='-'||*str=='+'){
		if(*str=='-'||*str=='+'){
			if(*str=='-')
				signal = -1; 
			str++;
		}
	}
	else return 0;
	while(*str>='0'&&*str<='9')
	result = result*10+(*str++ -'0');
	return signal*result;
}
void base64Decode(char encoded_string[],char ret[]) {
	char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int in_len = strlen(encoded_string);
	int c_len=64;
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
	int t=0;
    while (in_len-- && ( encoded_string[in_] != '=') &&(isalnum(encoded_string[in_]) || (encoded_string[in_] == '+') || (encoded_string[in_] == '/'))) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
			for (i = 0; i <4; i++){
				int a;
				for(a=0;a<c_len;a++){
					if(base64_chars[a]==char_array_4[i]){
						char_array_4[i]=a;
						break;
					}
				}
				if(a>=64){
					char_array_4[i]=-1;
				}
			}
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
           
            for (i = 0; (i < 3); i++)
                ret[t++]= char_array_3[i];
            i = 0;
        }
    }
   
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
       
		for (j = 0; j <4; j++){
			int a;
			for(a=0;a<c_len;a++){
				if(base64_chars[a]==char_array_4[j]){
					char_array_4[j]=a;
					break;
				}
			}
			if(a>=64){
					char_array_4[i]=-1;
			}
		}
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
       
        for (j = 0; (j < i - 1); j++)
			ret[t++]= char_array_3[j];
    }
	ret[t]='\0';
}
void sendUdp(char ip[],int port,char data[],int len)  
{  
	printf("该插件完全免费使用，请关注作者博客：www.mandroid.cn\n");
	printf("ip: %s \nport: %d \ndataLen: %d\n",ip,port,len);
	int s;  
    struct sockaddr_in addr;  
    int addr_len =sizeof(struct sockaddr_in);  
    char buffer[256];  
    if((s = socket(AF_INET,SOCK_DGRAM,0))<0){  
        perror("socket");  
        exit(1);  
    }  
    bzero(&addr,sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(port);  
    addr.sin_addr.s_addr = inet_addr(ip);  
	len=sendto(s,data,len,0,(struct sockaddr *)&addr,addr_len);  
	if(len=!1){
		printf("发送失败");
	}else{
		printf("\nsuccess\n");
	}
}  
int main(int argi,char **args)
{
	if(argi!=5){
		return 0;
	}
	int dataLen=my_atoi(args[4]);
	char realData[dataLen];
	printf("数据长度：%d\n",sizeof(realData));
	base64Decode(args[3],realData);
	sendUdp(args[1],my_atoi(args[2]),realData,dataLen);
	return 1;
}