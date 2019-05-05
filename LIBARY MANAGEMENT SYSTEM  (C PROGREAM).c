#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#define RETURNTIME 15

//list of function prototype
char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechanical","Architecture"};
void returnfunc();
void mainmenu();
void addbooks();
void deletebooks();
void editbooks();
void searchbooks();
void issuebooks();
void viewbooks();
void closeapplication();
int  getdata();
int  checkid();
int t();
//void show_mouse(void);
void Password();
void issuerecord();
void loaderanim();

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
//list of global files that can be accede form anywhere in program
FILE *fp,*ft,*fs;

int s;
char findbook;
char password[10]={"anik"};

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
int main()

{
      Password();
      getch();
   return 0;

}
void mainmenu()
{
    system("cls");

	int i;

	printf("\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
	printf("\n\xDB\xDB\xDB\xDB 1. Add Books \n  ");
	printf("\n\xDB\xDB\xDB\xDB 2. Delete books\n");
	printf("\n\xDB\xDB\xDB\xDB 3. Search Books\n");
	printf("\n\xDB\xDB\xDB\xDB 4. Issue Books\n");
	printf("\n\xDB\xDB\xDB\xDB 5. View Book list\n");
	printf("\n\xDB\xDB\xDB\xDB 6. Edit Book's Record\n");
	printf("\n\xDB\xDB\xDB\xDB 7. Close Application\n");
	printf("\n------------------------------------------\n");
	t();
	printf("\t\t\tEnter your choice:");
	switch(getch())
	{
		case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
		case '3':
		searchbooks();
	    break;
	case '4':
		issuebooks();
	    break;
	    case '5':
		viewbooks();
		break;
	    case '6':
		editbooks();
		break;
	    case '7':
	    {
		system("cls");
		printf("Thanks for using the Program..");
		printf("Exiting in 5 second...........>");

		delay(5000);
		exit(0);
	    }
	    default:
		{
		printf("\aWrong Entry!!Please re-entered correct option");
		if(getch())
		mainmenu();
		}

    }
}
void addbooks(void)    //function that add books
{
	system("cls");
	int i;
	printf("\t\t\tSELECT CATEGOIES\n");
	printf("\n1. Computer\n");
	printf("\n2. Electronics\n");
	printf("\n3. Electrical\n");
	printf("\n4. Civil\n");
	printf("\n5. Mechanical\n");
	printf("\n6. Architecture\n");
	printf("\n7. Back to main menu\n");
	printf("\n\t\t\tEnter your choice:");
	scanf("%d",&s);
	if(s==7)

	mainmenu() ;
	system("cls");
	fp=fopen("Bibek.dat","ab+");
	if(getdata()==1)
	{
	a.cat=catagories[s-1];
	fseek(fp,0,SEEK_END);
	fwrite(&a,sizeof(a),1,fp);
	fclose(fp);

	printf("\nThe record is successfully saved\n");

	printf("\nSave any more?(Y / N):");
	if(getch()=='n')
	    mainmenu();
	else
	    system("cls");
	    addbooks();
	}
}
void deletebooks()    //function that delete items from file fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
	system("cls");
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("Bibek.dat","rb+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
	    if(a.id==d)
	    {

		printf("\tThe book record is available\n");
		printf("\n\tBook name is %s",a.name);
		printf("\n\tRack No. is %d",a.rackno);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    printf("\n\tNo book record is found modify the search for next step");
	    if(getch())
	    mainmenu();
	}
	if(findbook=='t' )
	{
	    printf("\t\t\nDo you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("test.dat","wb+");  //temporary file for delete
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
		    if(a.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);
			fwrite(&a,sizeof(a),1,ft);
		    }                              //we want to delete
		}
		fclose(ft);
		fclose(fp);
		remove("Bibek.dat");
		rename("test.dat","Bibek.dat"); //copy all item from temporary file to fp except that
		fp=fopen("Bibek.dat","rb+");    //we want to delete
		if(findbook=='t')
		{
		    printf("\t\t\nThe record is successfully deleted\n");
		    printf("\t\t\nDelete another record?(Y/N)");
		}
	    }
	else
	mainmenu();
	fflush(stdin);
	another=getch();
	}
	}
    mainmenu();
}
void searchbooks()
{
    system("cls");
    int d;
    printf("\n\n*****************************Search Books*********************************\n");
    printf("\n1. Search By ID\n");
    printf("\n2. Search By Name\n");
    printf("\t\t\t\nEnter Your Choice\n");
    fp=fopen("Bibek.dat","rb+");       //open file for reading propose
    rewind(fp);                         //move pointer at the beginning of file
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    printf("\t\t****Search Books By Id****\n");
	    printf("\nEnter the book id:\n");
	    scanf("%d",&d);
	    printf("\t\tSearching........");
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(a.id==d)
		{
		    printf("The Book is available\n");
		    printf("\xB2 ID:%d\n",a.id);
		    printf("\n\xB2 Name:%s\n",a.name);
		    printf("\n\xB2 Author:%s \n",a.Author);
		    printf("\n\xB2 Quantity:%d\n ",a.quantity);
		    printf("\n\xB2 Price:Rs.%.2f\n",a.Price);
		    printf("\n\xB2 Rack No:%d \n",a.rackno);
		    findbook='t';
		}

	    }
	    if(findbook!='t')  //checks whether condition enters inside loop or not
	    {
	    printf("\aNo Record Found\n");
	    }

	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    printf("****Search Books By Name****\n");
	    printf("\nEnter Book Name:\n");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&a,sizeof(a),1,fp)==1)
	    {
		if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
		{
		    printf("The Book is available\n");
		    printf("\n\xB2 ID:%d\n",a.id);
		    printf("\n\xB2 Name:%s\n",a.name);
		    printf("\n\xB2 Author:%s\n",a.Author);
		    printf("\n\xB2 Quantity:%d\n",a.quantity);
		    printf("\n\xB2 Price:Rs.%.2f\n",a.Price);
		    printf("\n\xB2 Rack No:%d \n",a.rackno);

		    d++;
		}

	    }
	    if(d==0)
	    {
         printf("\aNo Record Found\n");
	    }

	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchbooks();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchbooks();
    }
    fclose(fp);
}
void issuebooks(void)  //function that issue books from library
{
    int t;

    system("cls");
    printf("\n\n********************************ISSUE SECTION**************************");
    printf("\n1. Issue a Book\n");
    printf("\n2. View Issued Book\n");
    printf("\n3. Search Issued Book\n");
    printf("\n4. Remove Issued Book\n");
    printf("\t\t\t\nEnter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{
		system("cls");
		int c=0;
		char another='y';
		while(another=='y')
		{
			system("cls");
			printf("\n\n***Issue Book section***");
			printf("\nEnter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Bibek.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0) //issues those which are present in library
			{
			     printf("The book record is available\n");                          // struct dosdate_t d; //for current date

			     printf("\nThere are %d unissued books in library \n",a.quantity);    // _dos_getdate(&d);

			     printf("\nEnter student name:");                                   // a.issued.dd=d.day;

			     printf("\nThe name of book is %s\n",a.name);                       // a.issued.mm=d.month;
                                                                                //a.issued.yy=d.year;
			     scanf("%s",a.stname);
			     printf("\nIssued date=%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
			     printf("\nThe BOOK of ID %d is issued\n",a.id);
			     a.duedate.dd=a.issued.dd+RETURNTIME;   //for return date
			     a.duedate.mm=a.issued.mm;
			     a.duedate.yy=a.issued.yy;
			     if(a.duedate.dd>30)
			     {
				 a.duedate.mm+=a.duedate.dd/30;
				 a.duedate.dd-=30;

			     }
			     if(a.duedate.mm>12)
			     {
				a.duedate.yy+=a.duedate.mm/12;
				a.duedate.mm-=12;

			     }
			     printf("To be return:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			     fseek(fs,sizeof(a),SEEK_END);
			     fwrite(&a,sizeof(a),1,fs);
			     fclose(fs);
			     c=1;
			}
			if(c==0)
			{

			printf("No record found");
			}
			printf("Issue any more(Y/N):");
			fflush(stdin);
			another=getche();
			fclose(fp);
		}

		break;
	}
	case '2':  //show issued book list
	{
		system("cls");
		int j=4;
		printf("\n\n*******************************Issued book list*******************************\n");
		printf("\nSTUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
	       fs=fopen("Issue.dat","rb");
		while(fread(&a,sizeof(a),1,fs)==1)
		{
			printf("%s\n",a.stname);
			printf("\n%s",a.cat);
			printf("\n%d",a.id);
			printf("\n%s",a.name);
			printf("\n%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
			printf("\n%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy); //printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

		}
		fclose(fs);
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		system("cls");
		printf("Enter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==p)
				{
					issuerecord();
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				printf("No Record Found");
			}
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  //remove issued books from list
	{
		system("cls");
		int b;
		FILE *fg;  //declaration of temporary file for delete
		char another='y';
		while(another=='y')
		{
			printf("Enter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.dat","rb+");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					printf("Do You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.dat","wb+");
						rewind(fs);
						while(fread(&a,sizeof(a),1,fs)==1)
						{
							if(a.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&a,sizeof(a),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						printf("\nThe issued book is removed from list");

				       }

				}
				if(findbook!='t')
          {
                    printf("\nNo Record Found");
				}
			}
			printf("\nDelete any more?(Y/N)");
			another=getch();
		}
	}
	default:
	printf("\aWrong Entry!!");
    getch();
	issuebooks();
	break;
      }
      returnfunc();
}
void viewbooks(void)  //show the list of book persists in library
{
    int i=0,j;
    system("cls");
    printf("\n\n*********************************Book List*****************************\n");
    printf("\n CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo \n");
    j=4;
    fp=fopen("Bibek.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
	printf("%s\n",a.cat);
	printf("%d\n",a.id);
	printf("%s\n",a.name);
	printf("%s\n",a.Author);
	printf("%d\n",a.quantity);
	printf("%.2f\n",a.Price);
	printf("%d\n",a.rackno);
	printf("\n\n");
	j++;
	i=i+a.quantity;
      }
      printf("\nTotal Books =%d",i);
      fclose(fp);
      returnfunc();
}
void editbooks(void)  //edit information about book
{
	system("cls");
	int c=0;
	int d,e;
	printf("\n\n****Edit Books Section****");
	char another='y';
	while(another=='y')
	{
		system("cls");
		printf("\nEnter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("Bibek.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("The book is available\n");
				printf("The Book ID:%d\n",a.id);
				printf("\nEnter new name:");scanf("%s",a.name);
				printf("\nEnter new Author:");scanf("%s",a.Author);
				printf("\nEnter new quantity:");scanf("%d",&a.quantity);
				printf("\nEnter new price:");scanf("%f",&a.Price);
				printf("\nEnter new rackno:");scanf("%d",&a.rackno);
				printf("\nThe record is modified");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);http://paste.ubuntu.com/15205483/
				c=1;
			}
			if(c==0)
			{
				printf("No record found");
			}
		}
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void returnfunc(void)
{
    {
	printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
	int t;
    printf("\t\t\nEnter the Information Below\n");
	printf("\nCategory:");
	printf("%s",catagories[s-1]);
	printf("\nBook ID:\t");
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
        printf("\aThe book id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	printf("Book Name:");
	scanf("%s",a.name);
	printf("\nAuthor:\n");
	scanf("%s",a.Author);
	printf("\nQuantity:");
	scanf("%d",&a.quantity);
	printf("\nPrice:");
	scanf("%f",&a.Price);
	printf("\nRack No:");
	scanf("%d",&a.rackno);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void Password(void) //for password option
{

   system("cls");
    printf("\n\t*************************************************\n");
    printf("\n\t\tWELCOME TO LIBRARY MANAGMENT SYSTEM\n");
    printf("\n\t*************************************************\n");

   char d[25]=" Password Protected";
   char ch,pass[10];
   int i=0,j;
    for(j=0;j<20;j++)
    {
    delay(20);
    printf("*");
    }
    for(j=0;j<20;j++)
   {
   delay(30);
   printf("%c",d[j]);
   }
   for(j=0;j<20;j++)
   {
   delay(30);
   printf("*");
   }
   printf("\t\t\nEnter Password:");http://paste.ubuntu.com/15205483/

   while(ch!=13)
   {
	ch=getch();

	if(ch!=13 && ch!=8){
	putch('*');
	pass[i] = ch;
	i++;
	}
   }
   pass[i] = '\0';
   if(strcmp(pass,password)==0)
   {
	printf("\nPassword matched");
	printf("\t\t\nPress any key to continue.....");
	getch();
	mainmenu();
   }
   else
   {
	 printf("\aWarning!! Incorrect Password");
	 getch();
	 Password();
   }
}
void issuerecord()  //display issued book's information
{
		 system("cls");
		 printf("The Book has taken by %s\n",a.stname);
		 printf("\nIssued Date:%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
		 printf("\nReturning Date:%d-%d-%d\n",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
void loaderanim()
{
int loader;
system("cls");
printf("LOADING........");
printf("\n\n");
for(loader=1;loader<20;loader++)
{
printf("%c",219);}
}
