#include "MangaIMS.h"

// <=================== Delete Part ==================>
void Delete_Menu(Data *Data_List, int *Item_Count){
    system("cls");

    char ID_Modify[8];
    do{
        Delete_Menu_UI();
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


    int index = Get_Data_Index(ID_Modify, Data_List);

    system("cls");
    Delete_Choice_UI(Data_List, index);

    char choice[10];

    do{
        printf("\n");
        printf("\033[1;94m[Y/n]: \033[0m");
        scanf(" %[^\n]", choice);

        if(strcmp(choice, MENU_EXIT) == 0){
            Delete_Menu(Data_List, Item_Count);
            return;
        }

    }while(strcmp(choice,"Y") != 0 && strcmp(choice, "n") != 0);

    if(strcmp(choice,"Y") == 0){
        Delete_Item(Data_List, Item_Count, ID_Modify);
        system("cls");
        Delete_Y_UI(ID_Modify);
    }else{
        system("cls");
        Delete_n_UI();
    }
    pressEnterToContinue();
    Delete_Menu(Data_List, Item_Count);
}

void Delete_Item(Data *Data_List, int *Item_Count, char *ID){
    int index = Get_Data_Index(ID, Data_List);

    while(index < *Item_Count - 1){
        strcpy(Data_List[index].ID, Data_List[index+1].ID);
        strcpy(Data_List[index].Name, Data_List[index+1].Name);
        strcpy(Data_List[index].Category, Data_List[index+1].Category);
        Data_List[index].Amount = Data_List[index+1].Amount;
        Data_List[index].Price = Data_List[index+1].Price;

        strcpy(Data_List[index].Note, Data_List[index+1].Note);
        index++;
    }
    strcpy(Data_List[index].ID, "NULL");
    strcpy(Data_List[index].Name, "NULL");
    strcpy(Data_List[index].Category, "NULL");
    Data_List[index].Amount = 0;
    Data_List[index].Price = 0;
    strcpy(Data_List[index].Note, "NULL");

    WriteData(Data_List, Item_Count);
    *Item_Count = get_count(WarehouseFileName);
}

