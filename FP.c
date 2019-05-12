#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int flag1, flag2, flag3, flag4, flag5;

int menit(int x, int y){
	if(x==y){
		return flag1=1;
	}
	else return flag1=0;
}

int jam2(int x, int y){
	if(x==y){
		return flag2=1;
	}
	else return flag2=0;
}

int hari1(int x, int y){
	if(x==y){
		return flag3=1;
	}
	else return flag3=0;
}

int bulan(int x, int y){
	if(x==y){
		return flag4=1;
	}
	else return flag4=0;
}

int hari2(int x, int y){
	if(x==y){
		return flag5=1;
	}
	else return flag5=0;
}

int main(void) {
	time_t waktu;
	struct tm *jam;
	time(&waktu);
	jam = localtime(&waktu);
	printf("Atime:%04d-%02d-%02d_%02d:%02d:%02d\n", jam->tm_year+1900, jam->tm_mon+1, jam->tm_mday, jam->tm_hour, jam->tm_min, jam->tm_sec);
	
	int i, j, time2[5], a, x;
   	FILE *fp;
   	char buff[255], time[2], cmd[50], temp[100];
   	fp = fopen("crontab.data", "r");
   	if(fp==NULL){
   		perror("Error while opening the file.\n");
      	exit(EXIT_FAILURE);
   	}
   	fgets(buff, 255, (FILE*)fp);
	
	i=0, a=0, x=0;
	for(j=0;j<14;j++){
		if(buff[j]!=' ') {
			if(buff[j]=='*'){
			 	time2[a++]=-1;
				//printf("a1=%d\n", a);
			}
			else {
				time[i++]=buff[j];
				if(buff[j+1]==' '){
					time2[a++]=atoi(time);
					//printf("a2=%d\n", a);
					time[0]=0;
					time[1]=0;
					time[2]=0;
					i=0;
				}	
			}	
		}
	}
	a=0;
	for(j=14;j<50;j++){
		if(buff[j]==' '){
			break;
		}
		else {
			temp[a++]=buff[j];
			if(temp[a-1]=='/'){
				a=0;
			}	
		}
	}
	strcat(cmd, temp);
	for(j=14;j<100;j++){
		if(buff[j]==' '){
			a=1;
			temp[0]=' ';
		}
		else {
			temp[a++]=buff[j];
		}
	}
	strcat(cmd, temp);
	

	//for(i=0;i<5;i++) printf("%d ", time2[i]);
	//printf("\n%s\n", cmd);
	//printf("%s\n", buff);
   	
   	//if(time2[1]==jam->tm_min) printf("Bisa1\n");
   	menit(jam->tm_min, time2[0]);
   	jam2(jam->tm_hour, time2[1]);
   	hari1(jam->tm_mday, time2[2]);
   	bulan(jam->tm_mon, time2[3]);
   	hari2(jam->tm_wday, time2[4]);
   	//printf("%d-%d-%d-%d-%d\n",flag1, flag2, flag3, flag4, flag5);
   	if(flag1==1 && flag2==1 && flag3==1 && flag4==1 && flag5==1)system(cmd);

   	fclose(fp);
	return 0;
}


