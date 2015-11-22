
int strcmp(const char *target,const char *source ,uint32_t count){
	for(uint32_t i = 0; i<count;i++){
		if(target[i]!=source[i]){
			return -1;
		}
	}
	return 1;
}
