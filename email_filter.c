#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_EMAIL_LENGTH 256
#define MAX_DOMAIN_LENGTH 256

int validate_email(const char *email) {
    if (strchr(email, '@') == NULL) {
        return 0;
    }

    return 1;
}

int check_email_existence(const char *email) {
    char domain[MAX_DOMAIN_LENGTH];
    sscanf(email, "%*[^@]@%255s", domain);

    struct hostent *host = gethostbyname(domain);
    if (host == NULL) {
        printf("Faild to resolve MX record for domain: %s\n", domain);
        return 0;
    }

    struct sockaddr_in sa;
    memcpy(&sa.sin_addr, host->h_addr_list[0], sizeof(struct in_addr));

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Faild to create socket.\n");
        return 0;
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(25);

    if (connect(sock, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
        printf("Failed to connect to mail server\n");
        close(sock);
        return 0;
    }

    char response[512];
    if (recv(sock, response, sizeof(response), 0) == -1) {
        printf("failed to receive response from mail server\n");
        close(sock);
        return 0;
    }

    char ehlo_command[512];
    snprintf(ehlo_command, sizeof(ehlo_command), "EHLO %s\r\n", domain);
    if (send(sock, ehlo_command, strlen(ehlo_command), 0) == -1) {
        printf("Failed to send EHLO command\n");
        close(sock);
        return 0;
    }

     
    if (recv(sock, response, sizeof(response), 0) == -1) {
        printf("failed to receive response from mail server\n");
        close(sock);
        return 0;
    }

    char mail_from_command[512];
    snprintf(mail_from_command, sizeof(mail_from_command), "MAIL FROM: <%s>\r\n", email);
    if (send(sock, mail_from_command, strlen(mail_from_command), 0) == -1) {
        printf("Failed to send MAIL FROM command\n");
        close(sock);
        return 0;
    }

    if (recv(sock, response, sizeof(response), 0) == -1) {
        printf("failed to receive response from mail server\n");
        close(sock);
        return 0;
    }

    const char *quit_command = "QUIT\r\n";
    if (send(sock, quit_command, strlen(quit_command), 0) == -1) {
        printf("Failed to send QUIT command\n");
        close(sock);
        return 0;
    }

    close(sock);

    if (response[0] == '2' && response[1] == '5' && response[2] == '5') {
        return 1;
    } else {
        return 0;
    }

    return 1;
}

void filter_emails(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr,
                "Error opening file: %s\n", 
                filename);
        return; 
    }

    FILE *validFile = fopen("./output/valid_emails.txt", "w");
    if (validFile == NULL) {
        fprintf(stderr,
                "Error creating ./output/valid_emails.txt\n");
        fclose(file);
        return;
    }

    FILE *invalidFile = fopen("./output/invalid_emails.txt", "w");
    if (invalidFile == NULL) {
        fprintf(stderr,
                "Error creating ./output/invalid_emails.txt\n");
        fclose(file);
        fclose(validFile);
        return;
    }

    char email[MAX_EMAIL_LENGTH];
    while (fgets(email, MAX_EMAIL_LENGTH, file) != NULL) {
        // Remove trailing newline character, if present
        email[strcspn(email, "\n")] = '\0';

        if (validate_email(email)) {
            if (check_email_existence(email)) {
                fprintf(validFile, "%s\n", email);
            } else {
                fprintf(invalidFile, "%s\n", email);
            }
        } else {
            fprintf(invalidFile, "%s\n", email);
        }
    }

    fclose(file);
    fclose(validFile);
    fclose(invalidFile);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s email_list.txt\n", argv[0]);
        return 0;
    }

    filter_emails(argv[1]);

    printf("Email filtering completed successfully.\n");

    return 1;
}
