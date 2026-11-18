#include<stdio.h>
#include<string.h>
#include<ctype.h>
// int main(){
//     char mail[] = "marat@sibguti.ru";
//     char login[100];
//     char domen[100];
//     int index = 0;

//     for (int i = 0; mail[i] != '\0'; i++) {
//         if (mail[i] == '@') {
//             index = i;
//             login[i] = '\0';
//             break;
//         }
//         login[i] = mail[i];
//     }
//     int j = 0;
//     for (int i = index + 1; mail[i] != '\0'; i++) {
//         domen[j] = mail[i];
//         j++;
//     }
//     domen[j] = '\0';
//     printf(" domen: %s \n login: %s \n index @: %d \n", domen, login, index);

//     return 0;
// }

// int main() {
//     char mail[] = "marat@sibguti.ru";
//     char login[100];
//     char domen[100];

//     char *p = strchr(mail, '@');
//     if (p != NULL) {
//         int index = p - mail;
//         strncpy(login, mail, index);
//         login[index] = '\0';
//         strcpy(domen, p + 1);

//     printf(" domen: %s \n login: %s \n index @: %d \n", domen, login, index);
//     }
//     return 0;
// }

// int main(){
//     char s[] = "A man a plan a canal Panama";
//     char swork[100];
//     int j = 0;
//     int flag = 1;
//     for(int i = 0; s[i]!= '\0'; i++){
//         if(isspace(s[i]) ==0){
//             swork[j] = tolower(s[i]);
//             j++;
//         }
//     }
//     swork[j] = '\0';
//     int lenght = strlen(swork);
//     for(int i = 0; i != lenght/2; i++){
//         if(swork[i] != swork[lenght-1]){
//             flag = 0;
//             break;
//         }
//         lenght--;
//     }
//     if(flag == 1) printf("PALIDROM");
//     else printf("NE PALIDROM");
//     return 0;
// }

int main(){
    char post[] = "#today #coding in c #strings arrays qwer qwe qw ";
    char hesh[sizeof post];
    int count = 0;

    for (int i = 0; post[i] != '\0'; i++) {
        if (post[i] == '#' && (i == 0 || post[i - 1] == ' ')) {
            int tmpindex = 0;
            for (int j = i; post[j] != ' ' && post[j] != '\0'; j++) {
                hesh[tmpindex] = post[j];
                tmpindex++;
            }
            hesh[tmpindex] = '\0';
            printf("%s\n", hesh);
            count++;
        }
    }
    printf("Количество хэштегов: %d\n", count);

    return 0;
}