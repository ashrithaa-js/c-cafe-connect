#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct
{
    char i_name[20];
    int i_number;
    float i_quantity;
}item_ingredient;

typedef struct
{
    int item_number,no_of_ingredients;
    char item_name[20];
    item_ingredient i[20];
    float item_cost;
    int sales;
}item;

typedef struct
{
    int ingredient_number;
    char ingredient_name[20];
    float ingredient_quantity;
    float ingredient_rate;
}ingredient;

typedef struct
{
        char name[20];
        int number,item_number;
        float rate,subtotal;
}bill;

int get_total_ingredients(){
        ingredient t;
        int a;
        FILE*p;
        p = fopen("ingredient.txt","r");
        if(p==NULL)
        {
                return 0;
        }
        while(fread(&t,sizeof(t),1,p)==1){
                a = t.ingredient_number;
        }
        fclose(p);
        return a;
}
int get_total_items(){
        item t;
        int a;
        FILE *p;
        p = fopen("items.txt","r");
        if(p==NULL)
        {
                return 0;
        }
        while(fread(&t,sizeof(t),1,p)==1){
                a = t.item_number;
        }
        fclose(p);
        return a;
}

void print_item(item t,int no_item_ingredients)
{
        int k;
         printf("  %-12d   %-13s %-11.2f",t.item_number,t.item_name,t.item_cost);
                for(k=0;k<no_item_ingredients;k++)
                {
                         printf(" %-11s                 %-18.2f\n                                           ",t.i[k].i_name,t.i[k].i_quantity);
                }
        printf("\n");
}

item get_item(int number,ingredient *ig1,int total_ig)
{
        int a,n,j,choice;
        char ch[20];
        item t;
        t.sales=0;
        t.item_number=number;
        printf("\nItem Number : %d\n",t.item_number);
        printf("Enter Item Name :");
        scanf(" %[^\n]%*c",t.item_name);
        printf("Enter cost of 1 %s : Rs.",t.item_name);
        scanf("%f",&t.item_cost);
        printf("Enter no. of ingredients required to make %s : ",t.item_name);
        scanf("%d",&t.no_of_ingredients);
        for(a=0;a<t.no_of_ingredients;a++)
        {
        L3:printf("\nEnter ingredient %d name :",a+1);
        scanf(" %[^\n]%*c",ch);
        for(j=0;j<total_ig;j++)
        {
                if(strcmp(ch,ig1[j].ingredient_name)==0)
                {
                        strcpy(t.i[a].i_name,ch);
                        t.i[a].i_number=ig1[j].ingredient_number;
                          break;
                }
        }
        if(j==total_ig)
        {
                printf("\nIngredient not available\n");
                goto L3;
        }
        printf("Enter quantity (in kg/litre) of %s required for 1 cup of %s : ",t.i[a].i_name,t.item_name);
        scanf("%f",&t.i[a].i_quantity);
        }
        return t;
}

ingredient get_ingredient(int number)
{
    ingredient t;
    t.ingredient_number=number;
    printf("\nIngredient Number:%d\n",t.ingredient_number);
    printf("Enter ingredient name:");
    scanf(" %[^\n]%*c",t.ingredient_name);
    printf("Enter ingredient quantity (in kg/litre):");
    scanf("%f",&t.ingredient_quantity);
    printf("Enter rate (per kg /per litre) of %s:",t.ingredient_name);
    scanf("%f",&t.ingredient_rate);
    return t;
}

void print_ingredients(ingredient *t,int num)
{
        int p;
         printf("NUMBER      NAME              QUANTITY      RATE\n");
        for(p=0;p<num;p++)
        {
                printf("%-12d %-15s %-11.2f %-10.2f\n",t[p].ingredient_number,t[p].ingredient_name,t[p].ingredient_quantity,t[p].ingredient_rate);
        }
}

