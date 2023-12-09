#include "MangaIMS.h"

int main() {
    // CSVtoBin();

    system("cls");

    //check if file is valid before start
    Check_File(WarehouseFileName);
    Check_File(ReportFileName);
    // Check_File(WarehouseCSVFilename);

    // ===== Initialization ======  Save Data to Struct and Count all items amount
    int Item_Count = get_count();
    Data Data_List[Item_Count];
    Bin2Struct(Data_List, &Item_Count);
    WriteData(Data_List, &Item_Count); 
    // ===========================


    // ====== Skip to menu =======
    Login_Menu(Data_List, &Item_Count);
    // Admin_Menu(Data_List, &Item_Count);
    // Cashier_Menu(Data_List, &Item_Count);
    // ===========================

    pressEnterToContinue();
    return 0;
}