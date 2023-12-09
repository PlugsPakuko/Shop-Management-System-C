#include "MangaIMS.h"

// <============ Struct Management =============>
void Bin2Struct(Data *Data_List, int *Item_Count){
    FILE *binaryFile = fopen(WarehouseFileName, "rb");

    for(int i = 0; i < *Item_Count; i++){
        fread(&Data_List[i], sizeof(Data), 1, binaryFile);
    }

    fclose(binaryFile);
}

int get_count(){
    FILE *WarehouseBin = fopen(WarehouseFileName, "rb");
    long filesize;
    int count;

    fseek(WarehouseBin, 0, SEEK_END);
    filesize = ftell(WarehouseBin);
    count = filesize/sizeof(Data);
    fclose(WarehouseBin);
    return count;
}

int Get_Data_Index(char *ID, Data *Data_List){
    for(int i = 0;;i++){
        if(strcmp(ID, Data_List[i].ID) == 0)
            return i;
    }
}

void Print_Data(Data *Data_List, int *Item_Count){
    int i = 0;
    while(i < *Item_Count){
        printf("%s,%s,%s,%d,%d,%s\n",Data_List[i].ID, Data_List[i].Category, Data_List[i].Name, Data_List[i].Amount, Data_List[i].Price, Data_List[i].Note);
        i++;
    }
}
