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
 * Lee el contenido del archivo "superblock.dat" y almacena los datos en la estructura proporcionada.
 * 
 * @param psup Puntero a la estructura `EXT_SIMPLE_SUPERBLOCK` donde se almacenarán los datos leídos.
 */
void LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup) {
    FILE *fich = fopen("superblock.dat", "rb");
    if (fich == NULL) {
        perror("Error opening file");
        return;
    }
    fread(psup, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    fclose(fich);
}

/**
 * Graba los datos de la estructura `EXT_SIMPLE_SUPERBLOCK` en el archivo "superblock.dat".
 * 
 * @param ext_superblock Puntero a la estructura `EXT_SIMPLE_SUPERBLOCK` que contiene los datos a escribir.
 * @param fich Puntero al archivo `FILE` en el que se escribirán los datos.
 */
void GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich) {
    if (fich == NULL) {
        perror("Error opening file");
        return;
    }
    fwrite(ext_superblock, sizeof(EXT_SIMPLE_SUPERBLOCK), 1, fich);
    fclose(fich);
}