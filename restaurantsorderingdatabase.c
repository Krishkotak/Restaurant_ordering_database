#include<stdio.h>
#include<string.h>
#include<math.h>



# define no_of_restaurants 10
# define no_of_fooditems 10
# define no_of_specialitems 10
# define no_of_orders 10
# define avgspeed 667 // speed=40km/hr == 667 meter/min used in calculation of delivery time 


struct Menuitems 
{
    char item_name[50];
    int item_price;
    int quantity; // Taken from user
    int servicetime; // in minutes

};

struct specialitems
{
    char special_item_name[50];
    int special_item_prices;
    int quantity; // Taken from user
    int servicetime; // in minutes

};
struct address{
    char area[50];
    int plot;
    //coordinates
    int x;  // in meters
    int y;  // in meters
};

struct Restaurants
{
  char name[50];
  struct address Address;
  char dayspecial[50];//item of the day name
  int dayspecial_price;
  int dayspecial_time; // in minutes
  struct Menuitems items[no_of_fooditems];//array containing normal menu items
  struct specialitems specialmeal[no_of_specialitems];//array containing special items
  int menusize;
  int specialitemsize;//size of array
};
struct food_ordered // used to maintain live order record
{
    char food_item_ordered[50];
    int quantity_ordered;
    int food_item_price;
   

};


struct userdetails{ //used to maintain live order record
    int orderid;
    char order_time[10];  // enter order time as stated in 24 hr clock
    char username[50];
    char phone_number[10];
    struct address useraddress;
    int delivery_time;
    char restaurant_name[50];
    struct  food_ordered order[no_of_orders];
    int no_of_food_ordered;
     int total_price;
            
};

float distance(int x1,int y1,int x2,int y2){// used to calculate delivery time acc to each location
    int x=((x1-x2)*(x1-x2));
    int y=((y1-y2)*(y1-y2));
    float distance =sqrt(x+y);
    return distance;
}

int delivery_time(int servicetime,float distance,int quantity){
    int del_time;
    int travel_time=distance/avgspeed;
    del_time=servicetime*quantity+travel_time;
    return del_time;
}

void sortlist(char restolist[][50],int n)
{       int flag1=0;
        int flag=0;
        char temp[50];
 
    // Sorting strings using bubble sort
    for (int i = 0; i < n - 1 && flag1==0; i++) {
        flag=0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(restolist[j], restolist[j + 1]) > 0) {
                strcpy(temp, restolist[j]);
                strcpy(restolist[j], restolist[j + 1]);
                strcpy(restolist[j + 1], temp);
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }

    }

}
void sortrestaurants(struct Restaurants restaurants[]){
    struct Restaurants temp;
    int flag1=0;
    int flag=0;
    int cmp;
    for(int i=0;i<no_of_restaurants-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<no_of_restaurants-i-1;j++){
            cmp=strcmp(restaurants[j].name,restaurants[j+1].name);
            if(cmp>0){
                temp=restaurants[j];
                restaurants[j]=restaurants[j+1];
                restaurants[j+1]=temp;
                flag=1;
            }
            else if(cmp==0){
                int cmp1=strcmp(restaurants[j].Address.area,restaurants[j+1].Address.area);
                if(cmp1>0){
                  temp=restaurants[j];
                  restaurants[j]=restaurants[j+1];
                  restaurants[j+1]=temp;
                  flag=1;  
                }
                else if(cmp1==0){
                    if(restaurants[j].Address.plot>restaurants[j+1].Address.plot){
                        temp=restaurants[j];
                        restaurants[j]=restaurants[j+1];
                        restaurants[j+1]=temp;
                        flag=1;
                    }
                }
            }
            
        }
        if(flag==0){
            flag1=1;
        }
    }
}

void binary_search(char name[],struct  Restaurants restaurants[],int index[],int *count){
    int s=0;
    int e=no_of_restaurants-1;
    int mid=s+(e-s)/2;
    int flag=0;
    
    while(s<=e){
        mid=s+(e-s)/2;
        int cmp=strcmp(restaurants[mid].name,name);
        if(cmp==0){
           index[*count]=mid;
           *count=*count+1;
           flag=1;
           if(mid+1<no_of_restaurants && strcmp(restaurants[mid+1].name,name)==0){
            s=mid+1;
           }
           else{
            e=mid-1;
           }
        }
        else if(cmp>0){
            e=mid-1;
        }
        else{
            s=mid+1;
        }
    }
    if(flag==0){
        index[0]=-1;
    }
    
}

 int binary_fooditem_search(struct Menuitems menu[],int n,char food_name[]){
    int s=0;
    int e=n-1;
    int mid;
    int cmp;
    int flag=0;
    int menuindex=-1;
    while(s<=e && flag==0 ){
        mid=s+(e-s)/2;
        cmp=strcmp(menu[mid].item_name,food_name);
        if(cmp==0){
            flag=1;
            menuindex=mid;
        }
        else if(cmp<0){
            s=mid+1;
        }
        else{
            e=mid-1;
        }
        
    }
    return menuindex;
 }

 int binary_specialfooditem_search(struct specialitems menu[],int n,char food_name[]){
    int s=0;
    int e=n-1;
    int mid;
    int cmp;
    int flag=0;
    int menuindex=-1;
    while(s<=e && flag==0 ){
        mid=s+(e-s)/2;
        cmp=strcmp(menu[mid].special_item_name,food_name);
        if(cmp==0){
            flag=1;
            menuindex=mid;
        }
        else if(cmp<0){
            s=mid+1;
        }
        else{
            e=mid-1;
        }
        
    }
    return menuindex;
 }
void sort_item(struct Menuitems menu[],int n){
   struct Menuitems temp;
    int flag1=0;
    int flag=0;
    int cmp;

    for(int i=0;i<n-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<n-i-1;j++){
            cmp=strcmp(menu[j].item_name,menu[j+1].item_name);
            if(cmp>0){
                temp=menu[j+1];
                menu[j+1]=menu[j];
                menu[j]=temp;
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }
    }
    
        

}
void sort_specialitem(struct specialitems menu[],int n){
   struct specialitems temp;
    int flag1=0;
    int flag=0;
    int cmp;
   
    for(int i=0;i<n-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<n-i-1;j++){
            cmp=strcmp(menu[j].special_item_name,menu[j+1].special_item_name);
            if(cmp>0){
                temp=menu[j+1];
                menu[j+1]=menu[j];
                menu[j]=temp;
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }
    }      
}
void sort_dayspecial(struct Restaurants restaurants[],int n)
{
    struct Restaurants temp;
    int flag1=0;
    int flag=0;
    int cmp;
   
    for(int i=0;i<n-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<n-i-1;j++){
            cmp=strcmp(restaurants[j].dayspecial,restaurants[j+1].dayspecial);
            if(cmp>0){
                temp=restaurants[j+1];
                restaurants[j+1]=restaurants[j];
                restaurants[j]=temp;
                flag=1;
            }
            else if(cmp==0){
                // sort on basis of prices 
                if(restaurants[j].dayspecial_price>restaurants[j+1].dayspecial_price){
                   temp=restaurants[j+1];
                   restaurants[j+1]=restaurants[j];
                    restaurants[j]=temp;
                    flag=1; 
                }
            }
        }
        if(flag==0){
            flag1=1;
        }
    }      
}
  
