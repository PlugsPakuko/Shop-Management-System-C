#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h> 

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


int main() {
    // CSVtoBin();

    system("cls");
    Check_File(WarehouseFileName);
    Check_File(ReportFileName);
    // Check_File(WarehouseCSVFilename);

    // ===== Initialization ======
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

// <=========== Input Management & General =============>
void pressEnterToContinue() {
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
    getchar();
    system("cls");
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int valid_date(Date date) {
    int day = atoi(date.day);
    int month = atoi(date.month);
    int year = atoi(date.year);
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(isLeapYear(year))
        daysInMonth[1] = 29;

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) 
        return 0;

    return 1; // Valid date
}

int isPureNumber(char *input) {
    while (*input) {
        if (!isdigit(*input) || *input == ' ') {
            return 0;
        }
        input++;
    }
    return 1;
}

int valid_ID(char *ID, Data *Data_List, int *Item_count){
    int i = 0;
    while(i < *Item_count){
        if(strcmp(ID,Data_List[i].ID) == 0)
            return 1;
        i++;
    }

    return (0);
}


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
        printf("Error opennign %s\nProgram Stop Execute.", FileName);
        pressEnterToContinue();
        exit(0);
    }else{
        fclose(Check);
    }
}

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

        printf(" ======= !! ALERT !! =======\n");
        printf("ID                 NAME               AMOUNT    NOTE\n\n");

        for (int i = 0; i < Alert_count; i++) {
            int cur = Get_Data_Index(ID_Alert[i], Data_List);
            printf("%s            %s    %d     %s\n", ID_Alert[i], Data_List[cur].Name, Data_List[cur].Amount ,Data_List[cur].Note);
        }
        printf("\n===========================\n\n");
        printf("Automatic Refill Press (R)\n\n");
    }
}

void Refill(Data *Data_List, int *Item_Count){
    for(int i = 0; i < *Item_Count; i++){
        if(Data_List[i].Amount < 10){
            Data_List[i].Amount += 50;
            printf(" ID: %s Book: %s Updated Amount: %d\n", Data_List[i].ID, Data_List[i].Name, Data_List[i].Amount);
        }
    }
    WriteData(Data_List, Item_Count);
    pressEnterToContinue();
}

// <============ System Login Part ============>
void Admin_Login(Data *Data_List, int *Item_Count)
{
    char username[50];
    char password[50];
    int i = 0;

    // Get username and password from the user
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");

    do{
        password[i] = getch(); 
        if(password[i] != '\r')
            printf("*");
        i++;
    }while(password[i-1] != '\r');
    password[i-1] = '\0';
    // scanf("%s", password);

    // Compare entered username and password with correct values
    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
    {
        system("cls"); // clear terminal screen
        printf("Login successful. Welcome Admin\n");
        pressEnterToContinue();
        Admin_Menu(Data_List, Item_Count);
    }
    else
    {
        system("cls");
        printf("Login failed. Incorrect username or password.\n");
    }
}

