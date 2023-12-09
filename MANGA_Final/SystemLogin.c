#include "MangaIMS.h"

// <============ System Login Part ============>
void Admin_Login(Data *Data_List, int *Item_Count)
{
    char username[50];
    char password[50];
    int i = 0;

    // Get username and password from the user
    Logo();
    printf("\033[1;94mEnter Username:\033[0m ");
    scanf("%s", username);
    printf("\033[1;94mEnter password:\033[0m ");

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
        Login_Success();
        pressEnterToContinue();
        Admin_Menu(Data_List, Item_Count);
    }
    else
    {
        system("cls");
        Login_Failed();
        pressEnterToContinue();
    }
}

void Admin_Menu(Data *Data_List, int *Item_Count){
    char choice[10];
    int noti = 1;
    do
        {
            Logo();
            Greet();
            if(noti == 1)
                Print_Alert(Data_List, Item_Count);

            

            Choices();

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
                    printf(blue"Notification Hided (");
                    printf("\033[1;31m%d\033[0m", Check_Alert(Data_List,Item_Count));
                    printf(blue")\n");
                }else
                    noti = 1;
            }else{
                system("cls"); //clear screen before call function
                printf("\n\033[1;31mInvalid choice. Please enter a valid option.\033[0m\n"); // error input text       
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
        Logo();
        Operator_menu();
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
            printf("\n\033[1;31mInvalid choice. Please enter a valid option.\033[0m\n");
            break;
        }
    } 
    while (atoi(choice) > 2 || isPureNumber(choice) == 0);
    Login_Menu(Data_List, Item_Count);
}
 