#include "MangaIMS.h"

// <============ Input Management and General =============>

void pressEnterToContinue() {
    printf("\33[0mPress \033[1;32m[Enter]\033[0m to continue...\n");
    while (getchar() != '\n'){};
    getchar();
    system("cls");
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int valid_date(Date date) {
    int day = atoi(date.day);
    int month = atoi(date.month);
    int year = atoi(date.year);
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(isLeapYear(year))
        daysInMonth[1] = 29;

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) 
        return 0;

    return 1; // Valid date
}

int isPureNumber(char *input) {
    while (*input) {
        if (!isdigit(*input) || *input == ' ') {
            return 0;
        }
        input++;
    }
    return 1;
}

int valid_ID(char *ID, Data *Data_List, int *Item_count){
    int i = 0;
    while(i < *Item_count){
        if(strcmp(ID,Data_List[i].ID) == 0)
            return 1;
        i++;
    }

    return (0);
}