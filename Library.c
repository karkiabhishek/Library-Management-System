#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
//Defined Marcos*******************************
#define flush fflush(stdin)
#define coff printf("\e[?25l")
#define con printf("\e[?25h")
//Defined Structures....**************************************************
typedef struct
    {
        char name[50];
        char author[25];
        int id,price;
        int rackno;
    }BOOK;

typedef struct
{
    char name[30];
    int sem;
    char faculty[20];
    int batch;
    char group;
    int rollno;
}STUDENT;

typedef struct
{
char bname[30];
char sname[30];
time_t time;
}ISSUEBOOK;
//****************************************************************

//Global FILES**********************************
FILE *fp,*ft,*fs,*fi;

//Function Declaration...**********************************
void printmenu();
void upper(char*);
void add_book();
void read_book();
void delete_book();
void add_student();
void read_student();
void delete_student();
void issue_book();
void view_issued_books();
void gotoxy(int,int);
void Password();
void welcome();

//Global Variables...*****************************************
BOOK b;
STUDENT s;
ISSUEBOOK ib;
COORD c={0,0};
char password[20]="nirajan";

//MAIN ******************************************
void main()
{
    char ch;
    Password();
    while(ch!=27)
    {
       printmenu();
       ch=getch();
       if(ch=='1') add_book();
       else if(ch=='2') read_book();
       else if(ch=='3') delete_book();
       else if(ch=='4') add_student();
       else if(ch=='5') read_student();
       else if(ch=='6') delete_student();
       else if(ch=='7') issue_book();
       else if(ch=='8') view_issued_books();
       else if (ch!=27){ gotoxy(24,15);
            printf("\aWrong Entry!! Please re-enter correct option...");coff;
            Sleep(1000);
            con;}
    }
}
//Welcome Function*************************

