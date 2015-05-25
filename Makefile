all=xenutil

$(all): xenutil.c
	cc xenutil.c -o xenutil -lxenstore

clean:
	rm xenutil
