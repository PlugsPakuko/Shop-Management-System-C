#define MENU_EXIT "Q"
#define MENU_ONE "1"
#define MENU_TWO "2"
#define MENU_THREE "3"
#define MENU_FOUR "4"
#define MENU_FIVE "5"
#define MENU_SIX "6"

#define correctUsername "user123"
#define correctPassword "1212312121"

#define WarehouseCSVFilename "MangaWarehouse.csv"
#define WarehouseFileName "Warehouse.bin"
#define ReportFileName "SalesReport.csv"


typedef struct
{
    char ID[7];
    char Category[100];
    char Name[100];
    int Amount;
    int Price;
    char Note[7]; //for "REFILL" word only
}Data;

typedef struct 
{
    char day[3];
    char month[3];
    char year[5];
}Date;

// <============ Notification Part ============> DONE
int Check_Alert(Data *Data_List, int *Item_Count);
void Save_Alert(Data *Data_List, char (*ID_Alert)[7], int Alert_Count);
void Print_Alert(Data *Data_List, int *Item_Count);
void Refill(Data *Data_List, int *Item_Count);

// <============ System Login Part ============> DONE
void Admin_Login(Data *Data_List, int *Item_Count);
void Admin_Menu(Data *Data_List, int *Item_Count);
void Login_Menu(Data *Data_List, int *Item_Count);

// <============ Create Part ============> DONE
void CreateNewBook(Data *Data_List, int *Item_Count);

// <============ Read Part ============> DONE
void Read_Menu(Data *Data_List, int *Item_Count);
void Read_All(Data *Data_List, int *Item_Count);
void Read_By_ID(Data *Data_List, int *Item_Count);
void Read_By_Category(Data *Data_List, int *Item_Count);
void Read_By_Price(Data *Data_List, int *Item_Count);
void Read_By_Ascending(Data *Data_List_Copy, int *Item_Count);
void Read_By_Descending(Data *Data_List_Copy, int *Item_Count);
int Compare_By_Price_Ascending(const void *a, const void *b);
int Compare_By_Price_Descending(const void *a, const void *b);

// <============ Update Part ============> DONE
void Cashier_Menu(Data *Data_List, int *Item_Count);
void Update_Cashier(Data *Data_List, int *Item_Count); //Update system for cashier user
void Update_Admin_Menu(Data *Data_List, int *Item_Count);
void Update_Admin(char *ID_Modify, Data *Data_List, int *Item_Count);// Update system for admin user
void Update_Name(char *ID, Data *Data_List, int *Item_Count);// Update Name in Warehouse
void Update_Category(char *ID, Data *Data_List, int *Item_Count);// Update Category in Warehouse
void Update_Price(char *ID, Data *Data_List, int *Item_Count);// Update Price in Warehouse
void Update_Amount(char *ID, Data *Data_List, int *Item_Count);// Update Amount in Warehouse
void Write_Report(char *ID, Data *Data_List ,int amount); // Make Sales File
Date GetDate(char *Line);
int compareDates(Date date1, Date date2);

// <============ Delete Part ============> DONE
void Delete_Menu(Data *Data_List, int *Item_Count);// Delete System for admin
void Delete_Item(Data *Data_List, int *Item_Count, char *ID);// Function to delete item

// <============ SalesReport Part ============> DONE
void SalesReport_Menu();
void All_Report();
void Monthly_Report();
void Daily_Report();
void print_sales(char *line);
int countDigits(int num);

// <=========== Struct Management ============> DONE
void Bin2Struct(Data *Data_List, int *Item_Count);
int get_count();
int Get_Data_Index(char *ID, Data *Data_List);// get index of element by ID
void Print_Data(Data *Data_List, int *Item_Count);//Print whole struct

// <=========== File Management ============> DONE
void WriteData(Data *Data_List, int *Item_Count);
void printBinaryFile();
void CSVtoBin();
void Check_File(char *FileName); //Chechk if File available

// <=========== Input Management & General ============> DONE
void pressEnterToContinue();
int isLeapYear(int year);
int valid_date(Date date);
int isPureNumber(char *input); // Chechk if the input is only number no contain alphabet
int valid_ID(char *ID, Data *Data_List, int *Item_count);
