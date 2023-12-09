#include "MangaIMS.h"

// ================= UI PAGE =============

//------- UI Part----------------



void Greet()
{

    printf("\033[1mHello! \033[1;32m%s\n\n"white, correctUsername);
}

void Login_Success()
{

    printf(green"   __             _          __                              __       _ _  \n");
    printf("  / /  ___   __ _(_)_ __    / _\\_   _  ___ ___ ___  ___ ___ / _|_   _| | |\n");
    printf(" / /  / _ \\ / _` | | '_ \\   \\ \\| | | |/ __/ __/ _ \\/ __/ __| |_| | | | | |\n");
    printf("/ /__| (_) | (_| | | | | |  _\\ \\ |_| | (_| (_|  __/\\__ \\__ \\  _| |_| | | |\n");
    printf("\\____/\\___/ \\__, |_|_| |_|  \\__/\\__,_|\\___\\___\\___||___/___/_|  \\__,_|_|_|\n");
    printf("            |___/                                                         \n"white);
    printf("\033[0m\n\n");
}

void Login_Failed()
{

    printf("\n\n");
    printf(" \033[1;31m  __             _             ___     _ _          _ \n");
    printf("  / /  ___   __ _(_)_ __       / __\\_ _(_) | ___  __| |\n");
    printf(" / /  / _ \\ / _` | | '_ \\     / _\\/ _` | | |/ _ \\/ _` |\n");
    printf("/ /__| (_) | (_| | | | | |   / / | (_| | | |  __/ (_| |\n");
    printf("\\____/\\___/ \\__, |_|_| |_|   \\/   \\__,_|_|_|\\___|\\__,_|\n");
    printf("            |___/                                     \n");
    printf("\033[0m\n\n");
}

void Operator_menu()
{

    printf("+----------- \033[1mMenu\033[0m -----------+\n");
    printf("|                            |\n");
    printf("|  \033[1;94mChoose Operator:          \033[0m|\n");
    printf("|                            |\n");
    printf("|  \033[1m(1)\033[0m Admin                 |\n");
    printf("|  \033[1m(2)\033[0m Cashier               |\n");
    printf("|  \033[1;31m(Q) Exit\033[0m                  |\n");
    printf("|                            |\n");
    printf("+----------------------------+\n");
    printf("\n");
    printf("\033[1;94mOperator:\033[0m ");
}

void Logo()
{
    printf("\033[0;33m");
    printf(" __  __                         _          _    _                _   "
           "                            /\\   \n");
    printf("|  \\/  |                       ( )        | |  | |              | | "
           "                            /  \\  \n");
    printf("| .  . | __ _ _ __   __ _  __ _|/ ___     | |  | | __ _ _ __ ___| "
           "|__   ___  _   _ ___  ___    /    \\ \n");
    printf("| |\\/| |/ _` | '_ \\ / _` |/ _` | / __|    | |/\\| |/ _` | '__/ _ "
           "\\ '_ \\ / _ \\| | | / __|/ _ \\  /______\\\n");
    printf("| |  | | (_| | | | | (_| | (_| | \\__ \\    \\  /\\  / (_| | | |  "
           "__/ | | | (_) | |_| \\__ \\  __/  |      |\n");
    printf("\\_|  |_/\\__,_|_| |_|\\__, |\\__,_| |___/     \\/  \\/ \\__,_|_|  "
           "\\___|_| |_|\\___/ \\__,_|___/\\___|  |      |\n");
    printf("                     __/ |                                           "
           "                         |______|\n");
    printf("                    |___/                                            "
           "                       \n");
    printf("\033[0m\n\n");
}

