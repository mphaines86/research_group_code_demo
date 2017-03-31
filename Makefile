.PHONY : all
all : rosenthal rosenthal_plot.png

rosenthal : rosenthal.cpp main.cpp
	c++ -o rosenthal rosenthal.cpp main.cpp

rosenthal_plot.png : rosenthal
	python rosenthal.py $^

.PHONY : clean
clean :
	rm -f rosenthal rosenthal_plot.png
