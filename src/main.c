#include "hexdump.h"

static void usage(const char* prog){
    fprintf(stderr,
    "usage: %s [-w 8|16|32] [-n bytes] [-o offset] [-A] <file>\n"
      "  -w   bytes per line (default 16)\n"
      "  -n   limit total bytes to read\n"
      "  -o   start offset (seek)\n"
      "  -A   hide ascii column\n",
      prog);
}

static int parse_size(const char* s, size_t *out){
    //supports plain numbers;
    char* end=NULL;
    unsigned long long v = strtoull(s,&end,10);

    if(!s[0] || (end && *end )) return 0;

    *out=(size_t)v;
    return 1;
}
int main(int argc, char* argv[]){
    const char* path=NULL;
    size_t width=16;
    size_t limit=(size_t)-1; //unlimited by default
    size_t start=0;
    int show_ascii=1;

    //parse command line arguments
    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i], "-w")&&i+1<argc){
            size_t w=(size_t)strtoul(argv[++i],NULL,10);
            if (!(w == 8 || w == 16 || w == 32)) { 
                usage(argv[0]); 
                return 1; 
            }
            width = w;
        }
        else if(!strcmp(argv[i],"-n")&&i+1<argc){
            if(!parse_size(argv[++i],&limit)){
                usage(argv[0]); 
                return 1; 
            }
        }
        else if(!strcmp(argv[i],"-o")&&i+1<argc){
            if(!parse_size(argv[++i],&start)){
                usage(argv[0]);
                return 1;
            }
        }
        else if(!strcmp(argv[i],"-A")){
            show_ascii=0;
        }
        else if(path){
            usage(argv[0]);
            return 1;
        }
        else{
            path=argv[i];
        }
    }

    //verify we have a file path
    if(!path){
        usage(argv[0]);
        return 1;
    }

    //open input file in binary mode
    FILE* f=fopen(path,"rb");
    if(!f){
        fprintf(stderr, "error: cannot open '%s': %s\n",path, strerror(errno));
        return 1;
    }

    //seek to starting offset if requested
    if(start){
        if(fseek(f,(long long)start,SEEK_SET)!=0){
            fprintf(stderr,"error: cannot seek to %zu: %s\n",start,strerror(errno));
            fclose(f);
            return 1;
        }
    }

    //allocate buffer for one line of input
    unsigned char* buf=(unsigned char*)malloc(width);
    if(!buf){
        fprintf(stderr,"error: cannot allocate memory\n",start,strerror(errno));
        fclose(f);
        return 1;
    }

    //track current position and bytes processed
    size_t offset=start;
    size_t seen=0;

    //main processing loop
    while(seen<limit){
        size_t want=width;
        if(limit-seen<want) want=limit-seen;

        size_t n=fread(buf,1,want,f);
        if(n==0) break;

        print_line(offset, buf, n, width,show_ascii);
        offset+=n;
        seen+=n;
        if(n<want) break; //end of file
    }

    //cleanup
    free(buf);
    fclose(f);
    return 0;
}