void Admin_Menu(Data *Data_List, int *Item_Count){
    char choice[10];
    int noti = 1;
    do
        {
            if(noti == 1)
                Print_Alert(Data_List, Item_Count);

            printf("\nManga's Warehouse\n");
            printf("(1) Create\n");
            printf("(2) Read\n");
            printf("(3) Update\n");
            printf("(4) Delete\n");
            printf("(5) Sales Report\n");
            printf("(6) Toggle Notification\n");
            printf("(Q) Back to main menu\n");
            scanf( " %[^\n]", choice);

            if(strcmp(choice, MENU_EXIT) == 0){
                system("cls"); //clear screen before call function
                return ;
            }else if(strcmp(choice, "R") == 0){
                system("cls"); //clear screen before call function
                Refill(Data_List, Item_Count);
                break;              
            }else if(strcmp(choice, MENU_ONE) == 0){
                system("cls"); //clear screen before call function
                CreateNewBook(Data_List, Item_Count);
                break;              
            }else if(strcmp(choice, MENU_TWO) == 0){
                system("cls"); //clear screen before call function
                Read_Menu(Data_List, Item_Count);
                break;           
            }else if(strcmp(choice, MENU_THREE) == 0){
                system("cls"); //clear screen before call function
                Update_Admin_Menu(Data_List, Item_Count);
                break;
            }else if(strcmp(choice, MENU_FOUR) == 0){
                system("cls"); //clear screen before call function
                Delete_Menu(Data_List, Item_Count);
                break;
            }else if(strcmp(choice, MENU_FIVE) == 0){
                system("cls"); //clear screen before call function
                SalesReport_Menu();
                break;
            }else if(strcmp(choice, MENU_SIX) == 0){
                system("cls"); //clear screen before call function
                if(noti == 1){
                    noti = 0;
                    printf("Notification Hided (%d)\n", Check_Alert(Data_List,Item_Count));
                }else
                    noti = 1;
            }else{
                system("cls"); //clear screen before call function
                printf("\nInvalid choice. Please enter a valid option.\n"); // error input text       
            }
        } 
        while (atoi(choice) > 4 || isPureNumber(choice) == 0);
        
        Admin_Menu(Data_List, Item_Count);
}

void Login_Menu(Data *Data_List, int *Item_Count)
{
    char choice[10];
    do
    {
        //---------------------edit output here!----------------------
        printf("\nManga's Warehouse\n");
        printf("(1) Admin\n");
        printf("(2) Cashier\n");
        printf("(Q) Exit\n");
        scanf(" %[^\n]", choice);

        if(strcmp(choice, MENU_EXIT) == 0){
            system("cls");
            return ;
        }else if(strcmp(choice, MENU_ONE) == 0){
            system("cls"); //clear screen before call function
            Admin_Login(Data_List, Item_Count);
            break;
        }else if(strcmp(choice, MENU_TWO) == 0){
            system("cls"); //clear screen before call function
            Cashier_Menu(Data_List, Item_Count);
            break;
        }else {
            system("cls"); //clear screen before call function
            printf("\nInvalid choice. Please enter a valid option.\n");
            break;
        }
    } 
    while (atoi(choice) > 2 || isPureNumber(choice) == 0);
    Login_Menu(Data_List, Item_Count);
}
 

// <============ Create Part ============>
void CreateNewBook(Data *Data_List, int *Item_Count)
{
    //==============================input ID===============================
    char CreateID[100];
    int exist=1,length,same=0;
    do{
        same=0;
        printf("(Exit Press Q)\nEnter Book ID (EX0001): \n");
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
            printf("6 digits only and the first two characters must be letters,\nthe remaining four characters are numbers.\n");
        }
        else if(same==1){
            system("cls");
            printf("This ID is exist.\n");
            exist=1;
        }
        else if(exist==0 && same==0){ //substitute
            strcpy(Data_List[*Item_Count].ID, CreateID);
            system("cls");
        }
    }while(exist == 1);

    //==============================input Name===============================
    char CreateName[200];
    printf("Enter Name: \n");
    scanf(" %[^\n]", CreateName);
    strcpy(Data_List[*Item_Count].Name, CreateName);
    system("cls");

    //==============================input category===============================
    char *Categories[10] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};
    int correct = 0;
    char CreateCategory[200];
    do{
        printf("Available Category: [Action, Fantasy, Comedy, Romance, Sports]\n");
        printf("Enter Category: \n");
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
            printf("!!! Unavailable Category !!!\n");
        }
    }while(correct == 0);

    //=============================input price=======================
    int again=1; 
    char CreatePrice[100];
    while(again){
        printf("Enter Price: ");
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
        printf("Wrong Input! Pls enter the positive integer\n");
    }

    //=============================input amount=======================
    again=1; 
    char CreateAmount[100];
    while(again){
        printf("Enter Amount: ");
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
        printf("Wrong Input! The Amount should >= 0\n");
    }
    //=============================input Note=======================
    if(atoi(CreateAmount) < 10)
        strcpy(Data_List[*Item_Count].Note, "REFILL");
    else
        strcpy(Data_List[*Item_Count].Note, "-");

    *Item_Count += 1; // Increment the item count
    WriteData(Data_List, Item_Count);
    printf("New book added successfully!\n");
    pressEnterToContinue();
}
// <============ Read Part ============>

