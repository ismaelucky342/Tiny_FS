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

int                Borrar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
                        EXT_SIMPLE_SUPERBLOCK *ext_superblock, char *nombre,  FILE *fich);
int                Copiar(EXT_ENTRADA_DIR *directorio, EXT_BLQ_INODOS *inodos, EXT_BYTE_MAPS *ext_bytemaps,
                        EXT_SIMPLE_SUPERBLOCK *ext_superblock, EXT_DATOS *memdatos, char *nombreorigen, char *nombredestino,  FILE *fich);
int                ComprobarComando(char *strcomando, char *orden, char *argumento1, char *argumento2);
