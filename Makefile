MAKEFLAGS += --silent

NAME1 = ft_nm

NAME2 = ft_otool

.PHONY : $(NAME2) $(NAME1)

all: $(NAME1) $(NAME2)

$(NAME1):
	$(MAKE) -f $(NAME1).mk

$(NAME2):
	$(MAKE) -f $(NAME2).mk

clean:
	$(MAKE) -f $(NAME1).mk clean
	$(MAKE) -f $(NAME2).mk clean

fclean:
	$(MAKE) -f $(NAME1).mk fclean
	$(MAKE) -f $(NAME2).mk fclean

re:
	$(MAKE) -f $(NAME1).mk re
	$(MAKE) -f $(NAME2).mk re
