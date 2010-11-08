all:
	gcc -o vmi vmi.c vmi_util.c -lxenctrl

clean:
	rm -f vmi
