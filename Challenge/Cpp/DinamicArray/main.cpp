#include <iostream>
#include <chrono>
#include "lib/array.h"
using namespace std;

struct Products {
    int Id;
    char* Nombre;
};

struct Products CreateNewProduct(int id, const char* nombre) {
    Products product;
    product.Id = id;
    product.Nombre = (char*)nombre;
    return product;
}

void ImprimirDatosProducto(struct Products producto) {
    printf("  Producto %i: %s\n", producto.Id, producto.Nombre);
}

int main() {
    List<Products> asfa = List<Products>();
	auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= 100000; i++) {
        asfa.push_last(CreateNewProduct(i, "Producto"));
    } 
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - start);
	cout << "Size: " << sizeof(asfa) << " Bytes ~ Execution Time: " << duration.count() << " ms" << endl;
    return 0;
}