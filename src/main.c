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

#include "../includes/tiny_fs.h"

#define LONGITUD_COMANDO 100

int main()
{
    char comando[LONGITUD_COMANDO];
    char orden[LONGITUD_COMANDO];
    char argumento1[LONGITUD_COMANDO];
    char argumento2[LONGITUD_COMANDO];
    
    EXT_SIMPLE_SUPERBLOCK ext_superblock;
    EXT_BYTE_MAPS ext_bytemaps;
    EXT_BLQ_INODOS ext_blq_inodos;
    EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
    EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
    EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
    int grabardatos = 0;
    FILE *fent;
    
    // Lectura del fichero completo de una sola vez
    fent = fopen("particion.bin", "r+b");
    if (fent == NULL) {
        perror("Error opening file");
        return 1;
    }
    fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);
    memcpy(&ext_superblock, &datosfich[0], SIZE_BLOQUE);
    memcpy(&ext_bytemaps, &datosfich[1], SIZE_BLOQUE);
    memcpy(&ext_blq_inodos, &datosfich[2], SIZE_BLOQUE);
    memcpy(directorio, &datosfich[3], MAX_FICHEROS * sizeof(EXT_ENTRADA_DIR));
    memcpy(memdatos, &datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);
    
    // Bucle de tratamiento de comandos
    for (;;)
    {
        do
        {
            printf(">> ");
            fflush(stdin);
            fgets(comando, LONGITUD_COMANDO, stdin);
        } while (ComprobarComando(comando, orden, argumento1, argumento2) != 0);
        
        if (strcmp(orden, "dir") == 0) {
            Directorio(directorio);
        }
        else if (strcmp(orden, "rename") == 0) {
            Renombrar(directorio, &ext_blq_inodos, argumento1, argumento2);
        }
        else if (strcmp(orden, "remove") == 0) {
            Borrar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
        }
        else if (strcmp(orden, "copy") == 0) {
            Copiar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, memdatos, argumento1, argumento2, fent);
        }
        else if (strcmp(orden, "salir") == 0) {
            GrabarDatos(memdatos, fent);
            fclose(fent);
            printf(COLOR_GREEN "Saliendo del sistema..." COLOR_RESET "\n");
            return 0;
        }
        else
        {
            printf(COLOR_RED "Comando desconocido: %s" COLOR_RESET "\n", orden);
        }

        GrabarInodosyDirectorio(directorio, &ext_blq_inodos, fent);
        GrabarByteMaps(&ext_bytemaps, fent);
        GrabarSuperBloque(&ext_superblock, fent);
        if (grabardatos)
            GrabarDatos(memdatos, fent);
        grabardatos = 0;
    }
}

