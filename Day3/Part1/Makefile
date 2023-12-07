NAME		:= gear
CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++11 -MMD

ifeq ($(DEBUG), 1)
	CXXFLAGS += -fsanitize=address -g3
endif

SRCS_DIR	:= srcs
OBJS_DIR	:= objs
INC_DIR		:= includes

SRCS		:= $(shell find ${SRCS_DIR} -name "*.cpp")
OBJS		:= $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

HEADER		:= $(shell find ${INC_DIR} -name "*.hpp")
INCLUDES	:= $(addprefix -I, $(dir ${HEADER})) -MMD
INC			:= ${INCLUDES}
RM			:= rm -rf

BL			:= \033[1;34m
DF			:= \033[0m

UNAME_S 	:= $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	INC += -include-pch ${PCH}
endif

all: $(NAME)

ifeq ($(DEBUG), 1)
	@echo "$(BL)DEBUG MODE$(DF)"
endif

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re env debug
