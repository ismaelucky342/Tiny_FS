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
 * Lee e imprime los datos del struct EXT_SIMPLE_SUPERBLOCK
 * 
 * @param psup Puntero a la estructura `EXT_SIMPLE_SUPERBLOCK` desde la que leer los datos.
 */
void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup)
{
    ft_printf("Bloque %u bytes\n", psup->s_block_size);
    ft_printf("Inodos particion %u\n", psup->s_inodes_count);
    ft_printf("Inodos libres %u\n", psup->s_free_inodes_count);
    ft_printf("Bloques particion %u\n", psup->s_blocks_count);
    ft_printf("Bloques libres %u\n", psup->s_free_blocks_count);
    ft_printf("Primer bloque de datos %u\n", psup->s_first_data_block);
}

/**
 * Graba los datos de la estructura `EXT_SIMPLE_SUPERBLOCK` en el archivo "superblock.dat".
 *
 * @param ext_superblock Puntero a la estructura `EXT_SIMPLE_SUPERBLOCK` que contiene los datos a escribir.
 * @param fich Puntero al archivo `FILE` en el que se escribirán los datos.
 */

void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich)
{
    if (fich == NULL)
    {
        ft_perror("Error opening file");
        return;
    }
    size_t bytes_written = fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    if (bytes_written != 1)
    {
        ft_perror("Error writing to file");
        return;
    }
}
