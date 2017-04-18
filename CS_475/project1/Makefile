all : cs_475_project_1

cs_475_project_1 : project1.cpp curve_calc.cpp csv_logger.cpp
	g++ -o project1 project1.cpp curve_calc.cpp csv_logger.cpp -O3 -lm -fopenmp -DNUMT=$(NUMT) -DNUMNODES=$(NUMNODES)

clean :
	rm -f project1