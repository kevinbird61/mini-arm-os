/* Implementation of <string.h> header file*/
/*
 Because C header file is machine dependent
 So we have to do it by yourself
 */
/* String Compare */
int strcmp(const char *target,const char *source ,uint32_t count){
	for(uint32_t i = 0; i<count;i++){
		if(target[i]!=source[i]){
			return -1;
		}
	}
	return 1;
}

/* String Copy */
void strcpy(char *dst_str , const char *src_str , size_t n){
	while(n-- && (*dst_str++ = *src_str++));
}

/* String Length */
size_t strlen(const char *str){
	const char *temp_s;
	for(temp_s = str; *temp_s ; ++temp_s);
	return (temp_s - str)
}

/* String Reverse */
void reverse(char *src_str){
	int i,j;
	for(i = 0,j = strlen(s)-1;i<j;i++,j--){
		char c = src_str[i];
		src_str[i] = src_str[j];
		src_str[j] = c;
	}
}

/* Int to String */
void itoa(int n , char *str){
	int i = 0;
	int flag = 1;
	
	if(n!=0){
		if(n<0){
			n = -n;
			flag = 0;
		}
		while(n != 0){
			str[i++] = n%10 + '0';
			n = n/10;
		}
		if(!flag) str[i++] = '-';
		str[i] = '\0';
		reverse(str);
	}
	else{
		str[0] = 0 + '0';
		str[1] = '\0';
	}
}

/* String to Int */
int atoi(char *str){
	int sum = 0;
	for(int i = 0; str[i]!='\0';i++){
		sum = sum*10 + str[i] - '0';
	}
	return sum;
}

/* String concat */

char *strcat(char *dst , const char *src){
	size_t i , j;
	for(i = 0; dst[i]!= '\0' ; i++)
		;
	for(j = 0; src[j]!= '\0' ; j++)
		dst[i+j] = src[j];
	dst[i+j] = '\0'; // end
	return dst;
}
