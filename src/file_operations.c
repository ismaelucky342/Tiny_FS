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
 * Borrar - Elimina un archivo del sistema.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param ext_bytemaps: Puntero a la estructura que gestiona los mapas de bytes para bloques e inodos.
 * @param ext_superblock: Puntero al bloque super del sistema de archivos.
 * @param nombre: Nombre del archivo que se va a borrar.
 * @param fich: Puntero al archivo donde se graban los datos actualizados.
 *
 * @return 0 si la operación fue exitosa, -1 si ocurrió un error.
 */
int Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
           EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre, FILE *fich)
{
    int inodo_index = -1;
    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (ft_strcmp(directorio[i].dir_nfich, nombre) == 0)
        {
            inodo_index = directorio[i].dir_inodo;
            directorio[i].dir_inodo = NULL_INODO;
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
        {
            ext_bytemaps->bmap_bloques[inodo->i_nbloque[i]] = 0;
            ext_superblock->s_free_blocks_count++;
            inodo->i_nbloque[i] = NULL_BLOQUE;
        }
    }

    ext_bytemaps->bmap_inodos[inodo_index] = 0;
    ext_superblock->s_free_inodes_count++;
    inodo->size_fichero = 0;

    GrabarInodosyDirectorio(directorio, inodos, fich);
    GrabarByteMaps(ext_bytemaps, fich);
    GrabarSuperBloque(ext_superblock, fich);

    return 0;
}

/**
 * Copiar - Copia un archivo a otro dentro del sistema.
 * @param directorio: Puntero a la estructura de directorio que contiene la información de los archivos.
 * @param inodos: Puntero a los bloques de inodos que contienen las referencias a los bloques de datos.
 * @param ext_bytemaps: Puntero a la estructura que gestiona los mapas de bytes para bloques e inodos.
 * @param ext_superblock: Puntero al bloque super del sistema de archivos.
 * @param memdatos: Puntero a la estructura de datos que contiene los datos de los bloques.
 * @param nombreorigen: Nombre del archivo fuente que se copiará.
 * @param nombredestino: Nombre del archivo destino donde se copiará el archivo.
 * @param fich: Puntero al archivo donde se graban los datos actualizados.
 *
 * @return 0 si la operación fue exitosa, -1 si ocurrió un error.
 */
int Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
           EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino, FILE *fich)
{
    int inodo_origen = -1;
    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (ft_strcmp(directorio[i].dir_nfich, nombreorigen) == 0)
        {
            inodo_origen = directorio[i].dir_inodo;
            break;
        }
    }

    if (inodo_origen == -1)
    {
        ft_printf(COLOR_RED "Error: Source file not found\n" );
        return -1;
    }

    int inodo_destino = -1;
    for (int i = 0; i < MAX_INODOS; i++)
    {
        if (ext_bytemaps->bmap_inodos[i] == 0)
        {
            inodo_destino = i;
            ext_bytemaps->bmap_inodos[i] = 1;
            ext_superblock->s_free_inodes_count--;
            break;
        }
    }

    if (inodo_destino == -1)
    {
        ft_printf(COLOR_RED "Error: No free inodes available\n" );
        return -1;
    }

    for (int i = 0; i < MAX_FICHEROS; i++)
    {
        if (directorio[i].dir_inodo == NULL_INODO)
        {
            ft_strcpy(directorio[i].dir_nfich, nombredestino);
            directorio[i].dir_inodo = inodo_destino;
            break;
        }
    }

    EXT_SIMPLE_INODE *inodo_src = &inodos->blq_inodos[inodo_origen];
    EXT_SIMPLE_INODE *inodo_dst = &inodos->blq_inodos[inodo_destino];
    inodo_dst->size_fichero = inodo_src->size_fichero;

    for (int i = 0; i < MAX_NUMS_BLOQUE_INODO; i++)
    {
        if (inodo_src->i_nbloque[i] != NULL_BLOQUE)
        {
            for (int j = 0; j < MAX_BLOQUES_PARTICION; j++)
            {
                if (ext_bytemaps->bmap_bloques[j] == 0)
                {
                    ext_bytemaps->bmap_bloques[j] = 1;
                    ext_superblock->s_free_blocks_count--;
                    inodo_dst->i_nbloque[i] = j;
                    ft_memmove(memdatos[j].dato, memdatos[inodo_src->i_nbloque[i]].dato, SIZE_BLOQUE);
                    break;
                }
            }
        }
        else
            inodo_dst->i_nbloque[i] = NULL_BLOQUE;
    }

    GrabarInodosyDirectorio(directorio, inodos, fich);
    GrabarByteMaps(ext_bytemaps, fich);
    GrabarSuperBloque(ext_superblock, fich);
    GrabarDatos(memdatos, fich);

    return 0;
}

/**
 * ComprobarComando - Divide una cadena de comando en orden, argumento1 y argumento2.
 * @param strcomando: Cadena de comando completa.
 * @param orden: Cadena para almacenar el comando principal.
 * @param argumento1: Cadena para almacenar el primer argumento.
 * @param argumento2: Cadena para almacenar el segundo argumento (opcional).
 *
 * @return 0 si se pudo dividir correctamente, -1 si hubo un error o la cadena está vacía.
 */
int ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2)
{
    char *token = strtok(strcomando, " \n");
    if (token == NULL)
        return -1;

    ft_strcpy(orden, token);
    token = strtok(NULL, " \n");
    if (token != NULL)
    {
        ft_strcpy(argumento1, token);
        token = strtok(NULL, " \n");
        if (token != NULL)
            ft_strcpy(argumento2, token);
        else
            argumento2[0] = '\0';
    }
    else
    {
        argumento1[0] = '\0';
        argumento2[0] = '\0';
    }

    return 0;
}
