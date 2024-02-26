#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void add();
void list();
void edit();
void delete1();
void search();
int checkRoomNumberExists(char roomNumber[]);

void setcolor(int ForgC, int BackC) {
    // Function for setting console text color
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor | (BackC << 4));
    }
}


void login() {
    // Function for user login
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "vipul";
    char pass[10] = "1234";
    do {
        system("cls");
        printf("\n  **************************  LOGIN FORM  **************************  ");
        printf(" \n                       ENTER USERNAME:-");
        scanf("%s", &uname);
        printf(" \n                       ENTER PASSWORD:-");
        while (i < 10) {
            pword[i] = getch();
            c = pword[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;
        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            printf("  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL");
            break;
        } else {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
            a++;
            getch();
        }
    } while (a <= 2);
    if (a > 2) {
        printf("\nSorry you have entered the wrong username and password for three times!!!");
        getch();
        exit(0);
    }
    system("cls");
}

struct CustomerDetails {
    // Structure for storing customer details
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[35];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;

int main() {
    int i = 0;
    time_t t;
    time(&t);
    char choice;
    login();
    system("cls");
    while (1) {
        system("cls");
        setcolor(6,0);
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf("   ******************************  |MAIN MENU|  ***************************** \n");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        setcolor(6,0);
        printf("\t\t *Please enter your choice for menu*:");
        printf("\n\n");
        printf(" \n Enter 1 -> Book a room");
        printf("\n------------------------");
        printf(" \n Enter 2 -> View Customer Record");
        printf("\n----------------------------------");
        printf(" \n Enter 3 -> Delete Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 4 -> Search Customer Record");
        printf("\n-----------------------------------");
        printf(" \n Enter 5 -> Edit Record");
        printf("\n-----------------------");
        printf(" \n Enter 6 -> Exit");
        printf("\n-----------------");
        printf("\n");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\nCurrent date and time : %s", ctime(&t));
        for (i = 0; i < 80; i++)
            printf("-");
        choice = getche();
        choice = toupper(choice);
        switch (choice) {
            case '1':
                add();
                break;
            case '2':
                list();
                break;
            case '3':
                delete1();
                break;
            case '4':
                search();
                break;
            case '5':
                edit();
                break;
            case '6':
                system("cls");
                printf("\n\n\t *****THANK YOU*****");
                printf("\n\t FOR TRUSTING OUR SERVICE");
                exit(0);
                break;
            default:
                system("cls");
                printf("Incorrect Input");
                printf("\n Press any key to continue");
                getch();
        }
    }
}

void add() {
    // Function to add a customer record
    FILE *f;
    char test;
    f = fopen("add.dat", "ab+");
    if (f == NULL) {
        f = fopen("add.dat", "wb+");
        if (f == NULL) {
            printf("Error opening file!\n");
            return;
        }
    }
    while (1) {
        system("cls");
        printf("\nEnter Customer Details:");
        printf("\n**************************");
        printf("\nEnter Room number:\n");
        scanf("\n%s", s.roomnumber);
        fflush(stdin);
        
        // Check if room number already exists
        if (checkRoomNumberExists(s.roomnumber)) {
            printf("\nRoom number already exists! Please enter a different room number.\n");
            continue;
        }
        
        printf("Enter Name:\n");
      
       gets(s.name);
        printf("Enter Address:\n");
        scanf("%s", s.address);
        printf("Enter Phone Number:\n");
        scanf("%s", s.phonenumber);
        printf("Enter Nationality:\n");
        scanf("%s", s.nationality);
        printf("Enter Email:\n");
        scanf(" %[^\n]", s.email);
        printf("Enter Period('x' days):\n");
        scanf("%s", s.period);
        printf("Enter Arrival date(dd\\mm\\yyyy):\n");
        scanf("%s", s.arrivaldate);
        
        fwrite(&s, sizeof(struct CustomerDetails), 1, f);
        fflush(stdin);
        printf("\n\nRoom is successfully booked!!");
        printf("\nPress esc key to exit, any other key to add another customer detail:");
        test = getche();
        if (test == 27)
            break;
    }
    fclose(f);
}

void list() {
    FILE *f;
    int i, j;
    struct CustomerDetails temp, records[100]; 

    // Opening the file for reading
    if ((f = fopen("add.dat", "rb")) == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    // Read records from the file into an array
    int numRecords = 0;
    while (fread(&records[numRecords], sizeof(struct CustomerDetails), 1, f) == 1) {
        numRecords++;
    }
    fclose(f);

    // Sort the records based on room numbers in ascending order-- used bubble sort.
    for (i = 0; i < numRecords - 1; i++) {
        for (j = 0; j < numRecords - i - 1; j++) {
            if (atoi(records[j].roomnumber) > atoi(records[j + 1].roomnumber)) {
                temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }

    // Print the sorted records with specified labels and margin pattern
    system("cls");
    printf("--------------------------------------------------------------\n");
    printf("                       Customer Records                        \n");
    printf("--------------------------------------------------------------\n");
    
    for (i = 0; i < numRecords; i++) {
        printf("Room Number no:   %s\n", records[i].roomnumber);
        printf("Name:             %s\n", records[i].name);
        printf("Address:          %s\n", records[i].address);
        printf("Phone number:     %s\n", records[i].phonenumber);
        printf("Nationality:      %s\n", records[i].nationality);
        printf("Email:            %s\n", records[i].email);
        printf("Period:           %s\n", records[i].period);
        printf("Arrival date:     %s\n", records[i].arrivaldate);
        printf("--------------------------------------------------------------\n");
    }
    
    printf("--------------------------------------------------------------\n");
    getch();
}





void delete1() {
    // Function to delete a customer record
    FILE *f, *t;
    char roomnumber[20];
    int found = 0;
    struct CustomerDetails s;

    if ((t = fopen("temp.dat", "wb")) == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }
    if ((f = fopen("add.dat", "rb")) == NULL) {
        printf("Error opening file.\n");
        fclose(t);
        return;
    }

    system("cls");
    printf("Enter the Room Number of the hotel to be deleted from the database: \n");
    fflush(stdin);
    scanf("%s", roomnumber);

    while (fread(&s, sizeof(struct CustomerDetails), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(struct CustomerDetails), 1, t);
    }

    fclose(f);
    fclose(t);

    if (!found) {
        printf("\n\n Records of Customer in this  Room number is not found!!");
        remove("temp.dat");
        return;
    }

    remove("add.dat");
    rename("temp.dat", "add.dat");
    printf("\n\nThe Customer is successfully removed....");
}

void search() {
    // Function to search for a customer record
    system("cls");
    FILE *f;
    char roomnumber[20];
    int flag = 1;
    f = fopen("add.dat", "rb+");
    if (f == 0)
        exit(0);
    fflush(stdin);
    printf("Enter Room number of the customer to search its details: \n");
    scanf("%s", roomnumber);
    while (fread(&s, sizeof(struct CustomerDetails), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            flag = 0;
            printf("\n\tRecord Found\n ");
            printf("\nRoom Number:\t%s", s.roomnumber);
            printf("\nName:\t\t%s", s.name);
            printf("\nAddress:\t%s", s.address);
            printf("\nPhone number:\t%s", s.phonenumber);
            printf("\nNationality:\t%s", s.nationality);
            printf("\nEmail:\t\t%s", s.email);
            printf("\nPeriod:\t\t%s", s.period);
            printf("\nArrival date:\t%s", s.arrivaldate);
            flag = 0;
            break;
        }
    }
    if (flag == 1) {
        printf("\n\tRequested Customer could not be found!");
    }
    getch();
    fclose(f);
}

void edit() {
    // Function to edit a customer record
    FILE *f;
    int k = 1;
    char roomnumber[20];
    long int size = sizeof(s);
    if ((f = fopen("add.dat", "rb+")) == NULL)
        exit(0);
    system("cls");
    printf("Enter Room number of the customer to edit:\n\n");
    scanf("%s", roomnumber);
    fflush(stdin);
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            k = 0;
            printf("\nEnter Room Number     :");
            gets(s.roomnumber);
            printf("\nEnter Name    :");
            fflush(stdin);
            scanf("%s", &s.name);
            printf("\nEnter Address        :");
            scanf("%s", &s.address);
            printf("\nEnter Phone number :");
            scanf("%s", &s.phonenumber);
            printf("\nEnter Nationality :");
            scanf("%s", &s.nationality);
            printf("\nEnter Email :");
            scanf("%s", &s.email);
            printf("\nEnter Period :");
            scanf("%s", &s.period);
            printf("\nEnter Arrival date :");
            scanf("%s", &s.arrivaldate);
            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            break;
        }
    }
    if (k == 1) {
        printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
        fclose(f);
        getch();
    } else {
        fclose(f);
        printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");

        getch();
    }
}

int checkRoomNumberExists(char roomNumber[]) {
    // Function to check if a room number already exists in the data file
    FILE *f;
    struct CustomerDetails cust;
    f = fopen("add.dat", "rb");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    while (fread(&cust, sizeof(struct CustomerDetails), 1, f) == 1) {
        if (strcmp(cust.roomnumber, roomNumber) == 0) {
            fclose(f);
            return 1; // Room number found
        }
    }
    fclose(f);
    return 0; // Room number not found
}
