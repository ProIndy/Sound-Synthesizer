gcc minisynth.c -L./libft -lft -framework IOKit -framework Cocoa -framework OpenGL `pkg-config --libs --cflags raylib` -o minisynth 
