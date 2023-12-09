#include "MangaIMS.h"

// <============ Update Part ============>
void Cashier_Menu(Data *Data_List, int *Item_Count){
    char choice[10];
    int correct;
    Check_File(WarehouseFileName);
    Check_File(ReportFileName);

    do{
        correct = 0;
        Cashier_UI();
        
        scanf(" %[^\n]", choice);

        if(strcmp(choice, MENU_ONE) == 0){
            system("cls"); //clear screen before call function
            Update_Cashier(Data_List, Item_Count);
            break;
        }else if(strcmp(choice, "Q") == 0){
            system("cls");
            return ;
        }else{
            system("cls");
            printf(" \033[1;31m!!! Invalid Choice. Please Enter Again !!!\n"white);
        }
    }while (correct == 0 || isPureNumber(choice) == 0 || atoi(choice) > 1);

    system("cls");
}

void Update_Cashier(Data *Data_List, int *Item_Count)
{
    char sell_item_count_a[10];
    int sell_item_count;

    char amount_a[10];
    int amount;
    do{
        Cashier_Logo();
        Selling_phase1();
        scanf(" %[^\n]", sell_item_count_a);

        if(strcmp(MENU_EXIT,sell_item_count_a) == 0){
            system("cls");
            Cashier_Menu(Data_List, Item_Count);
            return;
        }

        if(isPureNumber(sell_item_count_a) && atoi(sell_item_count_a) != 0){
            sell_item_count = atoi(sell_item_count_a);
        }
        else{
            system("cls");
            printf(red"!!! Please input a positive integer !!!\n"white);
        }
    }while(isPureNumber(sell_item_count_a) == 0|| atoi(sell_item_count_a) <= 0 );


    char Item_List[sell_item_count][7];
    int Amount_List[sell_item_count];
    system("cls");

    for(int i = 0; i < sell_item_count; i++){
        system("cls");
        if(i >=1){
            printf("======================================== Cart ========================================\n\n");
            printf("\033[1mID%*cNAME%*cPRICE%*cAMOUNT%*cTOTAL\033[0m\n\n", 8, ' ', 46, ' ', 4, ' ',4, ' ');
        }
        for (int j = 0; j < i; j++)
        {
            int cur_i = Get_Data_Index(Item_List[j], Data_List);
            printf("\033[1;33m%s    ", Data_List[cur_i].ID);
            printf("\033[1;32m%s%*c", Data_List[cur_i].Name, 50 - strlen(Data_List[cur_i].Name), ' ');
            printf("\033[0;33m%d%*c", Data_List[cur_i].Price, 9 - countDigits(Data_List[cur_i].Price), ' ');
            printf("\033[1;35m%d%*c", Amount_List[j], 10 - countDigits(Amount_List[j]), ' ');
            printf("\x1b[36m%d%*c\n\n\033[0m", Data_List[cur_i].Price * Amount_List[j], 10 - countDigits(Amount_List[j] * Data_List[cur_i].Price), ' ');
        }
        // printf("\n======================================================================================\n\n");

        char ID_modify[8];

        //Check ID
        do{
            // Cashier_Logo();
            Selling_phase2(i);
            scanf(" %s", ID_modify);

            if(strcmp(ID_modify, MENU_EXIT) == 0){
                system("cls");
                Cashier_Menu(Data_List, Item_Count);
                return;
            }

            if(valid_ID(ID_modify, Data_List, Item_Count) == 0){
                system("cls");
                printf(red"Please input the existed ID!\n"white);
            }

        }while(valid_ID(ID_modify,Data_List, Item_Count) == 0);
        strcpy(Item_List[i], ID_modify);
        system("cls");

        //after id valid check if amount valid for sell
        int index = Get_Data_Index(ID_modify, Data_List);
        //Check Amount
        if(Data_List[index].Amount > 0){
            do{
                Cashier_Logo();
                Selling_phase3(Data_List,index);
                scanf("%s", amount_a);

                if(strcmp(MENU_EXIT,amount_a) == 0){
                    system("cls");
                    Cashier_Menu(Data_List,Item_Count);
                    return;
                }

                if(isPureNumber(amount_a)){
                    amount = atoi(amount_a);
                    if(amount <= 0){
                        system("cls");
                        printf(red"!!! Invalid input. Please enter a positive integer. !!!\n"white);

                    }else if(amount > Data_List[index].Amount){
                        system("cls");
                        printf(red"!!! Insufficient amount input. Please enter a lesser positive integer. !!!\n"white);
                    }
                    else{
                        Amount_List[i] = amount;
                        break;
                    }
                }
                else{
                    system("cls");
                    printf(red"!!! Invalid input. Please enter a positive integer. !!!\n"white);
                }
            }while(isPureNumber(amount_a) == 0 || atoi(amount_a) > Data_List[index].Amount);

        }else{
            printf(red"Sorry, the ");
            printf(cream"\"%s\"", Data_List[index].Name);
            printf(red" is out of stock. Going to next item\n"white);
            pressEnterToContinue();
            i -= 1;
            sell_item_count -= 1;
        }
    }

    system("cls");
    Cashier_Logo();
    printf("======================================== Cart ========================================\n\n");
    printf("\033[1mID%*cNAME%*cPRICE%*cAMOUNT%*cTOTAL\n\n\033[0m", 8, ' ', 46, ' ', 4, ' ',4, ' ');

    for (int j = 0; j < sell_item_count; j++)
    {
        int cur_i = Get_Data_Index(Item_List[j], Data_List);
        printf("\033[1;33m%s    ", Data_List[cur_i].ID);
        printf("\033[1;32m%s%*c", Data_List[cur_i].Name, 50 - strlen(Data_List[cur_i].Name), ' ');
        printf("\033[0;33m%d%*c", Data_List[cur_i].Price, 9 - countDigits(Data_List[cur_i].Price), ' ');
        printf("\033[1;35m%d%*c", Amount_List[j], 10 - countDigits(Amount_List[j]), ' ');
        printf("\x1b[36m%d%*c\n\n\033[0m", Data_List[cur_i].Price * Amount_List[j], 10 - countDigits(Amount_List[j] * Data_List[cur_i].Price), ' ');
    }
    printf("\n======================================================================================\n\n");
    pressEnterToContinue();

    Logo();
    for(int i = 0; i < sell_item_count; i++){
        //Update Struct
        int index = Get_Data_Index(Item_List[i], Data_List);
        Data_List[index].Amount -= Amount_List[i];

        //Write Struct to file
        WriteData(Data_List, Item_Count);
        Write_Report(Item_List[i], Data_List, Amount_List[i]);
        
        printf("ID: \033[1;33m%s\033[0m Amount: \033[1;33m%d\033[0m    \033[1;32m Updated!\033[0m\n", Item_List[i], Amount_List[i]);
        printf("Stock ID: \033[1;33m%s\033[0m Name:\033[1;33m%s\033[0m Amount:\033[1;33m %d\033[0m\n\n",Data_List[Get_Data_Index(Item_List[i], Data_List)].ID, Data_List[Get_Data_Index(Item_List[i], Data_List)].Name, Data_List[Get_Data_Index(Item_List[i], Data_List)].Amount);
    }
    pressEnterToContinue();
    Cashier_Menu(Data_List, Item_Count);
}

