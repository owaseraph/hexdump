#include "hexdump.h"


int main(int argc, char* argv[]){
    if(argc<2){
        fprintf(stderr, "usage: %s <file>\n", (argc > 0 ? argv[0] : "hexdump"));
        return 1;
    }
    const char* path=argv[1];

    FILE* f=fopen(path,"rb");
    if(!f){
        fprintf(stderr,"error: cannot open '%s': '%s'\n",path,strerror(errno));
        return 1; /* avoid using a NULL FILE* */
    }

    unsigned char buf[BYTES_PER_LINE];
    size_t offset=0;
    for(;;){
        size_t n=fread(buf,1,BYTES_PER_LINE,f);
        if(n==0) break;
        print_line(offset,buf,n);
        offset+=n;
        if(n<BYTES_PER_LINE) break;
    }

    fclose(f);
    return 0;
}