//GOTO Co-ordinate Function*******************
void gotoxy(int x,int y)
{
    c.X=x;c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
//Password Login Function*********************
void Password()
{
char ch,pass[10];
int i=0;
line2:
system("cls");
gotoxy(15,7);
printf("Enter Password:");
int state=1,len=strlen(password);
do
{
ch=getch();
if (ch==8 && i>=0){
if (i==0) continue;
i--;
gotoxy(30+i,7);printf(" ");
gotoxy(30+i,7);
continue;
}

putch('*');
pass[i] = ch;
if (pass[i]==password[i]) {
gotoxy(15,8);
printf("Continue Typing....");
}
else
{
    gotoxy(15,8);
    printf("Password Wrong!!!!!");

}
gotoxy(31+i,7);
i++;

}while (i<len);
pass[i]='\0';
if(strcmp(pass,password)!=0)
{
i=0;
goto line2;}

}

//UPPER string*******************
void upper(char *a)
{
    while(*a!='\0')
    {
        *a=toupper(*a);
        a++;
    }
}
//PRINT Menu******************************
void printmenu()
{
    system("cls");
    printf("\n\n\n\n");
    printf("\t\t\t1. Add Books.\n");
    printf("\t\t\t2. Display Books.\n");
    printf("\t\t\t3. Delete Book Record.\n");
    printf("\t\t\t4. Add Students.\n");
    printf("\t\t\t5. Display Students.\n");
    printf("\t\t\t6. Delete Student Record.\n");
    printf("\t\t\t7. Issue Book to the Student.\n");
    printf("\t\t\t8. View Issued Books.\n");

    printf("\n\t\t\tSelect the Task(ESC to Exit): ");
}
//Add BOOK function *********************************
void add_book(){
    system("cls");
    char cha;
    printf("Enter the new book records.\n");
    fp=fopen("Books.dat","ab");
    while(1){
    printf("ID: ");
    scanf("%d",&b.id);flush;
    printf("Name: ");
    gets(b.name);upper(b.name);
    printf("Author: ");
    gets(b.author);upper(b.author);
    printf("Price: ");
    scanf("%d",&b.price);flush;
    printf("Rack NO: ");
    scanf("%d",&b.rackno);
    fwrite(&b,sizeof(b),1,fp);
    printf("Press (ESC) to Exit...Other to Continue ");
    cha=getch();
    if(cha==27) break;
    printf("\n\nNEW RECORD:\n");
    }
    fclose(fp);
}

//Read Books Function********************************
void read_book(){
    system("cls");
    fp=fopen("Books.dat","rb");
    int i=0;
    while(fread(&b,sizeof(b),1,fp)!=0){
    i=1;
    printf("ID: %d\n",b.id);
    printf("Name: ");
    puts(b.name);
    printf("Author: ");
    puts(b.author);
    printf("Price: %d\n",b.price);
    printf("Rack No: %d\n\n",b.rackno);
    getch();
    }
    fclose(fp);
    if(i==0) {printf("No Books are Added Till Now!!!");getch();}
}

void delete_book()
{
    system("cls");
    int inpu;
    char input[25];
    fp=fopen("Books.dat","rb");
    ft=fopen("Temp.dat","wb");
    printf("Select Deleting Method:\n");
    printf("1.By Name of Book.\n");
    printf("2.By ID of book\n");
    switch(getch())
    {
case '1':

    printf("Enter the name of Book: ");
    flush;
    gets(input);upper(input);
    while(fread(&b,sizeof(b),1,fp)!=0)
    {
        if(strcmp(b.name,input)!=0)
            {
                fwrite(&b,sizeof(b),1,ft);
            }
    }
    break;
case '2':

    printf("Enter the ID of Book: ");
    scanf("%d",&inpu);
    while(fread(&b,sizeof(b),1,fp)!=0)
    {
        if(b.id!=inpu)
            {
                fwrite(&b,sizeof(b),1,ft);
            }
    }
    break;
    }

    fclose(fp);
    fclose(ft);
    remove("Books.dat");
    rename("Temp.dat","Books.dat");
}

//Add Student Function *****************************************
void add_student()
{
    system("cls");
    char chr;
    fs=fopen("Students.dat","ab");
    printf("Enter the records of the students:\n");
    printf("Roll No: ");
    scanf("%d",&s.rollno);flush;
    printf("Name: ");
    gets(s.name);upper(s.name);
    printf("Group: ");
    scanf("%c",&s.group);flush;s.group=toupper(s.group);
    printf("Faculty: ");
    gets(s.faculty);upper(s.faculty);
    printf("Semester: ");
    scanf("%d",&s.sem);flush;
    printf("Batch: ");
    scanf("%d",&s.batch);flush;
    fwrite(&s,sizeof(s),1,fs);
    while(1)
    {
    printf("Press (ESC) to exit: ");
    chr=getch();
    if(chr==27) {flush;break;}
    printf("\n\nNEW RECORD:\n");
    printf("Roll No: ");
    scanf("%d",&s.rollno);flush;
    printf("Name: ");
    gets(s.name);upper(s.name);
    printf("Group: ");
    scanf("%c",&s.group);flush;s.group=toupper(s.group);
    printf("Faculty: ");
    gets(s.faculty);upper(s.faculty);
    fwrite(&s,sizeof(s),1,fs);
    }
    fclose(fs);
}

 //Read Student***************
 void read_student()
 {
    system("cls");
    int i=0;
    fs=fopen("Students.dat","rb");
    while(fread(&s,sizeof(s),1,fs)!=0){
    i=1;
    printf("Roll No: ");
    printf("%d\n",s.rollno);
    printf("Name: ");
    puts(s.name);
    printf("Group: ");
    printf("%c\n",s.group);
    printf("Faculty: ");
    puts(s.faculty);
    printf("Semester: ");
    printf("%d\n",s.sem);
    printf("Batch: ");
    printf("%d\n\n",s.batch);
    getch();
    }
    if(i==0) {printf("No Students are Added Till Now!!!");getch();}
    fclose(fs);


 }

 //Delete Student*************
 void delete_student()
{
    system("cls");
    int inpu;
    char input[25];
    fs=fopen("Students.dat","rb");
    ft=fopen("Temp.dat","wb");
    printf("Select Deleting Method:\n");
    printf("1.By Name of Student.\n");
    printf("2.By Roll no. of Student.\n");
    switch(getch())
    {
case '1':

    printf("Enter the name of Student: ");
    flush;
    gets(input);upper(input);
    while(fread(&s,sizeof(b),1,fs)!=0)
    {
        if(strcmp(s.name,input)!=0)
            {
                fwrite(&s,sizeof(s),1,ft);
            }
    }
    break;
case '2':

    printf("Enter the roll no. of Student: ");
    scanf("%d",&inpu);
    while(fread(&s,sizeof(s),1,fs)!=0)
    {
        if(s.rollno!=inpu)
            {
                fwrite(&s,sizeof(s),1,ft);
            }
    }
    break;
    }

    fclose(fs);
    fclose(ft);
    remove("Students.dat");
    rename("Temp.dat","Students.dat");
}

void issue_book()
{
    system("cls");
    fi=fopen("Issue.dat","wb");
    fs=fopen("Students.dat","rb");
    fp=fopen("Books.dat","rb");
    printf("Enter Data Required to be Issued.\n");
    printf("Issue to: ");
    gets(ib.sname);upper(ib.sname);
    int check=0;
    while(fread(&s,sizeof(s),1,fs)!=0)
    {
    if(strcmp(ib.sname,s.name)==0) {check=1;break;};
    }
    if (check==1)
    {
        check=0;
        printf("Book Name: ");
        gets(ib.bname);upper(ib.bname);
        while(fread(&b,sizeof(b),1,fp)!=0)
        {
        if(strcmp(ib.bname,b.name)==0) {check=1;break;}
        }
        if(check==1)
        {
            ib.time=time(0);
            fwrite(&ib,sizeof(ib),1,fi);
        }
        else printf("No Such Book Found !!! Please Add The Book First.");

    }
    else printf("No Such Student Found!!! Please Add The Student First.");
    getch();
    fclose(fp);
    fclose(fs);
    fclose(fi);
}

void view_issued_books()
{
    double d;
    int da,h,m;
    system("cls");
    int i=0;
    fi=fopen("Issue.dat","rb");
    while(fread(&ib,sizeof(ib),1,fi)!=0)
    {
        i=1;
        printf("Student: ");
        puts(ib.sname);
        printf("Book Issued: ");
        puts(ib.bname);
        d=difftime(time(0),ib.time);
        da=d/86400;
        h=(int)(d/3600)%24;
        m=(int)(d/60)%60;
        printf("Taken for %d Days %d Hours %d Minutes",da,h,m);
        getch();

    }
    fclose(fi);
    if(i==0){printf("No Books Issued Till Now.");getch();}
}