void Update_Admin_Menu(Data *Data_List, int *Item_Count){
    system("cls");
    Check_File(WarehouseFileName);

    char ID_Modify[8];
    do{
        Update_Menu_UI();
        scanf(" %[^\n]", ID_Modify);
        if(strcmp(ID_Modify, MENU_EXIT) == 0){
            system("cls");
            return;
        }

        if(valid_ID(ID_Modify,Data_List,Item_Count) == 0){
            system("cls");
            printf("\033[1;31mPlease input the existed ID!\n");
        }
    }while(valid_ID(ID_Modify,Data_List,Item_Count) == 0);
    Update_Admin(ID_Modify, Data_List, Item_Count);
}

void Update_Admin(char *ID_Modify, Data *Data_List, int *Item_Count){
    system("cls");
    int correct;
    while (1)
    {
        correct = 0;
        int index = Get_Data_Index(ID_Modify, Data_List);
        char choice[10];

        do{
            Update_Choices_UI(Data_List, index);

            scanf(" %[^\n]", choice);
            if(strcmp(choice, MENU_EXIT) == 0){
                system("cls");
                Update_Admin_Menu(Data_List, Item_Count);
                return ;
            }
            else if(strcmp(choice, MENU_ONE) == 0){
                system("cls");
                Update_Name(ID_Modify, Data_List, Item_Count);
                break;
            }
            else if(strcmp(choice, MENU_TWO) == 0){
                system("cls");
                Update_Category(ID_Modify, Data_List, Item_Count);
                break;
            }
            else if(strcmp(choice, MENU_THREE) == 0){
                system("cls");
                Update_Price(ID_Modify, Data_List, Item_Count);
                break;
            }
            else if(strcmp(choice, MENU_FOUR) == 0){
                system("cls");
                Update_Amount(ID_Modify, Data_List, Item_Count);
                break;
            }else{
                system("cls");
                printf(red"!!! Invalid input. Please enter the valid choice !!!\n"white);
            }
        }while(correct == 0 || atoi(choice) > 4 || isPureNumber(choice) == 0);
    }
}

