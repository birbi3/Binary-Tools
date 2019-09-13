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
  Elf64_Shdr sec_header;
  char* sec_name;
  int sec_index;
  long text_index;
  char **text_beg = ".text";
  char **text_end = ".rodata";
  long text_beg_off;
  long text_end_off; 

  FILE* file = fopen(elfFile, "rb");
  if(file) {
    fread(&header, 1, sizeof(header), file);

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0) {
      /*dumps ELF header info */
      printf("%s\n", header.e_ident);
      get_type(header.e_type);
      printf("Entry point: %ld\n", header.e_entry);
      printf("Architecture: ");
      get_architecture(header.e_machine);

      fseek(file, header.e_shoff + header.e_shstrndx * sizeof(sec_header), SEEK_SET);
      fread(&sec_header, 1, sizeof(sec_header), file);

      sec_name = malloc(sec_header.sh_size);
      fseek(file, sec_header.sh_offset, SEEK_SET);
      fread(sec_name, 1, sec_header.sh_size, file);

      /*Dumps all section header info */
      for (sec_index = 0; sec_index < header.e_shnum; sec_index++){
        const char* name = "";
        fseek(file, header.e_shoff + sec_index * sizeof(sec_header), SEEK_SET);
        fread(&sec_header, 1, sizeof(sec_header), file);

        if (sec_header.sh_name){
          name = sec_name + sec_header.sh_name;
        }
        /*grabs offset of .text and .rodata */
        if (strcmp(name,text_beg) == 0){
          text_beg_off = sec_header.sh_offset;
        }
        else if (strcmp(name, text_end) == 0){
          text_end_off = sec_header.sh_offset;
        }
        printf("%2u %s %ld\n", sec_index, name, sec_header.sh_offset);
        
      }
        /* design a structure that can store the data of each .text line. Will have to go 
      do more research on how that data is structured */
      fseek(file, text_beg_off , SEEK_SET);
      for(text_index = text_beg_off; sec_index < text_end_off; sec_index++){
        fseek(file, text_index, SEEK_SET);
        fread()
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
  if(mach == 0){printf("No machine\n");}
  else if(mach == 1){printf("AT&T WE 32100\n");}
  else if (mach == 2){printf("SPARC\n");}
  else if (mach == 3){printf("Intel 80386\n");}
  else if (mach == 4){printf("Motorola 68000\n");}
  else if (mach == 5){printf("Motorola 88000\n");}
  else if (mach == 7){printf("Intel 80860\n");}
  else if (mach == 8){printf("MIPS I Architecture\n");}
  else if (mach == 9){printf("IBM System/370 Processor\n");}
  else if (mach == 10){printf("MIPS RS3000 Little-endian\n");}
  else if (mach == 15){printf("Hewlett-Packard PA-RISC\n");}
  else if (mach == 17){printf("Fujitsu VPP500\n");}
  else if (mach == 18){printf("Enhanced instruction set SPARC");}
  else if (mach == 19){printf("Intel 80960\n");}
  else if (mach == 20){printf("PowerPC\n");}
  else if (mach == 21){printf("64-bit PowerPC\n");}
  else if (mach == 22){printf("IBM System/390 Processor\n");}
  else if (mach == 36){printf("NEC V800\n");}
  else if (mach == 37){printf("Fujitsu FR20\n");}
  else if (mach == 38){printf("TRW RH-32\n");}
  else if (mach == 39){printf("Motorola RCE\n");}
  else if (mach == 40){printf("Advanced RISC Machines ARM\n");} 
  else if (mach == 41){printf("Digital Alpha\n");}
  else if (mach == 42){printf("Hitachi SH\n");}
  else if (mach == 43){printf("SPARC Version 9");}
  else if (mach == 44){printf("Siemens TriCore embedded processor\n");}
  else if (mach == 45){printf("Argonaut RISC Core, Argonaut Technologies Inc.\n");}
  else if (mach == 46){printf("Hitachi H8/300\n");}
  else if (mach == 47){printf("Hitachi H8/300H\n");}
  else if (mach == 48){printf("Hitachi H8S\n");}
  else if (mach == 49){printf("Hitachi H8/500");}
  else if (mach == 50){printf("Intel IA-64 processor architecture");}
  else if (mach == 51){printf("Stanford MIPS-X\n");}
  else if (mach == 52){printf("Motorola ColdFire\n");}
  else if (mach == 53){printf("Motorola M68HC12\n");}
  else if (mach == 54){printf("Fujitsu MMA Multimedia Accelerator\n");}
  else if (mach == 55){printf("Siemens PCP\n");}
  else if (mach == 56){printf("Sony nCPU embedded RISC processor\n");}
  else if (mach == 57){printf("Denso NDR1 microprocessor\n");}
  else if (mach == 58){printf("Motorola Star*Core processor\n");}
  else if (mach == 59){printf("Toyota ME16 processor\n");}
  else if (mach == 60){printf("STMicroelectronics ST100 processor\n");}
  else if (mach == 61){printf("Advanced Logic Corp. TinyJ embedded processor family\n");}
  else if (mach == 62){printf("AMD x86-64 architecture\n");}
  else if (mach == 63){printf("Sony DSP Processor\n");}
  else if (mach == 64){printf("Digital Equipment Corp. PDP-10\n");}
  else if (mach == 65){printf("Digital Equipment Corp. PDP-11\n");}
  else if (mach == 66){printf("Siemens FX66 microcontroller\n");}
  else if (mach == 67){printf("STMicroelectronics ST9+ 8/16 bit microcontroller\n");}
  else if (mach == 68){printf("STMicroelectronics ST7 8-bit microcontroller\n");}
  else if (mach == 69){printf("Motorola MC68HC16 Microcontroller\n");}
  else if (mach == 70){printf("Motorola MC68HC11 Microcontroller\n");}
  else if (mach == 71){printf("Motorola MC68HC08 Microcontroller\n");}
  else if (mach == 72){printf("Motorola MC68HC05 Microcontroller");}
  else if (mach == 73){printf("Silicon Graphics SVx\n");}
  else if (mach == 74){printf("STMicroelectronics ST19 8-bit microcontroller\n");}
  else if (mach == 75){printf("Digital VAX\n");}
  else if (mach == 76){printf("Axis Communications 32-bit embedded processor\n");}
  else if (mach == 77){printf("Infineon Technologies 32-bit embedded processor\n");}
  else if (mach == 78){printf("Element 14 64-bit DSP Processor\n");}
  else if (mach == 79){printf("LSI Logic 16-bit DSP Processor\n");}
  else if (mach == 80){printf("Donald Knuth's educational 64-bit processor");}
  else if (mach == 81){printf("Harvard University machine-independent object files\n");}
  else if (mach == 82){printf("SiTera Prism\n");}
  else if (mach == 83){printf("Atmel AVR 8-bit microcontroller\n");}
  else if (mach == 84){printf("Fujitsu FR30");}
  else if (mach == 85){printf("Mitsubishi D10V\n");}
  else if (mach == 86){printf("Mitsubishi D30V\n");}
  else if (mach == 87){printf("NEC v850\n");}
  else if (mach == 88){printf("Mitsubishi M32R\n");}
  else if (mach == 89){printf("Matsushita MN10300\n");}
  else if (mach == 90){printf("Matsushita MN10200\n");}
  else if (mach == 91){printf("picoJava\n");}
  else if (mach == 92){printf("OpenRISC 32-bit embedded processor\n");}
  else if (mach == 93){printf("ARC Cores Tangent-A5\n");}
  else if (mach == 94){printf("Tensilica Xtensa Architecture\n");}
  else if (mach == 95){printf("Alphamosaic VideoCore processor\n");}
  else if (mach == 96){printf("Thompson Multimedia General Purpose Processor\n");}
  else if (mach == 97){printf("National Semiconductor 32000 series\n");}
  else if (mach == 98){printf("Tenor Network TPC processor\n");}
  else if (mach == 99){printf("Trebia SNP 1000 processor\n");}
  else if (mach == 100){printf("STMicroelectronics (www.st.com) ST200 microcontroller\n");}
  else{printf("Unknown\n");}
}