#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MENU_EXIT 'Q'
#define MENU_ONE '1'
#define MENU_TWO '2'
#define MENU_THREE '3'
#define MENU_FOUR '4'
#define MENU_FIVE '5'
#define MENU_SIX '6'

// Initialize function
// <============ UI Part ============>
void Login_Menu();
void Admin_Login();

void Admin_Menu();
void Cashier_Menu();

void Create_Menu();
void Read_Menu(); 
void Update_Cashier_Menu();
void Update_Admin_Menu();
void Delete_Menu();

void List_Warehouse();

// <============ Login system Part ============>
void SelectUser();
void AdminVerify();

// <============ Create Part ============>
void CreateItem();

// <============ Read Part ============>
void ReadAll();
void ReadByCategory();
void ReadByPrice();
void SearchID();

// <============ Update Part ============>
void UpdateCashier();
void UpdateAdmin();

// <============ Delete Part ============>
void Delete();


void Exit(){
    exit(0);
}

int valid_choice(char *choice, char *valid_choice) {
    int i = 0;
    while (valid_choice[i]) {
        if (*choice == valid_choice[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}

int valid_ID(char *ID, char (*ID_List)[7]){
    int i = 0;
    while(ID_List[i][0]){
        if(strcmp(ID,ID_List[i]) == 0)
            return 1;
        i++;
    }

    return (0);

}

void loop_input(char *choice, char *valid){
    do{
        printf("Choose valid choice: ");
        scanf(" %c", choice);
    }
    while (valid_choice(choice, valid) == 0);
}

int get_count(FILE *WarehouseFile){
    int count = 0;
    char line[200];
    while(fgets(line,sizeof(line),WarehouseFile)){
        count++;
    }

    rewind(WarehouseFile);
    return count;
}

void make_valid_ID_list(FILE *WarehouseFile,int item_count, char (*ID_list)[7]){
    char line[200];
    int i = 0;
    fgets(line, sizeof(line),WarehouseFile);
    while (fgets(line,sizeof(line),WarehouseFile))
    {
        char *token = strtok(line,",");
        if(token != NULL){
            strcpy(ID_list[i], token);
            i++;
        }
    }
    ID_list[i][0] = '\0'; 
    rewind(WarehouseFile);
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Update_Warehouse(FILE *WarehouseFile,FILE *ReportFile,char *ID, int amount, int users){
    char line[200];
    char TempFile[] = "temp.csv";
    int wh_amount;
    int wh_price;

    FILE *tempSale = fopen("tempSales.csv", "w");
    FILE *tempFile = fopen(TempFile, "w");

    while (fgets(line,sizeof(line),WarehouseFile) )
    {

        if(strncmp(ID,line,6) == 0){
            char *token = strtok(line,",");
            
            fprintf(tempFile,"%s,", token);

            for(int i = 0; i < 3; i++){
                token = strtok(NULL,",");
                if(i != 2)
                    fprintf(tempFile,"%s,", token);
            }

            wh_amount = atoi(token);
            wh_amount -= amount;
            fprintf(tempFile, "%d,", wh_amount);

            token = strtok(NULL,",");
            wh_price = atoi(token);
            fprintf(tempFile,"%d", wh_price);

            if(wh_amount < 10)
                fprintf(tempFile,",%s\n", "REFILL");
            else
                fprintf(tempFile,"\n");


        }else{
            fputs(line,tempFile);
        }
    }

    if(users == 1){
        line[200];

        while (fgets(line,sizeof(line),ReportFile))
        {
            fputs(line,tempSale);
        }
        fprintf(tempSale,"\n");

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(tempSale,"%02d/%02d/%d,%02d:%02d:%02d,%s,%s,%d,%d,%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,ID,"Product_name",wh_price,amount,amount * wh_price);
    }

    fclose(WarehouseFile);
    fclose(ReportFile);

    fclose(tempSale);
    fclose(tempFile);

    remove("MangaWarehouse.csv");
    remove("SalesReport.csv");

    rename("tempSales.csv", "SalesReport.csv");
    rename(TempFile, "MangaWarehouse.csv");
    printf("%s Updated!\n", ID);

}

void Update_Cashier(FILE *WarehouseFile, FILE *ReportFile, char (*ID_List)[7]) {
    char choice;
    char valid[] = {MENU_EXIT, MENU_ONE};

    system("cls");

    printf("========================\n");
    printf("Choose your menu (Exit Press Q)\n\n");
    printf("1. Sell item (Update Fn)\n");
    printf("========================\n\n");

    
    loop_input(&choice, valid);

    system("cls");

    if(choice == MENU_ONE){
        char ID_modify[8];
        char amount_a[10];
        int amount;

        do{
            printf("Input item ID to sell(Back to menu press Q): ");
            scanf(" %s", ID_modify);

            if(ID_modify[0] == MENU_EXIT){
                Update_Cashier(WarehouseFile,ReportFile,ID_List);
                return;
            }

            if(valid_ID(ID_modify,ID_List) == 0){
                system("cls");
                printf("Please input the existed ID!\n");

            }
        }while( valid_ID(ID_modify,ID_List) == 0);

        int status;
        do{
            printf("Input Amount to sell(Back to menu press Q): ");
            scanf(" %s", &amount_a);

            if(strcmp("Q",amount_a) == 0){
                Update_Cashier(WarehouseFile,ReportFile,ID_List);
                return;
            }

            amount = atoi(amount_a);
            if(amount <= 0){
                system("cls");
                printf("Invalid input. Please enter a positive integer.\n");
            }
        }while( amount <= 0 );

        Update_Warehouse(WarehouseFile,ReportFile,ID_modify,amount,1);
        printf("%s Updated!\n", ID_modify);
    }
    else if(choice == MENU_EXIT){
        Exit();
    }
    else{
        Update_Cashier(WarehouseFile,ReportFile,ID_List);
        return ;
    }
}

void Update_Admin(FILE* WarehouseFile){

}

int main(void){
    char MangaWarehouse[] = "MangaWarehouse.csv";
    char SalesReport[] = "SalesReport.csv";

    FILE* WarehouseFile = fopen(MangaWarehouse, "r+");
    if(WarehouseFile == NULL){
        printf("Error opening Warehouse file\n");
        Exit();
    }

    FILE* ReportFile = fopen(SalesReport, "r+");
    if(SalesReport == NULL){
        printf("Error opening Report file\n");
        Exit();
    }

    int Item_count = get_count(WarehouseFile) - 1;//Delete column name
    char ID_List[Item_count][7];
    make_valid_ID_list(WarehouseFile, Item_count, ID_List);

    // int i = 0;
    // while (ID_List[i][0])
    // {
    //     printf("%s\n", ID_List[i]);
    //     i++;
    // }
    
    // printf("%d", valid_ID("J",ID_List));


    // Update_Warehouse(WarehouseFile,ReportFile,"PL0001",2,1);
    Update_Cashier(WarehouseFile, ReportFile, ID_List);
    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);
    // printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(WarehouseFile);
    fclose(ReportFile);
    return 0;
}