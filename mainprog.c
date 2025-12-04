 #include<stdio.h>
#include<stdlib.h>


#include<string.h>

#include<sys/types.h>
 #define MIN_USERNAME_LENGTH 6
#define MAX_USERNAME_LENGTH 20
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 32

typedef struct UserAccount {
  char username[MAX_USERNAME_LENGTH + 1];
  char password[MAX_PASSWORD_LENGTH + 1];
} UserAccount;
void createNewUserAccount(UserAccount *user) {
  FILE* fu=NULL;
   fu=fopen("user.txt" ,"w");
  printf("Entrer username: ");
  fscanf("%s", user->username);

  // Validate username length
  if (strlen(user->username) < MIN_USERNAME_LENGTH ||
      strlen(user->username) > MAX_USERNAME_LENGTH) {
    printf("Username doit etre entre %d et %d de langueur de characters .\n",
           MIN_USERNAME_LENGTH, MAX_USERNAME_LENGTH);

  }

  // Get password from the user
  printf("Entre password: ");
  fscanf("%s", user->password);

  // Validate password length
  if (strlen(user->password) < MIN_PASSWORD_LENGTH ||
      strlen(user->password) > MAX_PASSWORD_LENGTH) {
    printf("Password doit etre entre %d et %d de langueur de characteres.\n",
           MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);

  }

  fclose(FILE* fu);
}


