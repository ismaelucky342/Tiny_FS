/***************************************************************************************/
/*                                                                                     */
/*                                         ██╗   ██╗   ████████╗ █████╗ ██████╗        */
/*      TINY_FS                            ██║   ██║   ╚══██╔══╝██╔══██╗██╔══██╗       */
/*                                         ██║   ██║█████╗██║   ███████║██║  ██║       */
/*      created:        12/12/2024         ██║   ██║╚════╝██║   ██╔══██║██║  ██║       */
/*      last change:    12/12/2024         ╚██████╔╝      ██║   ██║  ██║██████╔╝       */
/*                                          ╚═════╝       ╚═╝   ╚═╝  ╚═╝╚═════╝        */
/*                                                                                     */
/*       Ismael Hernandez Clemente              ismael.hernandez@live.u-tad.com        */
/*                                                                                     */
/*       Izhan Sastre Hernando                  izhan.sastre@live.u-tad.com            */
/*                                                                                     */
/***************************************************************************************/

#ifndef TINY_FS
#define TINY_FS

/*=======================================INCLUDES AREA==========================================*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*=======================================DEFINES AREA==========================================*/

#define SIZE_BLOQUE 512
#define MAX_INODOS 24
#define MAX_FICHEROS 20
#define MAX_BLOQUES_DATOS 96
#define PRIM_BLOQUE_DATOS 4
#define MAX_BLOQUES_PARTICION MAX_BLOQUES_DATOS + PRIM_BLOQUE_DATOS        //superbloque + bytemap inodos y bytemap bloques + inodos + directorio
#define MAX_NUMS_BLOQUE_INODO 7
#define LEN_NFICH 17
#define NULL_INODO 0xFFFF
#define NULL_BLOQUE 0xFFFF

/*==========================================COLORS=============================================*/

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

/*=======================================STRUCTS AREA==========================================*/

/* Estructura del superbloque */
typedef struct {
        unsigned int s_inodes_count;                        /* inodos de la partición */
        unsigned int s_blocks_count;                        /* bloques de la partición */
        unsigned int s_free_blocks_count;                /* bloques libres */
        unsigned int s_free_inodes_count;                /* inodos libres */
        unsigned int s_first_data_block;                /* primer bloque de datos */
        unsigned int s_block_size;                                /* tamaño del bloque en bytes */
        unsigned char s_relleno[SIZE_BLOQUE - 6 * sizeof(unsigned int)];        /* relleno a 0's*/
} EXT_SIMPLE_SUPERBLOCK;

/* Bytemaps, caben en un bloque */
typedef struct {
        unsigned char bmap_bloques[MAX_BLOQUES_PARTICION];
        unsigned char bmap_inodos[MAX_INODOS];  /* inodos 0 y 1 reservados, inodo 2 directorio */
        unsigned char bmap_relleno[SIZE_BLOQUE - (MAX_BLOQUES_PARTICION + MAX_INODOS) * sizeof(char)];
} EXT_BYTE_MAPS;

/* inodo */
typedef struct {
        unsigned int size_fichero;
        unsigned short int i_nbloque[MAX_NUMS_BLOQUE_INODO];
} EXT_SIMPLE_INODE;

/* Lista de inodos, caben en un bloque */
typedef struct {
        EXT_SIMPLE_INODE blq_inodos[MAX_INODOS];
        unsigned char blq_relleno[SIZE_BLOQUE - MAX_INODOS * sizeof(EXT_SIMPLE_INODE)];
} EXT_BLQ_INODOS;

/* Entrada individual del directorio */
typedef struct {
        char dir_nfich[LEN_NFICH];
        unsigned short int dir_inodo;
} EXT_ENTRADA_DIR;

/* Bloque de datos */
typedef struct {
        unsigned char dato[SIZE_BLOQUE];
} EXT_DATOS;

/*=======================================FUNCTIONS AREA==========================================*/

/*------------------------------------------bytemaps.c-------------------------------------------*/

void        Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps);
void        GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich);

/*------------------------------------------data_block.c-------------------------------------------*/

void        GrabarDatos(EXT_DATOS *memdatos, FILE *fich);

/*---------------------------------------------inode.c---------------------------------------------*/

int                BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre);
int                Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo);
void        GrabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich);

/*----------------------------------------superblock.c---------------------------------------------*/

void        LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);
void        GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);

/*------------------------------------------directory.c--------------------------------------------*/

void        Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos);
int                Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre);

/*--------------------------------------file_operations.c------------------------------------------*/

int                ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
int                Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
                        EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre,  FILE *fich);
int                Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
                        EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino,  FILE *fich);


#endif