#include "MangaIMS.h"

// <============ Read Part ============>

void Read_All(Data *Data_List, int *Item_Count) {
    Read_Logo();
    printf("\033[1mID%*cCATEGORY%*cNAME%*cPRICE%*cAMOUNT%*cNOTE\033[0m\n\n", 8, ' ', 7, ' ', 46, ' ',5, ' ', 4, ' ');
    for (int i = 0; i < *Item_Count; i++) {
        Print_Read(Data_List[i]);
    }
    pressEnterToContinue();
}

void Read_Menu(Data *Data_List, int *Item_Count) {
    char choice[10];
    int correct;
    do {
        correct = 0;
        Read_menu();
        scanf(" %[^\n]", choice);

        if (strcmp(choice, MENU_EXIT) == 0) {
            system("cls"); //clear screen before call function
            return;
        } else if (strcmp(choice, MENU_ONE) == 0) {
            system("cls"); //clear screen before call function
            Read_By_ID(Data_List, Item_Count);
            break;
        } else if (strcmp(choice, MENU_TWO) == 0) {
            system("cls"); //clear screen before call function
            Read_By_Category(Data_List, Item_Count);
            break;
        } else if (strcmp(choice, MENU_THREE) == 0) {
            system("cls"); //clear screen before call function
            Read_By_Price(Data_List, Item_Count);
            break;
        } else if (strcmp(choice, MENU_FOUR) == 0) {
            system("cls"); //clear screen before call function
            Read_All(Data_List, Item_Count);
            break;
        } else {
            system("cls"); //clear screen before call function
            printf("\nInvalid choice. Please enter a valid option.\n"); // error input text
        }
    } while(correct == 0 || atoi(choice) > 4 || isPureNumber(choice) == 0);
    Read_Menu(Data_List, Item_Count);
}

void Read_By_Category(Data *Data_List, int *Item_Count) {
    char category[100];
    char *Categories[5] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};
    int checkTemp = 0;

    do {
        

        Read_Cat_UI();

        scanf(" %[^\n]", category);

        if(strcmp(category, MENU_EXIT) == 0){
            system("cls");
            return ;
        }
        for (int i = 0; i < 5; ++i) {
            if (strcmp(category, Categories[i]) == 0) {
                checkTemp = 1;
                break;
            }
        }

        if (checkTemp == 0) {
            system("cls");
            Read_Logo();
            puts(red"Error!!! Please input the correct category.\n"white);
        }

    } while (checkTemp == 0);

    system("cls");
    Read_Logo();
    printf("\nItems in Category \033[1;35m%s\033[0m:\n\n", category);
    printf("\033[1mID%*cCATEGORY%*cNAME%*cPRICE%*cAMOUNT%*cNOTE\033[0m\n\n", 8, ' ', 7, ' ', 46, ' ',5, ' ', 4, ' ');
    for (int i = 0; i < *Item_Count; i++) {
        if (strcmp(category, Data_List[i].Category) == 0) {
            Print_Read(Data_List[i]);
        }
    }
    pressEnterToContinue();
}
void Read_By_ID(Data *Data_List, int *Item_Count) {
    char ID[8];
    int index;

    do {
        Read_ID_UI();
        scanf(" %[^\n]", ID);

        if (strcmp(ID, "Q") == 0) {
            system("cls");
            return;  // Go back to Read_Menu
        }

        if (valid_ID(ID, Data_List, Item_Count)) {
            system("cls");
            index = Get_Data_Index(ID, Data_List);
            Read_Logo();
            printf("\033[1mID%*cCATEGORY%*cNAME%*cPRICE%*cAMOUNT%*cNOTE\033[0m\n\n", 8, ' ', 7, ' ', 46, ' ',5, ' ', 4, ' ');
            Print_Read(Data_List[index]);
        } else {
            system("cls");
            printf(red"Item with ID \033[1;33m%s\033[1;31m not found. Please try again.\n"white, ID);
            index = -1;  // Reset index to force the loop to continue
        }

    } while (index == -1);
    pressEnterToContinue();
    system("cls");
}

