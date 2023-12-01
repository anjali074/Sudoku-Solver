#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int size;   
int temp;
int findemptycell(int arr[][size],int* row,int* col){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]==0){       
                *row=i;*col=j;
                return 1;
            }
        }
    }
    return 0;                     
}
int presentinsubgrid(int row,int col,int number,int arr[][size]){
    if(temp*temp!=size)                
      return 0;
    int startrow,startcol;
    for(int i=temp;i<=size;i+=temp){   
         if(row<i){
             startrow=i-temp;
             break;
         }
    }
    for(int l=temp;l<=size;l+=temp){   
         if(col<l){
             startcol=l-temp;
             break;
         }
    }

    for(int j=0;j<temp;j++){          
        for(int k=0;k<temp;k++){
            if(arr[j+startrow][k+startcol]==number)
              return 1;                
        }
    }
    return 0;                        
}
int sudokusolver(int arr[][size],int** rowbacktracking,int** colbacktracking){
      int row,col;
      int flag=0;
      int temp=findemptycell(arr,&row,&col);   
      if(temp==0)                              
        return 1;
      for(int i=1;i<=size;i++){
          if(rowbacktracking[row][i-1] || colbacktracking[col][i-1] || presentinsubgrid(row,col,i,arr)) 
            continue; 

          arr[row][col]=i;                
          rowbacktracking[row][i-1]=1;    
          colbacktracking[col][i-1]=1;    
          flag=sudokusolver(arr,rowbacktracking,colbacktracking);  
          if(flag==1)
            return 1;
          else{
            arr[row][col]=0;
            rowbacktracking[row][i-1]=0;
            colbacktracking[col][i-1]=0;
            continue;
          }
      }
    return 0;
}

int letsSolveSudoku(int arr[][size]){
    int ** rowbacktracking=(int**)malloc(sizeof(int*)*size); 
    int ** colbacktracking=(int**)malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
        rowbacktracking[i]=(int*)malloc(sizeof(int)*size);
        colbacktracking[i]=(int*)malloc(sizeof(int)*size);
        for(int j=0;j<size;j++){
            rowbacktracking[i][j]=0;
            colbacktracking[i][j]=0;
        }
    }
    
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]>size)
              return -1;
            if(arr[i][j]!=0){
                 if(rowbacktracking[i][arr[i][j]-1]==0)
                    rowbacktracking[i][arr[i][j]-1]=1;
                else
                  return 0;
            }
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]>size)
              return -1;
            if(arr[i][j]!=0){
                if(colbacktracking[j][arr[i][j]-1]==0)
                  colbacktracking[j][arr[i][j]-1]=1;
                else
                  return 0;
            }
        }
    }      
    
    return sudokusolver(arr,rowbacktracking,colbacktracking);
}
int lenofint(int a){
    int count=0;
    while(a!=0){
        a/=10;
        count++;
    }
    return count;
}
void accurateprint(int a){
    int len=lenofint(a);
    int lenofsize=lenofint(size);
    for(int i=0;i<lenofsize-len;i++){
        printf(" ");
    }
    printf(" %d ",a);
}
int main(){
    printf("\nSudoku Solver Programme!!!\n");
    while(1){
        printf("\nsize of sudoku in integer format (enter -1 to exit)\n");
        scanf("%d",&size);
        if(size==-1)
          break;
        else if(size<=0){
            printf("the correct size\n");
            continue;
        }
        temp=sqrt(size);
        int grid[size][size];
        printf("the Sudoku Grid\n");         
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                scanf("%d",&grid[i][j]);
            }
        }
        int ans=letsSolveSudoku(grid);        

        if(ans==1){          
            printf("\nAnlong!!! The ans is\n\n") ;  
            int var=(lenofint(size)+2)*size+(int)ceil(sqrt(size))+1;
            for(int i=0;i<size;i++){
                if(i==0 || i%(int)ceil(sqrt(size))==0){
                    for(int k=0;k<var;k++)
                       printf("-");
                    printf("\n");
                }
                for(int j=0;j<size;j++){
                    if(j==0 || j%(int)ceil(sqrt(size))==0)
                      printf("|");
                
                    accurateprint(grid[i][j]);
                }
                printf("|");
                printf("\n");
            }
            for(int k=0;k<var;k++)
                printf("-");
            printf("\n");
        }
        else if(ans==-1)
            printf("\nthe values in Sudoku\n");           
        else                                     
            printf(" No of solution exits for given Suduku\n");  

        char c;
        printf("\n Press x for yes n for no\n");
        scanf("\n%c",&c);
        if(c=='n')
          break;
    }
return 0;
}

