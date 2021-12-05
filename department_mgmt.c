#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void login(void);
void registration(void);
void menu();
void insert();
void display();
void search();
void erase();
void update();
void sort();
void bill();
void totalbill(int[], int[], int);

typedef struct ITEMS
{
    int product_code;
    char product_name[20];
    float rate;
    int quantity;
    float weight;
    char description[50];

} item;
item *items;
struct login
{
    char fname[30];
    char lname[30];
    char username[30];
    char password[20];
};

int main(void)
{
    int option;

    printf("Press '1' to Register\nPress '2' to Login\n\n");
    scanf("%d", &option);

    getchar();
    if (option == 1)
    {
        system("CLS");
        registration();
    }

    else if (option == 2)
    {
        system("CLS");
        login();
    }
}
int i;
void login(void)

{
    char username[30], password[20], ch;
    FILE *log;
    log = fopen("login.txt", "r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(3);
    }
    struct login l;
username:
    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:");
    fflush(stdin);
    gets(username);
    printf("\nPassword: ");
    while ((ch = getch()) != 13)
    {
        password[i] = ch;
        i++;
        printf("*");
    }

    password[i] = '\0';
    printf("\n");
    while (fread(&l, sizeof(l), 1, log))
    {
        if ((strcmp(username, l.username) == 0) && (strcmp(password, l.password) == 0))
        {
            printf("***********LOGGED IN************\n\n***********WELCOME TO OUR DEPARTMENTAL STORE********\n");
            menu();
        }
        else
        {
            printf("\nUsername or Password incorrect! Please try again\n");
            goto username;
        }
    }
}
void registration(void)
{
    FILE *log;
    char firstname[15];
    log = fopen("login.txt", "a");
    struct login l;
    printf("\nEnter First Name: ");
    scanf("%s", l.fname);
    fflush(stdin);
    printf("\nEnter Surname: ");
    scanf("%c", l.lname);
    fflush(stdin);
    printf("\nEnter Username: ");
    scanf("%s", l.username);
    printf("\nEnter Password: ");
    scanf("%s", l.password);
    fwrite(&l, sizeof(l), 15, log);
    fclose(log);
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");
    getch();
    getchar();
    system("CLS");
    login();
}
void menu()
{
    int choice;

    printf("\nEnter your choice: \n1.INSERT \n2.DISPLAY \n3.SEARCH \n4.ERASE \n5.sort \n6.UPDATE \n7.BILL \n8.EXIT ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("\nInsert\n");
        insert();
        menu();
        break;
    case 2:
        printf("Display\n");
        display();
        menu();
        break;
    case 3:
        printf("Search\n");
        search();
        break;
    case 4:
        printf("Erase\n");
        erase();
        break;

    case 5:
        printf("sort\n");
        sort();
        break;

    case 6:
        printf("Update\n");
        update();
        break;
    case 7:
        printf("Bill\n");
        bill();
        break;

    case 8:
        printf("Exit\n");
        break;

    default:
        printf("\nEnter valid choice:");
        menu();
        break;
    }
}
void insert()
{
    FILE *fp;
    fp = fopen("record.txt", "a");
    item a;
    printf("\nEnter product code: ");
    scanf("%d", &a.product_code);
    printf("\nEnter product_name: ");
    scanf(" %[^\n]s", a.product_name);
    printf("\nEnter rate: ");
    scanf(" %f", &a.rate);
    printf("\nEnter weight(in gm): ");
    scanf(" %f", &a.weight);
    printf("\nEnter quantity: ");
    scanf(" %d", &a.quantity);

    printf("\nEnter description: ");
    scanf(" %[^\n]s", a.description);
    printf("product_code= %d \nproduct_name= %s \nrate= %.2f \nweight(in gm)= %.2f \nquantity= %d \ndescripition= %s\n", a.product_code, a.product_name, a.rate, a.weight, a.quantity, a.description);
    fwrite(&a, sizeof(a), 1, fp);
    printf("!!!!RECORD INSERTED SUCCESSFULLY!!!!!\n");
    fclose(fp);
}
void display()
{
    item a;
    FILE *fp;

    fp = fopen("record.txt", "r");
    printf("\n******ITEM DETAILS ARE AS FOLLOW****\n");
    printf("product_code\tproduct_name\t\trate\t\tweight(in gm)\t\tquantity\t\tdescripition\n");
    while (fread(&a, sizeof(a), 1, fp) == 1)
    {

        printf("%-15d %-23s %-15.2f %-25.2f %-21d %s\n", a.product_code, a.product_name, a.rate, a.weight, a.quantity, a.description);
    }
    fclose(fp);
}
void search()
{
    FILE *fp;
    item a;
    int code;
    int count = 0;
    fp = fopen("record.txt", "rb");
    printf("\nEnter the code of an item to be search: ");
    scanf("%d", &code);
    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.product_code == code)
        {
            count = 1;
            printf("\nRECORD FOUND\n");
            printf("product_code\tproduct_name\t\trate\t\tquantity\tweight(in kg)\t\tdescripition\n");
            printf("%d %20s %20.2f %20d %20d %20s\n", a.product_code, a.product_name, a.rate, a.weight, a.quantity, a.description);
        }
    }
    if (count == 0)

        printf("\nNOT FOUND\n");

    fclose(fp);
    menu();
}

