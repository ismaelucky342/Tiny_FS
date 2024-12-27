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

/**
 * Directorio - Muestra los nombres de los archivos en un directorio.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 */
void Directorio(EXT_ENTRADA_DIR *directorio)
{
    if (directorio == NULL) {
        fprintf(stderr, COLOR_RED "Error: Null pointer argument\n" COLOR_RESET);
        return;
    }

    printf("Directorio:\n");
    int i = 1;
    while (i < MAX_FICHEROS)
    {
        if (directorio[i].dir_inodo != NULL_INODO)
            printf("%i: %s\n", i, directorio[i].dir_nfich);
        i++;
    }
}


/**
 * Imprimir - Imprime los datos de un archivo basado en su nombre.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param memdatos: Puntero a la estructura de datos que contiene los datos de los bloques.
 * @param nombre: Nombre del archivo que se desea imprimir.
 *
 * @return -1 si no se encuentra el archivo, 0 en caso de éxito.
 */
int Imprimir(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_DATOS *memdatos, char *nombre)
{
    int inodo_index = -1;
    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (strcmp(directorio[i].dir_nfich, nombre) == 0)
        {
            inodo_index = directorio[i].dir_inodo;
            break;
        }
    }

    if (inodo_index == -1)
    {
        printf(COLOR_RED "Error: File not found\n" COLOR_RESET);
        return -1;
    }

    EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[inodo_index];
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++)
    {
        if (inodo->i_nbloque[i] != NULL_BLOQUE)
            printf("%s", memdatos[inodo->i_nbloque[i]].dato);
    }
    printf("\n");
    return 0;
}
