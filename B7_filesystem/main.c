#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {    
    if (argc != 2) {
        printf("Loi: Ban nhap sai cu phap!\n");
        printf("Huong dan su dung (Usage): %s <file_path>\n", argv[0]);
        return 1; 
    }
    
    printf("Chuc mung! Ban da nhap dung.\n");
    printf("He thong chuan bi kiem tra file: %s\n", argv[1]);

    struct stat file_info = {0}; 
    if (lstat(argv[1], &file_info) == -1) {
        printf("Loi: Khong the truy xuat thong thong tin file.\n");
        return 1; 
    }

    printf("File Path: %s\n", argv[1]);
    
    printf("File Type: ");
    if(S_ISREG(file_info.st_mode)){
        printf("Regular file\n");
    }else if(S_ISDIR(file_info.st_mode)){
        printf("Directory\n");
    }else if(S_ISLNK(file_info.st_mode)){
        printf("Symbolic Link\n");
    }else{
        printf("Other file\n");
    }
    
    printf("Size: %ld bytes\n", file_info.st_size);
    printf("Time: %s", ctime(&file_info.st_mtime));
    
    return 0; 
}