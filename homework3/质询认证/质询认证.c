# include <stdio.h>
# include <stdlib.h>
# include <time.h>
void main (void);
void main (void)
{
/*int num = 100;
char str[10];
itoa(num, str, 16);
printf("The number 'num' is %d and the string 'str' is %s. \n" ,
num, str);
	*/
	srand(time(NULL));
	int N=rand()%11 + 10;
	unsigned int qlst[20]={0};
    unsigned char qlst_unsigned_char[80]={0};
	char qlst_char[80]={0};
	int i,j;
	for(i=0;i<N;i++){
		qlst[i]=rand();
		printf("%d\t",qlst[i]);
		for(j=i*4;j<i*4+4;j++){
			qlst_unsigned_char[j]=unsigned char((qlst[i]) >> (4*i+3-j)*8);
			if(qlst_unsigned_char[j]<127)
				qlst_char[j]=char(qlst_unsigned_char[j]);
			else
                qlst_char[j]=char(qlst_unsigned_char[j]-256);
		}
	}
	unsigned char un_qlst_char[80]={0};
    for(i=0;i<4*N;i++)
	{
		if(qlst_char[i]<127)
			un_qlst_char[i]=unsigned char(qlst_char[i]);
		else
            un_qlst_char[i]=unsigned char(qlst_char[i]+256);
	}
			printf("\n\n\n");
		unsigned int k[20] = {0};
		for(i=0;i<N;i++){
			for(j=i*4;j<i*4+4;j++){
				k[i] +=unsigned int((un_qlst_char[j]) << (4*i+3-j)*8);
				
			}
			printf("%d\t",k[i]);
		}
		
		//unsigned int k=0;
		//for(i=0;i<4;i++){
		//	k +=(int)a[i] << (3-i)*8;
		//}
		//	printf("%d",k);
	}