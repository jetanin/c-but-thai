default:
	gcc -o app main.c hashmap.c dict.c image.c option.c line.c && ./app
win:
	gcc -o app main.c hashmap.c dict.c image.c option.c line.c && app.exe