void Update_Name(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[100];
    system("cls");
    UpdateName_UI(Data_List,index);
    scanf(" %[^\n]", temp);

    if( strcmp(temp, MENU_EXIT) == 0){{
        system("cls");
        return;
    }
    }else{
        strcpy(Data_List[index].Name, temp);
    }

    WriteData(Data_List, Item_Count);
    printf(green"\nUpdated!\n\n"white);
    pressEnterToContinue();
}

void Update_Category(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);
    char *Categories[10] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};

    int correct = 0;
    system("cls");

    char temp[200];
    
    do{
        UpdateCategory_UI(Data_List,index);
        scanf(" %[^\n]", temp);

        if(strcmp(temp, MENU_EXIT) == 0){
            system("cls");
            return;
        }

        for(int i = 0; i < 5; i++){
            if(strcmp(temp, Categories[i]) == 0){
                strcpy(Data_List[index].Category, temp);
                correct = 1;
                break;
            }
        }
        if(correct == 0){
            system("cls");
            printf(red"!!! Unavailable Category !!!\n"white);
        }
    }while(correct == 0);

    WriteData(Data_List, Item_Count);
    printf(green"\nUpdated!\n\n"white);
    pressEnterToContinue();
}  

void Update_Price(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        UpdatePrice_UI(Data_List,index);
        scanf(" %[^\n]", temp);

        if(strcmp(temp, MENU_EXIT) == 0){
            system("cls");
            return;
        }

        if(isPureNumber(temp) && atoi(temp) > 0){
            Data_List[index].Price = atoi(temp);

        }else{
            system("cls");
            printf(red"!!! Error Input !!!\n"white);
        }
    }while(isPureNumber(temp) == 0 || atoi(temp) < 0);

    WriteData(Data_List, Item_Count);
    printf(green"\nUpdated!\n\n"white);
    pressEnterToContinue();
}

void Update_Amount(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        UpdateAmount_UI(Data_List,index);
        scanf(" %[^\n]", temp);

        if(strcmp(temp, MENU_EXIT) == 0){
            system("cls");
            return;
        }

        if(isPureNumber(temp) && atoi(temp) >= 0){
            Data_List[index].Amount = atoi(temp);
            if (Data_List[index].Amount >= 10){
                strcpy(Data_List[index].Note, "-");
            }else{
                strcpy(Data_List[index].Note, red"REFILL");
            }
        }else{
            system("cls");
            printf(red"!!! Error Input !!!\n"white);
        }
    }while(isPureNumber(temp) == 0 || atoi(temp) < 0);

    WriteData(Data_List, Item_Count);
    
    printf(green"\nUpdated!\n\n"white);
    pressEnterToContinue();
}

