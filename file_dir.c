#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

// 인수로 전달 받은 디렉토리의 하위 디렉토리를 출력하는 함수.
void subdirOutput(char *wd);

// 디렉토리 들여쓰기를 위한 디렉토리 경로 레벨 저장용.
int indent = 0;

int main()
{
    printf("Sub-Directory Ouput!!!\n");
    printf("----------------------\n");

 

    // /user 디렉토리의 하위 디렉토리를 출력시킨다.
    subdirOutput("/usr");

 

    return 0;
}

 

void subdirOutput(char *wd)
{
    struct dirent *dentry;
    struct stat fstat;
    DIR *dirp;
    int i;

 

    // 인수로 전달받은 디렉토리로 이동한다.
    if(chdir(wd) < 0) {
        printf("error: chdir..\n");
        exit(1);
    }

 

    // 이동한 현재 디렉토리를 연다.
    if((dirp = opendir(".")) == NULL) {
        printf("error: opendir..\n");
        exit(1);
    }

 

    // 열린 디렉토리의 모든 항목을 읽는다.
    while(dentry = readdir(dirp)) {

 

        // 디렉토리의 항목의 아이노드번호가 0 아닌 것을 찾는다.
         // 아이노드번호가 0 이면 그 항은 삭제가 된 것이다.
         if(dentry->d_ino != 0) {

 

            // 읽어혼 항목중 "."(현재디렉토리)와 ".."(부모디렉토리)는 건너뛴다.
            // 이는 하위 디렉토리를 출력하는 것이기 때문에 제외하는 것이다.
            if((!strcmp(dentry->d_name, ".")) || (!strcmp(dentry->d_name, "..")))
                continue;

 

            // 현재 항목의 상태정보를 가져온다.
            stat(dentry->d_name, &fstat);

 

            // 하위 디렉토리의 출력을 보기 좋게 하기 위해서
            // 디렉토리 경로 레벨별로 Tab으로 구분한다.
            for(i = 0; i < indent; i++)
                printf("\t");
   
            // 현재 항목의 상태가 디렉토리일 경우 
            // 항목명을 출력하고 디렉토리 경로 레벨을 증가시킨 후
            // subdirOutput함수를 재귀 호출하면서 현재 항목명을 인수로 전달한다.
            if(S_ISDIR(fstat.st_mode)) {
                printf("%s\n", dentry->d_name);
                indent++;
                subdirOutput(dentry->d_name);
   
            // 현재 항목의 상태가 디렉토리가 아닐 경우
            // 디렉토리명을 보기 좋게 출력하기 위해
            // Tab으로 이동시킨 커서를 되돌린다.
            } else {
                printf("\r");
            }
        }
    }

 

    // 열린 현재 디렉토리의 사용이 끝났으므로 닫아준다.
    // 인수로 전달받은 디렉토리의 하위 디렉토리 출력이 끝났으므로 
    // 디렉토리 경로 레벨을 감소 시킨후 부모 디렉토리로 이동한다.
    closedir(dirp);
    indent--;
    chdir("..");
}
