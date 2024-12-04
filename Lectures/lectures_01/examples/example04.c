#include <unistd.h>
#include <fcntl.h>
int main(){
    int filedesc = open("testfile.txt", O_WRONLY | O_APPEND);
    if(filedesc < 0)
        return 1;
    if(write(filedesc,"Output to testfile.txt\n", 23) != 23){
        write(2,"Error writing to testfile.txt\n",30);
        return 1;
    }
    close(filedesc);
    return 0;
}
