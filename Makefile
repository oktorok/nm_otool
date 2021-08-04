NAME1 := ft_nm
NAME2 := ft_otool

.PHONY : all clean fclean re check_libft check_libprintf

GCC = gcc

FLAGS = -Wall -Wextra -Werror

OBJ_DIR := objects/

OBJ_DIR1 := $(OBJ_DIR)objects_nm/

OBJ_DIR2 := $(OBJ_DIR)objects_otool/

SRC_DIR = src/

FILES_DIR := files_list_nm/

FILE_LIST_FULL := $(shell ls -d $(FILES_DIR)*)

FILE_LIST_NOEXT := $(basename $(shell ls files_list_nm))
FILE_LIST_NOEXT := $(patsubst %,:$(SRC_DIR)%,$(FILE_LIST_NOEXT))

SRC := $(shell cat $(FILE_LIST_FULL)| grep "\.c")

HEADERS := $(shell cat files_list_nm/headers.txt)


FILES_DIR2 := files_list_otool/

FILE_LIST_FULL2 := $(shell ls -d $(FILES_DIR2)*)

FILE_LIST_NOEXT2 := $(basename $(shell ls files_list_otool))
FILE_LIST_NOEXT2 := $(patsubst %,:$(SRC_DIR)%,$(FILE_LIST_NOEXT2))

SRC2 := $(shell cat $(FILE_LIST_FULL2)| grep "\.c")

HEADERS2 := $(shell cat files_list_otool/headers.txt)


INCLUDES_DIR = includes

VPATH := $(SRC_DIR)$(FILE_LIST_NOEXT):$(SRC_DIR)$(FILE_LIST_NOEXT2)

LIBFT_PATH = libft/
LIBFT_HEADERS = $(LIBFT_PATH)includes
LIBFT = libft.a

LIBFTPRINTF_PATH = ft_printf/
LIBFTPRINTF_HEADERS = ./includes
LIBFTPRINTF = libftprintf.a

HEADER_PATH = $(patsubst %.h, $(INCLUDES_DIR)/%.h, $(HEADERS))
HEADER_PATH2 = $(patsubst %.h, $(INCLUDES_DIR)/%.h, $(HEADERS2))

OBJ1 = $(patsubst %.c, $(OBJ_DIR1)%.o, $(SRC))
OBJ2 = $(patsubst %.c, $(OBJ_DIR2)%.o, $(SRC2))

MODE = 1

ifeq ($(MODE), 0)

all:  check_libft check_libftprintf $(NAME1) $(NAME2)

$(NAME1): $(OBJ1) $(LIBFT_PATH)$(LIBFT) $(LIBFTPRINTF_PATH)$(LIBFTPRINTF)
	@$(GCC) $(OBJ1) -L$(LIBFT_PATH) -L$(LIBFTPRINTF_PATH) -lft -lftprintf -o $(NAME1)

$(NAME2): $(OBJ2) $(LIBFT_PATH)$(LIBFT) $(LIBFTPRINTF_PATH)$(LIBFTPRINTF)
	@$(GCC) $(OBJ2) -L$(LIBFT_PATH) -L$(LIBFTPRINTF_PATH) -lft -lftprintf -o $(NAME2)

$(OBJ_DIR1)%.o : %.c $(HEADER_PATH)
	@printf "\r                                          "
	@printf "\r\033[92m--->Compiling $(@F)\033[0m"
	@$(GCC) $(FLAGS) -I$(INCLUDES_DIR) -I $(LIBFT_HEADERS) -c $<
	@mkdir -p $(OBJ_DIR1)
	@mv -f $(@F) $(OBJ_DIR1)

$(OBJ_DIR2)%.o : %.c $(HEADER_PATH2)
	@printf "\r                                          "
	@printf "\r\033[92m--->Compiling $(@F)\033[0m"
	@$(GCC) $(FLAGS) -I$(INCLUDES_DIR) -I $(LIBFT_HEADERS) -c $<
	@mkdir -p $(OBJ_DIR2)
	@mv -f $(@F) $(OBJ_DIR2)

else

all: check_libft check_libftprintf $(NAME1) $(NAME2)

$(NAME1) : $(OBJ1) $(LIBFT_PATH)$(LIBFT) $(LIBFTPRINTF_PATH)$(LIBFTPRINTF)
	@$(GCC) $(OBJ1) -L$(LIBFT_PATH) -L$(LIBFTPRINTF_PATH) -lft -lftprintf -o $(NAME1)

$(NAME2) : $(OBJ2) $(LIBFT_PATH)$(LIBFT) $(LIBFTPRINTF_PATH)$(LIBFTPRINTF)
	@$(GCC) $(OBJ2) -L$(LIBFT_PATH) -L$(LIBFTPRINTF_PATH) -lft -lftprintf -o $(NAME2)

$(OBJ_DIR1)%.o : %.c $(HEADER_PATH)
	@printf "\033[92mCompiling $(NAME1)...\033[0m\n"
	@$(MAKE) $(NAME1) MODE=0
	@printf "\r                                          "
	@printf "\r\033[92mDone $(NAME1)[\xE2\x9C\x94]\n\033[0m"


$(OBJ_DIR2)%.o : %.c $(HEADER_PATH2)
	@printf "\033[92mCompiling $(NAME2)...\033[0m\n"
	@$(MAKE) $(NAME2) MODE=0
	@printf "\r                                          "
	@printf "\r\033[92mDone $(NAME2)[\xE2\x9C\x94]\n\033[0m"
	@printf "\r                                          "

endif

check_libft:
	@$(MAKE) -C $(LIBFT_PATH)

check_libftprintf:
	@$(MAKE) -C $(LIBFTPRINTF_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(LIBFTPRINTF_PATH) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@$(MAKE) -C $(LIBFTPRINTF_PATH) fclean
	@rm -f $(NAME1)
	@rm -f $(NAME2)

re: fclean all
