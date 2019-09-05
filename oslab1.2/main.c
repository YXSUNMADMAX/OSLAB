#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

//#define SIZES 10000
int buf[400000000]={0};    //以我的计算机为例，数组目前仅开到40000000个整数（仍有扩展空间极限约为4亿），即sizemax=160000000
                          //出于偷懒的角度没有使用链表动态分配但是进行了边界处理，可以应对生成器-o 参数 1-1600000（手动滑稽）
                          //由于老师的generator性能在开到这个数量级时已经有极大的延时而本程序并无较大延时，因此静态数组可以保证性能
                          //而到达4亿后，其延迟将是无法承受的（动态数组也一样）
int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}


int get_file_size(int f)
{
    struct stat st;
    fstat(f, &st);
    return st.st_size;
}

int main(int argc,char *argv[])
{
    int fd,fp,size;
    if(argc<2)
    {
        fprintf(stderr,"Usage:%s Filename\n",argv[0]);
        exit(1);
    }
    fd=open(argv[1],O_RDONLY);
    int SIZES=get_file_size(fd);
    if(fd<0)
    {
        fprintf(stderr,"Fail to open file\n");
        exit(2);
    }
    else
    {
        size=read(fd,buf,SIZES);
        //revert=(int*)buf1;
        if(size<0)
        {
            fprintf(stderr,"Fail to read file\n");
            exit(3);
        }
        else
        {
            printf("From File %s Read %d bytes\n",argv[1],size);
            int i;
            for(i=0;i<size/4;i++)
            {
                printf("%d ",buf[i]);
            }
            printf("\n");
            qsort(buf+1, size/4-1, sizeof(int), cmpfunc);//key 没有进入排序 排序后仍保留在首位
            for(i=0;i<size/4;i++)
            {
                fprintf(stdout,"%d ",buf[i]);
            }
            printf("\n");
        }

        close(fd);
    }
    //fp=open(argv[2],O_WRONLY|O_CREAT);
    fp=open(argv[2],O_WRONLY);
    if(fd<0)
    {
        fprintf(stderr,"Fail to open file\n");
        exit(2);
    }
    else
    {
        int size1=-1;
        size1=write(fp,buf,size);
        //revert=(int*)buf1;
        if(size1<0)
        {
            fprintf(stderr,"Fail to write file\n");
            exit(3);
        }
        else
        {
            fprintf(stdout,"SUCCEED\n");
        }
        close(fp);
    }
    printf("%d\n",SIZES);
    return 0;
}