void Write_Report(char *ID, Data *Data_List ,int amount){
    char TempSaleName[] = "tempSales.csv";

    FILE *ReportFile = fopen(ReportFileName, "r");
    FILE *tempSale = fopen(TempSaleName, "w");

    int index = Get_Data_Index(ID, Data_List);
    char line[200];
    char temp[200];

    Date Current_Date = {"0", "0", "0"};
    Date Previous_Date = {"0", "0", "0"};

    double sum_buffer;
    double amount_buffer;
    double sum = 0;
    double sum_amount = 0;

    int DataAbove = 0;

    //skip column name
    fgets(line,sizeof(line),ReportFile);
    fputs(line,tempSale);

    while (fgets(line,sizeof(line),ReportFile))
    {
        if(strncmp(line, "Total",5) == 0 || strcmp(line, "\n") == 0)
            continue;

        strcpy(temp, line);
        Current_Date = GetDate(temp);

        if(compareDates(Current_Date, Previous_Date) == 1)
        {
            if(DataAbove){
                fprintf(tempSale, "Total,,,,,%.2lf,%.2lf\n\n", sum_amount, sum);
                sum = 0;
                sum_amount = 0;
            }
            
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%lf,%lf",&amount_buffer, &sum_buffer);
            sum += sum_buffer;
            sum_amount += amount_buffer;
            fprintf(tempSale, line);
        }
        else
        {
            DataAbove = 1;
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%lf,%lf",&amount_buffer, &sum_buffer);
            sum += sum_buffer;
            sum_amount += amount_buffer;
            fprintf(tempSale, line);
        }
        Previous_Date = Current_Date;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    // if the same day add before sum
    if(atoi(Current_Date.day) == tm.tm_mday && atoi(Current_Date.month) == tm.tm_mon + 1 && atoi(Current_Date.year) == tm.tm_year +1900){
        fprintf(tempSale,"%02d/%02d/%d,%02d:%02d:%02d,%s,%s,%d,%d,%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,ID, Data_List[index].Name , Data_List[index].Price, amount, amount * Data_List[index].Price);
        sum_amount += amount;
        sum += amount * Data_List[index].Price;
        fprintf(tempSale, "Total,,,,,%.2lf,%.2lf\n\n", sum_amount, sum);
        sum = 0;
        sum_amount = 0;  
    }else{
        fprintf(tempSale, "Total,,,,,%.2lf,%.2lf\n\n", sum_amount, sum);

        fprintf(tempSale,"%02d/%02d/%d,%02d:%02d:%02d,%s,%s,%d,%d,%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,ID, Data_List[index].Name , Data_List[index].Price, amount, amount * Data_List[index].Price);
        fprintf(tempSale, "Total,,,,,%d,%.2d\n\n", amount, amount * Data_List[index].Price);
    }


    fclose(ReportFile);
    fclose(tempSale);
    remove(ReportFileName);
    rename(TempSaleName, ReportFileName);
}

Date GetDate(char *Line){
    Date Current_Date;

    char *token = strtok(Line, "/");
    int i = 0;
    while(token != NULL && i < 3){
        switch (i)
        {
        case 0:
            strcpy(Current_Date.day, token);
            token = strtok(NULL, "/");
            break;
        case 1:
            strcpy(Current_Date.month, token);
            token = strtok(NULL, ",");
            break;
        case 2:
            strcpy(Current_Date.year, token);
            break;
        default:
            break;
        }
        i++;
    }
    return Current_Date;
}

int compareDates(Date date1, Date date2) {
    int year1 = atoi(date1.year);
    int year2 = atoi(date2.year);

    if (year1 > year2)
        return 1; 
    else if (year1 < year2) 
        return 0; 

    int month1 = atoi(date1.month);
    int month2 = atoi(date2.month);

    if (month1 > month2)
        return 1; 
    else if (month1 < month2)
        return 0; 

    int day1 = atoi(date1.day);
    int day2 = atoi(date2.day);

    if (day1 > day2)
        return 1; 
    else if (day1 < day2)
        return 0; 

    return 0;
}