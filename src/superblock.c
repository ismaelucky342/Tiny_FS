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

void        LeeSuperBloque(EXT_SIMPLE_SUPERBLOCK *psup);
void        GrabarSuperBloque(EXT_SIMPLE_SUPERBLOCK *ext_superblock, FILE *fich);
