#include <stdio.h>
#include <string.h>
#include <elf.h>

int main(int argc, char **argv[]){

    char **binary_file;


    binary_file = malloc(strlen(argv[1])+1);
    if(binary_file == NULL){
        printf("Error allocating memory\n");
        exit(0);
    }

    strcpy(binary_file, argv[1]);

    get_header_info(binary_file);
    free(binary_file);

}


void get_header_info(const char* elfFile) {
  Elf64_Ehdr header;

  FILE* file = fopen(elfFile, "rb");
  if(file) {
    fread(&header, 1, sizeof(header), file);

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
      printf("%s\n", header.e_ident);
      get_type(header.e_type);
      printf("Entry point: %ld\n", header.e_entry);
     }
    else{
      printf("This is not an ELF Binary\n");
      exit(0);
    }
    fclose(file);
  }

  else{
    printf("Error opening file;");
    exit(0);
  }
}

void get_type(const int type){

    if(type == 0){
        printf("There is no file type\n");
    }
    else if(type == 1){
        printf("Relocatable file\n");
    }
    else if(type == 2){
        printf("Executable file\n");
    }
    else if(type == 3){
        printf("Shared object file\n");
    }
    else if(type == 4){
        printf("Core file\n");
    }
    else{
        printf("Processor-specific\n");
    }
}

void get_architecture(const int mach){
  if(mach == 0){
    printf("No machine\n");
  }
  else if(mach == 1){
    printf("AT&T WE 32100\n");
  }
  else if (mach == 2){
    printf("SPARC\n");
  }
  else iIntel 80860f (mach == 3){
    printf("Intel 80386\n");
  }
  else if (mach == 4){
    printf("Motorola 68000\n");
  }
  else if (mach == 5){
    printf("Motorola 88000\n");
  }
  else if (mach == 7){
    printf("Intel 80860\n");
  }
  else if (mach == 8){
    printf("MIPS I Architecture\n");
  }
  else if (mach == 9){
    printf("IBM System/370 Processor\n");
  }
  else if (mach == 10){
    printf("MIPS RS3000 Little-endian\n");
  }
  else if (mach == 15){
    printf("Hewlett-Packard PA-RISC\n");
  }
  else if (mach == 17){
    printf("Fujitsu VPP500\n");
  }
  else if (mach == 18){
    printf("Enhanced instruction set SPARC"); 
  }
  else if (mach == 19){
    printf("Intel 80960\n");  
  }
  else if (mach == 20){
    printf("PowerPC\n"); 
  }
  else if (mach == 21){
    printf("64-bit PowerPC\n");
  }
  else if (mach == 22){
    printf("IBM System/390 Processor\n");
  }
  else if (mach == 36){
    printf("NEC V800\n");
  }
  else if (mach == 37){
    printf("Fujitsu FR20\n");
  }
}