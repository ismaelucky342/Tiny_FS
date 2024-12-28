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
 * Printbytemaps - Imprime los mapas de bytes de inodos y bloques.
 *
 * @param ext_bytemaps: Puntero a la estructura EXT_BYTE_MAPS que contiene los mapas de bytes.
 *
 * La función recorre los mapas de bytes de inodos y bloques, imprimiendo cada valor
 * en la consola. Primero imprime los inodos y luego los bloques.
 */
void Printbytemaps(EXT_BYTE_MAPS *ext_bytemaps)
{
    int i;

    ft_printf("Inodos: ");
    for (i = 0; i < MAX_INODOS; i++)
        ft_printf("%d ", ext_bytemaps->bmap_inodos[i]);
    ft_printf("\nBloques[0-25]: ");
    for (i = 0; i < 25; i++)
        ft_printf("%d ", ext_bytemaps->bmap_bloques[i]);
    ft_printf("\n");
}

/**
 * GrabarByteMaps - Guarda los mapas de bytes en un archivo.
 *
 * @param ext_bytemaps: Puntero a la estructura EXT_BYTE_MAPS que contiene los mapas de bytes.
 * @param fich: Puntero al archivo donde se escribirán los mapas de bytes.
 *
 * La función posiciona el puntero del archivo en el segundo bloque (después del bloque de arranque)
 * y escribe la estructura EXT_BYTE_MAPS en el archivo.
 */

void GrabarByteMaps(EXT_BYTE_MAPS *ext_bytemaps, FILE *fich)
{
    fseek(fich, SIZE_BLOQUE, SEEK_SET);
    fwrite(ext_bytemaps, SIZE_BLOQUE, 1, fich);
}