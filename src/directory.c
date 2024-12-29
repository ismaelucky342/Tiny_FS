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
/***************************************************************************************/

#include "../includes/tiny_fs.h"

/**
 * Directorio - Muestra los nombres de los archivos en un directorio.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 */
void Directorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos)
{
    if (directorio == NULL || inodos == NULL) {
        ft_perror ("Error: Null pointer argument\n" );
        return;
    }

    ft_printf("Directorio:\n");
    int i = 1;
    while (i < MAX_FICHEROS)
    {
        if (directorio[i].dir_inodo != NULL_INODO) {
            EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[directorio[i].dir_inodo];
            ft_printf("%i: %s, Tamaño: %d, Inodo: %d, Bloques: ", i, directorio[i].dir_nfich, inodo->size_fichero, directorio[i].dir_inodo);
            for (int j = 0; j < MAX_NUMS_BLOQUE_INODO; j++) {
                if (inodo->i_nbloque[j] != NULL_BLOQUE) {
                    ft_printf("%d ", inodo->i_nbloque[j]);
                }
            }
            ft_printf("\n");
        }
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
        if (ft_strcmp(directorio[i].dir_nfich, nombre) == 0)
        {
            inodo_index = directorio[i].dir_inodo;
            break;
        }
    }

    if (inodo_index == -1)
    {
        ft_printf(COLOR_RED "Error: File not found\n" );
        return -1;
    }

    EXT_SIMPLE_INODE *inodo = &inodos->blq_inodos[inodo_index];
    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++)
    {
        if (inodo->i_nbloque[i] != NULL_BLOQUE)
            ft_printf("%s", memdatos[inodo->i_nbloque[i]].dato);
    }
    ft_printf("\n");
    return 0;
}
