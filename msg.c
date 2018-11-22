#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
struct whatsapp
{
        char id[20];
        char pswd[20];
};
 
struct whatsapp user1;
void login(FILE *);
void send();
void rec();
void signup(FILE *);
struct msgqbuf
{
        long mtype;
        char mtext[50];
};
typedef struct msgqbuf msgque;
 
int main()
{
	int i,z;
	FILE *fp; 
        char ch;
        char str[50];
	fp=fopen("database.txt","r+");
	if(fp==NULL)
	{
		perror("\nError in opening file...\n");
		exit(1);
	}
 
        do
        {
                system("clear");
                printf("\n************************\n* Linux Chat Messenger *\n************************\n\n");
                printf("Enter Choices:\n\n1.Login\n\n2.New User\n\n");
                scanf("%d",&i);
		switch(i)
		{
                	case 1:	
				rewind(fp);
				login(fp);
				break;
			case 2:
				signup(fp);
				break;
		        default:
				printf("\nInvalid Options\n");
		}
                sleep(5);
                system("clear");
                printf("\nDo U wish to continue chat....\nY:Yes\nN:No\n");
		scanf(" %c",&ch);
	}while(ch=='y'||ch=='Y');
	fclose(fp);
	return 0;
}
void send()
{
        int msgqid,siz,siz1,i,client_id,ans; 
	char ch,client_[2];
	msgque q,q1;	
	printf("\nEnter Client ID to chat:-\n");
	printf("Client ID's are:\n1.ID-0 Name-Mohit\n2.ID-1 Name-Manoj\n");
        scanf("%d",&client_id);	
	switch(client_id)
	{
	case 0:
        	msgqid=msgget(1234,0666|IPC_CREAT);
        	if(msgqid==-1)
        	{
         	        perror("\nMsg Queue Can't Create...\n");
                	exit(1);
        	}
        	else
        	{
                	printf("\nMsg Queue Created Successfully...\n");
                	q.mtype=0;
          send_again: 	printf("\nEnter Message:\n");
			scanf("%s",q.mtext);
			while(strcmp(q.mtext,"bye")!=0)
			{
				siz=msgsnd(msgqid,q.mtext,strlen(q.mtext),0);
                		if(siz==-1)
                		{
                			perror("\nMsg Sending Failed....\n");
                        		exit(1);
                		}	
                		else if(siz==0)
                		{
                 	       		printf("\nMsg Sent Successfully...\n");
					printf("\nWhat do you want now?\n1.Send\n2.Recieve\n");
					scanf("%d",&ans);
					
					if(ans==1)
					{
						goto send_again;	
					}
					else
					{
						rec();
					}
				}
			}
		}
//	rec();
			break;
	case 1:
        	msgqid=msgget(1234,0666|IPC_CREAT);
        	if(msgqid==-1)
        	{
         	       perror("\nMsg Queue Can't Create...\n");
                       exit(1);
        	}
        	else
        	{
                	printf("\nMsg Queue Created Successfully...\n");
                	q.mtype=0;
    again_send2:            	printf("\nEnter Message:\n");
			scanf("%s",q.mtext);
			while(strcmp(q.mtext,"bye")!=0)
			{
				siz=msgsnd(msgqid,q.mtext,strlen(q.mtext),0);
                		if(siz==-1)
                		{
                			perror("\nMsg Sending Failed....\n");
                        		exit(1);
                		}	
                		else if(siz==0)
                		{
                 	       		printf("\nMsg Sent Successfully...\n");
					printf("\nWhat do you want now?\n1.Send\n2.Recieve\n");
					scanf("%d",&ans);
					if(ans==1)
					{
						goto again_send2;	
					}
					else
					{
						rec();
					}
				}
			}
		}
	break;
	default:
		break;
}
}
void rec()
{
 
        int msgqid,siz,siz1,i,ans;
        char ch;
        msgque q,q1;    
        msgqid=msgget(1234,0666|IPC_CREAT);
        if(msgqid==-1)
        {
                perror("\nMsg Queue Can't Create...\n");
                exit(1);
        }
        else
        {
                printf("\nMsg Queue Created Successfully...\n");
                q.mtype=0;
                printf("\nNow reading\n");
		while(strcmp(q.mtext,"bye")!=0)
		{                
                	siz=msgrcv(msgqid,q.mtext,BUFSIZ,0,0);
                	if(siz1==-1)
                	{
	                	perror("\nMsg Recieve Error\n");
                        	exit(1);
                	}
                	else
                	{
                        	printf("\nMsg Recieved Successfully...\n");
                        	printf("\nMsg:%s\tSize:%d\n",q.mtext,siz);
				printf("\nWhat do you want now?\n1.Send\n2.Recieve\n");
				scanf("%d",&ans);
				if(ans==1)
				{
					send();		
				}
				else
				{
					rec();
                		}
			}
		}
	}
}
 
void login(FILE *fp)
{
	int k,z;
	char u[20],p[20],ch;
        int n=0;
        system("clear");
        printf("\nLogin into your messenger\n");
        printf("\nWarning:3 attempts only\n");
        login:
                fread(&user1,sizeof(user1),1,fp);
                printf("\nEnter User ID:");
                scanf("%s",u);
                printf("\nEnter Password:");
                scanf("%s",p);
                if(strcmp(user1.id,u)==0 && strcmp(user1.pswd,p)==0)
                {
                        printf("Congratulations!");
                        sleep(1);
			system("clear");
			printf("\nChoose what to do???\n1:Send a Message\n2.Read a message\n");
			scanf("%d",&z);
			if(z==1)
                        send();
			else if(z=2)
			rec();
                }
                else
                {
                        while(n<2)
                        {
                                n++;
                                printf("\nIncorrect user-id or password,%d trials left.\n",3-n);
                                goto login;
                                if(n==3)
                                {
                                        printf("\nTry Later\n");
                                        break;
                                }
                        }
                }
}
        
void signup(FILE *fp)
{
	int st=0,num=0,i,chr=0;
again:	
	num=0;
	chr=0;
	printf("\nEnter Mobile Number as a User ID to Create:\n");
	scanf("%s",&user1.id);
	for(i=1;i<strlen(user1.id);i++)
	{
		if(user1.id[i]>'0' && user1.id[i]<='9')
		{
			num=1;
		}
		else if(user1.id[i]>='a' && user1.id[i]<='z' || user1.id[i]>='A' && user1.id[i]<='Z')
		{
			chr=1;
		}
 
	}
	if(chr==1 && num==1)
	{
		goto again;
	}
	else if(chr==1)
	{
		goto again;
	}
	else 
	{
		st=1;
	}
	printf("\nEnter password to Create:\n");
	scanf("%s",&user1.pswd);
	st=2;
	printf("\nCongratulations.....Your registration is Completed...Thank You!!\n\n \nYou are being redirected to Main Portal.....\n");
        switch(st)
        {
        	case 2:
                       fwrite(&user1,sizeof(user1),1,fp);
                       printf("\nRecord saved successfully\n");
                       break;
               default:
                       perror("\nData can't be saved because of wrong entries.\n");
                       exit(1);
        }
	sleep(1);
}
