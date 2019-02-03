#include <iostream>
#include <chrono>
#include "lib/list.hpp"
using namespace std;

template <typename T>
size_t GetBytesSize(List<T> list) {
    return list.length() * sizeof(list);
}

namespace Models {
    struct Producto {
        int id;
        char* nombre;
        double costo;

        Producto() : id(0), nombre((char*)""), costo(0.0) { }
        Producto(int _id, const char* _nombre, double _costo) 
        : id(_id), nombre((char*)_nombre), costo(_costo) { }
    };
}

namespace Data {
    struct Table_Productos {
        List<Models::Producto> productosData = List<Models::Producto>();
        Table_Productos() {
            this->productosData = List<Models::Producto>();
            this->productosData.push_back(Models::Producto(0, "Langley", 144.883));
            this->productosData.push_back(Models::Producto(1, "Hinton", 84.0902));
            this->productosData.push_back(Models::Producto(2, "Patel", 15.8934));
            this->productosData.push_back(Models::Producto(3, "Henson", 161.877));
            this->productosData.push_back(Models::Producto(4, "Cash", 132.913));
            this->productosData.push_back(Models::Producto(5, "Decker", 1.382));
            this->productosData.push_back(Models::Producto(6, "Acevedo", 127.1603));
            this->productosData.push_back(Models::Producto(7, "Rose", 56.0588));
            this->productosData.push_back(Models::Producto(8, "Gonzales", 133.542));
            this->productosData.push_back(Models::Producto(9, "Burks", 190.891));
            this->productosData.push_back(Models::Producto(10, "Cooke", 34.524));
            this->productosData.push_back(Models::Producto(11, "Fry", 163.2334));
            this->productosData.push_back(Models::Producto(12, "Frank", 169.893));
            this->productosData.push_back(Models::Producto(13, "Alston", 25.646));
            this->productosData.push_back(Models::Producto(14, "Morton", 165.848));
            this->productosData.push_back(Models::Producto(15, "Yang", 45.149));
            this->productosData.push_back(Models::Producto(16, "Mccullough", 63.969));
            this->productosData.push_back(Models::Producto(17, "Green", 105.474));
            this->productosData.push_back(Models::Producto(18, "Montgomery", 84.478));
            this->productosData.push_back(Models::Producto(19, "Dickerson", 75.172));
        }
        ~Table_Productos() {
            productosData.clear();
        }
    };
}

int main() {
    Data::Table_Productos table_productos = Data::Table_Productos();
    printf("\n -------------------------------------- \n");
    printf("  %-5s| %-20s| %7s\n", "ID", "PERSONA", "CREDITO");
    printf(" --------------------------------------\n");
    table_productos.productosData.forEach([](int _, Models::Producto &product) -> void {
        printf("  %-5i| %-20s| $ %-7.2lf\n", product.id, product.nombre, product.costo);
    });
    printf(" --------------------------------------\n");
    return 0;
}