void sort_by_price(struct specialitems menu[],int n){
    struct specialitems temp;
    int flag1=0;
    int flag=0;
    for(int i=0;i<n-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<n-i-1;j++){
           
            if(menu[j].special_item_prices>menu[j+1].special_item_prices){
                temp=menu[j+1];
                menu[j+1]=menu[j];
                menu[j]=temp;
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }
    }   
}
void sort_by_priceitem(struct Menuitems menu[],int n){
    struct Menuitems temp;
    int flag1=0;
    int flag=0;
    for(int i=0;i<n-1 && flag1==0;i++){
        flag=0;
        for(int j=0;j<n-i-1;j++){
           
            if(menu[j].item_price>menu[j+1].item_price){
                temp=menu[j+1];
                menu[j+1]=menu[j];
                menu[j]=temp;
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }
    }  
}
void sort_index(int indexof_restaurants[],int n){
    int flag1=0;
    int flag=1;

    for(int i=0;i<n-1;i++){
        flag=0;
        for(int j=0;j<n;j++){
            if(indexof_restaurants[j]>indexof_restaurants[j+1]){
                int temp=indexof_restaurants[j];
                indexof_restaurants[j]=indexof_restaurants[j+1];
                indexof_restaurants[j+1]=temp;
                flag=1;
            }
        }
        if(flag==0){
            flag1=1;
        }
    }
}

void getItemListInSortedOrder(struct  Restaurants restaurants[]){
    printf("Enter the name of Restaurant\n");
    char restaurant_name[50];
    fflush(stdin);
    gets(restaurant_name);
    int indexof_restaurants[no_of_restaurants];
    int count=0;
    binary_search(restaurant_name,restaurants,indexof_restaurants,&count);   
    

    if(indexof_restaurants[0]==-1){
         printf("Enter the valid Restaurant name\n");
    }
    else{
        int size=count;
       
        sort_index(indexof_restaurants,size);
        int totalitems;
        for(int i=0;i<size;i++){
            totalitems=restaurants[indexof_restaurants[i]].menusize;
            sort_item(restaurants[indexof_restaurants[i]].items,totalitems);
            printf("Name of Restaurant --->> %s \n",restaurants[indexof_restaurants[i]].name);
            printf("area --->>> %s \n",restaurants[indexof_restaurants[i]].Address.area);
            for(int j=0;j<totalitems;j++){
                printf("Item: %s ----->>> Price: %d \n",restaurants[indexof_restaurants[i]].items[j].item_name,restaurants[indexof_restaurants[i]].items[j].item_price);

            }
            printf("\n");
        }

    }
    
}
 int getItemAvailability(struct Restaurants restaurant[],char food_name[]){
    //  printf("Enter the name of food: ");
    //  char food_name[50];
    //  gets(food_name);


     int flag=0;
     int price_of_regularitem;
     int price_of_special_item;
     int availability=1;
     for(int i=0;i<no_of_restaurants;i++){
        sort_item(restaurant[i].items,restaurant[i].menusize);
        sort_specialitem(restaurant[i].specialmeal,restaurant[i].specialitemsize);
        price_of_regularitem=binary_fooditem_search(restaurant[i].items,restaurant[i].menusize,food_name);
        price_of_special_item=binary_specialfooditem_search(restaurant[i].specialmeal,restaurant[i].specialitemsize,food_name);
        if(price_of_regularitem!=-1){
            flag=1;
            printf("Price of %s in Restaurant-->> %s (area: %s ) is -->> %d \n",food_name,restaurant[i].name,restaurant[i].Address.area,restaurant[i].items[price_of_regularitem].item_price);
        }
        if(price_of_special_item!=-1){
            flag=1;
             printf("Price of %s in Restaurant-->> %s (area: %s ) is -->> %d \n",food_name,restaurant[i].name,restaurant[i].Address.area,restaurant[i].specialmeal[price_of_special_item].special_item_prices);
        }
        if(strcmp(restaurant[i].dayspecial,food_name)==0){
            flag=1;
            printf("Price of %s in Restaurant-->> %s (area: %s ) is -->> %d \n",food_name,restaurant[i].name,restaurant[i].Address.area,restaurant[i].dayspecial_price);
        }
     }
     if(flag==0){
        printf("Sorry %s is not currently available \n",food_name);
        availability=0;
     }
     return availability;
 }
 
void getMinTime(struct Restaurants restaurant[],char food_name[],int food_quantity,int x,int y){
     int index_of_regularitem;
     int index_of_specialitem;
     int minTime=999999;  // Ordering time can't be that large(999999) in minutes;
     int mintime_restaurant;
     int flag=0;
     for(int i=0;i<no_of_restaurants;i++){
        float distance=(restaurant[i].Address.x,restaurant[i].Address.y,x,y);
         sort_item(restaurant[i].items,restaurant[i].menusize);
         sort_specialitem(restaurant[i].specialmeal,restaurant[i].specialitemsize);
         index_of_regularitem=binary_fooditem_search(restaurant[i].items,restaurant[i].menusize,food_name);
         index_of_specialitem=binary_specialfooditem_search(restaurant[i].specialmeal,restaurant[i].specialitemsize,food_name);
         if(index_of_regularitem!=-1){
            flag=1;
            
            int expected_time=delivery_time(restaurant[i].items[index_of_regularitem].servicetime,distance,food_quantity);
            if(minTime>expected_time){
                minTime=expected_time;
                mintime_restaurant=i;
            }
            
        }
         if(index_of_specialitem!=-1){
             flag=1;
           int expected_time1=delivery_time(restaurant[i].specialmeal[index_of_specialitem].servicetime,distance,food_quantity);
           if(minTime>expected_time1){
                minTime=expected_time1;
                mintime_restaurant=i;
            }
            
         }
         if(strcmp(food_name,restaurant[i].dayspecial)==0){
            flag=1;
             int expected_time2=delivery_time(restaurant[i].dayspecial_time,distance,food_quantity);
             if(minTime>expected_time2){
                minTime=expected_time2;
                mintime_restaurant=i;
            }
            
        }
    }
    if(flag==0){
        printf("Sorry %s is not currently available in any of the restaurant \n",food_name);

    }
    else{
        printf("Minimum time taking restaurant is %s -->> area : %s and time required to Diliver food is %d  minutes\n",restaurant[mintime_restaurant].name,restaurant[mintime_restaurant].Address.area,minTime);
    }

    
}

void getAllSpecialItemListinSortedOrder(struct Restaurants restaurants[]){
     int n;
     printf("Enter the no: of restaurants: ");
     scanf("%d",&n);
     char resname[n][50];
     printf("Enter the restaurant name : \n");
     for(int i=0;i<n;i++){
        fflush(stdin);
        gets(resname[i]);
     }
     printf("Type 1 to sort on basis of items or 0 to sort on basis of price");
        int temp;
        scanf("%d",&temp);
     for(int j=0;j<n;j++){
     int indexof_res[no_of_specialitems];
     int count=0;
     binary_search(resname[j],restaurants,indexof_res,&count);
     if(indexof_res[0]==-1){
         printf("The %d name inserted restaurant is not present\n ",resname[j]);
     }
     else{

        int size=count;
        sort_index(indexof_res,size);

        

        for(int i=0;i<size;i++){
            printf("Name of Restaurant --->>> %s\n",restaurants[indexof_res[i]].name);
            printf("area --->>> %s\n",restaurants[indexof_res[i]].Address.area);
            
            if(temp==1){
                // on basis of name;
                sort_specialitem(restaurants[indexof_res[i]].specialmeal,restaurants[indexof_res[i]].specialitemsize);
                for(int j=0;j<restaurants[indexof_res[i]].specialitemsize;j++){
                    printf("Item: %s ---->>> Price: %d \n",restaurants[indexof_res[i]].specialmeal[j].special_item_name,restaurants[indexof_res[i]].specialmeal[j].special_item_prices);
                }
                printf("\n");
            }
            else if(temp==0){
                sort_by_price(restaurants[indexof_res[i]].specialmeal,restaurants[indexof_res[i]].specialitemsize);
                for(int j=0;j<restaurants[indexof_res[i]].specialitemsize;j++){
                    printf("Item: %s ---->>> Price: %d \n",restaurants[indexof_res[i]].specialmeal[j].special_item_name,restaurants[indexof_res[i]].specialmeal[j].special_item_prices);
                }
                printf("\n");
            }
            else{
                printf("Enter the valid input \n");
                printf("\n");
            }
        }
       
     }
     }
    

 }
void getItemListInAreaSortedOrder(struct Restaurants restaurants[],char *area)
{
    int c=0;
    for(int i=0;i<no_of_restaurants;i++)
    {
        if(strcmp(restaurants[i].Address.area,area)==0)
        {   c=1;
            sort_item(restaurants[i].items,restaurants[i].menusize);
            printf("\n\nsorted item list from restaurant %s:\n\n",restaurants[i].name);
            for(int j=0;j<restaurants[i].menusize;j++)
            {
                printf("%s\n",restaurants[i].items[j].item_name);
            }
            sort_specialitem(restaurants[i].specialmeal,restaurants[i].specialitemsize);
            printf("\n\nsorted special item list from restaurant %s:\n\n",restaurants[i].name);
            for(int j=0;j<restaurants[i].specialitemsize;j++)
            {
                printf("%s\n",restaurants[i].specialmeal[j].special_item_name);
            }
        }
    }
    if(c==0){
        printf("Enter the valid restaurant name: \n");
    }
}
void getItemofDayListinSortedOrder(struct Restaurants restaurants[],char *area)
{
    struct Restaurants restaurants1[no_of_restaurants];
    int j=0;
    for(int i=0;i<no_of_restaurants;i++)
    {
        if(strcmp(restaurants[i].Address.area,area)==0)
        {
            restaurants1[j]=restaurants[i];
            j++;          


        }
    }
    sort_dayspecial(restaurants1,j);
    
    for(int i =0; i<j;i++)
    {
        printf("%s--->%d\n",restaurants1[i].dayspecial,restaurants1[i].dayspecial_price);
    }
}
void getAllUniqueItems(struct Restaurants restaurant[],char restolist[][50],int n)
{   printf("Want to sort on basis of price if yes type 1 else 0 : ");
    int counter;
    scanf("%d",&counter); 
    
       
    
    sortlist(restolist,n);
    int index=0;
    int resindex[n];
    int size=0;
    int i=0;
    while(i<n){
        int cmp1=strcmp(restaurant[index].name,restolist[i]);
        if(cmp1==0){
            resindex[size]=index;
            size++;
            index++;
        }
        else if(cmp1<0){
            index++;
            
        }  
        else{
          i++;  
        }     
    }
    int c=0;
    int flag=0;
    if(counter == 1){
         for(int i=0;i<size;i++)
             sort_by_priceitem(restaurant[resindex[i]].items,restaurant[resindex[i]].menusize);
            
    }
    else{
        for(int i=0;i<size;i++){
        sort_item(restaurant[resindex[i]].items,restaurant[resindex[i]].menusize);
        }
    }
    
    
        for(int i=0;i<size;i++)
        {   int index1=0;
            int special_itemindex[restaurant[resindex[i]].menusize];
            printf("\nUnique items in %s Address: %s plot: %d \n",restaurant[resindex[i]].name,restaurant[resindex[i]].Address.area,restaurant[resindex[i]].Address.plot);
            for(int j=0;j<restaurant[resindex[i]].menusize;j++)
            {   
                
                
                c=0;
                
                for(int k=0;k<size;k++)
                {
                    if(k!=i){
                            for(int l=0;l<restaurant[resindex[k]].menusize;l++)
                        {
                         
                            if(strcmp(restaurant[resindex[i]].items[j].item_name,restaurant[resindex[k]].items[l].item_name)==0)
                            {
                                c++;
                           
                            }
                           
                        }
                    }
                    
                }
               

                if (c==0)
                {   
                   special_itemindex[index1++]=j;
                   flag=1;

                }
            }
           
            for(int x=0;x<index1;x++){
                printf("%s ----->>> %d  \n",restaurant[resindex[i]].items[special_itemindex[x]].item_name,restaurant[resindex[i]].items[special_itemindex[x]].item_price);
                flag=1;
            }
            if(flag==0)
            printf("No unique items in the restaurant\n");
        }
    

}
int getcommonregular(struct Restaurants restaurant[],int resindex[],int c){
        sort_item(restaurant[resindex[0]].items,restaurant[resindex[0]].menusize);
        int present=-1;    
        int availreg;
        int j=0;
        int k=1;
        int final_present;
        while(j<restaurant[resindex[0]].menusize){
            k=1;
            final_present=-1;   
             int itemindex[c];
             itemindex[0]=j;
             int count=1;
            while(k<c){
                sort_item(restaurant[resindex[k]].items,restaurant[resindex[k]].menusize);
                availreg=binary_fooditem_search(restaurant[resindex[k]].items,restaurant[resindex[k]].menusize,restaurant[resindex[0]].items[j].item_name);
                if(availreg!=-1){
                    final_present=1;
                    itemindex[count]=availreg;
                    count++;  
                }
                else{
                    final_present=-1;
                }
                k++;
            }
            if(final_present==1){
                present=1;
                for(int p=0;p<c;p++){
                   printf("%s --->> %d in restaurant : %s area : %s\n",restaurant[resindex[p]].items[itemindex[p]].item_name,restaurant[resindex[p]].items[itemindex[p]].item_price,restaurant[resindex[p]].name,restaurant[resindex[p]].Address.area) ;     
                }
            }
            j++;
        }
        return present;
       
}
int getcommonspecial(struct Restaurants restaurant[],int resindex[],int c){
        sort_specialitem(restaurant[resindex[0]].specialmeal,restaurant[resindex[0]].specialitemsize);      
        int availspecial;
        int present=-1;
        int j=0;
        int k=1;
        int final_present;
        while(j<restaurant[resindex[0]].specialitemsize){
            k=1;
            final_present=-1;   
             int itemindex[c];
             itemindex[0]=j;
             int count=1;
            while(k<c){
               
                sort_specialitem(restaurant[resindex[k]].specialmeal,restaurant[resindex[k]].specialitemsize);
                availspecial=binary_specialfooditem_search(restaurant[resindex[k]].specialmeal,restaurant[resindex[k]].specialitemsize,restaurant[resindex[0]].specialmeal[j].special_item_name);
                if(availspecial!=-1){
                    final_present=1;
                    itemindex[count]=availspecial;
                    count++;  
                }
                else{
                    final_present=-1;
                }
                k++;
            }
            if(final_present==1){
                present=1;
                for(int p=0;p<c;p++){
                   printf("%s --->> %d in restaurant : %s area : %s\n",restaurant[resindex[p]].specialmeal[itemindex[p]].special_item_name,restaurant[resindex[p]].specialmeal[itemindex[p]].special_item_prices,restaurant[resindex[p]].name,restaurant[resindex[p]].Address.area) ;     
                }
            }
            j++;
        }
        return present;
}
void getCommonItem(struct Restaurants restaurant[],char restolist[][50],int n)
{  
    sortlist(restolist,n);
    int index=0;
    int resindex[n];
    int size=0;
    int i=0;
    while(i<n){
        int cmp1=strcmp(restaurant[index].name,restolist[i]);
        if(cmp1==0){
            resindex[size]=index;
            size++;
            index++;
        }
        else if(cmp1<0){
            index++;
            
        }  
        else{
          i++;  
        }     
    }
    int flagreg=getcommonregular(restaurant,resindex,size);
    int flagspec=getcommonspecial(restaurant,resindex,size);
    int flag=0;
    for(int j=1;j<size && flag==0;j++){
        int cmp=strcmp(restaurant[resindex[j]].dayspecial,restaurant[resindex[0]].dayspecial);
        if(cmp!=0){
            flag=-1;
        }
    }
    if(flag==0){
        for(int j=0;j<size;j++){
            printf("%s -->> %d in restaurant : %s area: %s \n",restaurant[resindex[j]].dayspecial,restaurant[resindex[j]].dayspecial_price,restaurant[resindex[j]].name,restaurant[resindex[j]].Address.area);
        }
    }

    if(flag==-1 && flagreg==-1 && flagspec==-1){
        printf("NO common item is present in the given restaurant list .\n");
    }
    
         
 }
void history(struct userdetails user[],int count){
    printf("**Order History**\n");
    printf("\n");
    int flag=0;
    for(int i=0;i<count;i++){
        flag=1;
      printf("Coustomer Details --\n");
      printf("Name : %s\n",user[i].username);
      printf("Address: Area:%s Plot=%d X-Coordinate=%d Y-Coordinate:%d \n",user[i].useraddress.area,user[i].useraddress.plot,user[i].useraddress.x,user[i].useraddress.y);
      printf("Phone Number : %s\n",user[i].phone_number);
      printf("\n");
      printf("Order Details -- \n");
      printf("Order ID = %d\n",user[i].orderid);
      printf("Restaurant : %s\n",user[i].restaurant_name);
      printf("Order time: %s\n",user[i].order_time);
      printf("Food Ordered: ===>>>>>\n");
      for(int j=0;j<user[i].no_of_food_ordered;j++){
        printf("Food Item = %s\n",user[i].order[j].food_item_ordered);
        printf("Quantity = %d    Price = %d\n",user[i].order[j].quantity_ordered,user[i].order[j].food_item_price);
      }
      printf("Total Price = %d",user[i].total_price);
      printf("\n");    
    }
    if(flag==0){
        printf("You haven't ordered anything yet \n");
    }
    printf("-------------------------------------------------------X--------------------------------------------------------------");
}

int find_restaurant(struct Restaurants restaurants[],struct userdetails user[],int count){
    int found=0;
    int restaurant_index;
    
    while(found==0){
    printf("Enter the name of Restaurant from where you want to order your Food: \n");
    fflush(stdin);
    gets(user[count].restaurant_name);
    int cmp;
    char ans[5]="No";
    int i=0;
    while(i<no_of_restaurants &&strcmp(ans,"No")==0){
       cmp=strcmp(user[count].restaurant_name,restaurants[i].name);
       if(cmp==0){
        restaurant_index=i;
        found=1;
        printf("You want to order your food from %s Address=%s Plot=%d? (Yes/No) ",restaurants[i].name,restaurants[i].Address.area,restaurants[i].Address.plot);
        fflush(stdin);
        gets(ans);
       }
       i++;
    }
    if(found==0)
        printf("Please Enter the valid name of Restaurant !!\n");   
    }
    return restaurant_index;
}

    
void placeOrder(struct userdetails user[],int count,struct Restaurants restaurants[]){
    printf("Enter the user name : ");
    fflush(stdin);
    gets(user[count].username);
     printf("%s Enter your area : ",user[count].username);
    fflush(stdin);
    gets( user[count].useraddress.area);
 
    printf("Enter your coordinates = X-coordinate : ");
    scanf("%d",&user[count].useraddress.x);
    printf("Enter your coordinates = Y-Coordinate: ");
    scanf("%d",&user[count].useraddress.y);
    printf("%s enter your phone number : ",user[count].username);
  
    fflush(stdin);
    gets(user[count].phone_number);
    // Checking if phone number is valid or not 
    int flagnum=0;
    while(flagnum==0){
        int c=0;
        for(int i=0;user[count].phone_number[i]!='\0';i++){
            c++;
        }
        if(c!=10){
           
            printf("Please enter the valid phone number !!\n");
            printf("%s enter your phone number : ",user[count].username);
            fflush(stdin);
            gets(user[count].phone_number);
        }
        else{
            flagnum=1;
        }
    }
     printf("Your restaurant options:\n");
    for(int i=0;i<no_of_restaurants;i++)
    {
        printf("%s ----> %s \n",restaurants[i].name,restaurants[i].Address.area);
    }
    int restaurant_index=find_restaurant(restaurants,user,count);

    int sum=0;
    char ordermore[5]="Yes";
    int totalorder=0;
    while(strcmp(ordermore,"Yes")==0){
        
        printf("dayspecial of %s",restaurants[restaurant_index].name);
        printf("%s---->%d in time %d mins \n",restaurants[restaurant_index].dayspecial,restaurants[restaurant_index].dayspecial_price,restaurants[restaurant_index].dayspecial_time);
        printf("menu of %s:\n",restaurants[restaurant_index].name);
        for(int i=0;i<restaurants[restaurant_index].menusize;i++)
        {
            printf("%s--->%d\n",restaurants[restaurant_index].items[i].item_name,restaurants[restaurant_index].items[i].item_price);
        }
        printf("special items menu of %s:\n",restaurants[restaurant_index].name);
        for(int i=0;i<restaurants[restaurant_index].specialitemsize;i++)
        {
            printf("%s--->%d\n",restaurants[restaurant_index].specialmeal[i].special_item_name,restaurants[restaurant_index].specialmeal[i].special_item_prices);
        }

        int checkavail=0;
        while(checkavail==0){
            printf("Enter the Food item name : ");
            fflush(stdin);
            gets(user[count].order[totalorder].food_item_ordered);
            for(int i=0;i<restaurants[restaurant_index].menusize;i++){
                if(strcmp(user[count].order[totalorder].food_item_ordered,restaurants[restaurant_index].items[i].item_name)==0){
                    checkavail=1;
                    printf("Quantity: ");
                    scanf("%d",&user[count].order[totalorder].quantity_ordered);
                    user[count].order[totalorder].food_item_price=(restaurants[restaurant_index].items[i].item_price)*user[count].order[totalorder].quantity_ordered;
                    sum=sum+user[count].order[totalorder].food_item_price;
                }
            }
            for(int i=0;i<restaurants[restaurant_index].specialitemsize;i++){
                if(strcmp(user[count].order[totalorder].food_item_ordered,restaurants[restaurant_index].specialmeal[i].special_item_name)==0){
                    checkavail=1;
                    printf("Quantity: ");
                    scanf("%d",&user[count].order[totalorder].quantity_ordered);
                    user[count].order[totalorder].food_item_price=(restaurants[restaurant_index].specialmeal[i].special_item_prices)*user[count].order[totalorder].quantity_ordered;
                    sum=sum+user[count].order[totalorder].food_item_price;
                }
            }
            if(strcmp(user[count].order[totalorder].food_item_ordered,restaurants[restaurant_index].dayspecial)==0){
                    checkavail=1;
                    printf("Quantity: ");
                    scanf("%d",&user[count].order[totalorder].quantity_ordered);
                    user[count].order[totalorder].food_item_price=(restaurants[restaurant_index].dayspecial_price)*user[count].order[totalorder].quantity_ordered;
                    sum=sum+user[count].order[totalorder].food_item_price;
            }
            if(checkavail==0){
                printf("The item is not currently available in the given restaurant !!\n");
            }
            else{
                printf("Want to Order More?Yes/No ");
                fflush(stdin);
                gets(ordermore);
                if(strcmp(ordermore,"Yes")==0){
                    totalorder++;
                }
            }
        }
    }
    user[count].total_price=sum;
    printf("Enter Order Time: ");
    fflush(stdin);
    gets(user[count].order_time);
    user[count].no_of_food_ordered=totalorder+1;  // +1 Because total order is an index 
    user[count].orderid=count+1;
    printf("Order ID == %d",user[count].orderid);
} 
    

int performtask(char perform[])
{           int ans;
            int flag=0;
            while(flag==0){
                printf("\n");
                printf("Want to continue?(Yes/No) ");
                fflush(stdin);
                gets(perform);
                if(strcmp(perform,"Yes")!=0 && strcmp(perform,"No")!=0 ){
                    printf("Enter the valid input same as Yes / No \n");
                }
                else{
                    flag=1;
                }
  
            }
            if(strcmp("Yes",perform)==0){
                ans= 1;
            }
            else{
                ans= 0;
            }
            return ans;
}



int main(){

    struct  Restaurants restaurants[no_of_restaurants];
    struct userdetails user[100];
    {// First Restaurant data
    strcpy(restaurants[0].name,"Little");
    strcpy(restaurants[0].Address.area,"Ram Nagar");
    strcpy(restaurants[0].dayspecial,"Special Burger");
    restaurants[0].Address.plot=10;
    restaurants[0].Address.x=100;
    restaurants[0].Address.y=-200;

    restaurants[0].dayspecial_price=150;
    restaurants[0].dayspecial_time=15;
    restaurants[0].menusize=4;
    restaurants[0].specialitemsize=3;
    // MEal
    strcpy(restaurants[0].items[0].item_name,"Burger");
    strcpy(restaurants[0].items[1].item_name,"Pizza");
    strcpy(restaurants[0].items[2].item_name,"Sandwitch");
    strcpy(restaurants[0].items[3].item_name,"Noodles");

    restaurants[0].items[0].item_price=100;
    restaurants[0].items[1].item_price=200;
    restaurants[0].items[2].item_price=100;
    restaurants[0].items[3].item_price=80;

    restaurants[0].items[0].servicetime=10;
    restaurants[0].items[1].servicetime=15;
    restaurants[0].items[2].servicetime=10;
    restaurants[0].items[3].servicetime=20;
    // special item
    strcpy(restaurants[0].specialmeal[0].special_item_name,"Paneer");
    strcpy(restaurants[0].specialmeal[1].special_item_name,"Manchurian");
    strcpy(restaurants[0].specialmeal[2].special_item_name,"Kofta");

    restaurants[0].specialmeal[0].special_item_prices=150;
    restaurants[0].specialmeal[1].special_item_prices=200;
    restaurants[0].specialmeal[2].special_item_prices=90;

    restaurants[0].specialmeal[0].servicetime=10;
    restaurants[0].specialmeal[1].servicetime=15;
    restaurants[0].specialmeal[2].servicetime=20;

                                             /*****/

    // Second restaurant data

    strcpy(restaurants[1].name,"Food Island");
    strcpy(restaurants[1].Address.area,"Gandhi Chowk");
    strcpy(restaurants[1].dayspecial,"Masala Dosa");
    restaurants[1].Address.plot=15;
    restaurants[1].Address.x=400;
    restaurants[1].Address.y=-405;

    restaurants[1].dayspecial_price=100;
    restaurants[1].dayspecial_time=15;
    restaurants[1].menusize=5;
    restaurants[1].specialitemsize=3;
    // Meal
    strcpy(restaurants[1].items[0].item_name,"Panner");
    strcpy(restaurants[1].items[1].item_name,"Chola");
    strcpy(restaurants[1].items[2].item_name,"Sandwitch");
    strcpy(restaurants[1].items[3].item_name,"Cheese Panner");
    strcpy(restaurants[1].items[4].item_name,"Chilly Panner");

    restaurants[1].items[0].item_price=300;
    restaurants[1].items[1].item_price=250;
    restaurants[1].items[2].item_price=50;
    restaurants[1].items[3].item_price=350;
    restaurants[1].items[4].item_price=400;

    restaurants[1].items[0].servicetime=10;
    restaurants[1].items[1].servicetime=15;
    restaurants[1].items[2].servicetime=10;
    restaurants[1].items[3].servicetime=20;
    restaurants[1].items[4].servicetime=30;
    // special item
    strcpy(restaurants[1].specialmeal[0].special_item_name,"Idle");
    strcpy(restaurants[1].specialmeal[1].special_item_name,"Pav Bhaji");
    strcpy(restaurants[1].specialmeal[2].special_item_name,"Pizza");

    restaurants[1].specialmeal[0].special_item_prices=60;
    restaurants[1].specialmeal[1].special_item_prices=80;
    restaurants[1].specialmeal[2].special_item_prices=120;

    restaurants[1].specialmeal[0].servicetime=10;
    restaurants[1].specialmeal[1].servicetime=10;
    restaurants[1].specialmeal[2].servicetime=20;

                                            /*****/

    // Third Restaurant
    strcpy(restaurants[2].name,"Chat Center");
    strcpy(restaurants[2].Address.area,"Ramdaspeth");
    strcpy(restaurants[2].dayspecial,"Bhindi Masala");
    restaurants[2].Address.plot=20;
    restaurants[2].Address.x=700;
    restaurants[2].Address.y=-300;

    restaurants[2].dayspecial_price=100;
    restaurants[2].dayspecial_time=20;
    restaurants[2].menusize=5;
    restaurants[2].specialitemsize=4;
    // MEal
    strcpy(restaurants[2].items[0].item_name,"Mix Veg");
    strcpy(restaurants[2].items[1].item_name,"Paneer");
    strcpy(restaurants[2].items[2].item_name,"Chicken Masala");
    strcpy(restaurants[2].items[3].item_name,"Dal Tadka");
    strcpy(restaurants[2].items[4].item_name,"Rice");

    restaurants[2].items[0].item_price=150;
    restaurants[2].items[1].item_price=250;
    restaurants[2].items[2].item_price=300;
    restaurants[2].items[3].item_price=250;
    restaurants[2].items[4].item_price=100;

    restaurants[2].items[0].servicetime=20;
    restaurants[2].items[1].servicetime=20;
    restaurants[2].items[2].servicetime=30;
    restaurants[2].items[3].servicetime=10;
    restaurants[2].items[4].servicetime=20;
    // special item
    strcpy(restaurants[2].specialmeal[0].special_item_name,"Delhi Grill");
    strcpy(restaurants[2].specialmeal[1].special_item_name,"Pav Bhaji");
    strcpy(restaurants[2].specialmeal[2].special_item_name,"Chicken roll");
    strcpy(restaurants[2].specialmeal[3].special_item_name,"Panner roll");

    restaurants[2].specialmeal[0].special_item_prices=100;
    restaurants[2].specialmeal[1].special_item_prices=90;
    restaurants[2].specialmeal[2].special_item_prices=100;
    restaurants[2].specialmeal[3].special_item_prices=120;

    restaurants[2].specialmeal[0].servicetime=20;
    restaurants[2].specialmeal[1].servicetime=15;
    restaurants[2].specialmeal[2].servicetime=15;
    restaurants[2].specialmeal[3].servicetime=20;

                               /***/
    // Fourth Restaurant

    strcpy(restaurants[3].name,"Food Island");
    strcpy(restaurants[3].Address.area,"Wardha Road");
    strcpy(restaurants[3].dayspecial,"Chocolate Sauce");
    restaurants[3].Address.plot=18;
    restaurants[3].Address.x=550;
    restaurants[3].Address.y=1000;

    restaurants[3].dayspecial_price=150;
    restaurants[3].dayspecial_time=20;
    restaurants[3].menusize=6;
    restaurants[3].specialitemsize=5;
    // MEal
    strcpy(restaurants[3].items[0].item_name,"Paneer");
    strcpy(restaurants[3].items[1].item_name,"Chicken Curry");
    strcpy(restaurants[3].items[2].item_name,"Laccha Paratha");
    strcpy(restaurants[3].items[3].item_name,"Vegetable Biryani");
    strcpy(restaurants[3].items[4].item_name,"Red Chilli Pasta");
    strcpy(restaurants[3].items[5].item_name,"Chocolate Shake");

    restaurants[3].items[0].item_price=350;
    restaurants[3].items[1].item_price=300;
    restaurants[3].items[2].item_price=50;
    restaurants[3].items[3].item_price=130;
    restaurants[3].items[4].item_price=100;
    restaurants[3].items[5].item_price=90;

    restaurants[3].items[0].servicetime=30;
    restaurants[3].items[1].servicetime=30;
    restaurants[3].items[2].servicetime=20;
    restaurants[3].items[3].servicetime=20;
    restaurants[3].items[4].servicetime=20;
    restaurants[3].items[5].servicetime=30;

    // special item
    strcpy(restaurants[3].specialmeal[0].special_item_name,"Pizza");
    strcpy(restaurants[3].specialmeal[1].special_item_name,"Chicken Popcorn");
    strcpy(restaurants[3].specialmeal[2].special_item_name,"Chicken Roll");
    strcpy(restaurants[3].specialmeal[3].special_item_name,"Panner Roll");
    strcpy(restaurants[3].specialmeal[4].special_item_name,"French Fries");

    restaurants[3].specialmeal[0].special_item_prices=200;
    restaurants[3].specialmeal[1].special_item_prices=180;
    restaurants[3].specialmeal[2].special_item_prices=100;
    restaurants[3].specialmeal[3].special_item_prices=120;
    restaurants[3].specialmeal[4].special_item_prices=80;

    restaurants[3].specialmeal[0].servicetime=20;
    restaurants[3].specialmeal[1].servicetime=15;
    restaurants[3].specialmeal[2].servicetime=15;
    restaurants[3].specialmeal[3].servicetime=20;
    restaurants[3].specialmeal[4].servicetime=10;

                                           /****/

    // Fifth Restaurant
    strcpy(restaurants[4].name,"Grill Inn");
    strcpy(restaurants[4].Address.area,"Dharampeth");
    strcpy(restaurants[4].dayspecial,"White Saus Pasta");
    restaurants[4].Address.plot=30;
    restaurants[4].Address.x=-2000;
    restaurants[4].Address.y=3000;

    restaurants[4].dayspecial_price=170;
    restaurants[4].dayspecial_time=20;
    restaurants[4].menusize=6;
    restaurants[4].specialitemsize=5;
    // MEal
    strcpy(restaurants[4].items[0].item_name,"Veg Grilled Sandwich");
    strcpy(restaurants[4].items[1].item_name,"Pizza");
    strcpy(restaurants[4].items[2].item_name,"Chicken Hot Burger");
    strcpy(restaurants[4].items[3].item_name,"Sandwitch");
    strcpy(restaurants[4].items[4].item_name,"Crispy Panner Wrap");
    strcpy(restaurants[4].items[5].item_name,"Crispy Chicken Wrap");

    restaurants[4].items[0].item_price=110;
    restaurants[4].items[1].item_price=150;
    restaurants[4].items[2].item_price=200;
    restaurants[4].items[3].item_price=180;
    restaurants[4].items[4].item_price=100;
    restaurants[4].items[5].item_price=120;

    restaurants[4].items[0].servicetime=30;
    restaurants[4].items[1].servicetime=20;
    restaurants[4].items[2].servicetime=30;
    restaurants[4].items[3].servicetime=20;
    restaurants[4].items[4].servicetime=15;
    restaurants[4].items[5].servicetime=30;

    // special item
    strcpy(restaurants[4].specialmeal[0].special_item_name,"Panner Biryani");
    strcpy(restaurants[4].specialmeal[1].special_item_name,"Chicken Biryani");
    strcpy(restaurants[4].specialmeal[2].special_item_name,"Panner Masala");
    strcpy(restaurants[4].specialmeal[3].special_item_name,"Mushroom Masala");
    strcpy(restaurants[4].specialmeal[4].special_item_name,"Chicken Pizza");

    restaurants[4].specialmeal[0].special_item_prices=180;
    restaurants[4].specialmeal[1].special_item_prices=200;
    restaurants[4].specialmeal[2].special_item_prices=150;
    restaurants[4].specialmeal[3].special_item_prices=150;
    restaurants[4].specialmeal[4].special_item_prices=100;

    restaurants[4].specialmeal[0].servicetime=20;
    restaurants[4].specialmeal[1].servicetime=30;
    restaurants[4].specialmeal[2].servicetime=20;
    restaurants[4].specialmeal[3].servicetime=20;
    restaurants[4].specialmeal[4].servicetime=30;
    
                                          /***/
    // 6th restaurant
    strcpy(restaurants[5].name,"Food Fusion");
    strcpy(restaurants[5].Address.area,"Bajaj Nagar");
    strcpy(restaurants[5].dayspecial,"Chicken Burger");
    restaurants[5].Address.plot=1;
    restaurants[5].Address.x=-800;
    restaurants[5].Address.y=-400;

    restaurants[5].dayspecial_price=150;
    restaurants[5].dayspecial_time=20;
    restaurants[5].menusize=6;
    restaurants[5].specialitemsize=3;
    // MEal
    strcpy(restaurants[5].items[0].item_name,"Masala Maggi");
    strcpy(restaurants[5].items[1].item_name,"Veg Burger");
    strcpy(restaurants[5].items[2].item_name,"Chicken Nuggets");
    strcpy(restaurants[5].items[3].item_name,"Veg Roll");
    strcpy(restaurants[5].items[4].item_name,"Plain Maggi");
    strcpy(restaurants[5].items[5].item_name,"Veg Nuggets");

    restaurants[5].items[0].item_price=100;
    restaurants[5].items[1].item_price=200;
    restaurants[5].items[2].item_price=250;
    restaurants[5].items[3].item_price=100;
    restaurants[5].items[4].item_price=50;
    restaurants[5].items[5].item_price=200;

    restaurants[5].items[0].servicetime=20;
    restaurants[5].items[1].servicetime=30;
    restaurants[5].items[2].servicetime=20;
    restaurants[5].items[3].servicetime=15;
    restaurants[5].items[4].servicetime=10;
    restaurants[5].items[5].servicetime=20;
    // special item
    strcpy(restaurants[5].specialmeal[0].special_item_name,"Peri Peri Maggi");
    strcpy(restaurants[5].specialmeal[1].special_item_name,"Cheese Maggi");
    strcpy(restaurants[5].specialmeal[2].special_item_name,"Chicken Roll");


    restaurants[5].specialmeal[0].special_item_prices=100;
    restaurants[5].specialmeal[1].special_item_prices=90;
    restaurants[5].specialmeal[2].special_item_prices=100;
    

    restaurants[5].specialmeal[0].servicetime=20;
    restaurants[5].specialmeal[1].servicetime=15;
    restaurants[5].specialmeal[2].servicetime=15;

    
                               /***/
    // seventh Restaurant
    strcpy(restaurants[6].name,"Haldiram");
    strcpy(restaurants[6].Address.area,"Dharampeth");
    strcpy(restaurants[6].dayspecial,"Masala Dosa");
    restaurants[6].Address.plot=44;
    restaurants[6].Address.x=980;
    restaurants[6].Address.y=432;

    restaurants[6].dayspecial_price=150;
    restaurants[6].dayspecial_time=20;
    restaurants[6].menusize=6;
    restaurants[6].specialitemsize=3;
    // MEal
    strcpy(restaurants[6].items[0].item_name,"Paneer Butter Masala");
    strcpy(restaurants[6].items[1].item_name,"Shahi Paneer");
    strcpy(restaurants[6].items[2].item_name,"Aloo Mutter");
    strcpy(restaurants[6].items[3].item_name,"Sandwitch");
    strcpy(restaurants[6].items[4].item_name,"Garlic Naan");
    strcpy(restaurants[6].items[5].item_name,"Moong Daal");

    restaurants[6].items[0].item_price=200;
    restaurants[6].items[1].item_price=200;
    restaurants[6].items[2].item_price=150;
    restaurants[6].items[3].item_price=200;
    restaurants[6].items[4].item_price=50;
    restaurants[6].items[5].item_price=100;

    restaurants[6].items[0].servicetime=20;
    restaurants[6].items[1].servicetime=30;
    restaurants[6].items[2].servicetime=20;
    restaurants[6].items[3].servicetime=15;
    restaurants[6].items[4].servicetime=10;
    restaurants[6].items[5].servicetime=20;
    // special item
    strcpy(restaurants[6].specialmeal[0].special_item_name,"Kheer");
    strcpy(restaurants[6].specialmeal[1].special_item_name,"Raita");
    strcpy(restaurants[6].specialmeal[2].special_item_name,"Pizza");
    


    restaurants[6].specialmeal[0].special_item_prices=100;
    restaurants[6].specialmeal[1].special_item_prices=90;
    restaurants[6].specialmeal[2].special_item_prices=100;
    
    

    restaurants[6].specialmeal[0].servicetime=20;
    restaurants[6].specialmeal[1].servicetime=15;
    restaurants[6].specialmeal[2].servicetime=25;

                                    /****/
     // eighth Restaurant
    strcpy(restaurants[7].name,"Haldiram");
    strcpy(restaurants[7].Address.area,"Sitabuldi");
    strcpy(restaurants[7].dayspecial,"Masala Dosa");
    restaurants[7].Address.plot=33;
    restaurants[7].Address.x=568;
    restaurants[7].Address.y=982;

    restaurants[7].dayspecial_price=150;
    restaurants[7].dayspecial_time=20;
    restaurants[7].menusize=6;
    restaurants[7].specialitemsize=3;
    // MEal
    strcpy(restaurants[7].items[0].item_name,"Paneer Butter Masala");
    strcpy(restaurants[7].items[1].item_name,"Shahi Paneer");
    strcpy(restaurants[7].items[2].item_name,"Aloo Mutter");
    strcpy(restaurants[7].items[3].item_name,"Dal Makhani");
    strcpy(restaurants[7].items[4].item_name,"Garlic Naan");
    strcpy(restaurants[7].items[5].item_name,"Sandwitch");

    restaurants[7].items[0].item_price=200;
    restaurants[7].items[1].item_price=200;
    restaurants[7].items[2].item_price=150;
    restaurants[7].items[3].item_price=200;
    restaurants[7].items[4].item_price=50;
    restaurants[7].items[5].item_price=100;

    restaurants[7].items[0].servicetime=15;
    restaurants[7].items[1].servicetime=20;
    restaurants[7].items[2].servicetime=20;
    restaurants[7].items[3].servicetime=15;
    restaurants[7].items[4].servicetime=10;
    restaurants[7].items[5].servicetime=20;
    // special item
    strcpy(restaurants[7].specialmeal[0].special_item_name,"Kheer");
    strcpy(restaurants[7].specialmeal[1].special_item_name,"Raita");
    strcpy(restaurants[7].specialmeal[2].special_item_name,"Pizza");
    
    restaurants[7].specialmeal[0].special_item_prices=100;
    restaurants[7].specialmeal[1].special_item_prices=90;
    restaurants[7].specialmeal[2].special_item_prices=120;

    restaurants[7].specialmeal[0].servicetime=20;
    restaurants[7].specialmeal[1].servicetime=20;
    restaurants[7].specialmeal[2].servicetime=20;

                                  /***/
    
    // ninth restaurant data

    strcpy(restaurants[8].name,"Navratna Sagar");
    strcpy(restaurants[8].Address.area,"Pratap Nagar");
    strcpy(restaurants[8].dayspecial,"Daal Bhatti");
    restaurants[8].Address.plot=36;
    restaurants[8].Address.x=1200;
    restaurants[8].Address.y=650;

    restaurants[8].dayspecial_price=100;
    restaurants[8].dayspecial_time=15;
    restaurants[8].menusize=5;
    restaurants[8].specialitemsize=3;
    // MEal
    strcpy(restaurants[8].items[0].item_name,"Paneer");
    strcpy(restaurants[8].items[1].item_name,"Chola");
    strcpy(restaurants[8].items[2].item_name,"Aloo Mutter");
    strcpy(restaurants[8].items[3].item_name,"Papad");
    strcpy(restaurants[8].items[4].item_name,"Roti");

    restaurants[8].items[0].item_price=300;
    restaurants[8].items[1].item_price=250;
    restaurants[8].items[2].item_price=200;
    restaurants[8].items[3].item_price=50;
    restaurants[8].items[4].item_price=10;

    restaurants[8].items[0].servicetime=10;
    restaurants[8].items[1].servicetime=15;
    restaurants[8].items[2].servicetime=10;
    restaurants[8].items[3].servicetime=5;
    restaurants[8].items[4].servicetime=5;
    // special item
    strcpy(restaurants[8].specialmeal[0].special_item_name,"Kachori");
    strcpy(restaurants[8].specialmeal[1].special_item_name,"Samosa");
    strcpy(restaurants[8].specialmeal[2].special_item_name,"Pulao Rice");

    restaurants[8].specialmeal[0].special_item_prices=60;
    restaurants[8].specialmeal[1].special_item_prices=80;
    restaurants[8].specialmeal[2].special_item_prices=100;

    restaurants[8].specialmeal[0].servicetime=10;
    restaurants[8].specialmeal[1].servicetime=10;
    restaurants[8].specialmeal[2].servicetime=15;

                                            /*****/

    // tenth restaurant data

    strcpy(restaurants[9].name,"Lush House");
    strcpy(restaurants[9].Address.area,"Bajaj Nagar");
    strcpy(restaurants[9].dayspecial,"Pizza");
    restaurants[9].Address.plot=19;
    restaurants[9].Address.x=-650;
    restaurants[9].Address.y=920;

    restaurants[9].dayspecial_price=300;
    restaurants[9].dayspecial_time=15;
    restaurants[9].menusize=5;
    restaurants[9].specialitemsize=3;
    // MEal
    strcpy(restaurants[9].items[0].item_name,"Pasta");
    strcpy(restaurants[9].items[1].item_name,"Burger");
    strcpy(restaurants[9].items[2].item_name,"Sandwitch");
    strcpy(restaurants[9].items[3].item_name,"Cheese burger");
    strcpy(restaurants[9].items[4].item_name,"Arabiata");
    restaurants[9].items[0].item_price=300;
    restaurants[9].items[1].item_price=250;
    restaurants[9].items[2].item_price=150;
    restaurants[9].items[3].item_price=350;
    restaurants[9].items[4].item_price=400;

    restaurants[9].items[0].servicetime=10;
    restaurants[9].items[1].servicetime=15;
    restaurants[9].items[2].servicetime=10;
    restaurants[9].items[3].servicetime=20;
    restaurants[9].items[4].servicetime=30;
    // special item
    strcpy(restaurants[9].specialmeal[0].special_item_name,"Pesto Pasta");
    strcpy(restaurants[9].specialmeal[1].special_item_name,"Garlic Bread");
    strcpy(restaurants[9].specialmeal[2].special_item_name,"Mini Burger");

    restaurants[9].specialmeal[0].special_item_prices=250;
    restaurants[9].specialmeal[1].special_item_prices=150;
    restaurants[9].specialmeal[2].special_item_prices=200;

    restaurants[9].specialmeal[0].servicetime=20;
    restaurants[9].specialmeal[1].servicetime=10;
    restaurants[9].specialmeal[2].servicetime=10;

    
    }
   
    printf("*  Welcome   *\n");
    sortrestaurants(restaurants);
    int usercount=0;
        printf("getMinTime() --->>> 1\n");
        printf("getItemAvailability() --->>> 2\n");
        printf("placeOrder() --->>> 3\n");
        printf("getItemListInSortedOrder() --->> 4\n");
        printf("getItemListInAreaSortedOrder() --->> 5\n");
        printf("getAllSpecialItemListinSortedOrder() ---->> 6\n");
        printf("getItemofDayListinSortedOrder() --->>> 7\n");
        printf("getCommonItem() --->>> 8\n");
        printf("getAllUniqueItem() --->>> 9\n");
        printf("Want to check order history---->>> 10\n");
        

    char perform[3]="Yes";
    while(strcmp(perform,"Yes")==0){
        printf("Enter the task number which you want to perform : ");
        int Question;
        scanf("%d",&Question);
        if(Question==1){
            char food_name[50];
            int food_quantity;
            printf("Enter the food item : ");
            fflush(stdin);
            gets(food_name);
            printf("Enter the Quantity eg 1,2,3 plates resp and etc : ");
            scanf("%d",&food_quantity);
            int x;
            int y;
            printf("Enter your coordinates = X-coordinate : ");
            scanf("%d",&x);
            printf("Enter your coordinates = Y-coordinate: ");
            scanf("%d",&y);
            getMinTime(restaurants,food_name,food_quantity,x,y);
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if(Question==2){
            printf("Enter the name of food: ");
            char food_name[50];
             fflush(stdin);
            gets(food_name);
            int availability=getItemAvailability(restaurants,food_name);
             char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==3)
        {
           placeOrder(user,usercount,restaurants);
           usercount++;
          
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==4)
        {
           getItemListInSortedOrder(restaurants);  
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==5)
        {
            char area[50];
            printf("Enter the area: ");
            fflush(stdin);
            gets(area);
            getItemListInAreaSortedOrder(restaurants,area);
             char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==6)
        {
            getAllSpecialItemListinSortedOrder(restaurants); 
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==7)
        {
         
            char area[50];
            printf("Enter the area: ");
            fflush(stdin);
            gets(area);
            getItemofDayListinSortedOrder(restaurants,area);
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==8)
        {   int n;
             printf("Enter the no. of restaurants : ");
             scanf("%d",&n);
            char restolist[n][50];
            for(int i=0;i<n;i++){
                fflush(stdin);
                gets(restolist[i]);
            }
            getCommonItem(restaurants,restolist,n);
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        else if (Question==9)
        {
              int n;
             printf("Enter the no. of restaurants : ");
             scanf("%d",&n);
            char restolist[n][50];
            for(int i=0;i<n;i++){
                fflush(stdin);
                gets(restolist[i]);
            }
            getAllUniqueItems(restaurants,restolist,n);
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            } 
            printf("/n");
        }
        else if (Question==10)
        {
           
           history(user,usercount);
            char wanttoperform[3];
            int ans=performtask(wanttoperform);
            if(ans==1){
                strcpy(perform,"Yes");
            }
            else{
                strcpy(perform,"No");
            }
            printf("/n");
        }
        
        else{
            printf("!! Enter the valid input !!\n");
            printf("/n");
        }
     
    }
    printf("\n");
    printf("***Thank You*****");

    
    return 0;
}