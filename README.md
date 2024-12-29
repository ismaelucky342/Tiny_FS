# Tiny_FS

## Descripción
Tiny_FS es un simulador del sistema de archivos basado en particiones que permite la gestión de archivos mediante estructuras de datos esenciales como inodos, directorios y bloques de datos. Este proyecto está diseñado para emular operaciones básicas de un sistema de archivos tradicional, permitiendo crear, leer, escribir, modificar y eliminar archivos en un entorno controlado.

## Objetivo Principal
El objetivo principal de Tiny_FS es proporcionar una estructura mínima pero funcional para la gestión de archivos y directorios, utilizando conceptos fundamentales como:

#### Inodos
Cada archivo o directorio está asociado a un inodo que almacena metadatos importantes como permisos, punteros a bloques de datos, tamaño, y tipo de contenido.
#### Directorios
Los directorios permiten organizar y almacenar múltiples archivos, proporcionando una jerarquía simple y eficiente para la navegación del sistema de archivos.
#### Bloques de Datos
Los bloques de datos son las unidades básicas para almacenar información en el sistema, gestionando contenido como texto, imágenes, etc.

## Dependencias
#### Librería Libft
#### Bibliotecas estándar:
    - stdio.h
    - stdlib.h
    - string.h
    - ctype.h
    - unistd.h
#### Bibliotecas adicionales:
    - readline/readline.h
    - readline/history.h
# Uso de librería Auxiliar (42 Libft)

En este proyecto, he incorporado mi librería de funciones personalizadas, libft, desarrollada en el marco de la escuela 42 Madrid. La finalidad de utilizar esta librería es mejorar y robustecer las funciones estándar al proporcionar versiones personalizadas adaptadas específicamente a las necesidades de este proyecto.

Enlace al proyecto original:  [**42_Libft**](https://github.com/ismaelucky342/Libft)

funciones utilizadas:
- ft_memmove: función de copiado memoria utilizada como sustituto a memcpy para evitar solapamiento. 
- ft_strtok:  version segura de strtok que evita problemas de alteración de cadena original 
- ft_printf:  función que emula el comportamiento de printf de manera mas óptima. 
- ft_perror:  versión propia de perror a partir de write con colores personalizados. 
- ft_strcpy y ft_strcmp:  versiones personalizadas de strcpy y strcmp con protecciones adicionales. 
## Clonado y compilación

1. Clonar el repositorio:
    ```bash
    git clone https://github.com/usuario/proyecto.git
    ```
2. Usos del makefile:
    ```bash
    make all # para compilación de Librería auxiliar y programa principal

    make # para compilación de unicamente la Librería auxiliar

    make re # para recompilar todo 

    make fclean # para limpieza de objetos y ejecutable
    ```
3. Ejecución del programa:
    ```bash
    ./tiny_fs
    ```

## Uso
Ejecuta `./tiny_fs` para interactuar con el sistema de archivos. Comandos disponibles:

- info: Mostrar información del superbloque.

- imprimir [nombre]: Imprimir el contenido de un archivo.

- info: Mostrar información del superbloque.

- rename [nombre antiguo] [nuevo nombre]: Cambiar el nombre de un archivo o directorio.

- remove [nombre]: Borrar un archivo o directorio.

- Copy [nombre] [nuevo nombre]: Copiar un archivo o directorio.

- bytemaps: Mostrar información sobre los mapas de bytes.

- salir: Salir del sistema de archivos.

Adicionalmente el programa cuenta con un historial funcional con las flechas arriba y abajo del teclado que permiten al usuario usar comandos utilizados anteriormente. 

## Estructura del Proyecto
```
├── Libft
├── Makefile
├── README.md
├── includes 
|    └── tiny_fs.h
└── src
     ├── bytemaps.c
     ├── directory.c
     ├── file_operations.c
     ├── inode.c
     ├── save_data.c
     ├── superblock.c 
     └── main.c
```

## Licencia
Este proyecto está licenciado bajo la licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.

## Extras 
Este proyecto ha proporcionado una experiencia enriquecedora para profundizar en el manejo avanzado de ficheros dentro del ámbito de sistemas operativos. Además, servirá como base sólida para futuros desarrollos y proyectos relacionados con la gestión de sistemas y archivos.


![image](https://github.com/ismaelucky342/U-Tad/assets/153450550/62bc16fd-1d63-401e-962d-b090cad59bdc)
