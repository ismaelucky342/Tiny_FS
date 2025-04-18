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

#define LONGITUD_COMANDO 100

/**
 * @brief Función principal que gestiona la ejecución de comandos y las operaciones en el sistema de archivos.
 *
 * Esta función se encarga de la interacción con el usuario a través de comandos, y realiza diversas operaciones
 * como lectura y escritura de datos en un sistema de archivos basado en particiones. Los comandos pueden ser:
 * - `info`: Mostrar información del superbloque.
 * - `imprimir`: Imprimir el contenido de un archivo.
 * - `dir`: Mostrar el contenido del directorio.
 * - `rename`: Cambiar el nombre de un archivo o directorio.
 * - `remove`: Eliminar un archivo o directorio.
 * - `copy`: Copiar un archivo o directorio.
 * - `bytemaps`: Mostrar los mapas de bytes.
 * - `salir`: Guardar los cambios y salir del sistema.
 *
 * @return int Retorna 0 si la ejecución es exitosa, o un valor distinto si ocurre algún error.
 */
int main()
{
    char *comando;
    char orden[LONGITUD_COMANDO];
    char argumento1[LONGITUD_COMANDO];
    char argumento2[LONGITUD_COMANDO];

    EXT_SIMPLE_SUPERBLOCK ext_superblock = {MAX_INODOS, MAX_BLOQUES_PARTICION, MAX_BLOQUES_DATOS, MAX_FICHEROS, PRIM_BLOQUE_DATOS, SIZE_BLOQUE, {0}};
    EXT_BYTE_MAPS ext_bytemaps;
    EXT_BLQ_INODOS ext_blq_inodos;
    EXT_ENTRADA_DIR directorio[MAX_FICHEROS];
    EXT_DATOS memdatos[MAX_BLOQUES_DATOS];
    EXT_DATOS datosfich[MAX_BLOQUES_PARTICION];
    int grabardatos = 0;
    FILE *fent;

    // Lectura del fichero completo de una sola vez
    fent = fopen("particion.bin", "r+b");
    if (fent == NULL)
    {
        ft_perror("Error opening file");
        return 1;
    }
    fread(&datosfich, SIZE_BLOQUE, MAX_BLOQUES_PARTICION, fent);

    /*Función memcpy modificada por memmove para evitar solapamiento de memoria*/
    ft_memmove(&ext_superblock, &datosfich[0], SIZE_BLOQUE);
    ft_memmove(&ext_bytemaps, &datosfich[1], SIZE_BLOQUE);
    ft_memmove(&ext_blq_inodos, &datosfich[2], SIZE_BLOQUE);
    ft_memmove(directorio, &datosfich[3], MAX_FICHEROS * sizeof(EXT_ENTRADA_DIR));
    ft_memmove(memdatos, &datosfich[4], MAX_BLOQUES_DATOS * SIZE_BLOQUE);

    // Bucle de tratamiento de comandos
    while (1)
    {
        comando = readline(">> ");
        if (comando == NULL)
        {
            perror("Error reading command");
            continue;
        }
        if (ft_strlen(comando) > 0)
            add_history(comando);
        if (ComprobarComando(comando, orden, argumento1, argumento2) != 0)
        {
            ft_printf(COLOR_RED "Error: Invalid command\n" );
            free(comando);
            continue;
        }
        if (ft_strcmp(orden, "info") == 0)
            LeeSuperBloque(&ext_superblock);
        else if (ft_strcmp(orden, "imprimir") == 0)
            Imprimir(directorio, &ext_blq_inodos, memdatos, argumento1);
        else if (ft_strcmp(orden, "dir") == 0)
            Directorio(directorio, &ext_blq_inodos);
        else if (ft_strcmp(orden, "rename") == 0)
            Renombrar(directorio, &ext_blq_inodos, argumento1, argumento2);
        else if (ft_strcmp(orden, "remove") == 0)
            Borrar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, argumento1, fent);
        else if (ft_strcmp(orden, "Copy") == 0)
            Copiar(directorio, &ext_blq_inodos, &ext_bytemaps, &ext_superblock, memdatos, argumento1, argumento2, fent);
        else if (ft_strcmp(orden, "bytemaps") == 0)
            Printbytemaps(&ext_bytemaps);
        else if (ft_strcmp(orden, "salir") == 0)
        {
            GrabarDatos(memdatos, fent);
            fclose(fent);
            ft_printf(COLOR_GREEN "Saliendo del sistema..." COLOR_RESET "\n");
            free(comando);
            break;
        }
        else
            ft_printf(COLOR_RED "Comando desconocido: %s" COLOR_RESET "\n", orden);

        GrabarInodosyDirectorio(directorio, &ext_blq_inodos, fent);
        GrabarByteMaps(&ext_bytemaps, fent);
        GrabarSuperBloque(&ext_superblock, fent);
        
        if (grabardatos)
            GrabarDatos(memdatos, fent);
        grabardatos = 0;
        free(comando);
    }
}

