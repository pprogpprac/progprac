all:
	#g++ -g -std=c++0x -pthread -o prac -fdump-tree-all -fdump-rtl-all prac.cpp
	#g++ -E prac.cpp > prac_preprocessed_source_code.txt #Generate preprocessed source code
	#g++ -S prac.cpp #Generate assembly code
	#g++ -g -std=c++1y --save-temps -pthread -o prac prac.cpp
	g++ -g -std=c++11 --save-temps -pthread -o prac prac.cpp
clean:
	rm -rf prac
