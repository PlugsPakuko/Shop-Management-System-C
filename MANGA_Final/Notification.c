#include "MangaIMS.h"

// <============ Notification Part ============>
int Check_Alert(Data *Data_List, int *Item_Count){
    int count = 0;
    for(int i = 0; i < *Item_Count; i++){
        if(strcmp(Data_List[i].Note, "-") != 0){
            count++;
        }
    }
    return count;
}

void Save_Alert(Data *Data_List ,char (*ID_Alert)[7], int Alert_Count){
    int i = 0;
    int count = 0;
    while(count < Alert_Count){
        if(strcmp(Data_List[i].Note, "-") != 0){
            strcpy(ID_Alert[count], Data_List[i].ID);
            count++;
        }
        i++;
    }
}

void Print_Alert(Data *Data_List, int *Item_Count){
    int Alert_count = Check_Alert(Data_List, Item_Count);
    char ID_Alert[Alert_count][7];
    if (Alert_count > 0) {
        Save_Alert(Data_List, ID_Alert, Alert_count);

        printf(red"================================== !! ALERT !! ===================================\n\n"white);
        printf("\033[1mID%*cNAME%*cAMOUNT%*cNOTE\n\n", 8, ' ', 46, ' ', 4, ' ');

        for (int i = 0; i < Alert_count; i++) {
            int cur = Get_Data_Index(ID_Alert[i], Data_List);
            printf(cream"%s    ", Data_List[cur].ID);
            printf(green"%s%*c", Data_List[cur].Name, 50 - strlen(Data_List[cur].Name), ' ');
            printf(cyan"%*c%d%*c",2, ' ' ,Data_List[cur].Amount , 8 - countDigits(Data_List[cur].Amount), ' ');
            printf(pink"%s\n\n"white, Data_List[cur].Note);
        }
        printf(red"\n==================================================================================\n\n"white);
        printf(blue"Automatic Refill Press (");
        printf(red"R");
        printf(blue")\n\n");
    }
}

void Refill(Data *Data_List, int *Item_Count){
    printf("++\n");
    printf("||\n");
    for(int i = 0; i < *Item_Count; i++){
        if(Data_List[i].Amount < 10){
            Data_List[i].Amount += 50;
            printf("||   ID: \033[1;33m%s\033[0m Book: \033[1;32m%s\033[0m Updated Amount: \033[1;94m%d\033[0m\n", Data_List[i].ID, Data_List[i].Name, Data_List[i].Amount);
            printf("||\n");
        }
    }
    
    printf("++\n\n");
    WriteData(Data_List, Item_Count);
    pressEnterToContinue();
}
