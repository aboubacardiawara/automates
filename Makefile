all: buildExec

######################################
#    INITIALISATION DE VARIBALES     #
######################################
CC = gcc
CFLAG = -Wall -Werror -ansi -pedantic
ASAN_FLAG = -O0 -g -fsanitize=address
GDB_FLAG = -O0 -g -fno-stack-protector
MODULE_DIR = ./src/module
BUILD_DIR = ./build
#####################################


######################################
#  CREATION DES FICHIERS EXECUTABLES #
######################################

${BUILD_DIR}/main: ${MODULE_DIR}/main.o
	$(CC) -o $@ $^ $(CFLAG)


######################################
#    CREATION DES FICHIERS OBJETS    #
######################################
${MODULE_DIR}/%.o: src/%.c
	$(CC) -c $^ $(CFLAG); make reorganize


######################################
# 			AUTRES REGLESS   	     #
######################################

# placer les fichiers objets dans les bons Dossiers
reorganize:
	mv *.o ${MODULE_DIR}

# supprimer tous les fichiers objets (de ./src/module)
clean:
	make removeExec;
	make removeObject;


# supprimer tous les EXECUTABLES
removeObject:
	@ cd ${MODULE_DIR} && rm *.o && cd ../..;


# supprimer tous les EXECUTABLES
removeExec:
	@ cd ${BUILD_DIR} && rm -f *;
	@ cd ../

# creer le programme
buildExec:
	make ${BUILD_DIR}/main;