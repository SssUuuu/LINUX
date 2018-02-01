#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    umask(0);
    if(mkfifo("mypipe", 0644) < 0){
        perror("mkfifo");
        exit(1);
    }

    int rfd = open("mypipe", O_RDONLY);
    if(rfd < 0){
        perror("open");
        exit(1);
    }

    char buf[1024] = {0};
    while(1){
        printf("please wait...\n");
        ssize_t read_count = read(rfd, buf, sizeof(buf)-1);
        if(read_count > 0){
            buf[read_count] = '\0';
            printf("client say : %s", buf);
        }else if(read_count == 0){
            printf("client quit, read to exit!\n");
            exit(0);
        }else{
            perror("read");
            exit(1);
        }
    }

    close(rfd);
    return 0;
}