void Read_All(Data *Data_List, int *Item_Count) {
    for (int i = 0; i < *Item_Count; i++) {
        printf("\nID: %s\n", Data_List[i].ID);
        printf("Category: %s\n", Data_List[i].Category);
        printf("Name: %s\n", Data_List[i].Name);
        printf("Price: %d\n", Data_List[i].Price);
        printf("Amount: %d\n", Data_List[i].Amount);
        printf("Note: %s\n", Data_List[i].Note);
    }

    pressEnterToContinue();
}

void Read_Menu(Data *Data_List, int *Item_Count) {
    char choice[10];
    int correct;
    do {
        correct = 0;
        printf("\nRead Menu\n");
        printf("(1) Read by ID\n");
        printf("(2) Read by Category\n");
        printf("(3) Read by Price\n");
        printf("(4) Read All\n");
        printf("(Q) Back to admin menu\n");
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
        printf("======= Please Enter the category to read =======\n");
        printf("Available Categories: Action, Fantasy, Comedy, Romance, Sports (Case Sensitive)\n");
        printf("(Q) Back to Read menu\n");
        printf("=================================================\n");

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
            puts("Error! Please input the correct category.\n");
        }

    } while (checkTemp == 0);

    printf("\nItems in Category %s:\n", category);
    for (int i = 0; i < *Item_Count; i++) {
        if (strcmp(category, Data_List[i].Category) == 0) {
            printf("\nID: %s\n", Data_List[i].ID);
            printf("Category: %s\n", Data_List[i].Category);
            printf("Name: %s\n", Data_List[i].Name);
            printf("Price: %d\n", Data_List[i].Price);
            printf("Amount: %d\n", Data_List[i].Amount);
            printf("Note: %s\n", Data_List[i].Note);
        }
    }

    pressEnterToContinue();
}
void Read_By_ID(Data *Data_List, int *Item_Count) {
    char ID[8];
    int index;

    do {
        printf("Enter the ID to read\n(or 'Q' to go back)\nID: ");
        scanf(" %[^\n]", ID);

        if (strcmp(ID, "Q") == 0) {
            system("cls");
            return;  // Go back to Read_Menu
        }

        if (valid_ID(ID, Data_List, Item_Count)) {
            system("cls");
            index = Get_Data_Index(ID, Data_List);
            printf("ID: %s\n", Data_List[index].ID);
            printf("Category: %s\n", Data_List[index].Category);
            printf("Name: %s\n", Data_List[index].Name);
            printf("Price: %d\n", Data_List[index].Price);
            printf("Amount: %d\n", Data_List[index].Amount);
            printf("Note: %s\n", Data_List[index].Note);
        } else {
            system("cls");
            printf("Item with ID %s not found. Please try again.\n", ID);
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
        printf("\nRead By Price Menu\n");
        printf("(1) Ascending\n");
        printf("(2) Descending\n");
        printf("(Q) Back to read menu\n");
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
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (1);
}

void Read_By_Ascending(Data *Data_List_Copy, int *Item_Count){
    char min[10];
    char max[10];

    do {
        printf("======= Please enter a valid value. =======\n");
        printf("(Q) Back to read by price menu\n");
        printf("Enter the minimum price: ");
        scanf(" %[^\n]", min);
        if (strcmp(min, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        printf("Enter the maximum price: ");
        scanf(" %[^\n]", max);
        if (strcmp(max, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        if(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max)){
            system("cls");
            printf("!!! Error Input! Please try again !!!\n");
        }
    }while(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max));

    printf("\nItems with Price between %s and %s:\n", min, max);
    qsort(Data_List_Copy, *Item_Count, sizeof(Data), Compare_By_Price_Ascending);
    int itemsFound = 0; // Flag to check if any items are found

    for (int i = 0; i < *Item_Count; i++) {
        if (Data_List_Copy[i].Price >= atoi(min) && Data_List_Copy[i].Price <= atoi(max)) {
            printf("%s        %s        %s         %d          %d         %s\n", Data_List_Copy[i].ID, Data_List_Copy[i].Category, Data_List_Copy[i].Name, Data_List_Copy[i].Price, Data_List_Copy[i].Amount, Data_List_Copy[i].Note);
            itemsFound = 1;  // Set the flag since an item is found
        }
    }

    if (!itemsFound) {
        system("cls");
        printf("No items found in the specified price range.\n");
    }
    pressEnterToContinue();
}

void Read_By_Descending(Data *Data_List_Copy, int *Item_Count){
    char min[10];
    char max[10];

    do {
        printf("======= Please enter a valid value. =======\n");
        printf("(Q) Back to read by price menu\n");
        printf("Enter the maximum price: ");
        scanf(" %[^\n]", max);
        if (strcmp(max, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        printf("Enter the minimum price: ");
        scanf(" %[^\n]", min);
        if (strcmp(min, MENU_EXIT) == 0) {
            system("cls");
            return;
        }

        if(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max)){
            system("cls");
            printf("!!! Error Input! Please try again !!!\n");
        }
    }while(isPureNumber(min) == 0 || isPureNumber(max) == 0 || atoi(min) < 0 || atoi(max) > 1000 || atoi(min) > atoi(max));
    
    printf("\nItems with Price between %s and %s:\n", min, max);
    qsort(Data_List_Copy, *Item_Count, sizeof(Data), Compare_By_Price_Descending);
    int itemsFound = 0; // Flag to check if any items are found

    for (int i = 0; i < *Item_Count; i++) {
        if (Data_List_Copy[i].Price >= atoi(min) && Data_List_Copy[i].Price <= atoi(max)) {
            itemsFound = 1;  // Set the flag since an item is found
            printf("%s        %s        %s         %d          %d         %s\n", Data_List_Copy[i].ID, Data_List_Copy[i].Category, Data_List_Copy[i].Name, Data_List_Copy[i].Price, Data_List_Copy[i].Amount, Data_List_Copy[i].Note);
        }
    }
    
    if (!itemsFound) {
        system("cls");
        printf("No items found in the specified price range.\n");
    }
    pressEnterToContinue();
}

int Compare_By_Price_Ascending(const void *a, const void *b) {
    return ((Data *)a)->Price - ((Data *)b)->Price;
}

int Compare_By_Price_Descending(const void *a, const void *b) {
    return ((Data *)b)->Price - ((Data *)a)->Price;
}

// <============ Update Part ============>
void Cashier_Menu(Data *Data_List, int *Item_Count){
    char choice[10];
    int correct;
    Check_File(WarehouseFileName);
    Check_File(ReportFileName);

    do{
        correct = 0;
        printf("========================\n");
        printf("Hello, Cashier\n");
        printf("Choose your menu \n\n");
        printf("1. Sell item\n");
        printf("Q. Return to menu\n");
        printf("========================\n\n");
        printf("Your choice: ");
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
            printf("!!! Invalid Choice. Please Enter Again !!!\n");
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
        printf("How many books to sell\n(Back to menu press Q)\nAmount: ");
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
            printf("!!! Please input a positive integer !!!\n");
        }
    }while(isPureNumber(sell_item_count_a) == 0|| atoi(sell_item_count_a) <= 0 );


    char Item_List[sell_item_count][7];
    int Amount_List[sell_item_count];
    system("cls");

    for(int i = 0; i < sell_item_count; i++){
        system("cls");
        if(i >=1){
            printf("======== Cart ========\n\n");
            printf("ID                 NAME            PRICE         AMOUNT         TOTAL\n");
        }
        for(int j = 0; j < i; j++){
            int cur_i = Get_Data_Index(Item_List[j], Data_List);
            printf("%s    %s     %d     %d     %d\n", Data_List[cur_i].ID, Data_List[cur_i].Name, Data_List[cur_i].Price, Amount_List[j], Amount_List[j] * Data_List[cur_i].Price);
        }
        printf("\n====================\n");

        char ID_modify[8];

        //Check ID
        do{
            printf("Input item %d's ID to sell\n(Back to menu press Q)\nID: ", i+1);
            scanf(" %[^\n]", ID_modify);

            if(strcmp(ID_modify, MENU_EXIT) == 0){
                system("cls");
                Cashier_Menu(Data_List, Item_Count);
                return;
            }

            if(valid_ID(ID_modify, Data_List, Item_Count) == 0){
                system("cls");
                printf("Please input the existed ID!\n");
            }

        }while(valid_ID(ID_modify,Data_List, Item_Count) == 0);
        strcpy(Item_List[i], ID_modify);
        system("cls");

        //after id valid check if amount valid for sell
        int index = Get_Data_Index(ID_modify, Data_List);
        //Check Amount
        if(Data_List[index].Amount > 0){
            do{
                printf("Input Amount of Book \"%s\" to sell (%d left)\n(Back to menu press Q)\nAmount: ",  Data_List[index].Name, Data_List[index].Amount);
                scanf(" %[^\n]", amount_a);

                if(strcmp(MENU_EXIT,amount_a) == 0){
                    Cashier_Menu(Data_List,Item_Count);
                    return;
                }

                if(isPureNumber(amount_a)){
                    amount = atoi(amount_a);
                    if(amount <= 0){
                        system("cls");
                        printf("!!! Invalid input. Please enter a positive integer. !!!\n");
                    }else if(amount > Data_List[index].Amount){
                        system("cls");
                        printf("!!! Insufficient amount input. Please enter a lesser positive integer. !!!\n");
                    }
                    else{
                        Amount_List[i] = amount;
                        break;
                    }
                }
                else{
                    system("cls");
                    printf("!!! Invalid input. Please enter a positive integer. !!!\n");
                }
            }while(isPureNumber(amount_a) == 0 || atoi(amount_a) > Data_List[index].Amount);

        }else{
            printf("Sorry, the \"%s\" is out of stock. Going to next item\n", Data_List[index].Name);
            pressEnterToContinue();
            i -= 1;
            sell_item_count -= 1;
        }
    }

    system("cls");
    printf("This is all of your Cart.\n");
    printf("======== Cart ========\n\n");
    for(int j = 0; j < sell_item_count; j++){
        int cur_i = Get_Data_Index(Item_List[j], Data_List);
        printf("ID:%s Name:%s Price:%d Amount:%d Total:%d\n", Data_List[cur_i].ID, Data_List[cur_i].Name, Data_List[cur_i].Price, Amount_List[j], Amount_List[j] * Data_List[cur_i].Price);
    }
    printf("\n====================\n\n");
    pressEnterToContinue();

    for(int i = 0; i < sell_item_count; i++){
        //Update Struct
        int index = Get_Data_Index(Item_List[i], Data_List);
        Data_List[index].Amount -= Amount_List[i];

        //Write Struct to file
        WriteData(Data_List, Item_Count);
        Write_Report(Item_List[i], Data_List, Amount_List[i]);
        printf("ID: %s Amount: %d Updated!\n", Item_List[i], Amount_List[i]);
        printf("Stock ID: %s Name:%s Amount: %d\n\n",Data_List[Get_Data_Index(Item_List[i], Data_List)].ID, Data_List[Get_Data_Index(Item_List[i], Data_List)].Name, Data_List[Get_Data_Index(Item_List[i], Data_List)].Amount);
    }
    pressEnterToContinue();
    Cashier_Menu(Data_List, Item_Count);
}

void Update_Admin_Menu(Data *Data_List, int *Item_Count){
    system("cls");
    Check_File(WarehouseFileName);

    char ID_Modify[8];
    do{
        printf("========================\n");
        printf("Hello, Admin\n");
        printf("Input ID you want to Update(Exit Press Q)\n\n");
        printf("========================\n\n");
        printf("ID: ");
        scanf(" %[^\n]", ID_Modify);
        if(strcmp(ID_Modify, MENU_EXIT) == 0){
            system("cls");
            return;
        }

        if(valid_ID(ID_Modify,Data_List,Item_Count) == 0){
            system("cls");
            printf("Please input the existed ID!\n");
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
            printf("========================\n");
            printf("ID: %s\n", Data_List[index].ID);
            printf("Name: %s\n", Data_List[index].Name);
            printf("Category: %s\n", Data_List[index].Category);
            printf("Price: %d\n", Data_List[index].Price);
            printf("Amount: %d\n", Data_List[index].Amount);
            printf("Note: %s\n", Data_List[index].Note);
            printf("========================\n");
            printf("Choose the option(Exit Press Q)\n\n");
            printf("1. Update Name\n");
            printf("2. Update Category\n");
            printf("3. Update Price\n");
            printf("4. Update Amount\n");
            printf("========================\n\n");
            printf("Your choice: ");

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
                printf("!!! Invalid input. Please enter the valid choice !!!\n");
            }
        }while(correct == 0 || atoi(choice) > 4 || isPureNumber(choice) == 0);
    }
}

void Update_Name(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[100];
    system("cls");
    printf("========================\n");
    printf("ID: %s Old Name: %s\n", ID, Data_List[index].Name);
    printf("(Q) Back to Update menu\n");
    printf("========================\n\n");
    printf("New Name: ");
    scanf(" %[^\n]", temp);

    if( strcmp(temp, MENU_EXIT) == 0){{
        system("cls");
        return;
    }
    }else{
        strcpy(Data_List[index].Name, temp);
    }

    WriteData(Data_List, Item_Count);
    printf("Updated!");
    pressEnterToContinue();
}

void Update_Category(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);
    char *Categories[10] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};

    int correct = 0;
    system("cls");

    char temp[200];
    
    do{
        printf("========================\n");
        printf("ID: %s Old Category: %s\n", ID, Data_List[index].Category);
        printf("Available Category: [Action, Fantasy, Comedy, Romance, Sports]\n");
        printf("(Q) Back to Update menu\n");
        printf("========================\n\n");
        printf("New Category: ");
        scanf(" %[^\n]", temp);

        if(strcmp(temp, "Q") == 0){
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
            printf("!!! Unavailable Category !!!\n");
        }
    }while(correct == 0);

    WriteData(Data_List, Item_Count);
    printf("Updated!\n");
    pressEnterToContinue();
}  

void Update_Price(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        printf("========================\n");
        printf("ID: %s Old Price: %d\n", ID, Data_List[index].Price);
        printf("(Q) Back to Update menu\n");
        printf("========================\n\n");
        printf("New Price: ");
        scanf(" %[^\n]", temp);

        if(strcmp(temp, "Q") == 0){
            system("cls");
            return;
        }

        if(isPureNumber(temp) && atoi(temp) > 0){
            Data_List[index].Price = atoi(temp);

        }else{
            system("cls");
            printf("!!! Error Input !!!\n");
        }
    }while(isPureNumber(temp) == 0 || atoi(temp) < 0);

    WriteData(Data_List, Item_Count);
    printf("Updated!\n");
    pressEnterToContinue();
}

