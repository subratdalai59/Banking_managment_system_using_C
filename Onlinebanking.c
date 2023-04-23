#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user
{
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

int main()
{
    struct user user, user1;
    int opt, choice;
    FILE *fp;
    char filename[50], pno[50], pword[50];
    char cont = 'y';
    float amount;

    printf("\nWhat do you want to do ?");
    printf("\n\n1 . Register an account .");
    printf("\n2 . Login to your account .");

    printf("\n\nYour choice:\n");
    scanf("%d", &opt);

    if (opt == 1)
    {
        system("cls");
        printf("Enter your account number :\t");
        scanf("%s", &user.ac);
        printf("Enter your phone  number :\t");
        scanf("%s", &user.phone);
        printf("Enter your new password :\t");
        scanf("%s", &user.password);
        user.balance = 0;
        strcpy(filename, user.phone);
        fp = fopen(strcat(filename, ".dat"), "w");
        fwrite(&user, sizeof(struct user), 1, fp);
        if (fwrite != 0)
        {
            printf("\n\nAccount successfully registered");
        }
        else
        {
            printf("Something went wrong,try again");
        }
        fclose(fp);
    }

    if (opt == 2)
    {
        system("cls");
        printf("Enter your phone number :\t");
        scanf("%s", &pno);
        printf("Enter your password :\t");
        scanf("%s", &pword);
        strcpy(filename, pno);
        fp = fopen(strcat(filename, ".dat"), "r");
        if (fp == NULL)
        {
            printf("Account number is not registered.");
        }
        else
        {
            fread(&user, sizeof(struct user), 1, fp);
            fclose(fp);
            if (!strcmp(pword, user.password))
            {
                printf("\n\tWelcome %s",user.phone);
                while (cont == 'y')
                {
                    system("cls");
                    printf("\nPress 1 to check balance .");
                    printf("\nPress 2 to deposit an amount .");
                    printf("\nPress 3 to withdraw an amount .");
                    printf("\nPress 4 to transfer the amount .");
                    printf("\nPress 5 to change the password .");
                    printf("\nYOur choice\n");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        printf("\nYour current balance is Rs.%.2f", user.balance);
                        break;
                    case 2:
                        printf("\nEnter the amount");
                        scanf("%f", &amount);
                        user.balance += amount;
                        fp = fopen(filename, "w ");
                        fwrite(&user, sizeof(struct user), 1, fp);
                        if (fwrite != NULL)
                        {
                            printf("\nSuccessfully deposited .");
                        }
                        fclose(fp);
                        break;
                    case 3:
                        printf("\nEnter the amount you want to withdraw : ");
                        scanf("%f", &amount);
                        if (amount > user.balance)
                        {
                            printf("\n Insufficient balance");
                        }
                        else
                        {
                            user.balance -= amount;
                            fp = fopen(filename, "w ");
                            fwrite(&user, sizeof(struct user), 1, fp);
                            if (fwrite != NULL)
                            {
                                printf("\nSuccessfully withdrawl the amount %f .", amount);
                            }
                            fclose(fp);
                        }
                        break;

                    case 4:
                        printf("\nplease enter the phone number to transfer the amount :\t ");
                        scanf("%s", &pno);
                        printf("\nPlease enter the amount to transfer :\t");
                        scanf("%f", &amount);
                        strcpy(filename, pno);
                        fp = fopen(strcat(filename, ".dat"), "r");
                        if (fp == NULL)
                        {
                            printf("\nPhone number not registered .");
                            return 0;
                        }
                        else
                        {
                            fread(&user1, sizeof(struct user), 1, fp);
                            fclose(fp);

                            if (amount > user.balance)
                            {
                                printf("\nInsufficient balance");
                            }
                            else
                            {

                                fp = fopen(filename, "w");
                                user1.balance += amount;
                                fwrite(&user1, sizeof(struct user), 1, fp);
                                fclose(fp);
                                if (fwrite != NULL)
                                {
                                    printf("\nYou have successfully transfered Rs.%.2f to %s", amount, pno);
                                    strcpy(filename, user.phone);
                                    fp = fopen(strcat(filename, ".dat"), "w");
                                    user.balance -= amount;
                                    fwrite(&user, sizeof(struct user), 1, fp);
                                    fclose(fp);
                                }
                            }
                        }

                    case 5:
                        printf("\nPlease enter your new password : \t");
                        scanf("%s",&pword);
                        fp=fopen(filename,"w");
                        strcpy(user.password,pword);
                        fwrite(&user,sizeof(struct user),1,fp);
                        fclose(fp);
                        if(fwrite != NULL){
                            printf("\nPassword successfully changed .");
                        }
                        break;

                    default:
                        printf("\nInvalid option");   
                    }

                    printf("\nDo you want to continue the transaction [y/n]");
                    scanf("%s", &cont);
                }
            }
            else
            {
                printf("\nInvalid password");
            }
        }
    }
    return 0;
}