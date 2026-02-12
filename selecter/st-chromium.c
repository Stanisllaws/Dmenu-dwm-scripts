#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    FILE *menu;
    char choice[64];

    /* Start dwm */
    if (fork() == 0) {
        execlp("dwm", "dwm", NULL);
        perror("dwm");
        exit(1);
    }

    /* Give dwm time to start */
    sleep(1);

    /* Open dmenu */
    menu = popen(
        "printf \"firefox\nchromium-browser\nbrave-browser\n\" | dmenu -p \"Launch:\"",
        "r"
    );

    if (!menu)
        return 1;

    fgets(choice, sizeof(choice), menu);
    pclose(menu);

    /* Remove newline */
    choice[strcspn(choice, "\n")] = 0;

    if (choice[0] == '\0')
        return 0;

    /* Launch selected program */
    if (fork() == 0) {
        execlp(choice, choice, NULL);
        perror(choice);
        exit(1);
    }

    return 0;
}

