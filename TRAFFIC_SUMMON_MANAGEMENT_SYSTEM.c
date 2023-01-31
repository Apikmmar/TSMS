/*
    TRAFFIC SUMMON SYSTEM
    SECTION 01 GROUP 06
    PROGRAMMER:
        MUHAMMAD AFIQ AMMAR BIN MURAD
        MOHAMAD ZULFIKRY BIN MOHAMAD ZUKI
        NUR NAQIAH BINTI MUSTAZA
        NOR HIDAYATI BINTI KASIM
        SITI NUR ALIYAH BINTI FIRDAUS LIEW
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

struct Vehicle {
    char vehicleType[10];
    char platNo[8];
};

struct Date {
    int day;
    int month;
    int year;
};

struct Offender {
    char name[30];
    int age;
    char ic[13];
    struct Vehicle vehicle;
};

struct Summon {
    char fault[200];
    float fee;

    struct Offender offender;
    struct Date date;
    struct Summon *summonptrnext;
};

struct Summon *summonheadptr, *summonnewptr, *summoncurrentptr, *summondeleteptr, *summonprevptr;

struct IDSummon {
    char summonID[5];
    char icNum[13];

    struct IDSummon *idsummonptrnext;
};

struct IDSummon *idsummonheadptr, *idsummonnewptr, *idsummoncurrentptr, *idsummondeleteptr, *idsummonpreviousptr;

struct Police {
    char policeName[30];
    char policeID[8];
	char policePosition[30];
};

struct Police policeData(); // by afiq
struct Police policePos(); // by afiq
void printPoliceData(struct Police police); // by afiq
void userInterface(); // by al
void recordSummon(); // by naqiah
void listRecordedSummon(); // by naqiah
void searchSummon(); // by zul
void sortSummon(); // by aliyah
void swap(struct Summon *a, struct Summon *b); // by aliyah
void updateSummon(); // by hidayati
void deleteRecordedSummon(); // by hidayati
void closeSystem(struct Police police); // by zul

void main() {
    char choice;
    int userChoice = TRUE;
    int pass, x = 3;

    struct Police police;

    //Initializing pointers
    summonheadptr = (struct Summon *)NULL;
    idsummonheadptr = (struct IDSummon *) NULL;

    while (x!=0) {
        printf("\nInput the password: ");
        scanf("%d", &pass);

        if(pass == 1234) {
            printf("Correct password\n");
            break;
        } else {
            x--;
            if(x != 0) {
                printf("Wrong password, you have %d more chance\n", x);
            } else {
                printf("Too many wrong attempts, exiting the program\n");
                exit(0);
            }
        }
    }

    police = policeData();
    police = policePos();
    system("@cls||clear");
    printPoliceData(police);

    do {
        userInterface();
        printf("\n\nENTER YOUR CHOICE: ");
        scanf(" %c", &choice);

        choice = toupper(choice);

        switch (choice) {
            case 'I':
                printf("\n\nRECORD NEW SUMMON");
                recordSummon();
                break;

            case 'R' :
                printf("\n\nSORT ALL AVAILABLE SUMMON");
                sortSummon(summonheadptr);
                listRecordedSummon();
                break;

            case 'L':
                system("@cls||clear");
                printf("\n\nLIST ALL AVAILABLE SUMMON");
                listRecordedSummon();
                break;

            case 'S' :
                system("@cls||clear");
                printf("\n\nCHECK SUMMON");
                searchSummon();
                break;

            case 'D' :
                printf("\n\nDELETE LAST SUMMON");
                deleteRecordedSummon();
                listRecordedSummon();
                break;

            case 'U' :
                printf("\n\nUPDATE SUMMON");
                updateSummon();
                break;

            case 'X' :
                system("@cls||clear");
                closeSystem(police);
                userChoice = FALSE;
                exit(0);

            default :
                printf("Wrong input, please try again\n");
                break;
        }
    } while (userChoice);
}

struct Police policeData() {
    struct Police police;

    printf("\nEnter Your Name: ");
    scanf("%s", &police.policeName);
    printf("Enter Your Police ID: ");
    scanf("%s", &police.policeID);

    return police;
}

struct Police policePos() {
    struct Police police;

	printf("Enter Your Position(ACRONYM): ");
    scanf("%s", &police.policePosition);

    return police;
}

void printPoliceData(struct Police police) {
    time_t t;
    time(&t);

    fflush(stdin);
    printf("\nACCESSING TIME %s", ctime(&t));
    printf("WELCOME OFFICER %s", police.policeName);
    printf("\nPOSITION: %s",police.policePosition);
    printf("\nPOLICE ID: %s", police.policeID);
}

void userInterface() {
    printf("\n __________________________________");
    printf("\n| WELCOME TO TRAFFIC SUMMON SYSTEM |");
    printf("\n ++++++++++++++++++++++++++++++++++");
    printf("\n|       PLEASE CHOOSE OPTION       |");
    printf("\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|");
    printf("\n|         I. INSERT SUMMON         |");
    printf("\n|         L. LIST SUMMON           |");
    printf("\n|         R. SORT SUMMON           |");
    printf("\n|         S. SEARCH SUMMON         |");
    printf("\n|         D. DELETE SUMMON         |");
    printf("\n|         U. UPDATE SUMMON         |");
    printf("\n|         X. EXIT SYSTEM           |");
    printf("\n ----------------------------------");
}

void recordSummon() {
    // push stack
    idsummonnewptr = (struct IDSummon *)malloc(sizeof(struct IDSummon));

    printf("\nEnter IC Number: ");
    scanf("%s", &idsummonnewptr->icNum);
    printf("Enter Summon ID Number: ");
    scanf("%s", &idsummonnewptr->summonID);
    printf("ID RECORDED\n\n");

    if (idsummonheadptr == (struct IDSummon *)NULL) {
        idsummonheadptr = idsummonnewptr;
        idsummonnewptr->idsummonptrnext = (struct IDSummon *)NULL;
    } else {
        idsummoncurrentptr = idsummonheadptr;
        while(idsummoncurrentptr->idsummonptrnext != (struct IDSummon *)NULL) {
            idsummoncurrentptr = idsummoncurrentptr->idsummonptrnext;
        }

        idsummoncurrentptr->idsummonptrnext = idsummonnewptr;
        idsummonnewptr->idsummonptrnext = NULL;
    }

    //insert linked list
    summonnewptr = (struct Summon *)malloc(sizeof (struct Summon));

    printf("Enter Name: ");
    scanf("%s", &summonnewptr->offender.name);
    printf("Enter Age: ");
    scanf("%d", &summonnewptr->offender.age);
    printf("Enter Summon Date:-\n");
    printf("Day: ");
    scanf("%d", &summonnewptr->date.day);
    printf("Month: ");
    scanf("%d", &summonnewptr->date.month);
    printf("Year: ");
    scanf("%d", &summonnewptr->date.year);
    fflush(stdin);
    printf("Enter Vehicle Type: ");
    scanf("%[^\n]%*c", &summonnewptr->offender.vehicle.vehicleType);
    fflush(stdin);
    printf("Enter Plate Number: ");
    scanf("%[^\n]%*c", &summonnewptr->offender.vehicle.platNo);
    fflush(stdin);
    printf("Enter Fault: ");
    scanf("%[^\n]%*c", &summonnewptr->fault);
    fflush(stdin);
    printf("Enter Summon Fee: ");
    scanf("%f", &summonnewptr->fee);

    if (summonheadptr == (struct Summon *)NULL) {
        summonheadptr = summonnewptr;
        summonnewptr->summonptrnext = (struct Summon *)NULL;
    } else {
        summoncurrentptr = summonheadptr;

        while(summoncurrentptr->summonptrnext != (struct Summon *)NULL) {
            summoncurrentptr = summoncurrentptr->summonptrnext;
        }

        summoncurrentptr->summonptrnext = summonnewptr;
        summonnewptr->summonptrnext = NULL;
    }
    printf("SUMMON RECORDED\n");
}

void listRecordedSummon() {
    // list inserted data using stack
    if (idsummonheadptr == NULL) {
        printf("\nNo summon ID recorded");
    } else {
        idsummoncurrentptr = idsummonheadptr;
        printf("\nSummon ID\tIC Number");
        do {
            printf("\n%s\t\t%s", idsummoncurrentptr->summonID, idsummoncurrentptr->icNum);
            idsummoncurrentptr = idsummoncurrentptr->idsummonptrnext;
        } while (idsummoncurrentptr != (struct IDSummon *)NULL);
    }

    // list inserted data using linked list
    if(summonheadptr == (struct Summon*)NULL) {
        printf("\nNo summon recorded\n");
        return;
    }

    summoncurrentptr = summonheadptr;

    printf("\nName\tAge\tSummon Date\tVehicle Type\tPlate Number\tFault\tSummon Fee(RM)");
    do {
        fflush(stdin);
        printf("\n%s\t%d\t%d/%d/%d\t%s\t\t%s\t\t%s\t\t%.2f", summoncurrentptr->offender.name,summoncurrentptr->offender.age, summoncurrentptr->date.day, summoncurrentptr->date.month, summoncurrentptr->date.year, summoncurrentptr->offender.vehicle.vehicleType, summoncurrentptr->offender.vehicle.platNo, summoncurrentptr->fault, summoncurrentptr->fee);
        summoncurrentptr = summoncurrentptr->summonptrnext;
    } while (summoncurrentptr != (struct Summon*)NULL);
}

void searchSummon() {
    // search and print summon founded
    char searchSummon[15];

    fflush(stdin);
    if(summonheadptr == (struct Summon *)NULL) {
        printf("\nNo summon recorded");
    }
    else {

        printf("\nEnter offender name: ");
        fflush(stdin);
        scanf("%s", &searchSummon);

        summoncurrentptr = summonheadptr;

        while(summoncurrentptr->summonptrnext != (struct Summon *)NULL) {
            if(strcmp(summoncurrentptr->offender.name, searchSummon)==0) {
                goto searchfound;
                return;
            } else {
                summonprevptr = summoncurrentptr;
                summoncurrentptr = summoncurrentptr->summonptrnext;
            }

            searchfound:
            if(strcmp(summoncurrentptr->offender.name, searchSummon)==0) {
                printf("\nData founded!:-");
                printf("\nName\tAge\tSummon Date\tVehicle Type\tPlate Number\tFault\tSummon Fee(RM)");
                printf("\n%s\t%d\t%d/%d/%d\t\t%s\t\t%s\t%s\t%.2f", summoncurrentptr->offender.name,summoncurrentptr->offender.age, summoncurrentptr->date.day, summoncurrentptr->date.month, summoncurrentptr->date.year, summoncurrentptr->offender.vehicle.vehicleType, summoncurrentptr->offender.vehicle.platNo, summoncurrentptr->fault, summoncurrentptr->fee);
                summoncurrentptr;
                return;
            } else {
                printf("\nNo data founded");
            }
        }
    }
}

void swap(struct Summon *a, struct Summon *b) {
    struct Summon temp = *a;
    *a = *b;
    *b = temp;
}

void sortSummon(struct Summon *summonheadptr) {
   char sortChoice;
    printf("\nSorting....\n");

    printf("\nEnter category to sort by (A - Age, N - Name): ");
    scanf(" %c", &sortChoice);

    sortChoice = toupper(sortChoice);

    switch(sortChoice) {
        case 'A':
            // Use bubble sort to sort the linked list by offender's age
            summoncurrentptr = summonheadptr;
            printf("\nBefore sorting by age: \n");
            listRecordedSummon();
            while (summoncurrentptr != NULL) {
                summonprevptr = summoncurrentptr;
                summoncurrentptr = summoncurrentptr->summonptrnext;
                while (summoncurrentptr != NULL) {
                    if (summonprevptr->offender.age > summoncurrentptr->offender.age) {
                        swap(summonprevptr, summoncurrentptr);
                    }
                    printf("\nprev age : %d, curr age: %d", summonprevptr->offender.age, summoncurrentptr->offender.age);
                    summonprevptr = summoncurrentptr;
                    summoncurrentptr = summoncurrentptr->summonptrnext;
                }
            }

            printf("\nAfter sorting by age: \n");
            listRecordedSummon();
            break;

        case 'N':
            // Use bubble sort to sort the linked list by offender's name
            summoncurrentptr = summonheadptr;
            printf("Before sorting by name: \n");
            listRecordedSummon();

            while (summoncurrentptr != NULL) {
                summonprevptr = summoncurrentptr;
                summoncurrentptr = summoncurrentptr->summonptrnext;
                while (summoncurrentptr != NULL) {
                    if (strcmp(summonprevptr->offender.name, summoncurrentptr->offender.name) > 0) {
                        swap(summonprevptr, summoncurrentptr);
                    }
                    printf("prev name: %s, curr name: %s\n", summonprevptr->offender.name, summoncurrentptr->offender.name);

                    summonprevptr = summoncurrentptr;
                    summoncurrentptr = summoncurrentptr->summonptrnext;
                }
            }
             printf("After sorting by name: \n");
            listRecordedSummon();
            break;

        default: printf("Invalid choice.\n");
    }
    
    printf("Sorting done\n");
}

void updateSummon() {
    char update[15];

    fflush(stdin);
    if(summonheadptr == (struct Summon*)NULL) {
        printf("\nNo summon recorded");
    } else {
        printf("\nEnter offender name: ");
        fflush(stdin);
        scanf("%s", &update);

        summoncurrentptr = summonheadptr;

        while(summoncurrentptr->summonptrnext != (struct Summon *)NULL) {
            if(strcmp(summoncurrentptr->offender.name, update)==0) {
                printf("\nSummond Found!\n");
            } else {
                summonprevptr = summoncurrentptr;
                summoncurrentptr = summoncurrentptr->summonptrnext;
            }

            if(strcmp(summoncurrentptr->offender.name, update)==0) {
                fflush(stdin);
                printf("\nUpdate new summon fee: ");
                scanf("%f", &summoncurrentptr->fee);

                printf("\nName\tAge\tSummon Date\tVehicle Type\tPlate Number\tFault\tSummon Fee(RM)");
                printf("\n%s\t%d\t%d/%d/%d\t\t%s\t\t%s\t\t%s\t%.2f", summoncurrentptr->offender.name,summoncurrentptr->offender.age, summoncurrentptr->date.day, summoncurrentptr->date.month, summoncurrentptr->date.year, summoncurrentptr->offender.vehicle.vehicleType, summoncurrentptr->offender.vehicle.platNo, summoncurrentptr->fault, summoncurrentptr->fee);
                summoncurrentptr;
                return;
            } else {
                printf("\nNo data founded");
            }
        }
    }
}

void deleteRecordedSummon() {
    // pop stack
    if(idsummonheadptr == NULL) {
        printf("\nNo data recorded yet");
    } else {
        idsummondeleteptr = idsummonheadptr;
        printf("\nID deleted");
        idsummonheadptr = idsummondeleteptr->idsummonptrnext;
        free(idsummondeleteptr);
    }

    // delete linked list
    if(summonheadptr == (struct Summon *)NULL) {
        printf("\nNo summon recorded");
    } else {
        printf("\nSummon deleted");
        summoncurrentptr = summonheadptr;

        summonheadptr = summonheadptr -> summonptrnext;
        free(summoncurrentptr);
    }
}

void closeSystem(struct Police police) {
    time_t t;
    time(&t);

    printf("\nSYSTEM LOG OUT");
    printf("\nTIME LOGGING OUT %s", ctime(&t));
    printf("THANK YOU %s %s", police.policePosition, police.policeName);
    printf("\nHAVE A NICE DAY!!!");
}