int authenticateUser(char *username, char *password) {

  UserAccount *userAccount = findUserAccount(username);


  if (userAccount == NULL) {
    return 1;
  }

  // Compare the entered password to the stored password
  if (strcmp(password, userAccount->password) != 0) {
    return 2;
  }

  // Authentication successful
  return 0;
}
User *findUserByUsernameAndPasswordFromFile(char *filename, char *username, char *password) {
  FILE *fu = fopen("user.txt, "+r");
  if (fp == NULL) {
    printf("Erreur d'ouverture du fichier %s\n", user.txt);
    return NULL;
  }

  char line[1024];
  char *fileUsername, *filePassword;

  while (fgets(line, sizeof(line), fp) != NULL) {
    if (line[0] == '#') continue; // Ignorer les lignes de commentaire

    fileUsername = strtok(line, ":");
    filePassword = strtok(NULL, "\n");

    if (strcmp(fileUsername, username) == 0 && strcmp(filePassword, password) == 0) {
      fclose(fp);
      return malloc(sizeof(User)); // Allouer de la mémoire pour un nouvel utilisateur
    }
  }

  fclose(fu);
  return NULL;
}






int authenticateUser(char *username, char *password) {
  // Load user accounts from a secure storage
  // ...

  // Find the user account with the specified username
  UserAccount *userAccount = findUserAccount(username);

  // If the user account was not found, return an error
  if (userAccount == NULL) {
    return 1;
  }

  // Compare the entered password to the stored password
  if (strcmp(password, userAccount->password) != 0) {
    return 2;
  }

  // Authentication successful
  return 0;
}

void updateUsername(char *currentUsername, char *newUsername) {
  // Re-authenticate the user
  char password[MAX_PASSWORD_LENGTH + 1];
  printf("Enter current password: ");
  fscanf("%s", password);

  if (authenticateUser(currentUsername, password) != 0) {
    printf("Authentication failed.\n");
    return;
  }


  if (strlen(newUsername) < MIN_USERNAME_LENGTH ||
      strlen(newUsername) > MAX_USERNAME_LENGTH) {
    printf("Username must be between %d and %%d characters long.\n",
           MIN_USERNAME_LENGTH, MAX_USERNAME_LENGTH);
    return;
  }


  strcpy(currentUsername, newUsername);



  printf("Username updated to %s.\n", newUsername);
}

void updatePassword(char *username) {
  // Re-authenticate the user
  char currentPassword[MAX_PASSWORD_LENGTH + 1];
  printf("Enter current password: ");
  scanf("%s", currentPassword);

  if (authenticateUser(username, currentPassword) != 0) {
    printf("Authentication failed.\n");
    return;
  }

  // Get the new password from the user
  char newPassword[MAX_PASSWORD_LENGTH + 1];
  printf("Enter new password: ");
  scanf("%s", newPassword);

  // Validate the new password
  if (strlen(newPassword) < MIN_PASSWORD_LENGTH ||
      strlen(newPassword) > MAX_PASSWORD_LENGTH) {
    printf("Password must be between %d and %d characters long.\n",
           MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
    return;
  }

  // Update the password in the user account
  strcpy(currentPassword, newPassword);

  // Save the updated user account to a secure storage
  // ...

  printf("Password updated.\n");
}
void deleteAccount(char *username) {
  // Re-authenticate the user
  char password[MAX_PASSWORD_LENGTH + 1];
  printf("Enter password again to confirm: ");
  scanf("%s", password);

  if (authenticateUser(username, password) != 0) {
    printf("Authentication failed.\n");
    return;
  }

  // Delete the user account from the secure storage
  // ...

  printf("Account deleted.\n");
}
#define MAX_MESSAGE_LENGTH 1024
#define MAX_MESSAGES 100

typedef struct Message {
  char senderUsername[MAX_USERNAME_LENGTH + 1];
  char recipientUsername[MAX_USERNAME_LENGTH + 1];
  char subject[MAX_MESSAGE_LENGTH + 1];
  char body[MAX_MESSAGE_LENGTH + 1];
  time_t timestamp;
} Message;
void sendMessage(char *senderUsername, char *recipientUsername, char *message) {
  // Check if the recipient username exists
  if (findUserAccount(recipientUsername) == NULL) {
    printf("Recipient username not found.\n");

  }
  else

       printf("Message sent to %s.\n", recipientUsername);
}
void checkInbox(char *username) {

  UserAccount *userAccount = findUserAccount(username);

  // If the user account was not found, return an error
  if (userAccount == NULL) {
    printf("User account not found.\n");
    return;
  }

  // Display the user's inbox
  if (userAccount->numMessages == 0) {
    printf("Your inbox is empty.\n");
  } else {
    int choice;
    do {
      printf("\nChoose an option:\n");
      printf("1. View messages sorted by date\n");

      printf("3. Search messages\n");
      printf("4. Back to main menu\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);

      switch (choice) {
        case 1:
          displayMessagesSortedByDate(userAccount);
          break;


        case 3:
          searchMessages(userAccount);
          break;
        case 4:
          break;
        default:
          printf("Invalid choice.\n");
      }
    } while (choice != 4);
  }
}




void displayMessagesSortedByDate(UserAccount *userAccount) {
  // Sort messages by timestamp
  for (int i = 0; i < userAccount->numMessages - 1; i++) {
    for (int j = i + 1; j < userAccount->numMessages; j++) {
      if (userAccount->messages[i].timestamp < userAccount->messages[j].timestamp) {
        Message temp = userAccount->messages[i];
        userAccount->messages[i] = userAccount->messages[j];
        userAccount->messages[j] = temp;
      }
    }
  }

  // Display messages
  for (int i = 0; i < userAccount->numMessages; i++) {
    printf("\nMessage %d:\n", i + 1);
    printf("From: %s\n", userAccount->messages[i].senderUsername);
  }}
  typedef struct Node {
  Message message;
  struct Node *next;
} Node;
typedef struct Message {
  char *sender;
  char *content;
} Message;
void loadMessagesFromFile(UserAccount *userAccount, char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Erreur d'ouverture du fichier %s\n", filename);
    return;
  }

  char line[1024];
  int numMessages = 0;

  // Compter le nombre de messages dans le fichier
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (line[0] == '#') continue; // Ignorer les lignes de commentaire
    numMessages++;
  }

  // Allouer de la mémoire pour les messages
  userAccount->messages = malloc(sizeof(Message *) * numMessages);
  if (userAccount->messages == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    return;
  }

  // Revenir au début du fichier
  fseek(fp, 0, SEEK_SET);

  // Charger les messages dans le tableau
  int i = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (line[0] == '#') continue; // Ignorer les lignes de commentaire

    char *sender = strtok(line, ":");
    char *content = strtok(NULL, "\n");

    Message *message = malloc(sizeof(Message));
    if (message == NULL) {
      printf("Erreur d'allocation de mémoire\n");
      return;
    }

    message->sender = strdup(sender);
    message->content = strdup(content);

    userAccount->messages[i] = message;
    i++;
  }

  userAccount->numMessages = numMessages;

  fclose(fp);
}
void searchMessages(UserAccount *userAccount) {
  char searchTerm[1024];
  printf("Entrez le terme de recherche : ");
  scanf("%s", searchTerm);

  int foundMessages = 0;
  for (int i = 0; i < userAccount->numMessages; i++) {
    if (strstr(userAccount->messages[i]->sender, searchTerm) != NULL ||
        strstr(userAccount->messages[i]->content, searchTerm) != NULL) {
      printf("De : %s\n", userAccount->messages[i]->sender);
      printf("Contenu : %s\n\n", userAccount->messages[i]->content);
      foundMessages++;
    }
  }

  if (foundMessages == 0) {
    printf("Aucun message trouvé pour le terme de recherche '%s'\n", searchTerm);
  }
}






 void main ()
 {UserAccount user;
 char enterkey;

printf("if you want to sign up write s or if you want to log in write l");
scanf("%c",enterkey);
if (enterkey=='s'||enterkey=='S'){
  if (createNewUserAccount(&user) == 0) {
    printf("le compte de l utilisateur  est cree avec succes.\n");
  } else {
    printf("echoue a creer le compte.\n");
  }
 }
 else{  printf("Enter username: ");
  scanf("%s", username);

  printf("Enter password: ");
  scanf("%s", password);
 }
  int result = authenticateUser(username, password);

  if (result == 0) {
    printf("Authentication successful.\n");
    printf("Logged in as %s.\n", username);
  }
  } else {
    printf("Something went wrong .\n");
  }
  char option[7];
printf ("if  you wanna search about someone type search if you wanna update something write up ")
scanf ("%s",option);
if ( option =='up'||option='UP')
 {

  int choice;
  do {
    printf("\nChoose an option:\n");
    printf("1. Update username\n");
    printf("2. Update password\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        updateUsername(username, newUsername);
        break;
      case 2:
        updatePassword(username);
        break;
      case 3:
        break;
      default:
        printf("Invalid choice.\n");
    }
  } while (choice != 3);


 }
