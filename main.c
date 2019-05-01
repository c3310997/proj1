#include <stdio.h>

const char qwerty_keyboard[26] = "QWERTYUIOPASDFGHJKLZXCVBNM"; /* kwerty keyboard layout used for sustitution cipher*/

/* encrypt msg using rotate cipher */
void caesar_cipher_e(char msg[], int key) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = ((msg[i] + key) % 26) + 'A';
        }
        i++;
    }
}

/* decrypt msg using rotate cipher */
void caesar_cipher_d(char msg[], int key) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = ((msg[i] - key) % 26) + 'A';
        }
        i++;
    }
}

/* do rotation cypher encryption by position as key 1,2,3.... */
void rotate_cipher_e(char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = ((msg[i] + i) % 26) + 'A';
        }
        i++;
    }
}

/* do rotation cypher decryption by position as key 1,2,3.... */
void rotate_cipher_d(char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = ((msg[i] - i) % 26) + 'A';
        }
        i++;
    }
}

/* do substitution cipher encryption using qwerty keyboard layout */
void substitution_cipher_e(char msg[]) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = qwerty_keyboard[msg[i] - 'A'];
        }
        i++;
    }
}

/* do substitution cipher decryption using qwerty keyboard layout */
void substitution_cipher_d(char msg[]) {
    int i = 0, j;
    while (msg[i] != '\0') {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            for(j = 0; j < 26; j++){
                if(msg[i] == qwerty_keyboard[j]){
                    msg[i] = 'A' + j;
                    break;
                }
            }
        }
        i++;
    }
}

int main() {
    int key; // caeser cipher key
    size_t MAX = 1000;
    char command[MAX], msg[MAX]; // command and msg read
    char inputFile[100]; // store input filename
    char outputFile[100]; // store output filename
    printf("Enter input filename: ");
    scanf("%s", inputFile);
    printf("Enter output filename: ");
    scanf("%s", outputFile);
    //open files
    FILE *in = fopen (inputFile, "r");
    FILE *out = fopen (outputFile, "w");
    //if input file not found
    if(in == NULL){
        printf("Input file not found\n");
        return 0;      
    }
    //read input file instructions and write output into output file
    while (fgets (command, MAX, in) != NULL ) /* read a command */
    {
        //if command is caeser read key
        if(strcmp("caeser_enc\n\0", command) == 0 || strcmp("caeser_dec\n\0", command) == 0){
            fscanf(in, "%d",&key);
            fgets (msg, MAX, in); // clear line after it
        }
        //read msg
        fgets (msg, MAX, in);
        //convert lowercase to uppercase
        int k = 0;
        while (msg[k] != '\0') {
            if(msg[k] >= 'a' && msg[k] <= 'z')
                msg[k] -= 32;
            k++;
        }
        //check command and print result
        if(strcmp("caeser_enc\n\0", command) == 0)
            caesar_cipher_e(msg, key);
        else if(strcmp("caeser_dec\n\0", command) == 0)
            caesar_cipher_d(msg, key);
        else if(strcmp("rotate_enc\n\0", command) == 0)
            rotate_cipher_e(msg);
        else if(strcmp("rotate_dec\n\0", command) == 0)
            rotate_cipher_d(msg);
        else if(strcmp("sub_enc\n\0", command) == 0)
            substitution_cipher_e(msg);
        else if(strcmp("sub_dec\n\0", command) == 0)
            substitution_cipher_d(msg);
        ///write the msg
        fprintf(out, msg); 
    }
    //close files
    fclose(in);
    fclose(out);
    return 0;
}