void Read_By_Price(Data *Data_List, int *Item_Count){
    char choice[10];

    Data Copy_Data_List[*Item_Count];
    for (int i = 0; i < *Item_Count; i++)
        Copy_Data_List[i] = Data_List[i];

    do {
        Read_Price_UI();
        scanf(" %[^\n]", choice);

        if (strcmp(choice, MENU_EXIT) == 0) {
            system("cls");
            return;
        } else if (strcmp(choice, MENU_ONE) == 0) {
            system("cls");
            Read_By_Ascending(Copy_Data_List, Item_Count);
        } else if (strcmp(choice, MENU_TWO) == 0) {
            system("cls");
            Read_By_Descending(Copy_Data_List, Item_Count);
        } else {
            system("cls");
            printf(red"Invalid choice. Please enter a valid option.\n"white);
        }
    } while (1);
}

void Read_By_Ascending(Data *Data_List_Copy, int *Item_Count){
    char min[10];
    char max[10];

    do {
        Read_Logo();
        Read_As_min_UI();
        scanf(" %[^\n]", min);
        if (strcmp(min, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        Read_As_max_UI();
        scanf(" %[^\n]", max);
        if (strcmp(max, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        if(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max)){
            system("cls");
            printf(red"!!! Error Input! Please try again !!!\n"white);
        }
    }while(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max));

    system("cls");
    Read_Logo();
    printf("\nItems with Price between \033[1;33m%s\033[0m and \033[1;33m%s\033[0m:\n\n", min, max);
    printf("\033[1mID%*cCATEGORY%*cNAME%*cPRICE%*cAMOUNT%*cNOTE\033[0m\n\n", 8, ' ', 7, ' ', 46, ' ',5, ' ', 4, ' ');

    qsort(Data_List_Copy, *Item_Count, sizeof(Data), Compare_By_Price_Ascending);
    int itemsFound = 0; // Flag to check if any items are found

    for (int i = 0; i < *Item_Count; i++) {
        if (Data_List_Copy[i].Price >= atoi(min) && Data_List_Copy[i].Price <= atoi(max)) {
            Print_Read(Data_List_Copy[i]);
            itemsFound = 1;  // Set the flag since an item is found
        }
    }

    if (!itemsFound) {
        system("cls");
        Read_Logo();
        printf(red"No items found in the specified price range.\n"white);
    }
    pressEnterToContinue();
}

void Read_By_Descending(Data *Data_List_Copy, int *Item_Count){
    char min[10];
    char max[10];

    do {
        Read_Logo();
        Read_As_max_UI();
        scanf(" %[^\n]", max);
        if (strcmp(max, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        
        Read_As_min_UI();
        scanf(" %[^\n]", min);
        if (strcmp(min, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        if(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max)){
            system("cls");
            printf(red"!!! Error Input! Please try again !!!\n"white);
        }
    }while(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max));
    
    qsort(Data_List_Copy, *Item_Count, sizeof(Data), Compare_By_Price_Descending);
    int itemsFound = 0; // Flag to check if any items are found
    system("cls");
    Read_Logo();
    printf("\nItems with Price between \033[1;33m%s\033[0m and \033[1;33m%s\033[0m:\n\n", max, min);
    printf("\033[1mID%*cCATEGORY%*cNAME%*cPRICE%*cAMOUNT%*cNOTE\033[0m\n\n", 8, ' ', 7, ' ', 46, ' ',5, ' ', 4, ' ');

    for (int i = 0; i < *Item_Count; i++) {
        if (Data_List_Copy[i].Price >= atoi(min) && Data_List_Copy[i].Price <= atoi(max)) {
            Print_Read(Data_List_Copy[i]);
            itemsFound = 1;  // Set the flag since an item is found
        }
    }
    
    if (!itemsFound) {
        system("cls");
        Read_Logo();
        printf(red"No items found in the specified price range.\n\n"white);
    }
    pressEnterToContinue();
}

int Compare_By_Price_Ascending(const void *a, const void *b) {
    return ((Data *)a)->Price - ((Data *)b)->Price;
}

int Compare_By_Price_Descending(const void *a, const void *b) {
    return ((Data *)b)->Price - ((Data *)a)->Price;
}

void Print_Read(Data Data_List){
    printf(cream"%s%*c", Data_List.ID, 4, ' ');
    printf(pink"%s%*c", Data_List.Category, 15 - strlen(Data_List.Category), ' ');
    printf(green"%s%*c", Data_List.Name, 50 - strlen(Data_List.Name), ' ');
    printf(yellow"%d%*c", Data_List.Price, 10 - countDigits(Data_List.Price), ' ');
    printf(blue"%d%*c", Data_List.Amount, 10 - countDigits(Data_List.Amount), ' ');
    printf(red"%s\n\n"white, Data_List.Note);
}