void Update_Amount(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        printf("========================\n");
        printf("ID: %s Old Amount: %d\n", ID, Data_List[index].Amount);
        printf("(Q) Back to admin menu\n");
        printf("========================\n\n");
        printf("New Amount: ");
        scanf(" %[^\n]", temp);

        if(strcmp(temp, "Q") == 0){
            system("cls");
            return;
        }

        if(isPureNumber(temp) && atoi(temp) >= 0){
            Data_List[index].Amount = atoi(temp);
            if (Data_List[index].Amount >= 10){
                strcpy(Data_List[index].Note, "-");
            }else{
                strcpy(Data_List[index].Note, "REFILL");
            }
        }else{
            system("cls");
            printf("!!! Error Input !!!\n");
        }
    }while(isPureNumber(temp) == 0 || atoi(temp) < 0);

    WriteData(Data_List, Item_Count);
    printf("Updated!\n");
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


// <=================== Delete Part ==================>
void Delete_Menu(Data *Data_List, int *Item_Count){
    system("cls");

    char ID_Modify[8];
    do{
        printf("========================\n");
        printf("Hello, Admin\n");
        printf("Input ID you want to Delete(Exit Press Q)\n\n");
        printf("========================\n\n");
        printf("ID: ");
        scanf(" %[^\n]", ID_Modify);
        if(strcmp(ID_Modify, MENU_EXIT) == 0){
            system("cls");
            //goto admin menu
            return;
        }

        if(valid_ID(ID_Modify,Data_List,Item_Count) == 0){
            system("cls");
            printf("Please input the existed ID!\n");
        }
    }while(valid_ID(ID_Modify,Data_List,Item_Count) == 0);


    int index = Get_Data_Index(ID_Modify, Data_List);

    system("cls");
    printf("========================\n");
    printf("ID: %s\n", Data_List[index].ID);
    printf("Name: %s\n", Data_List[index].Name);
    printf("Category: %s\n", Data_List[index].Category);
    printf("Price: %d\n", Data_List[index].Price);
    printf("Amount: %d\n", Data_List[index].Amount);
    printf("Note: %s\n", Data_List[index].Note);
    printf("========================\n");
    printf("Are you sure to delete this item?[Y/n]\n(Exit Press Q)\n\n");
    printf("========================\n\n");

    char choice[10];

    do{
        printf("[Y/n]: ");
        scanf(" %[^\n]", choice);

        if(strcmp(choice, MENU_EXIT) == 0){
            Delete_Menu(Data_List, Item_Count);
            return;
        }

    }while(strcmp(choice,"Y") != 0 && strcmp(choice, "n") != 0);

    if(strcmp(choice,"Y") == 0){
        Delete_Item(Data_List, Item_Count, ID_Modify);
        system("cls");
        printf("Item %s Deleted\n",     ID_Modify);
    }else{
        system("cls");
        printf("Delete item was canceled\n");
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


// <============ Sales Report Part ============>
void SalesReport_Menu()
{

    char choice[10];

    Check_File(ReportFileName);

    do
    {
        printf("========================\n");
        printf("Hello, Cashier\n");
        printf("Choose your menu \n\n");
        printf("1. All Record\n");
        printf("2. Daily Report\n");
        printf("3. Monthly Report\n");
        printf("Q. Return to menu\n");
        printf("========================\n\n");
        printf("Your choice: ");

        scanf(" %s", choice);
        if (strcmp(choice, "Q") == 0)
        {
            system("cls");
            return;
        }
        else if (strcmp(choice, MENU_ONE) == 0)
        {
            system("cls");
            All_Report();
            break;
        }
        else if (strcmp(choice, MENU_TWO) == 0)
        {
            system("cls");
            Daily_Report();
            break;
        }
        else if (strcmp(choice, MENU_THREE) == 0)
        {
            system("cls");
            Monthly_Report();
            break;
        }
        else
        {
            system("cls");
            printf(" \033[1;31m!!! Invalid Choice. Please Enter Again !!!\n");
        }
    } while (isPureNumber(choice) == 0 || atoi(choice) == 0 || atoi(choice) > 3);
    SalesReport_Menu();
}

void All_Report()
{
    FILE *report = fopen(ReportFileName, "r");
    char line[256];
    fgets(line, sizeof(line), report);
    printf("DATE%*cTIME%*cID%*cNAME%*cPRICE%*cAMOUNT%*cTOTAl\n\n",11,' ', 11, ' ', 8, ' ', 46, ' ',5, ' ', 4, ' ');

    char amount[256];

    while (fgets(line, sizeof(line), report)){
        if(strncmp(line, "Total", 5) == 0)
        {
            printf("%s%*c", strtok(line, ","), 95, ' ');
            strcpy(amount, strtok(NULL, ","));
            printf("%s%*c", amount , 7 - countDigits(atoi(amount)) ,' ');
            printf("%s\n\n", strtok(NULL, ","));
        }else if(line[2] == '/'){
            print_sales(line);
        }else{
            continue;
        }
    }
    fclose(report);
    pressEnterToContinue();
    system("cls");
}

void Monthly_Report()
{    
    Date date;
    strcpy(date.day, "1");

    do
    {
        printf("Input Date (Format: MM YYYY)\nDate: ");
        scanf("%s %s", date.month, date.year);
        if(strcmp(date.month, MENU_EXIT) == 0){
            system("cls");
            return ;
        }

        if (!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year))
        {
            system("cls");
            printf("!!! Invalid Date, Input Again !!!\n");
        }
        else
        {
            break;
        }
    } while (!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year));

    system("cls");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    int amount, sum_amount = 0;
    int total, sum_total = 0;

    // skip column name
    fgets(line, sizeof(line), report);
    printf("DATE%*cTIME%*cID%*cNAME%*cPRICE%*cAMOUNT%*cTOTAl\n\n",11,' ', 11, ' ', 8, ' ', 46, ' ',5, ' ', 4, ' ');

    while (fgets(line, sizeof(line), report))
    {
        strcpy(temp, line);
        Date cur_date = GetDate(temp);

        if (strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0)
        {
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d,%d",&amount, &total);
            sum_amount += amount;
            sum_total += total;
            print_sales(line);
            count++;
        }
    }
    if (!count){
        system("cls");
        printf("Date: %s/ %s has no sales Record\n", date.month, date.year);
    }else{
        printf("TOTAL%*c", 95, ' ');
        printf("%d%*c", sum_amount , 10 - countDigits(sum_amount) ,' ');
        printf("%d\n\n", sum_total);       
    }
    fclose(report);
    pressEnterToContinue();
}

