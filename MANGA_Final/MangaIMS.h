#ifndef MANGA_IMS_H
#define MANGA_IMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h> 

//Define Menu choice using Macro for confusing protection.
#define MENU_EXIT "Q"
#define MENU_ONE "1"
#define MENU_TWO "2"
#define MENU_THREE "3"
#define MENU_FOUR "4"
#define MENU_FIVE "5"
#define MENU_SIX "6"

//Admin Authentication
#define correctUsername "user123"
#define correctPassword "1212312121"

//File used
#define WarehouseCSVFilename "MangaWarehouse.csv"
#define WarehouseFileName "Warehouse.bin"
#define ReportFileName "SalesReport.csv"

//Color code for decoration
#define green "\033[1;32m"
#define red "\033[1;31m" 
#define blue "\033[1;94m" 
#define cream "\033[1;33m"  
#define yellow "\033[0;33m" 
#define pink "\033[1;35m"
#define white "\033[0m" 
#define cyan "\x1b[36m"

//struct Data represent the data from file
typedef struct
{
    char ID[7]; //Manga book
    char Category[100]; //Manga Category
    char Name[100]; // Managa Name
    int Amount; //Manga Amount
    int Price; //Manga Price
    char Note[7]; //for "REFILL" word only (Amount < 10)
}Data;

//struct Date represent the date
typedef struct 
{
    char day[3];
    char month[3];
    char year[5];
}Date;

// <============ Notification Part ============> DONE
int Check_Alert(Data *Data_List, int *Item_Count); //Check if there are REFILL needed stock
void Save_Alert(Data *Data_List, char (*ID_Alert)[7], int Alert_Count); //Save the ID that need to re-stock
void Print_Alert(Data *Data_List, int *Item_Count); //Print list of item needed to re-stock 
void Refill(Data *Data_List, int *Item_Count); //Automatic refill the item needed to re-stock

// <============ System Login Part ============> DONE
void Admin_Login(Data *Data_List, int *Item_Count); //Admin Login authentication
void Admin_Menu(Data *Data_List, int *Item_Count); //Admin Menu link to other function page
void Login_Menu(Data *Data_List, int *Item_Count); //First page after execute the program

// <============ Create Part ============> DONE
void CreateNewBook(Data *Data_List, int *Item_Count); //Create New Book_Data saved to Data_List

// <============ Read Part ============> DONE
void Read_Menu(Data *Data_List, int *Item_Count); //Page that contain all Read-type function
void Read_All(Data *Data_List, int *Item_Count); //Display All Items from Data array
void Read_By_ID(Data *Data_List, int *Item_Count); //Display item by specific ID
void Read_By_Category(Data *Data_List, int *Item_Count); //Display items by specific category
void Read_By_Price(Data *Data_List, int *Item_Count); //Menu for choosing whether Ascend or Descend order
void Read_By_Ascending(Data *Data_List_Copy, int *Item_Count); //Display items by Ascending Price
void Read_By_Descending(Data *Data_List_Copy, int *Item_Count); //Display items by Descending Price
int Compare_By_Price_Ascending(const void *a, const void *b); //Ascending Compare function for qsort
int Compare_By_Price_Descending(const void *a, const void *b); //Descending Compare function for qsort
void Print_Read(Data Data_List); //Print the Data in correct format

// <============ Update Part ============> DONE
void Cashier_Menu(Data *Data_List, int *Item_Count); //Menu for cashier user type
void Update_Cashier(Data *Data_List, int *Item_Count); //sell item system
void Update_Admin_Menu(Data *Data_List, int *Item_Count); //Menu for input ID user wanted to update
void Update_Admin(char *ID_Modify, Data *Data_List, int *Item_Count); //Menu for update the item with 5 option for the Data struct
void Update_Name(char *ID, Data *Data_List, int *Item_Count); // Update Name in Struct
void Update_Category(char *ID, Data *Data_List, int *Item_Count);// Update Category in Struct
void Update_Price(char *ID, Data *Data_List, int *Item_Count);// Update Price in Struct
void Update_Amount(char *ID, Data *Data_List, int *Item_Count);// Update Amount in Struct
void Write_Report(char *ID, Data *Data_List ,int amount); // Write sales after cashier sell the items
Date GetDate(char *Line); //Function for get date saved to Date struct and write on the report FIle
int compareDates(Date date1, Date date2); 
//Function for checking that we it still in the same date. if new date found print summary of the past day to the file

// <============ Delete Part ============> DONE
void Delete_Menu(Data *Data_List, int *Item_Count); //Delete Menu for admin
void Delete_Item(Data *Data_List, int *Item_Count, char *ID); //Function to delete item

// <============ SalesReport Part ============> DONE
void SalesReport_Menu(); //List menu of read sales report; daily, monthly and all
void All_Report(); // print All report
void Monthly_Report(); //print monthly report
void Daily_Report(); //print daily report
void print_sales(char *line);  //print format of the sales report
int countDigits(int num); //function to count digits of num; used in calculate whitespace needed to print for alignment

// <=========== Struct Management ============> DONE
void Bin2Struct(Data *Data_List, int *Item_Count); // Pull data from binary file save into struct
int get_count(); //count items amount in database
int Get_Data_Index(char *ID, Data *Data_List); //get index of specific items in Data_List by ID

// <=========== File Management ============> DONE
void WriteData(Data *Data_List, int *Item_Count); // Save the modified struct to binary files
void printBinaryFile(); //Used for debugging; Print the whole binary file into readle-text
void CSVtoBin(); //for backup file, turn csv file into binary file
void Check_File(char *FileName); //Chechk if input File available

// <=========== Input Management & General ============> DONE
void pressEnterToContinue();
int isLeapYear(int year); //check whether input is leappyear or not
int valid_date(Date date);// check whether the input date is valid or not
int isPureNumber(char *input); // Chechk whether the input is contain only number or not
int valid_ID(char *ID, Data *Data_List, int *Item_count); // check if the input ID is in the Data_List or not

// ================= UI PAGE =============

// <============ UI Decoration Part ============> 

//-------mainmenu
void Greet();
void Login_Success();
void Login_Failed();
void Logo();
void Choices();

//-----del
void DeleteLogo();
void Delete_Menu_UI();
void Delete_Choice_UI(Data *Data_List, int index);
void Delete_Y_UI(char *ID_Modify);
void Delete_n_UI();

//--update
void UpdateLogo();
void Update_Menu_UI();
void Operator_menu();
void Update_Choices_UI(Data *Data_List,int index);
void UpdateName_UI(Data *Data_List, int index);
void UpdateCategory_UI(Data *Data_List, int index);
void UpdatePrice_UI(Data *Data_List, int index);
void UpdateAmount_UI(Data *Data_List, int index);

// chasier 
void Cashier_Logo();
void Cashier_UI();
void Selling_phase1();
void Selling_phase2(int i);
void Selling_phase3(Data *Data_List,int index);

//Sale report
void Sale_report_Logo();
void Sale_report_Menu_UI();
void Report_info();
void Dailyui();
void Monthlyui();

//Create
void Create_Logo();
void Create_ID_UI();
void Create_Name_UI();
void Create_Category_UI();
void Create_Amount_UI();
void Create_Price_UI();
void Create_Success();

//Read
void Read_Logo();
void Read_menu();
void Read_Price_UI();
void Read_Cat_UI();
void Read_ID_UI();
void Read_As_min_UI();
void Read_As_max_UI();

#endif