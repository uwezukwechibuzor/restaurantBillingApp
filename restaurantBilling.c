#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
    /* data */
    char item[20];
    float price;
    int qty;
};

struct orders
{
    /* data */
    char customers[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};


//functions to generate bills
void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t   ADV. Restuarant");
    printf("\n\t    ------------------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("-----------------------------------------------------------------\n");
    printf("Itens\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price){
   printf("%s\t\t", item);
         printf("%d\t\t", qty);
         printf("%.2f\t\t", qty * price);
         printf("\n");
}


void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst=0.09*netTotal, grandTotal=netTotal+2*cgst;
    printf("------------------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t---------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------------------------\n");
}

int main(){

   //float total;   
   int opt, n;
   struct orders ord;
   struct orders order;
   char saveBill = 'y', continueFlag = 'y';
   char name[50];
   FILE *fp;

   //dashboard
   while (continueFlag == 'y')
   {
    /* code */
    system("clear");
    float total = 0;
    int invoiceFound = 0;
   printf("\t=============ADV. RESTAURANT=============");
   printf("\n\nPlease Select Your Prefered Operation");
   printf("\n1.Generate Invoice");
   printf("\n2.Show all Invoice");
   printf("\n3.Search Invoice");
   printf("\n4.Exit");
   
   printf("\n\nYour Choice:\t");
   scanf("%d", &opt);
   fgetc(stdin);

   switch(opt){
       case 1:
       system("clear");
       printf("\nPlease Enter the name of the customer:\t");
       fgets(ord.customers, 50, stdin);
       ord.customers[strlen(ord.customers)-1] = 0;
       strcpy(ord.date, __DATE__);
       printf("\nPlease Enter The Number Of Items:\t");
       scanf("%d", &n);
       ord.numOfItems = n;
       for(int i=0; i<n; i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please Enter The Item %d:\t", i+1);
            fgets(ord.itm[i].item, 20, stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
            printf("Please Enter The Quantity:\t");
            scanf("%d", &ord.itm[i].qty);
            printf("Please Enter The Unit Price:\t");
            scanf("%f", &ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
       }
       
       generateBillHeader(ord.customers, ord.date);
       for(int i=0; i<ord.numOfItems; i++){
           generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
       }
       generateBillFooter(total);

       printf("\nDo You Want to Save the Invoice?[y/n]:\t");
       scanf("%s", &saveBill);
       if(saveBill == 'y'){
           fp = fopen("RestaurantBill.pdf", "a+");
           fwrite(&ord, sizeof(struct orders), 1, fp);
           if(fwrite != 0)
           printf("\nSuccessfully Saved");
           else
           printf("\nError Saving");
           fclose(fp);
       }
       break;
       
       case 2:
       system("clear");
       fp = fopen("RestaurantBill.pdf", "r");
       printf("\n ********Your Previous Invoices*******\n");
       while (fread(&order, sizeof(struct orders), 1, fp))
       {
        /* code */
          float totalBillSaved = 0;
          generateBillHeader(order.customers, order.date);
          for(int i=0; i<order.numOfItems; i++){
              generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
              totalBillSaved += order.itm[i].qty * order.itm[i].price;
          }
          generateBillFooter(totalBillSaved);
       }
       fclose(fp);
       break;
       
      case 3:
       printf("\nEnter the name of the customer:\t");
       //fgetc(stdin);
       fgets(name, 50, stdin);
       name[strlen(name)-1] = 0;
       system("clear");
       fp = fopen("RestaurantBill.pdf", "r");
       printf("\t ********Invoice Of %s*******", name);
       while (fread(&order, sizeof(struct orders), 1, fp))
       {
        /* code */
          float totalBillSaved = 0;
          if(!strcmp(order.customers,name)){
            generateBillHeader(order.customers, order.date);
             for(int i=0; i<order.numOfItems; i++){
                generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                totalBillSaved += order.itm[i].qty * order.itm[i].price;
             }
            generateBillFooter(totalBillSaved);
            invoiceFound = 1;
          }
       
       }
       if(!invoiceFound){
          printf("Sorry the invoice for %s doesnot exist", name);
       }
       fclose(fp);
       break;
       
       case 4:
       printf("\n\t\t Bye Bye :)\n\n");
       exit(0);
       break;
       

       default:
       printf("Sorry Invalid Option");
       break;

   }


   printf("\nDo You want to perform another Operation?[y/n]:\t");
   scanf("%s", &continueFlag);
   }

   printf("\n\t\t Bye Bye :)\n\n");
   printf("\n\n");

   return 0;

}