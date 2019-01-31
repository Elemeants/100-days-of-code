#include <iostream>
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
    for (int i = 1; i <= 70000; i++) {
        asfa.push_last(CreateNewProduct(i, "Producto"));
    }
    asfa.forEach(
            [](int index, Products &x) -> 
            void {
                ImprimirDatosProducto(x);
            } 
        );
    return 0;
}