float print_bill(bill *t,int num)
{
        int p;
        float result=0;
        printf("\nBILL\nITEM NAME\tRATE\tQUANTITY\tAMOUNT\n");
        for(p=0;p<num;p++)
        {

                if(t[p].number!=0)
                {
                        printf("%s\t\t%.2f\t\t%d\t\t%.2f\n",t[p].name,t[p].rate,t[p].number,t[p].subtotal);
                        result+=t[p].subtotal;
                }
                 }
        printf("TOTAL AMOUNT : Rs.%f\n",result);
        return result;
}

float refill_ingredients(float existing_quantity,char *refill_ingredient_name)
{
        float add_quantity;
        printf("Enter quantity (in kg/litre) of %s to be added : ",refill_ingredient_name);
        scanf("%f",&add_quantity);
        existing_quantity+=add_quantity;
        return existing_quantity;
}

int calculate_time()
{
        time_t t;
        int t1,t2,t3;
        time(&t);
        t1=((int)(ctime(&t))[11])-48;
        t2=((int)(ctime(&t))[12])-48;
        t3=t1*10+t2;
        return t3;
}
int main()
{
        int total_ingredients,i;
        float grand_total,ingredient_total;
        ingredient ig[20];
        item dish[20];
        total_ingredients=get_total_ingredients();
        FILE *ptr;
        i=0;
        ptr=fopen("ingredient.txt","r");
        if(ptr!=NULL)
        {
        while(!feof(ptr))
        {
                fread(&ig[i],sizeof(ig[i]),1,ptr);
                i++;
        }
        }
        fclose(ptr);
        int total_items;
        total_items=get_total_items();
        i=0;
        ptr=fopen("items.txt","r");
        if(ptr!=NULL)
        {
        while(!feof(ptr))
        {
            fread(&dish[i],sizeof(dish[i]),1,ptr);
                       i++;
        }
        }
        fclose(ptr);
        ptr=fopen("sales.txt","r");
        if(ptr!=NULL)
        {
                fread(&grand_total,sizeof(grand_total),1,ptr);
                fread(&ingredient_total,sizeof(ingredient_total),1,ptr);
        }
        else
        {
                grand_total=0;
                ingredient_total=0;
        }
        int temp,temp1,no_of_cups,c1,c2,c3,add_items,j,k,add_ingredients;
        float bill_total=0;
        char refill_ingredient_name[20];
        char repeat;
        bill dishes[5];
        char reduce,ensure,back;
        system("clear");
        printf("WELCOME TO OUR CAFE");
        L1:printf("\n\nWho is the user???\n1.Admin\n2.Customer\n3.Close Machine\nEnter choice:");
        scanf("%d",&c1);
        system("clear");
        switch(c1)
        {
                case 1:
                system("clear");
                L2:printf("\nADMIN HOMEPAGE\n1.Add new Ingredients\n2.Add new item\n3.Refill ingredients\n4.Check earnings and sales\n5.Check quantity of ingredients\n6.Check details of existing items\n7.Exit Admin HomePage\nEnter your choice:");
                scanf("%d",&c2);
                switch(c2)
                {
                        case 2:
                                system("clear");
                                if(total_ingredients!=0)
                                {
                                printf("AVAILABLE INGREDIENTS\n");
                                print_ingredients(ig,total_ingredients);
                                printf("\n");
                                printf("Ensure that all the necessary ingredients for the new item are present in the above ingredient list (y/n)???");
                                scanf(" %c",&ensure);
                                if(ensure=='y')
                                {
                                printf("\nEnter number of items you are going to add:");
                                scanf("%d",&add_items);
                                for(i=total_items;i<total_items+add_items;i++)
                                {
                                        dish[i]=get_item(i+1,ig,total_ingredients);
                                         printf("\n");
                                }
                                total_items+=add_items;
                                }
                                else{
                                        system("clear");
                                        goto L2;}
                                }
                                else
                                {
                                        printf("\nNo Ingredients available to initialise an item\nPlease add all required ingredients before initialising an item\n");
                                }
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 1:
                                system("clear");
                                printf("Enter number of ingredients you are going to add:");
                                scanf("%d",&add_ingredients);
                                for(i=total_ingredients;i<total_ingredients+add_ingredients;i++)
                                {
                                        ig[i]=get_ingredient(i+1);
                                        printf("\n");
                                        ingredient_total+=((ig[i].ingredient_rate)*(ig[i].ingredient_quantity));
                                }
                                total_ingredients+=add_ingredients;
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 3:
                                system("clear");
                                if(total_ingredients!=0)
                                {
                                printf("AVAILABLE INGREDIENTS\n");
                                print_ingredients(ig,total_ingredients);
                                printf("\n");
                                printf("Enter the number of ingredients to be refilled:");
                                scanf("%d",&k);
                                for(j=0;j<k;j++)
                                {
                                printf("\n%d. Enter name of ingredient to be refilled:",j+1);
                                scanf(" %[^\n]%*c",refill_ingredient_name);
                                for(i=0;i<total_ingredients;i++)
                                {
                                         if(strcmp(refill_ingredient_name,ig[i].ingredient_name)==0)
                                         {
                                                float initial;
                                                initial=ig[i].ingredient_quantity;
                                                 ig[i].ingredient_quantity=refill_ingredients(ig[i].ingredient_quantity,refill_ingredient_name);
                                         ingredient_total+=((ig[i].ingredient_quantity-initial)*ig[i].ingredient_rate);
                                                 break;
                                         }
                                }
                                if(i==total_ingredients){
                                        printf("\nINGREDIENT NOT AVAILABLE\n");
                                        break;}
                                }
                                }
                                else
                                {
                                        printf("\nNO INGREDIENT AVAILABLE\n");
                                }
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 4:
                                 system("clear");
                                if(total_items!=0)
                                {
                                printf("ITEM\t\tNO. OF CUPS SOLD\n");
                                for(i=0;i<total_items;i++)
                                {
                                    printf(" %-20s %-10d\n",dish[i].item_name,dish[i].sales);
                                }
                                printf("\nTOTAL EARNINGS:%.2f\n",grand_total);
                                }
                                else
                                        printf("\nNO ITEMS AVAILABLE\n");
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 5:
                                 system("clear");
                                if(total_ingredients>0)
                                {
                                        print_ingredients(ig,total_ingredients);
                                        printf("\nTOTAL AMOUNT SPENT ON INGREDIENTS:%.2f\n",ingredient_total);
                                }
                                else
                                        printf("\nNo ingredients available\n");
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 6:
                                 system("clear");
                                if(total_items!=0)
                                {
                                         printf("\nITEM NUMBER\t  NAME\t\tCOST\t   INGREDIENT NAME\t     QUANTITY\n");
                                for(i=0;i<total_items;i++)
                                {
                                        print_item(dish[i],dish[i].no_of_ingredients);
                                }
                                }
                                else
                                        printf("\nNO ITEMS AVAILABLE");
                                printf("\nPress ENTER to return to ADMIN HOME PAGE");
                                scanf("%c%*c",&back);
                                system("clear");
                                goto L2;
                        case 7:
                                system("clear");
                                goto L1;
                        default:
                                printf("\nINVALID CHOICE\n");
                                goto L2;
                }
                break;
                case 2:
                if(calculate_time()<6 || calculate_time()>15)
                {
                        printf("\nCAFE IS CLOSED\nONLY ADMIN ACCESS IS ALLOWED\n");
                        printf("\nPress ENTER to go back");
                        scanf("%c%*c",&back);
                        system("clear");
                        goto L1;
                }
                else if(total_items==0||total_ingredients==0)
                {
                        printf("\nPlease ask the admin to initialise the machine\n");
                        printf("Press ENTER to go back");
                                scanf("%c%*c",&back);
                                system("clear");
                        goto L1;
                }
                else
                {
                for(i=0;i<total_items;i++)
                        dishes[i].number=0;
                do{
                printf("\nMENU\n");
                for(i=0;i<total_items;i++)
                        printf("%d. %-20s Rs.%-10.2f\n",dish[i].item_number,dish[i].item_name,dish[i].item_cost);
                printf("Enter your choice:");
                scanf("%d",&c3);
                printf("Enter number of cups:");
                scanf("%d",&no_of_cups);
                strcpy(dishes[c3-1].name,dish[c3-1].item_name);
                dishes[c3-1].rate=dish[c3-1].item_cost;
                dishes[c3-1].item_number=dish[c3-1].item_number;
                L5:dishes[c3-1].number=no_of_cups;
                for(j=0;j<dish[c3-1].no_of_ingredients;j++)
                {
                        for(k=0;k<total_ingredients;k++)
                        {
                                if(ig[k].ingredient_number==dish[c3-1].i[j].i_number)
                                {
                                        ig[k].ingredient_quantity-=(dish[c3-1].i[j].i_quantity)*no_of_cups;
                                        if(ig[k].ingredient_quantity<0)
                                                {
                                                                dishes[c3-1].number=0;
                                                                for(temp=0;temp<j;temp++)
                                                                {
                                                                        for(temp1=0;temp1<total_ingredients;temp1++)
                                                                        {
                                                                                if(ig[temp1].ingredient_number==dish[c3-1].i[temp].i_number)
                                                                                {
                                                                                        ig[temp1].ingredient_quantity+=((dish[c3-1].i[temp].i_quantity)*no_of_cups);
                                                                                }
                                                                        }
                                                                }
                                                                ig[k].ingredient_quantity+=(dish[c3-1].i[j].i_quantity)*no_of_cups;
                                                                no_of_cups=0;
                                                                printf("%s is insufficient\nPlease Ask the admin to refill\n",ig[k].ingredient_name);
                                                                goto L6;
                                                }
                                }
                        }
                }
                L6:dish[c3-1].sales+=no_of_cups;
                dishes[c3-1].subtotal=dishes[c3-1].rate*dishes[c3-1].number;
                printf("Do you want to order any other item (y/n)???");
                scanf(" %c",&repeat);
                system("clear");
                }while(repeat=='y');
                 for(j=0;j<total_items;j++)
                {
                        if(dishes[j].number!=0)
                        {
                                bill_total=print_bill(dishes,total_items);
                                printf("\nEnjoy your drink!!!!Thank You for opting our CAFE!!!\n");
                                printf("Press ENTER to go back");
                                scanf("%c%*c",&back);
                                system("clear");
                                break;
                        }
                }
                grand_total+=bill_total;
                bill_total=0;
                goto L1;
               }
                case 3:
                i=0;
                ptr=fopen("ingredient.txt","w");
                for(i=0;i<total_ingredients;i++){
                fwrite(&ig[i],sizeof(ig[i]),1,ptr);}
                fclose(ptr);
                ptr=fopen("items.txt","w");
                for(i=0;i<total_items;i++)
                fwrite(&dish[i],sizeof(dish[i]),1,ptr);
                fclose(ptr);
                ptr=fopen("sales.txt","w");
                fwrite(&grand_total,sizeof(grand_total),1,ptr);
                fwrite(&ingredient_total,sizeof(ingredient_total),1,ptr);
                fclose(ptr);
                system("clear");
                if(ingredient_total<grand_total)
                printf("\nYou have gained Rs.%.2f as profit",grand_total-ingredient_total);
                else if(ingredient_total>grand_total)
                printf("\nYou have earned  Rs.%.2f so far....\n",grand_total);
                printf("\nTHANK YOU\n");
                break;

                default:
                        printf("\nINVALID CHOICE\n");
                        goto L1;
        }
    return 0;
}
