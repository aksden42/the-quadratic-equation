src = src

bin = objects

a.exe : $(bin)\main.o $(bin)\quadratic.o $(bin)\testQuadratic.o
	g++ $(bin)\main.o $(bin)\quadratic.o $(bin)\testQuadratic.o -o a.exe

$(bin)\main.o : $(src)\main.cpp $(src)\quadratic.h
	g++ -c $(src)\main.cpp -o $(bin)\main.o

$(bin)\quadratic.o : $(src)\quadratic.cpp $(src)\quadratic.h
	g++ -c $(src)\quadratic.cpp -o $(bin)\quadratic.o

$(bin)\testQuadratic.o : $(src)\testQuadratic.cpp $(src)\testQuadratic.h $(src)\quadratic.h
	g++ -c $(src)\testQuadratic.cpp -o $(bin)\testQuadratic.o