void erase()
{
    int code;
    int count = 0;
    item a;
    FILE *fp, *ft;
    fp = fopen("record.txt", "rb");
    printf("\nPreviously stored data:\n");
    display();
    printf("\nEnter the product code to delete: ");
    scanf(" %d", &code);
    ft = fopen("temp.txt", "ab");

    while (fread(&a, sizeof(a), 1, fp))
    {
        
        if (code == a.product_code)
        {

            printf("\nRECORD SUCCESSFULLY DELETED\n");
        }
        else
        {
            fwrite(&a, sizeof(a), 1, ft);
            count = 1;
        }
    }
    if (count == 0)
    {
        printf("\nNO SUCH RECORD FOUND!!!\n");
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    printf("\nUpdated record after deleting!\n");
    display();
    menu();
}
void update()
{
    FILE *fp, *fp1;
    item a, b;
    int code;

    fp = fopen("record.txt", "rb");
    fp1 = fopen("temp.txt", "ab");
    printf("enter the code to update");
    scanf("%d", &code);

    while (fread(&b, sizeof(b), 1, fp))
    {
        if (b.product_code == code)
        {
            printf("\nENTER THE NEW RECORD\n");
            printf("\n new item code:");
            scanf(" %d", &a.product_code);
            printf("\nnew item name:");
            scanf(" %s", &a.product_name);
            printf("new rate: ");
            scanf(" %f", &a.rate);
            printf("\nnew weight: ");
            scanf(" %f", &a.weight);
            printf("\nnew quantity: ");
            scanf(" %d", &a.quantity);

            printf("\nnew description: ");
            scanf(" %[^\n]s", a.description);

            fwrite(&a, sizeof(a), 1, fp1);
        }
        else
        {
            fwrite(&b, sizeof(b), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("record.txt");
    rename("temp.txt", "record.txt");

    printf("RECORD UPDATED SUCCESSFULLY ...!!please check display function\n ");
    menu();
}

void sort()
{
    int c = 0, i, j;
    item a, s[50], t;

    FILE *fp;
    fp = fopen("record.txt", "r");
    while (fread(&a, sizeof(a), 1, fp))
    {
        s[c] = a;
        c++;
    }
    fclose(fp);
    for (i = 0; i < c - 1; i++)
    {
        for (j = i + 1; j < c; j++)
        {
            if (s[i].product_code > s[j].product_code)
            {
                t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
        }
    }
    remove("record.txt");
    fp = fopen("record.txt", "ab");

    for (i = 0; i < c; i++)
    {

        fwrite(&s[i], sizeof(s[i]), 1, fp);
    }
    fclose(fp);
    printf("records sorted successfully use display option to view\n");

    system("pause");
    menu();
}
void bill()
{
    item a;
    int purchase_pcode[20], purchase_pqty[20];
    int count = 0, i;
    char response;
    while (1)
    {
        printf("purchase product_code: ");
        scanf("%d", &purchase_pcode[count]);
        printf("purchase product_quantity: ");
        scanf("%d", &purchase_pqty[count]);
        printf("are more product purchased(Y/N): ");
        scanf(" %c", &response);
        count++;
        if (response == 'N' || response == 'n')
        {
            break;
        }
    }
    FILE *fp, *ft;
    fp = fopen("record.txt", "rb");
    ft = fopen("temp.txt", "ab");
    while (fread(&a, sizeof(a), 1, fp))
    {

        for (i = 0; i < count; i++)
        {

            if (a.product_code == purchase_pcode[i] && a.quantity > 0)
            {
                a.quantity -= purchase_pqty[i];
                break;
            }
            else if ((a.product_code == purchase_pcode[i] && a.quantity == 0))
            {
                printf("out of stock");
            }
        }
        fwrite(&a, sizeof(a), 1, ft);
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    system("pause");
    totalbill(purchase_pcode, purchase_pqty, count);
}
void totalbill(int prod_id[], int prod_qty[], int count)
{
    int i;
    float total = 0.0;
    system("cls");
    FILE *fp;
    item a;
    printf("***************************");
    printf("\n------xyz store-------\n");
    printf("---------------------------");
    printf("\nname\tQTY\trate");
    fp = fopen("record.txt", "rb");
    while (fread(&a, sizeof(a), 1, fp))
    {
        for (i = 0; i < count; i++)
        {
            if (prod_id[i] == a.product_code)
            {
                total += a.rate * prod_qty[i];
                printf("\n%s\t%d\trs. %.2f", a.product_name, prod_qty[i], a.rate);
                break;
            }
        }
    }
    printf("\n---------------------------");
    printf("\n\t\ttotal= %.2f\n", total);
    printf("\n\t***please visit again***\n");
    fclose(fp);
    system("pause");
    menu();
}
