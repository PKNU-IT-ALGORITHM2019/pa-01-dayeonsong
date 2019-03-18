#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int find(char* storage[],int first,int last,char target[]);
int count;
int save_idx[30];

int main(void)
{
	char str[1500];
	char input_str[30];
	char*storage[200000];
	char target[30];
	int i=0,j,n;

	FILE*fp=fopen("dict.txt","rt");
	if(fp==NULL){
		puts("Failed to open file!");
		return -1;
	}
	while(1)
	{
		printf("$ ");
		fgets(input_str,sizeof(input_str),stdin);
		if(strcmp(input_str,"read dict.txt\n")==0) 
		/* 이렇게 하면 "read   dict.txt"와 같이 한 칸 이상 띄우거나 혹은 파일 이름 이 다르면 실행이 안됨. */
		/* 이보다는 input_str을 명령어 read와 파일 이름으로 split하는게 좋음 */
		{
			/* 파일을 읽은 이 부분은 별개의 함수로 만드는게 좋을 듯 */
			while(fgets(str,sizeof(str),fp)!=NULL)
			{
					storage[i]=(char*)malloc(1500);
					strcpy(storage[i],str);
					i++;
					/* 이렇게 공백 라인을 처리하는 것은 좋은 방법은 아님 *?
					fgets(str,sizeof(str),fp);
			}
		}
		else if(strcmp(input_str,"size\n")==0)
		{
			/* 단어의 개수를 i와 같이 너무 의미가 담기지 않은 이름의 변수에 저장하는 것은 좋지 않음 */
			if(i!=0)
				printf("%d \n",i);
			else
				printf("Please 'read dict.txt'! \n");
		}
		else if(strncmp(input_str,"find ",5)==0)
		{
			if(i==0)
				printf("Please 'read dict.txt'! \n");
			else
			{
				j=5,count=0;
				for(n=0;input_str[j]!='\n';n++)
				{
					target[n]=input_str[j];
					if(target[n]>=65&&target[n]<=90)
						target[n]+=32;
					j++;
				}
				/* C언어의 표준 라이브러리는 어떤 문자가 alphabet인지 digit인지 등을 검사하는 함수를 제공함 */
				/* 이렇게 ASCII코드 값으로 검사하는 것은 좋지 않음 */
				if(target[0]>=97&&target[0]<122)
					target[0]-=32;
				target[n]=0;
				find(storage,0,i-1,target);
				if(count!=0)
				{
					printf("Found %d item. \n",count);
					for(n=0;n<count;n++)
						printf("%s \n",storage[save_idx[n]]);
				}
				else
				{
					printf("Not found. \n");
					j=0;
					for(n=0;;n++)
					{
						if(*(storage[save_idx[0]]+n)==')')
							*(storage[save_idx[0]]+(n+1))=0,j++;
						if(*(storage[save_idx[1]]+n)==')')
							*(storage[save_idx[1]]+(n+1))=0,j++;
						if(j==2)
							break;
					}
					printf("%s \n",storage[save_idx[0]]);
					printf("- - - \n");
					printf("%s \n",storage[save_idx[1]]);
				}
			}
		}
		else if(strcmp(input_str,"exit\n")==0)
			break;
		else
			printf("Please re-enter. \n");
	}
	return 0;
}

int find(char* storage[],int first,int last,char target[])
{
	int mid,n,down,up;
	char i=0;
	if(first>last)
	{
		while(*(storage[first]+i)!='(')
			i++;
		if(strncmp(storage[first],target,i-1)<0)
			save_idx[0]=first,save_idx[1]=first+1;
		else
			save_idx[0]=first-1,save_idx[1]=first;
		return -1;
	}
	mid=(first+last)/2;
	while(*(storage[mid]+i)!='(')
		i++;
	if(strncmp(storage[mid],target,i-1)==0)
	{
		n=0;
		count=1;
		down=mid,up=mid;
		save_idx[n++]=mid;
		while(1)
		{	
			down--,i=0;
			if(down>=0)
			{
			while(*(storage[down]+i)!='(')
				i++;
			if(strncmp(storage[down],target,i-1)==0)
				count++,save_idx[n++]=down;
			}
			up++,i=0;
			while(*(storage[up]+i)!='(')
				i++;
		    if(strncmp(storage[up],target,i-1)==0)
				count++,save_idx[n++]=up;
			else
				break;
		}
		return 0;
	}
	else if(strncmp(storage[mid],target,i-1)<0)
		return find(storage,mid+1,last,target);
	else
		return find(storage,first,mid-1,target);
}
