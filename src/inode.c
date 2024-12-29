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

#ifndef MAX_NFICH
#define MAX_NFICH 255 // Define MAX_NFICH if not already defined
#endif

/**
 * BuscaFich - Busca un archivo en el directorio y devuelve su inodo correspondiente.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param nombre: Nombre del archivo a buscar.
 *
 * @return El índice del inodo si se encuentra el archivo, -1 si no se encuentra.
 */
int BuscaFich(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombre)
{
    if (directorio == NULL || inodos == NULL || nombre == NULL)
    {
        ft_perror ("Error: Null pointer argument\n" );
        return -1;
    }

    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (ft_strcmp(directorio[i].dir_nfich, nombre) == 0)
        {
            return directorio[i].dir_inodo;
        }
    }
    return -1; // File not found
}

/**
 * Renombrar - Cambia el nombre de un archivo en el directorio.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param nombreantiguo: Nombre del archivo antiguo.
 * @param nombrenuevo: Nuevo nombre para el archivo.
 *
 * @return 0 si la operación fue exitosa, -1 si ocurrió un error.
 */
int Renombrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, char *nombreantiguo, char *nombrenuevo)
{
    if (directorio == NULL || inodos == NULL || nombreantiguo == NULL || nombrenuevo == NULL)
    {
        ft_perror ("Error: Null pointer argument\n" );
        return -1;
    }

    if (nombrenuevo[0] == '\0')
    {
        ft_perror ("Error: New file name is empty\n" );
        return -1;
    }

    if (ft_strlen(nombrenuevo) >= MAX_NFICH)
    {
        ft_perror ("Error: New file name is too long\n" );
        return -1;
    }

    int inodo_index = BuscaFich(directorio, inodos, nombreantiguo);
    if (inodo_index == -1)
    {
        ft_perror ("Error: File not found\n" );
        return -1;
    }

    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (ft_strcmp(directorio[i].dir_nfich, nombrenuevo) == 0)
        {
            ft_perror ("Error: New file name already exists\n" );
            return -1;
        }
    }

    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (directorio[i].dir_inodo == inodo_index)
        {
            ft_strcpy(directorio[i].dir_nfich, nombrenuevo);
            break;
        }
    }

    return 0;
}

/**
 * GrabarInodosyDirectorio - Graba los datos de inodos y directorio en el archivo.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param fich: Puntero al archivo donde se graban los datos actualizados.
 *
 * La función utiliza `fseek` y `fwrite` para escribir los datos correspondientes en los bloques apropiados del archivo.
 */
void GrabarInodosyDirectorio(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, FILE *fich)
{
    if (directorio == NULL || inodos == NULL || fich == NULL)
    {
        ft_perror ("Error: Null pointer argument\n" );
        return;
    }

    // Escribir el bloque del directorio
    if (fseek(fich, 3 * SIZE_BLOQUE, SEEK_SET) != 0)
    {
        ft_perror ("Error seeking to directory block" );
        return;
    }
    if (fwrite(directorio, SIZE_BLOQUE, 1, fich) != 1)
    {
        ft_perror ("Error writing directory block" );
        return;
    }

    // Escribir el bloque de inodos
    if (fseek(fich, 2 * SIZE_BLOQUE, SEEK_SET) != 0)
    {
        ft_perror ("Error seeking to inodes block" );
        return;
    }
    if (fwrite(inodos, SIZE_BLOQUE, 1, fich) != 1)
    {
        ft_perror ("Error writing inodes block" );
        return;
    }

    // Flushing para asegurar que los datos sean escritos en el disco
    if (fflush(fich) != 0)
        ft_perror ("Error flushing file" );
}
