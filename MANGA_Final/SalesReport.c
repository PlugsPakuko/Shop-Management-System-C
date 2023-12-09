#include "MangaIMS.h"

// <============ Sales Report Part ============>
void SalesReport_Menu()
{
    char choice[10];
    Check_File(ReportFileName);

    do{
        Sale_report_Logo();
        Sale_report_Menu_UI();

        scanf(" %s", choice);
        if (strcmp(choice, MENU_EXIT) == 0){
            system("cls");
            return;
        }else if (strcmp(choice, MENU_ONE) == 0){
            system("cls");
            All_Report();
            break;
        }else if (strcmp(choice, MENU_TWO) == 0){
            system("cls");
            Daily_Report();
            break;
        }else if (strcmp(choice, MENU_THREE) == 0){
            system("cls");
            Monthly_Report();
            break;
        }else{
            system("cls");
            printf(" \033[1;31m!!! Invalid Choice. Please Enter Again !!!\n");
        }
    } while (isPureNumber(choice) == 0 || atoi(choice) == 0 || atoi(choice) > 3);
    SalesReport_Menu();
}

void All_Report()
{
    FILE *report = fopen(ReportFileName, "r");
    char line[256];
    fgets(line, sizeof(line), report);
    Sale_report_Logo();
    Report_info();

    char amount[256];

    while (fgets(line, sizeof(line), report)){
        if(strncmp(line, "Total", 5) == 0){
            printf(blue"%s%*c", strtok(line, ","), 95, ' ');
            strcpy(amount, strtok(NULL, ","));
            printf("\x1b[36m%s%*c", amount , 7 - countDigits(atoi(amount)) ,' ');
            printf("\x1b[36m%s\n\n", strtok(NULL, ","));
        }else if(line[2] == '/'){
            print_sales(line);
        }else{
            continue;
        }
    }
    fclose(report);
    pressEnterToContinue();
    system("cls");
}

void Monthly_Report()
{    
    Date date;
    strcpy(date.day, "1");

    do{
        Sale_report_Logo();
        Monthlyui();
        scanf("%s %s", date.month, date.year);
        if(strcmp(date.month, MENU_EXIT) == 0){
            system("cls");
            return ;
        }

        if(!isdigit(date.month[0]) || !isdigit(date.month[1])){
            system("cls");
            printf(red"Please Input the correct format(MM YYYY)\nExample:(09 2004)\n"white);
        }
        else if (!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year)){
            system("cls");
            printf(red"!!! Invalid Date, Input Again !!!\n"white);
        }else{
            break;
        }
    } while (!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year) 
    || !isdigit(date.month[0]) || !isdigit(date.month[1]));

    system("cls");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    int amount, sum_amount = 0;
    int total, sum_total = 0;

    // skip column name
    fgets(line, sizeof(line), report);
    Sale_report_Logo();
    Report_info();

    while (fgets(line, sizeof(line), report))
    {
        strcpy(temp, line);
        Date cur_date = GetDate(temp);

        if (strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0){
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d,%d",&amount, &total);
            sum_amount += amount;
            sum_total += total;
            print_sales(line);
            count++;
        }
    }if (!count){
        system("cls");
        Sale_report_Logo();
        printf("Date: \x1b[36m%s\x1b[0m/ \x1b[36m%s\x1b[0m has no sales Record\n\n", date.month, date.year);
    }else{
        printf("TOTAL%*c", 95, ' ');
        printf("\x1b[36m%d%*c", sum_amount , 10 - countDigits(sum_amount) ,' ');
        printf("\x1b[36m%d\n\n", sum_total);       
    }
    fclose(report);
    pressEnterToContinue();
}

void Daily_Report()
{
    Date date;
    do{
        Sale_report_Logo();
        Dailyui();
        scanf("%s %s %s", date.day, date.month, date.year);
        if(!isdigit(date.day[0]) || !isdigit(date.day[1]) || !isdigit(date.month[0]) || !isdigit(date.month[1])){
            system("cls");
            printf(red"Please Input the correct format( DD MM YYYY)\nExample:(06 09 2004)\n"white);
        }else if (!valid_date(date) || !isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year)){
            system("cls");
            printf(red"!!! Invalid Date, Input Again !!!\n"white);
        }else{
            break;
        }
    } while (!valid_date(date) || isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year) || !isdigit(date.day[0]) || !isdigit(date.day[1]) || !isdigit(date.month[0]) || !isdigit(date.month[1]));

    system("cls");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    // skip column name
    fgets(line, sizeof(line), report);
    int amount, sum_amount = 0;
    int total, sum_total = 0;

    Sale_report_Logo();
    Report_info();
    while (fgets(line, sizeof(line), report)){
        strcpy(temp, line);
        Date cur_date = GetDate(temp);
        if (strcmp(cur_date.day, date.day) == 0 && strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0){
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d,%d",&amount, &total);
            sum_amount += amount;
            sum_total += total;
            print_sales(line);
            count++;
        }
    }

    if (!count){
        system("cls");
        Sale_report_Logo();
        printf("Date: \x1b[36m%s\x1b[0m/ \x1b[36m%s\x1b[0m/ \x1b[36m%s\x1b[0m has no sales Record\n\n", date.day, date.month, date.year);
    }else{
        // last line
        printf("TOTAL%*c", 95, ' ');
        printf("\x1b[36m%d%*c", sum_amount , 10 - countDigits(sum_amount) ,' ');
        printf("\x1b[36m%d\n\n\x1b[0m", sum_total);
    }

    fclose(report);
    pressEnterToContinue();
}

void print_sales(char *line){
    char name[256];
    char price[256];
    char amount[256];
    printf(white"%s     ", strtok(line, ","));
    printf(white"%s", strtok(NULL, ","));
    printf(cream"%*c%s", 7, ' ', strtok(NULL, ","));

    strcpy(name, strtok(NULL, ","));
    printf(green"%*c%s", 4, ' ', name);

    strcpy(price, strtok(NULL, ","));
    printf(yellow"%*c%s", 50 - strlen(name), ' ', price);

    strcpy(amount, strtok(NULL, ","));
    printf(pink"%*c%s", 10 - countDigits(atoi(price)), ' ', amount);

    printf(blue"%*c%s\n\n", 10 - countDigits(atoi(amount)), ' ', strtok(NULL, "\n"));
}

int countDigits(int num){
    int count = 0;

    if(num == 0){
        return 1;
    }

    while(num > 0){
        count++;
        num /= 10;
    }

    return count;
}