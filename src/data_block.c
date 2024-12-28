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
 * GrabarDatos - Guarda los datos en un archivo.
 *
 * @param memdatos: Puntero a la estructura de datos que se va a escribir.
 * @param fich: Puntero al archivo donde se escribirán los datos.
 *
 * La función verifica que los punteros no sean NULL, posiciona el puntero
 * del archivo en el bloque de datos adecuado y escribe los datos en el archivo.
 * Si ocurre algún error durante estos procesos, se imprime un mensaje de error.
 */
void GrabarDatos(EXT_DATOS *memdatos, FILE *fich)
{
    if (memdatos == NULL)
    {
        perror("Error: memdatos is NULL\n");
        return;
    }
    if (fich == NULL)
    {
        perror("Error: fich is NULL\n");
        return;
    }
    if (fseek(fich, PRIM_BLOQUE_DATOS * SIZE_BLOQUE, SEEK_SET) != 0)
    {
        perror("Error seeking to the data block");
        return;
    }
    size_t written = fwrite(memdatos, SIZE_BLOQUE, MAX_BLOQUES_DATOS, fich);
    if (written != MAX_BLOQUES_DATOS)
    {
        perror("Error writing data to file");
        return;
    }

}