NAME		= 	webserv

SRCS		= 	main.cpp \
				cluster.cpp \
				default_server.cpp \
				server.cpp \
				connected_client.cpp \
				Response.cpp \
				Request.cpp \
				Cgi.cpp \
				utility.cpp \
				# location.cpp

OBJS		= 	$(SRCS:.cpp=.o)

CFLAGS		= 	-Wall -Wextra -Werror

CC			= 	g++

%.o :		%.cpp
			$(CC) -g -c -I. $(CFLAGS) $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re