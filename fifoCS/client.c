#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int wfd = open("mypipe", O_WRONLY);
    if(wfd < 0){
        perror("open");
        exit(1);
    }
    
    /* read(int fd, void* buf, size_t count)
     * write(int fd, void* data, size_t count)
     * read的count参数代表buf所最多容纳的大小
     * write的count代表要写入数据data的大小*/
    char buf[1024] = {0};
    while(1){
        printf("please enter : ");
        fflush(stdout);
        ssize_t read_count = read(0, buf, sizeof(buf)-1);
        if(read_count > 0){
            buf[read_count] = '\0';
            write(wfd, buf, strlen(buf));
        }else if(read_count <= 0){
            perror("read");
            exit(1);
        }
    }
    close(wfd);
    return 0;
}
