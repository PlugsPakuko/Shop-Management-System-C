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

// <============ Notification Part ============>
int Check_Alert(Data *Data_List, int *Item_Count);
void Save_Alert(Data *Data_List, char (*ID_Alert)[7], int Alert_Count);
void Print_Alert(Data *Data_List, int *Item_Count);
void Refill(Data *Data_List, int *Item_Count);

// <============ System Login Part ============>
void Admin_Login(Data *Data_List, int *Item_Count);
void Admin_Menu(Data *Data_List, int *Item_Count);
void Login_Menu(Data *Data_List, int *Item_Count);
// <============ Create Part ============>
void CreateNewBook(Data *Data_List, int *Item_Count);

// <============ Read Part ============>
void Read_Menu(Data *Data_List, int *Item_Count);
void Read_All(Data *Data_List, int *Item_Count);
void Read_By_ID(Data *Data_List, int *Item_Count);
void Read_By_Category(Data *Data_List, int *Item_Count);
void Read_By_Price(Data *Data_List, int *Item_Count);

int Compare_By_Price_Ascending(const void *a, const void *b) {
    return ((Data *)a)->Price - ((Data *)b)->Price;
}

int Compare_By_Price_Descending(const void *a, const void *b) {
    return ((Data *)b)->Price - ((Data *)a)->Price;
}

// <============ Update Part ============>
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

// <============ Delete Part ============>
void Delete_Menu(Data *Data_List, int *Item_Count);// Delete System for admin
void Delete_Item(Data *Data_List, int *Item_Count, char *ID);// Function to delete item

// <============ SalesReport Part ============>
void SalesReport_Menu();
void All_Report();
void Monthly_Report();
void Daily_Report();
void Print_Format(char *line);

// <=========== Struct Management ============>
void Bin2Struct(Data *Data_List, int *Item_Count);
int get_count();
int Get_Data_Index(char *ID, Data *Data_List);// get index of element by ID
void Print_Data(Data *Data_List, int *Item_Count);//Print whole struct

// <=========== File Management ============>
void Check_File(char *FileName); //Chechk if File available
void WriteData(Data *Data_List, int *Item_Count);
void printBinaryFile();
void CSVtoBin();

// <=========== Input Management ============>
void Exit();
void pressEnterToContinue();
int isLeapYear(int year);
int valid_date(Date date);
int isPureNumber(char *input); // Chechk if the input is only number no contain alphabet
int valid_ID(char *ID, Data *Data_List, int *Item_count);
void get_line_input(char *input);


int main() {
    CSVtoBin();
    system("cls");
    Check_File(WarehouseFileName);
    Check_File(WarehouseCSVFilename);
    Check_File(ReportFileName);
    // ===== Initialization ======
    int Item_Count = get_count();
    Data Data_List[Item_Count];
    Bin2Struct(Data_List, &Item_Count);
    WriteData(Data_List, &Item_Count);
    // ===========================

    // ===== On start Alert =====
    // Print_Alert(Data_List, &Item_Count);
    // pressEnterToContinue();
    // Uncomment to see readable-binary file
    // printBinaryFile();


    Login_Menu(Data_List, &Item_Count);
    // Admin_Menu(Data_List, &Item_Count);
    // Cashier_Menu(Data_List, &Item_Count);
    // Update_Admin_Menu(Data_List, &Item_Count);



    // for(int i = 0; i < 1; i++){
    //     printf("ID : %s\n", Data_List[i].ID);
    //     printf("Category: %s\n", Data_List[i].Category);
    //     printf("Name: %s\n", Data_List[i].Name);
    //     printf("Price : %d\n", Data_List[i].Price);
    //     printf("Amount : %d\n", Data_List[i].Amount);
    //     printf("Note : %s\n", Data_List[i].Note);
    //     printf("\n");
    // }

    // int i = Get_Data_Index("EX0001", Data_List);
    // Delete_Menu(Data_List, &Item_Count);
    // printf("%d", i);
    // Data_List[0].Amount -= 500;

    // WriteData(Data_List, &Item_Count);
    // Bin2Struct(Data_List, &Item_Count);


    // Monthly_Report();
    // Daily_Report();
    pressEnterToContinue();
    // Print_Data(Data_List, &Item_Count);
    // printf("\nCount: %d", Item_Count);

    return 0;
}

