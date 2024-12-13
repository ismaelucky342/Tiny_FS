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
    int entradadir;
    int grabardatos;
    FILE *fent;
    
    // Lectura del fichero completo de una sola vez
    // TODO ...
    fent = fopen("particion.bin", "r+b");
    if (fent == NULL) {
        perror("Error opening file");
        return 1;
    }
    fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);
        return 1;
    memcpy(directorio, (EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
    memcpy(&directorio, (EXT_ENTRADA_DIR *)&datosfich[3], SIZE_BLOQUE);
    memcpy(&ext_bytemaps, (EXT_BLQ_INODOS *)&datosfich[1], SIZE_BLOQUE);
    memcpy(&ext_blq_inodos, (EXT_BLQ_INODOS *)&datosfich[2], SIZE_BLOQUE);
    memcpy(&memdatos, (EXT_DATOS *)&datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);
    
    // Bucle de tratamiento de comandos
    for (;;)
    {
        do
        {
            printf (">> ");
            fflush(stdin);
            fgets(comando, LONGITUD_COMANDO, stdin);
        } while (ComprobarComando(comando, orden, argumento1, argumento2) != 0);
        
        if (strcmp(orden, "dir") == 0) {
            Directorio(directorio, &ext_blq_inodos);
            Directorio(directorio, &ext_blq_inodos);
            continue;
            }
        }
        else if (strcmp(orden, "rename") == 0) {
            Rename(argumento1, argumento2, directorio, &ext_blq_inodos);
            Rename(argumento1, argumento2, &directorio, &ext_blq_inodos);
        }
        else if (strcmp(orden, "remove") == 0) {
            Remove(argumento1, directorio, &ext_blq_inodos);
            Remove(argumento1, &directorio, &ext_blq_inodos);
        }
        else if (strcmp(orden, "copy") == 0) {
            Copy(argumento1, argumento2, directorio, &ext_blq_inodos, memdatos);
            Copy(argumento1, argumento2, &directorio, &ext_blq_inodos, &memdatos);
        }
        else if (strcmp(orden, "salir") == 0) {
            GrabarDatos(memdatos, fent);
            GrabarDatos(&memdatos, fent);
            fclose(fent);
            printf(COLOR_GREEN "Saliendo del sistema..." COLOR_RESET "\n");
            return 0;
        }
        else
        {
            printf(COLOR_RED "Comando desconocido: %s" COLOR_RESET "\n", orden);
        }

        GrabarInodosyDirectorio(directorio, &ext_blq_inodos, fent);
        GrabarInodosyDirectorio(&directorio, &ext_blq_inodos, fent);
        GrabarByteMaps(&ext_bytemaps, fent);
        GrabarSuperBloque(&ext_superblock, fent);
        if (grabardatos)
            GrabarDatos(&memdatos, fent);
        grabardatos = 0;
    }

