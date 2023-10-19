CXX = g++
CXXFLAGS = -std=c++2a -g
NAMEGLAGS = -o

make:
	$(CXX) $(NAMEGLAGS) sistemas_recomendacion $(CXXFLAGS) ../src/*.cc ../src/Metricas/*.cc ../src/Predicciones/*.cc -I .

.PHONY: all clean

	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f sistemas_recomendacion *.o