// <=========== Input Management =============>
void Exit(){
    exit(0);
}

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

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) 
        return 0;

    if (month == 2 && day == 29 && !isLeapYear(year)) 
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

void get_line_input(char *input){
    char line[200];
    gets(line);
    strcpy(input, line);
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
        Exit();
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
            get_line_input(choice);
            // scanf(" %s", choice);

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
        get_line_input(choice);
        // scanf(" %s", choice);

        if(strcmp(choice, MENU_EXIT) == 0){
            system("cls");
            return ;
        }else if(strcmp(choice, MENU_ONE) == 0){
            system("cls"); //clear screen before call function
            Admin_Login(Data_List, Item_Count);
            break;
        }else if(strcmp(choice, MENU_TWO) == 0){
            system("cls"); //clear screen before call function
            Update_Cashier(Data_List, Item_Count);
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
    printf("Enter Book ID (EX0001): ");
    scanf("%6s", Data_List[*Item_Count].ID);

    printf("Enter Book Name: ");
    getchar(); // consume the newline character left in the input buffer
    fgets(Data_List[*Item_Count].Name, sizeof(Data_List[*Item_Count].Name), stdin);
    Data_List[*Item_Count].Name[strcspn(Data_List[*Item_Count].Name, "\n")] = '\0'; // remove the trailing newline

    printf("Enter Category: ");
    scanf("%99s", Data_List[*Item_Count].Category);

    printf("Enter Price: ");
    scanf("%d", &Data_List[*Item_Count].Price);

    printf("Enter Amount in Stock: ");
    scanf("%d", &Data_List[*Item_Count].Amount);

    // Note should be "REFILL" only
    printf("Enter Note (should be 'REFILL'): ");
    scanf("%6s", Data_List[*Item_Count].Note);

    *Item_Count += 1; // Increment the item count
    WriteData(Data_List, Item_Count);
    printf("New book added successfully!\n");
    system("clean");
}

// <============ Read Part ============>

void Read_Menu(Data *Data_List, int *Item_Count) {
    char choice[10];
    do {

        printf("\nRead Menu\n");
        printf("(1) Read by ID\n");
        printf("(2) Read by Category\n");
        printf("(3) Read by Price\n");
        printf("(Q) Back to admin menu\n");
        scanf(" %s", choice);

        if (strcmp(choice, MENU_EXIT) == 0) {
            system("cls"); //clear screen before call function
            Admin_Menu(Data_List, Item_Count);
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
        } else {
            system("cls"); //clear screen before call function
            printf("\nInvalid choice. Please enter a valid option.\n"); // error input text
        }
    } while (atoi(choice) > 3 || isPureNumber(choice) == 0);

}

void Read_By_ID(Data *Data_List, int *Item_Count) {
    char ID[8];
    printf("Enter the ID to read: ");
    scanf("%s", ID);

    int index = Get_Data_Index(ID, Data_List);

    if (index != -1) {
        printf("\nID: %s\n", Data_List[index].ID);
        printf("Category: %s\n", Data_List[index].Category);
        printf("Name: %s\n", Data_List[index].Name);
        printf("Price: %d\n", Data_List[index].Price);
        printf("Amount: %d\n", Data_List[index].Amount);
        printf("Note: %s\n", Data_List[index].Note);
    } else {
        printf("Item with ID %s not found.\n", ID);
    }

    pressEnterToContinue();
}

void Read_By_Category(Data *Data_List, int *Item_Count) {
    char category[100];
    char *Categories[5] = {"Action", "Fantasy", "Comedy", "Romance", "Sports"};
    int checkTemp = 0;
    printf("======= Please Enter the category to read =======\n");
    printf("Available Categories : Action, Fantasy, Comedy, Romance, Sports (Case Sensitive)\n");
    scanf("%s", category);

    for (int i = 0; i < 5; ++i) {
        if (strcmp(category, Categories[i]) == 0) {
            checkTemp++;
            break;
        }
    }
    if(checkTemp == 0){
        printf("Error! Please input the correct category.\n");
    }
    else{ 
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
    }
    pressEnterToContinue();
}

void printData(Data *Data_List, int index) {
    printf("\nID: %s\n", Data_List[index].ID);
    printf("Category: %s\n", Data_List[index].Category);
    printf("Name: %s\n", Data_List[index].Name);
    printf("Price: %d\n", Data_List[index].Price);
    printf("Amount: %d\n", Data_List[index].Amount);
    printf("Note: %s\n", Data_List[index].Note);
}

void Read_By_Price(Data *Data_List, int *Item_Count) {

    Data Copy_Data_List[*Item_Count];
    for(int i = 0; i < *Item_Count; i++)
        Copy_Data_List[i] = Data_List[i];

}

// <============ Update Part ============>
void Cashier_Menu(Data *Data_List, int *Item_Count){
    char choice[10];

    system("cls");
    Check_File(WarehouseFileName);
    // Check_File(ReportFileName);

    do{
        printf("========================\n");
        printf("Hello, Cashier\n");
        printf("Choose your menu \n\n");
        printf("1. Sell item\n");
        printf("Q. Return to menu\n");
        printf("========================\n\n");
        printf("Your choice: ");

        scanf(" %s", choice);
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
    }while (isPureNumber(choice) == 0 || atoi(choice) > 1);

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
        scanf(" %s", sell_item_count_a);

        if(strcmp(MENU_EXIT,sell_item_count_a) == 0){
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
            scanf(" %s", ID_modify);

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
                scanf(" %s", amount_a);

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
        scanf(" %s", ID_Modify);
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
    while (1)
    {
        int index = Get_Data_Index(ID_Modify, Data_List);
        char choice[10];

        do{
            system("cls");
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

            scanf(" %s", choice);
            if(strcmp(choice, MENU_EXIT) == 0){
                system("cls");
                Update_Admin_Menu(Data_List, Item_Count);
                return ;
            }
            else if(atoi(choice) > 0 && atoi(choice) < 5){
                break;
            }else{
                system("cls");
                printf("!!! Invalid input. Please enter the valid choice !!!");
            }
            
        }while(atoi(choice) > 4 || isPureNumber(choice) == 0);


        if(strcmp(choice, MENU_ONE) == 0)
            Update_Name(ID_Modify, Data_List, Item_Count);
        else if(strcmp(choice, MENU_TWO) == 0)
            Update_Category(ID_Modify, Data_List, Item_Count);
        else if(strcmp(choice, MENU_THREE) == 0)
            Update_Price(ID_Modify, Data_List, Item_Count);
        else if(strcmp(choice, MENU_FOUR) == 0)
            Update_Amount(ID_Modify, Data_List, Item_Count);
    }
}

void Update_Name(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[100];
    system("cls");
    printf("========================\n");
    printf("ID: %s Old Name: %s\n(Return to previous page press Q)\n", ID, Data_List[index].Name);
    printf("========================\n\n");
    printf("New Name: ");
    getchar();
    fgets(temp, sizeof(temp), stdin);
    temp[strlen(temp) - 1] = '\0';
    if( strcmp(temp, MENU_EXIT) == 0){
        return;
    }else{
        strcpy(Data_List[index].Name,temp);
    }

    WriteData(Data_List, Item_Count);
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
        printf("========================\n\n");
        printf("New Category: ");
        scanf(" %s", temp);

        if(strcmp(temp, "Q") == 0)
            return;

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
}  

void Update_Price(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        printf("========================\n");
        printf("ID: %s Old Price: %d\n", ID, Data_List[index].Price);
        printf("========================\n\n");
        printf("New Price: ");
        scanf(" %s", temp);

        if(strcmp(temp, "Q") == 0)
            return;

        if(isPureNumber(temp) && atoi(temp) >= 0){
            Data_List[index].Price = atoi(temp);

        }else{
            system("cls");
            printf("!!! Error Input !!!\n");
        }
    }while(isPureNumber(temp) == 0 || atoi(temp) < 0);

    WriteData(Data_List, Item_Count);
}

void Update_Amount(char *ID, Data *Data_List, int *Item_Count){
    int index = Get_Data_Index(ID, Data_List);

    char temp[50];
    system("cls");

    do{
        printf("========================\n");
        printf("ID: %s Old Amount: %d\n", ID, Data_List[index].Amount);
        printf("========================\n\n");
        printf("New Amount: ");
        scanf(" %s", temp);

        if(strcmp(temp, "Q") == 0)
            return;

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
        fprintf(tempSale, "Total,,,,,%d,%.2lf\n\n", amount, amount * Data_List[index].Price);
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
        scanf(" %s", ID_Modify);
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
        scanf(" %s", choice);

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
void SalesReport_Menu(){

    char choice[10];

    Check_File(ReportFileName);

    do{
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
        if(strcmp(choice, "Q") == 0){
            system("cls");
            return ;
        }else if(strcmp(choice, MENU_ONE) == 0){
            system("cls");
            All_Report();
            break;
        }else if(strcmp(choice, MENU_TWO) == 0){
            system("cls");
            Daily_Report();
            break;
        }else if(strcmp(choice, MENU_THREE) == 0){
            system("cls");
            Monthly_Report();
            break;
        }
        else{
            system("cls");
            printf("!!! Invalid Choice. Please Enter Again !!!\n");
        }
    }while (isPureNumber(choice) == 0 || atoi(choice) == 0 || atoi(choice) > 3);
    SalesReport_Menu();
}

void All_Report(){
    FILE* report = fopen(ReportFileName, "r");
    char line[256];
    while (fgets(line, sizeof(line), report))
        Print_Format(line);
    pressEnterToContinue();
    fclose(report);
}

void Monthly_Report(){
    char month[20];
    char year[20];

    Date date;
    strcpy(date.day, "1");

    do{
        printf("Input Date (Format: MM YYYY)\nDate: ");
        scanf("%s %s", date.month, date.year);
        if(!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year)){
            system("cls");
            printf("!!! Invalid Date, Input Again !!!\n");
        }else{
            break;
        }
    }while(!valid_date(date) || !isPureNumber(date.month) || !isPureNumber(date.year));

    system("clear");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    //skip column name
    fgets(line, sizeof(line), report);
    Print_Format(line);

    while(fgets(line, sizeof(line), report)){
        strcpy(temp, line);
        Date cur_date = GetDate(temp);

        // printf("cur.date: %d %d Bool:%d \n", cur_date.month, cur_date.year, strcmp(cur_date.month, month) == 0);
        if(strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0){
            Print_Format(line);
            // printf("%s\n", line);
            count++;
        }
    }
    if(!count)
        printf("Date: %s/ %s has no sales Record\n", date.month, date.year);
    fclose(report);
    pressEnterToContinue();
}

void Daily_Report(){
    char day[20];
    char month[20];
    char year[20];


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Date date;
    do{
        printf("Input Date (Format: DD MM YYYY)\nDate: ");
        scanf("%s %s %s", date.day, date.month, date.year);
        if(!valid_date(date) || !isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year)){
            system("cls");
            printf("!!! Invalid Date, Input Again !!!\n");
        }else{
            break;
        }
    }while(!valid_date(date) || isPureNumber(date.day) || !isPureNumber(date.month) || !isPureNumber(date.year));

    system("cls");

    Check_File(ReportFileName);
    int count = 0;
    FILE *report = fopen(ReportFileName, "r");

    char line[256];
    char temp[256];
    //skip column name
    fgets(line, sizeof(line), report);
    Print_Format(line);

    while(fgets(line, sizeof(line), report)){
        strcpy(temp, line);
        Date cur_date = GetDate(temp);

        // printf("cur.date: %d %d Bool:%d \n", cur_date.month, cur_date.year, strcmp(cur_date.month, month) == 0);
        if(strcmp(cur_date.day, date.day) == 0 && strcmp(cur_date.month, date.month) == 0 && strcmp(cur_date.year, date.year) == 0){
            Print_Format(line);
            count++;
        }
    }

    if(!count)
        printf("Date: %s/ %s/ %s has no sales Record\n", date.day, date.month, date.year);
    fclose(report);
    pressEnterToContinue();
}

void Print_Format(char *line){
    while(*line){
        if(*line == ','){
            printf("%-*c", 5, ' ');
        }else
            printf("%c", *line);
        line++;
    }
    printf("\n");
}
