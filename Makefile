all=xenutil

$(all):
	cc xenutil.c -o xenutil -lxenstore

clean:
	rm xenutil