void Daily_Report()
{
    Date date;
    do
    {
        printf("Input Date (Format: DD MM YYYY)\nDate: ");
        scanf("%s %s %s", date.day, date.month, date.year);
        if (!valid_date(date) || !isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year))
        {
            system("cls");
            printf("!!! Invalid Date, Input Again !!!\n");
        }
        else
        {
            break;
        }
    } while (!valid_date(date) || isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year));

    system("cls");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    // skip column name
    fgets(line, sizeof(line), report);
    int amount, sum_amount = 0;
    int total, sum_total = 0;

    printf("DATE%*cTIME%*cID%*cNAME%*cPRICE%*cAMOUNT%*cTOTAl\n\n",11,' ', 11, ' ', 8, ' ', 46, ' ',5, ' ', 4, ' ');
    while (fgets(line, sizeof(line), report))
    {
        strcpy(temp, line);
        Date cur_date = GetDate(temp);
        if (strcmp(cur_date.day, date.day) == 0 && strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0)
        {
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d,%d",&amount, &total);
            sum_amount += amount;
            sum_total += total;
            print_sales(line);
            count++;
        }
    }

    if (!count){
        system("cls");
        printf("Date: %s/ %s/ %s has no sales Record\n", date.day, date.month, date.year);
    }else{
        printf("TOTAL%*c", 95, ' ');
        printf("%d%*c", sum_amount , 10 - countDigits(sum_amount) ,' ');
        printf("%d\n\n", sum_total);
    }

    fclose(report);
    pressEnterToContinue();
}

void print_sales(char *line){
    char name[256];
    char price[256];
    char amount[256];
    printf("%s     ", strtok(line, ","));
    printf("%s", strtok(NULL, ","));
    printf("%*c%s", 7, ' ', strtok(NULL, ","));

    strcpy(name, strtok(NULL, ","));
    printf("%*c%s", 4, ' ', name);

    strcpy(price, strtok(NULL, ","));
    printf("%*c%s", 50 - strlen(name), ' ', price);

    strcpy(amount, strtok(NULL, ","));
    printf("%*c%s", 10 - countDigits(atoi(price)), ' ', amount);

    printf("%*c%s\n", 10 - countDigits(atoi(amount)), ' ', strtok(NULL, "\n"));
}

int countDigits(int num){
    int count = 0;

    while(num > 0){
        count++;
        num /= 10;
    }

    return count;
}