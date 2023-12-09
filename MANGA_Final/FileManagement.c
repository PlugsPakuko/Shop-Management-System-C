#include "MangaIMS.h"

// <============ File Management =============>
void WriteData(Data *Data_List, int *Item_Count){

    FILE *temp = fopen("temp.bin", "wb");
    Check_File("temp.bin");

    for(int i = 0; i < *Item_Count; i++){
        if(strcmp(Data_List[i].ID,"NULL") == 0)
            continue;
    
        if(Data_List[i].Amount < 10)
            strcpy(Data_List[i].Note, "REFILL");
        else
            strcpy(Data_List[i].Note, "-");  
        fwrite(&Data_List[i], sizeof(Data), 1, temp);
    }

    fclose(temp);
    remove(WarehouseFileName);
    rename("temp.bin", WarehouseFileName);
}

void printBinaryFile() {
    FILE *binaryFile = fopen(WarehouseFileName, "rb");

    if (binaryFile == NULL) {
        perror("Error opening binary file");
        return;
    }

    Data currentItem;

    while (fread(&currentItem, sizeof(Data), 1, binaryFile) == 1) {
        printf("%s, %s, %s, %d, %d, %s\n", currentItem.ID, currentItem.Category, currentItem.Name, currentItem.Amount, currentItem.Price, currentItem.Note);
    }

    fclose(binaryFile);
}

void CSVtoBin() {
    FILE *csvFile = fopen(WarehouseCSVFilename, "r");
    FILE *binFile = fopen(WarehouseFileName, "wb");
    
    char line[200];
    Data currentItem;

    // Skip column name
    fgets(line, sizeof(line), csvFile);

    while (fgets(line, sizeof(line), csvFile)) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^\n]", currentItem.ID, currentItem.Category, currentItem.Name, &currentItem.Amount, &currentItem.Price, currentItem.Note);
        fwrite(&currentItem, sizeof(Data), 1, binFile);
    }

    fclose(csvFile);
    fclose(binFile);

    printf("CSV -> Binary Successfull!\n");
}

void Check_File(char *FileName){
    FILE *Check = fopen(FileName,"rb");

    if(Check == NULL){
        printf("Error openning %s\nProgram Stop Execute.", FileName);
        pressEnterToContinue();
        exit(0);
    }else{
        fclose(Check);
    }
}
