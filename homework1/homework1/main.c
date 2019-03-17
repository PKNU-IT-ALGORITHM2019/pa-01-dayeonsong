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
		{
			while(fgets(str,sizeof(str),fp)!=NULL)
			{
					storage[i]=(char*)malloc(1500);
					strcpy(storage[i],str);
					i++;
					fgets(str,sizeof(str),fp);
			}
		}
		else if(strcmp(input_str,"size\n")==0)
		{
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