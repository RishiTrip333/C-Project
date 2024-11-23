#include<stdio.h>
#include<string.h>
struct TransactionDetail{
    char transType[20];
    float transAmount;
};
struct AccountInfo{
    int acc_num;
    char accType[10];
    float currentBalance;
    float Loan;
    float loanRemaining;
    int loanCategory;
    struct TransactionDetail transDetails[100];
    int transCount;
    char accPassword[20];
};
int registerAccount(struct AccountInfo accounts[],int totalAcc){
    printf("+-----------------------------------------+\n");
    printf("|           Register New Account          |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter account number:                   |\n| ");
    scanf("%d",&accounts[totalAcc].acc_num);
    printf("| Enter account type (1. savings 2. current): |\n| ");
    scanf("%s",accounts[totalAcc].accType);
    printf("| Set a password:                         |\n| ");
    scanf("%s",accounts[totalAcc].accPassword);
    accounts[totalAcc].currentBalance=0;
    accounts[totalAcc].Loan=0;
    accounts[totalAcc].loanRemaining=0;
    accounts[totalAcc].transCount=0;
    printf("+-----------------------------------------+\n");
    printf("|        Account successfully created     |\n");
    printf("+-----------------------------------------+\n");
    return totalAcc+1;
}
int userLogin(struct AccountInfo accounts[],int totalAcc){
    int acc_num;
    char enteredPassword[20];
    printf("+-----------------------------------------+\n");
    printf("|               User Login                |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter account number:                   |\n| ");
    scanf("%d",&acc_num);
    for(int i=0;i<totalAcc;i++){
        if(accounts[i].acc_num==acc_num){
            printf("| Account found. Enter password:          |\n| ");
            scanf("%s",enteredPassword);
            if(strcmp(accounts[i].accPassword,enteredPassword)==0){
                printf("+-----------------------------------------+\n");
                printf("|             Login successful            |\n");
                printf("+-----------------------------------------+\n");
                return i;
            }else{
                printf("+-----------------------------------------+\n");
                printf("|           Incorrect password.           |\n");
                printf("+-----------------------------------------+\n");
                return -1;
            }
        }
    }
    printf("+-----------------------------------------+\n");
    printf("|           Account not found.            |\n");
    printf("+-----------------------------------------+\n");
    return -1;
}
void addDeposit(struct AccountInfo accounts[],int index){
    float amount;
    printf("+-----------------------------------------+\n");
    printf("|           Deposit Money                 |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter amount to deposit:                |\n| ");
    scanf("%f",&amount);
    accounts[index].currentBalance+=amount;
    printf("+-----------------------------------------+\n");
    printf("| Deposit successful. New Balance: %.2f   |\n",accounts[index].currentBalance);
    printf("+-----------------------------------------+\n");
    strcpy(accounts[index].transDetails[accounts[index].transCount].transType,"Deposit");
    accounts[index].transDetails[accounts[index].transCount].transAmount=amount;
    accounts[index].transCount++;
}
void withdrawFunds(struct AccountInfo accounts[],int index){
    float amount;
    printf("+-----------------------------------------+\n");
    printf("|           Withdraw Money                |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter amount to withdraw:               |\n| ");
    scanf("%f",&amount);
    if(amount<=accounts[index].currentBalance){
        accounts[index].currentBalance-=amount;
        printf("+-----------------------------------------+\n");
        printf("| Withdrawal successful. New Balance: %.2f |\n",accounts[index].currentBalance);
        printf("+-----------------------------------------+\n");
        strcpy(accounts[index].transDetails[accounts[index].transCount].transType,"Withdrawal");
        accounts[index].transDetails[accounts[index].transCount].transAmount=amount;
        accounts[index].transCount++;
    }else{
        printf("+-----------------------------------------+\n");
        printf("|       Insufficient funds available      |\n");
        printf("+-----------------------------------------+\n");
    }
}
void displayBalance(struct AccountInfo accounts[],int index){
    printf("+-----------------------------------------+\n");
    printf("|         Current balance: %.2f           |\n",accounts[index].currentBalance);
    printf("+-----------------------------------------+\n");
}
void requestLoan(struct AccountInfo accounts[],int index){
    float loanAmount;
    int loanCategory;
    printf("+-----------------------------------------+\n");
    printf("|              Request Loan               |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter loan type (1: Personal, 2: Home, 3: Business): |\n| ");
    scanf("%d",&loanCategory);
    printf("| Enter loan amount:                      |\n| ");
    scanf("%f",&loanAmount);
    float loanLimit;
    if(strcmp(accounts[index].accType,"savings")==0){
    loanLimit = 50000;
    }else{
    loanLimit = 200000;
}
    if(loanAmount>loanLimit){
        printf("+-----------------------------------------+\n");
        printf("|   Loan amount exceeds limit. Max: %.2f  |\n",loanLimit);
        printf("+-----------------------------------------+\n");
        return;
    }
    accounts[index].Loan+=loanAmount;
    accounts[index].loanRemaining+=loanAmount;
    accounts[index].loanCategory=loanCategory;
    printf("+-----------------------------------------+\n");
    printf("|   Loan of %.2f granted. Total due: %.2f |\n",loanAmount,accounts[index].loanRemaining);
    printf("+-----------------------------------------+\n");
    strcpy(accounts[index].transDetails[accounts[index].transCount].transType,"Loan Granted");
    accounts[index].transDetails[accounts[index].transCount].transAmount=loanAmount;
    accounts[index].transCount++;
}
void makeRepayment(struct AccountInfo accounts[],int index){
    float repayment;
    printf("+-----------------------------------------+\n");
    printf("|              Make Repayment             |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter repayment amount:                 |\n| ");
    scanf("%f",&repayment);
    if(repayment<=accounts[index].loanRemaining){
        accounts[index].loanRemaining-=repayment;
        printf("+-----------------------------------------+\n");
        printf("| Repayment successful. Remaining Loan: %.2f |\n",accounts[index].loanRemaining);
        printf("+-----------------------------------------+\n");
        strcpy(accounts[index].transDetails[accounts[index].transCount].transType,"Loan Repayment");
        accounts[index].transDetails[accounts[index].transCount].transAmount=repayment;
        accounts[index].transCount++;
    }else{
        printf("+-----------------------------------------+\n");
        printf("| Repayment exceeds amount due. Invalid.  |\n");
        printf("+-----------------------------------------+\n");
    }
}
void showTransactionHistory(struct AccountInfo accounts[],int index){
    printf("+-------------------------------------------------------------+\n");
    printf("|          Transaction history for account %d                  |\n",accounts[index].acc_num);
    printf("+-------------------------------------------------------------+\n");
    printf("| %-10s | %-10s | %-15s | %-10s |\n","Acc Num","Acc Type","Transaction Type","Amount");
    printf("+-------------------------------------------------------------+\n");
    for(int i=0;i<accounts[index].transCount;i++){
        printf("|%-10d|%-10s|%-15s|%-12.2f|%-12d|%-12.2f|\n",accounts[index].acc_num,accounts[index].accType,accounts[index].transDetails[i].transType,accounts[index].transDetails[i].transAmount,accounts[index].loanCategory,accounts[index].loanRemaining);
    }
    printf("+-------------------------------------------------------------+\n");
}
void modifyAccountDetails(struct AccountInfo accounts[],int index){
    printf("+-----------------------------------------+\n");
    printf("|         Editing Account Details         |\n");
    printf("+-----------------------------------------+\n");
    printf("| 1. Change password                      |\n");
    printf("| 2. Change account type                  |\n");
    printf("+-----------------------------------------+\n");
    printf("| Enter choice:                           |\n| ");
    int option;
    scanf("%d",&option);
    if(option==1){
        printf("| Enter new password:                     |\n| ");
        scanf("%s",accounts[index].accPassword);
        printf("+-----------------------------------------+\n");
        printf("|         Password updated successfully   |\n");
        printf("+-----------------------------------------+\n");
    }else if(option==2){
        printf("| Enter new account type (savings/current): |\n| ");
        scanf("%s",accounts[index].accType);
        printf("+-----------------------------------------+\n");
        printf("|          Account type updated           |\n");
        printf("+-----------------------------------------+\n");
    }else{
        printf("+-----------------------------------------+\n");
        printf("|              Invalid choice!            |\n");
        printf("+-----------------------------------------+\n");
    }
}
int main(){
    struct AccountInfo accounts[100];
    int totalAcc=0;
    int option=0,currentIndex;
    int LoggedIn=0;
    while(1){
        if(!LoggedIn){
            printf("+------------------------+\n");
            printf("|%-24s|\n","Main Menu");
            printf("+------------------------+\n");
            printf("| 1. Register            |\n");
            printf("| 2. Login               |\n");
            printf("| 3. Exit                |\n");
            printf("+------------------------+\n");
            printf("| Enter your choice:      |\n| ");
            scanf("%d",&option);
            if(option==1){
                totalAcc=registerAccount(accounts,totalAcc);
            }else if(option==2){
                currentIndex=userLogin(accounts,totalAcc);
                if(currentIndex!=-1){
                    LoggedIn=1;
                }
            }else if(option==3){
                printf("+------------------------+\n");
                printf("|%-24s|\n","Exiting system");
                printf("+------------------------+\n");
                break;
            }else{
                printf("+------------------------+\n");
                printf("|%-24s|\n","Invalid choice");
                printf("+------------------------+\n");
            }
        }else{
            printf("+------------------------+\n");
            printf("|%-24s|\n","Account Menu");
            printf("+------------------------+\n");
            printf("| 1. Deposit             |\n");
            printf("| 2. Withdraw            |\n");
            printf("| 3. Show Balance        |\n");
            printf("| 4. Request Loan        |\n");
            printf("| 5. Repay Loan          |\n");
            printf("| 6. Show Transaction    |\n");
            printf("| 7. Modify Account      |\n");
            printf("| 8. Logout              |\n");
            printf("+------------------------+\n");
            printf("| Enter your choice:      |\n| ");
            scanf("%d",&option);
            if(option==1){
                addDeposit(accounts,currentIndex);
            }else if(option==2){
                withdrawFunds(accounts,currentIndex);
            }else if(option==3){
                displayBalance(accounts,currentIndex);
            }else if(option==4){
                requestLoan(accounts,currentIndex);
            }else if(option==5){
                makeRepayment(accounts,currentIndex);
            }else if(option==6){
                showTransactionHistory(accounts,currentIndex);
            }else if(option==7){
                modifyAccountDetails(accounts,currentIndex);
            }else if(option==8){
                LoggedIn=0;
                printf("+------------------------+\n");
                printf("|%-24s|\n","Logged out successfully");
                printf("+------------------------+\n");
            }else{
                printf("+------------------------+\n");
                printf("|%-24s|\n","Invalid choice");
                printf("+------------------------+\n");
            }
        }
    }
}

