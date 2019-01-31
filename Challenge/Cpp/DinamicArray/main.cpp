#include <iostream>
#include "lib/list.h"
using namespace std;

template <typename T>
size_t GetBytesSize(List<T> list) {
    return list.length() * sizeof(list);
}

void ExampleList() {
    // Lista sin datos predefinidos, de longitud 0.
    List<int> IntegerList = List<int>();
    // Lista con 50 datos predefinidos como el default del tipo que se le pase <type>
    List<char*> List2 = List<char*>(50);
    // Agregamos data
    IntegerList.push(10);
    IntegerList.push(20);
    IntegerList.push(30);
    IntegerList.push(40);
    // Quitamos la informacion
    IntegerList.pop();
    // Accedemos al dato que pusimos
    IntegerList[0] = 1;
    // Limpiamos los datos de la lista2
    List2.clear();
    // Ejecutamos una funcion lambda para todos los elementos de una lista
    // Examples: 
    IntegerList.forEach(
        [](int index, int &valor) -> void {
            // Codigo de la funcion
            printf("%i-. %i\n", index, valor);
        }
    );

    // Funcion mapping que retorna una lista del valor definido ejecutando un filtro
    // de los elementos de la lista original
    //    - map < tipo de valor a retornar -> ( funcion lambda [](tipo &valor) -> tipo { codigo })
    List2 = IntegerList.map<char*>(
        [](int index, int &valor) -> char* {
            char* out = new char[3];
            itoa(valor, out, 10);
            return out;
        }
    );

    // Imprimimos los datos con un for en ves del forEach de la lista
    printf("\n");
    for (int i = 0; i < List2.length(); i++ ) {
        printf("%i -> %s\n", i, List2[i]);
    }
}

int main() {
    ExampleList();
    return 0;
}