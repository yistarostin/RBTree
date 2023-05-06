docs:
	pandoc -s -o readme.pdf README.md    
debug:
	g++ -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address,undefined,bounds -fno-sanitize-recover -fstack-protector -g -std=c++20 -D DEBUG rbtree.cpp -o debug
optimized:
	g++ -O3 rbtree.cpp -o optimized
genstress:
	python ./gen_stress.py > tests/stress.txt
