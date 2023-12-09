#include "MangaIMS.h"

// <============ Create Part ============>
void CreateNewBook(Data *Data_List, int *Item_Count)
{
    //==============================input ID===============================
    char CreateID[100];
    int exist=1,length,same=0;
    do{
        same=0;
        Create_ID_UI();
        scanf(" %[^\n]", CreateID);
        if(strcmp(CreateID,"Q")==0){ //press Q
            system("cls");
            return ;
        }
        length = strlen(CreateID); //check first 2 char && 4 num left && length 6
        if(length==6 && (isalpha(CreateID[0])) && (isalpha(CreateID[1])) && (isdigit(CreateID[2])) && (isdigit(CreateID[3])) && (isdigit(CreateID[4])) && (isdigit(CreateID[5])) ){
            system("cls");
            exist=0;
        }
        for(int i = 0;i <= *Item_Count;i++){ //check ID exist
            if(strcmp(CreateID, Data_List[i].ID) == 0){
                same=1;
            }
        }
        if(exist==1){ //printf exists
            system("cls");
            printf(red"6 digits only and the first two characters must be letters,\nthe remaining four characters are numbers.\n"white);
        }
        else if(same==1){
            system("cls");
            printf(red"This ID is already exist.\n");
            exist=1;
        }
        else if(exist==0 && same==0){ //substitute
            strcpy(Data_List[*Item_Count].ID, CreateID);
            system("cls");
        }
    }while(exist == 1);

    //==============================input Name===============================
    char CreateName[200];
    Create_Name_UI();
    scanf(" %[^\n]", CreateName);
    strcpy(Data_List[*Item_Count].Name, CreateName);
    system("cls");

    //==============================input category===============================
    char *Categories[10] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};
    int correct = 0;
    char CreateCategory[200];
    do{
        Create_Category_UI();
        scanf(" %[^\n]", CreateCategory);
        for(int i = 0; i < 5; i++){
            if(strcmp(CreateCategory, Categories[i]) == 0){
                strcpy(Data_List[*Item_Count].Category, CreateCategory);
                correct = 1;
                system("cls");
                break;
            }
        }
        if(correct == 0){
            system("cls");
            printf(red"!!! Unavailable Category !!!\n");
        }
    }while(correct == 0);

    //=============================input price=======================
    int again=1; 
    char CreatePrice[100];
    while(again){
        Create_Price_UI();
        scanf(" %[^\n]", CreatePrice);
        CreatePrice[strcspn(CreatePrice, "\n")] = '\0';
        if(isPureNumber(CreatePrice)){
            if(atoi(CreatePrice)>0){
                Data_List[*Item_Count].Price = atoi(CreatePrice);
                again=0;
                system("cls");
                break;
            }
        }
        system("cls");
        printf(red"Wrong Input! Please enter the positive integer\n");
    }

    //=============================input amount=======================
    again=1; 
    char CreateAmount[100];
    while(again){
        Create_Amount_UI();
        scanf(" %[^\n]", CreateAmount);
        CreateAmount[strcspn(CreateAmount, "\n")] = '\0';
        if(isPureNumber(CreateAmount)){
            if(atoi(CreateAmount)>=0){
                Data_List[*Item_Count].Amount = atoi(CreateAmount);
                again=0;
                system("cls");
                break;
            }
        }
        system("cls");
        printf(red"Wrong Input! The Amount should be MORE THAN 0!!!\n");
    }
    //=============================input Note=======================
    if(atoi(CreateAmount) < 10)
        strcpy(Data_List[*Item_Count].Note, "REFILL");
    else
        strcpy(Data_List[*Item_Count].Note, "-");

    *Item_Count += 1; // Increment the item count
    WriteData(Data_List, Item_Count);
    Create_Success();
    pressEnterToContinue();
}