void Choices()
{
    printf("\033[0m+--------------------- ");
    printf("\033[1mMenu");
    printf("\033[0m --------------------+\n");
    printf("|                                               |\n");
    printf(
        "|   \033[1;94mChoose Operation:                        \033[0m   |\n");
    printf("|                                               |\n");
    printf("|           (1) Create                          |\n");
    printf("|           (2) Read                            |\n");
    printf("|           (3) Update                          |\n");
    printf("|           (4) Delete                          |\n");
    printf("|           (5) Sell's Report                   |\n");
    printf("|           (6) Hide Notification               |\n");
    printf("|           ");
    printf("\033[1;31m(Q) Back to main menu\033[0m");
    printf("               |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
    printf("\033[1;94m|Operation| :\033[0m ");
}

void DeleteLogo()
{
    printf("\033[1;31m______     _      _       \n");
    printf("|  _  \\   | |    | |      \n");
    printf("| | | |___| | ___| |_ ___ \n");
    printf("| | | / _ \\ |/ _ \\ __/ _ \\ \n");
    printf("| |/ /  __/ |  __/ ||  __/\n");
    printf("|___/ \\___|_|\\___|\\__\\___|\n");

    printf("\033[0m\n\n");
}

void Delete_Menu_UI()
{

    DeleteLogo();
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|   Hello! \033[1;32m%s\033[0m                              |\n",
           correctUsername);
    printf(
        "|   Input ID you want to \033[1;94mDelete\033[0m                 |\n");
    printf("|   \033[1;31m(Q) Back \033[0m                                   |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n\n");
    printf("\033[1;94m Enter ID:\033[0m ");
}

void Delete_Choice_UI(Data *Data_List, int index)
{
    DeleteLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Name: %s   \n", Data_List[index].Name);
    printf("|   Category: %s\n", Data_List[index].Category);
    printf("|   Price: %d\n", Data_List[index].Price);
    printf("|   Amount: %d\n", Data_List[index].Amount);
    printf("|   Note: %s\n", Data_List[index].Note);
    printf("| \n");
    printf("+----------------------------------------------------------+\n\n");

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|  \033[1mConfirm your command\033[0m                         |\n");
    printf("|  \033[1;31m[Y] to Delete\033[0m  \033[1;32m[n] to Cancel\033[0m                 |\n");
    printf("|  \033[1;94m(Q) Back\033[0m                                     |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
}

void Delete_Y_UI(char *ID_Modify)
{
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|   Item \033[1;32m%s\033[0m has been \033[1;94mDeleted\033[0m                |\n", ID_Modify);
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
}

void Delete_n_UI()
{
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|         \033[1;94mDelete iteam was canceled\033[0m             |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
}

void UpdateLogo()
{
    printf("\033[0;94m");
    printf(" _   _           _       _       \n");
    printf("| | | |         | |     | |      \n");
    printf("| | | |_ __   __| | __ _| |_ ___ \n");
    printf("| | | | '_ \\ / _` |/ _` | __/ _ \\\n");
    printf("| |_| | |_) | (_| | (_| | ||  __/\n");
    printf(" \\___/| .__/ \\__,_|\\__,_|\\__\\___|\n");
    printf("      | |                         \n");
    printf("      |_|                         \n");
    printf("\033[0m\n\n");
}

void Update_Menu_UI()
{

    UpdateLogo();

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|   Hello! \033[1;32m%s\033[0m                              |\n",
           correctUsername);
    printf(
        "|   Input ID you want to \033[1;94mUpdate\033[0m                 |\n");
    printf(
        "|   \033[1;31m(Q) Back \033[0m                                   |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n\n");
    printf("\033[1;94m Enter ID:\033[0m ");
}

void Update_Choices_UI(Data *Data_List, int index)
{

    UpdateLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Name: \033[1;32m%s\033[0m   \n", Data_List[index].Name);
    printf("|   Category: \033[1;32m%s\033[0m\n", Data_List[index].Category);
    printf("|   Price: \033[1;32m%d\033[0m\n", Data_List[index].Price);
    printf("|   Amount: \033[1;32m%d\033[0m\n", Data_List[index].Amount);
    printf("|   Note: \033[1;31m%s\033[0m\n", Data_List[index].Note);
    printf("| \n");
    printf("+----------------------------------------------------------+\n\n");

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|   \033[1;94mChoose Option:\033[0m                              |\n");
    printf("|                                               |\n");
    printf("|           (1) Update Name                     |\n");
    printf("|           (2) Update Category                 |\n");
    printf("|           (3) Update Price                    |\n");
    printf("|           (4) Update Amount                   |\n");
    printf("|           ");
    printf("\033[1;31m(Q) Back to main menu\033[0m");
    printf("               |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
    printf("\033[1;94m|Option| :\033[0m ");
}



void UpdateName_UI(Data *Data_List, int index)
{
    UpdateLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Name:\033[1;33m %s \033[0m  \n", Data_List[index].Name);
    printf("|   ");
    printf("\033[1;31m(Q) Back\033[0m\n");
    printf("| \n");
    printf("+----------------------------------------------------------+\n");

    printf("\033[0;94m|| Rename to ||:\033[0m \033[1;32m");
}



void UpdateCategory_UI(Data *Data_List, int index){

    UpdateLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Category:\033[1;33m %s \033[0m  \n", Data_List[index].Category);
    printf("|   ");
    printf("\033[1;31m(Q) Back\033[0m\n");
    printf("| \n");
    printf("+----------------------------------------------------------+\n\n");

     printf("+--------------------+\n");
    printf("| \033[0;94mAvailable Category\033[0m |\n");
    printf("+--------------------+\n\n");

    printf("+--------------------+\n");
    printf("|       \033[1;31mAction\033[0m       |\n");
    printf("|       \033[0;36mFantasy\033[0m      |\n");
    printf("|       \033[0;33mComedy\033[0m       |\n");
    printf("|       \033[1;35mRomance\033[0m      |\n");
    printf("|       \033[1;32mSports\033[0m       |\n");
    printf("+--------------------+\n\n");

    printf("\033[0;94m|| New Category ||:\033[0m \033[1;32m");

}



void UpdatePrice_UI(Data *Data_List, int index)
{
    UpdateLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Price\033[1;33m %d \033[0m  \n", Data_List[index].Price);
    printf("|   ");
    printf("\033[1;31m(Q) Back\033[0m\n");
    printf("| \n");
    printf("+----------------------------------------------------------+\n");
    printf("\n\n");

    printf("\033[0;94m|| New Price ||:\033[0m \033[1;32m");
}


void UpdateAmount_UI(Data *Data_List, int index)
{
    UpdateLogo();
    printf("+----------------------------------------------------------+\n");
    printf("| \n");
    printf("|   ID: \033[1;32m%s\033[0m    \n", Data_List[index].ID);
    printf("|   Amount:\033[1;33m %d \033[0m  \n", Data_List[index].Amount);
    printf("|   ");
    printf("\033[1;31m(Q) Back\033[0m\n");
    printf("| \n");
    printf("+----------------------------------------------------------+\n");
    printf("\n\n");

    printf("\033[0;94m|| New Amount ||:\033[0m \033[1;32m");
}


void Cashier_Logo(){

    printf("\x1b[36m   ___          _     _           \n");
    printf("  / __\\__ _ ___| |__ (_) ___ _ __ \n");
    printf(" / /  / _` / __| '_ \\| |/ _ \\ '__|\n");
    printf("/ /__| (_| \\__ \\ | | | |  __/ |   \n");
    printf("\\____/\\__,_|___/_| |_|_|\\___|_|   \n");
    printf("\033[0m\n\n");
}

void Cashier_UI(){
        Cashier_Logo();
        
        printf("+-----------------------------------------------+\n");
        printf("|                                               |\n");
        printf("|   Hello, \033[1;35mCashier\033[0m                              |\n");
        printf("|                                               |\n");
        printf("|   \033[1;94mChoose your option:\033[0m                         |\n");
        printf("|                                               |\n");
        printf("|        (1) Sell Item                          |\n");
        printf("|        \033[1;31m(Q) Return to Operator menu\033[0m            |\n");
        printf("|                                               |\n");
        printf("+-----------------------------------------------+\n\n");

        printf("\033[1;94m|| Option ||: \033[0m ");
    }
void cart_ui(){

}


void Selling_phase1(){

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|    How many book IDs to sell:\033[1;94m(AMOUNT)\033[0m         |\n");
    printf("|    \033[1;31m(Q)Back to Cashier menu\033[0m                    |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| AMOUNT ||: \033[0m ");
}


void Selling_phase2(int i){

    printf("++\n");
    printf("||                                               \n");
    printf("||  \033[1;33m%d\033[0m's ID to sell:\033[1;94m(ID)\033[0m                        \n",i + 1);
    printf("||  \033[1;31m(Q)Back to Cashier menu\033[0m                    \n");
    printf("||                                               \n");
    printf("++\n");
    printf("\n");

    printf("\033[1;94m|| ID ||: \033[0m ");

 
    
}

void Selling_phase3(Data *Data_List,int index){
    
    printf("++\n");
    printf("||                                               \n");
    printf("||  Input Amount of Book \"\033[1;33m%s\033[0m\" to sell: \033[1;94m(AMOUNT)\033[0m \n", Data_List[index].Name);
    printf("||  Total Left (\033[1;94m%d\033[0m) \n",Data_List[index].Amount);
    printf("||  \033[1;31m(Q)Back to Cashier menu\033[0m                    \n");
    printf("||                                               \n");
    printf("++\n");
    printf("\n");

    printf("\033[1;94m|| AMOUNT ||: \033[0m ");
}

// sale report

void Sale_report_Logo(){
    printf(yellow"______                      _   \n");
    printf("| ___ \\                    | |  \n");
    printf("| |_/ /___ _ __   ___  _ __| |_ \n");
    printf("|    // _ \\ '_ \\ / _ \\| '__| __|\n");
    printf("| |\\ \\  __/ |_) | (_) | |  | |_ \n");
    printf("\\_| \\_\\___| .__/ \\___/|_|   \\__|\n");
    printf("          | |                   \n");
    printf("          |_|                   \n"white);
    printf("\n");
}


void Sale_report_Menu_UI(){

        printf("+-----------------------------------------------+\n");
        printf("|                                               |\n");
        printf("|   Hello, \033[1;35mCashier\033[0m                              |\n");
        printf("|                                               |\n");
        printf("|   \033[1;94mChoose your option:\033[0m                         |\n");
        printf("|                                               |\n");
        printf("|        (1) All Record                         |\n");
        printf("|        (2) Daily Report                       |\n");
        printf("|        (3) Monthly Report                     |\n");
        printf("|        \033[1;31m(Q) Return to Operator menu\033[0m            |\n");
        printf("|                                               |\n");
        printf("+-----------------------------------------------+\n\n");

        printf("\033[1;94m|| Option ||: \033[0m ");

}

void Report_info(){
    printf("\033[1mDATE%*c",11,' ');
    printf("\033[1mTIME%*c", 11, ' ');
    printf("\033[1mID%*c", 8, ' ');
    printf("\033[1mNAME%*c", 46, ' ');
    printf("\033[1mPRICE%*c",5, ' ');
    printf("\033[1mAMOUNT%*c", 4, ' ');
    printf("\033[1mTOTAl\n\n");
}

void Dailyui(){
    

    printf("+-------------------------------+\n");
    printf("|                               |\n");
    printf("|  Input Date: \033[1;94m( DD MM YYYY )\033[0m   |\n");
    printf("|                               |\n");
    printf("+-------------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| DATE ||: \033[0m ");
}

void Monthlyui(){
    

    printf("+-----------------------------+\n");
    printf("|                             |\n");
    printf("|  Input Date: \033[1;94m( MM YYYY )\033[0m    |\n");
    printf("|                             |\n");
    printf("+-----------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| DATE ||: \033[0m ");
}

//------------------create
void Create_Logo(){

    printf("\x1b[36m _____                _       \n");
    printf("/  __ \\              | |      \n");
    printf("| /  \\/_ __ ___  __ _| |_ ___ \n");
    printf("| |   | '__/ _ \\/ _` | __/ _ \\ \n");
    printf("| \\__/\\ | |  __/ (_| | ||  __/\n");
    printf(" \\____/_|  \\___|\\__,_|\\__\\___|\n\033[0m");
    printf("\n");
    printf("\n");

}

void Create_ID_UI(){

    Create_Logo();

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|    Enter Book ID: \033[1;94m[EX0001]\033[0m                    |\n");
    printf("|    \033[1;31m(Q)Back to Mainmenu\033[0m                        |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| ID ||: \033[0m ");
    
}

void Create_Name_UI(){
    Create_Logo();
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|    Enter Book Name: \033[1;94m[Name]\033[0m                    |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| Name ||: \033[0m ");
    
}

void Create_Category_UI(){

    Create_Logo();

     printf("+--------------------+\n");
    printf("| \033[0;94mAvailable Category\033[0m |\n");
    printf("+--------------------+\n\n");

    printf("+--------------------+\n");
    printf("|       \033[1;31mAction\033[0m       |\n");
    printf("|       \033[0;36mFantasy\033[0m      |\n");
    printf("|       \033[0;33mComedy\033[0m       |\n");
    printf("|       \033[1;35mRomance\033[0m      |\n");
    printf("|       \033[1;32mSports\033[0m       |\n");
    printf("+--------------------+\n\n");

    printf("\033[1;94m|| Category ||: \033[0m ");

}

void Create_Price_UI(){

    Create_Logo();

    printf("  $$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
    printf(" $$                        $$\n");
    printf("$$   Enter Price: \033[1;94m[PRICE]\033[0m   $$\n");
    printf(" $$                        $$\n");
    printf("  $$$$$$$$$$$$$$$$$$$$$$$$$$ \n");

    printf("\n\n");

    printf("\033[0;94m|| Enter Price ||:\033[0m ");
    
}

void Create_Amount_UI(){

    Create_Logo();
    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|        Enter Amount of Book: \033[1;94m[Amount]\033[0m         |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");

    printf("\033[1;94m|| Amount ||: \033[0m ");
    
}

void Create_Success(){

   
    printf("+-----------------------------+\n");
    printf("|                             |\n");
    printf("|      \033[1;32mNew Book Added!!!\033[0m      |\n");
    printf("|                             |\n");
    printf("+-----------------------------+\n");
    printf("\n\n");

}

// Read

void Read_Logo(){

  printf("\x1b[32m _____               _ \n");
  printf("| ___ \\             | |\n");
  printf("| |_/ /___  __ _  __| |\n");
  printf("|    // _ \\/ _` |/ _` |\n");
  printf("| |\\ \\  __/ (_| | (_| |\n");
  printf("\\_| \\_\\___|\\__,_|\\__,_|\x1b[0m\n");
  printf("\n");
  printf("\n");

}

void Read_menu(){

    Read_Logo();

    printf("+-----------------------------------------------+\n");
    printf("|                                               |\n");
    printf("|   \033[1;94mChoose Option:\033[0m                              |\n");
    printf("|                                               |\n");
    printf("|           (1) Read by ID                      |\n");
    printf("|           (2) Read by Category                |\n");
    printf("|           (3) Read by Price                   |\n");
    printf("|           (4) Read All                        |\n");
    printf("|           ");
    printf("\033[1;31m(Q) Back to Admin menu\033[0m");
    printf("              |\n");
    printf("|                                               |\n");
    printf("+-----------------------------------------------+\n");
    printf("\n");
    printf("\033[1;94m|Option| :\033[0m ");

}

void Read_Price_UI(){

    Read_Logo();

printf("+----------------------------+\n");
        printf("|                            |\n");
        printf("|  \033[1;94mChoose Option:            \033[0m|\n");
        printf("|                            |\n");
        printf("|  \033[1m(1)\033[0m Ascending             |\n");
        printf("|  \033[1m(2)\033[0m Decending             |\n");
        printf("|  \033[1;31m(Q) Exit\033[0m                  |\n");
        
        printf("|                            |\n");
        printf("+----------------------------+\n");
        printf("\n");
        printf("\033[1;94mOperator:\033[0m ");

}

void Read_Cat_UI(){

    Read_Logo();

    printf("+--------------------+\n");
    printf("| \033[0;94mAvailable Category\033[0m |\n");
    printf("+--------------------+\n\n");

    printf("+--------------------+\n");
    printf("|       \033[1;31mAction\033[0m       |\n");
    printf("|       \033[0;36mFantasy\033[0m      |\n");
    printf("|       \033[0;33mComedy\033[0m       |\n");
    printf("|       \033[1;35mRomance\033[0m      |\n");
    printf("|       \033[1;32mSports\033[0m       |\n");
    printf("+--------------------+\n\n");

    printf("\033[1;31m(Q) Exit\033[0m\n\n");

    printf("\033[1;94m||Category|| :\033[0m ");


}

void Read_ID_UI(){

    Read_Logo();

        printf("+-----------------------------------------------+\n");
        printf("|                                               |\n");
        printf("|       Enter the ID of Book to read \033[1;94m(ID)\033[0m       |\n");
        printf("|       \033[1;31m(Q) Return to Operator menu\033[0m             |\n");
        printf("|                                               |\n");
        printf("+-----------------------------------------------+\n\n");

        printf("\033[1;94m|| ID || :\033[0m ");
    
}

void Read_As_min_UI(){
 

        printf("+-----------------------------------------------+\n");
        printf("|                                               |\n");
        printf("|       Enter the \033[1;33mMinimum\033[0m price \033[1;94m(PRICE)\033[0m         |\n");
        printf("|       \033[1;31m(Q) Return to Read by price menu\033[0m        |\n");
        printf("|                                               |\n");       
        printf("+-----------------------------------------------+\n\n");

        printf("\033[1;94m|| Minimum || :\033[0m ");
    
}

void Read_As_max_UI(){

        printf("\n");
        printf("+-----------------------------------------------+\n");
        printf("|                                               |\n");
        printf("|       Enter the \033[1;33mMaximum\033[0m price \033[1;94m(PRICE)\033[0m         |\n");
        printf("|       \033[1;31m(Q) Return to Read by price menu\033[0m        |\n");
        printf("|                                               |\n");       
        printf("+-----------------------------------------------+\n\n");

        printf("\033[1;94m|| Maximum || :\033[0m ");
    
}
