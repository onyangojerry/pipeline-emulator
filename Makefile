decoder_tester:
	g++ -std=c++14 -O0 -g -Wall -Isrc src/decoder_tester.cc -o bin/decoder_tester

single_cycle:
	g++ -std=c++14 -O0 -g -Wall -Isrc src/single_cycle.cc -o bin/single_cycle

simple_pipeline:
	g++ -std=c++14 -O0 -g -Wall -Isrc src/simple_pipeline.cc -o bin/simple_pipeline

hazard_checking:
	g++ -std=c++14 -O0 -g -Wall -Isrc src/hazard_checking.cc -o bin/hazard_checking

forwarding:
	g++ -std=c++14 -O0 -g -Wall -Isrc src/forwarding.cc -o bin/forwarding

clean:
	rm -r bin/*

all:
	make clean decoder_tester single_cycle simple_pipeline hazard_checking forwarding

