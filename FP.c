#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>


pthread_t tid1, tid2;
int flag1, flag2, flag3, flag4, flag5;
char buff[255], waktu[2], cmd[50], temp[100];
int time2[5];

void* baca(){
	int i, j, a, x;
   	FILE *fp;
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
				waktu[i++]=buff[j];
				if(buff[j+1]==' '){
					time2[a++]=atoi(waktu);
					//printf("a2=%d\n", a);
					waktu[0]=0;
					waktu[1]=0;
					waktu[2]=0;
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
	for(i=0;i<5;i++) printf("%d ", time2[i]);
	printf("\n%s\n", cmd);
	fclose(fp);
}

void* cek(){

	time_t waktu;
	struct tm *jam;
	time(&waktu);
	jam = localtime(&waktu);
	printf("Atime:%04d-%02d-%02d_%02d:%02d:%02d\n", jam->tm_year+1900, jam->tm_mon+1, jam->tm_mday, jam->tm_hour, jam->tm_min, jam->tm_sec);

	//Menit
	if(time2[0]==-1){
		flag1=1;
	}
	else if(time2[0]!=-1){
		if(time2[0]<0 || time2[0]>59)
      		exit(EXIT_FAILURE);
		else if(jam->tm_min==time2[0])
			flag1=1;
		else flag1=0;
	}
	
	//Jam
	if(time2[1]==-1){
		flag2=1;
	}
	else if(time2[1]!=-1){
		if(time2[1]<0 || time2[1]>23)
      		exit(EXIT_FAILURE);
		else if(jam->tm_hour==time2[1])
			flag2=1;
		else flag2=0;
	}
	
	//Hari(Tanggal)
	if(time2[2]==-1){
		flag3=1;
	}
	else if(time2[2]!=-1){
		if(time2[2]<1 || time2[2]>31)
      		exit(EXIT_FAILURE);
		else if(jam->tm_mday==time2[2])
			flag3=1;
		else flag3=0;
	}
	
	//Bulan
	if(time2[3]==-1){
		flag4=1;
	}
	else if(time2[3]!=-1){
		if(time2[3]<1 || time2[3]>12)
      		exit(EXIT_FAILURE);
		else if(jam->tm_mon==time2[3])
			flag4=1;
		else flag4=0;
	}
	
	//Hari
	if(time2[4]==-1){
		flag5=1;
	}
	else if(time2[4]!=-1){
		if(time2[4]==7){
			time2[4]=0;
			if(time2[4]<0 || time2[4]>7)
      			exit(EXIT_FAILURE);
			else if(jam->tm_wday==time2[4])
				flag5=1;
			else flag5=0;
		}
	}
   	
}


int main(void) {
	
	pthread_create(&(tid1), NULL, (void*)baca, NULL);
    pthread_join(tid1, NULL);

    pthread_create(&(tid2), NULL, (void*)cek, NULL);
    pthread_join(tid2, NULL);
	
	//printf("%s\n", buff);
   	
   	//if(time2[1]==jam->tm_min) printf("Bisa1\n");
   	
   	printf("%d-%d-%d-%d-%d\n",flag1, flag2, flag3, flag4, flag5);
   	if(flag1==1 && flag2==1 && flag3==1 && flag4==1 && flag5==1)system(cmd);
   	
	return 0;
}


