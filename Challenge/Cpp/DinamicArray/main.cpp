#include <iostream>
#include <chrono>
#include "lib/list.hpp"
using namespace std;

namespace Models {
    struct Producto {
        int id;
        char* nombre;
        double costo;

        Producto() : id(0), nombre((char*)""), costo(0.0) { }
        Producto(int _id, const char* _nombre, double _costo) 
        : id(_id), nombre((char*)_nombre), costo(_costo) { }
    };
    struct Usuario {
        int id;
        char* nombre;

        Usuario(): id(0), nombre((char*)"") { }
        Usuario(const char* _nombre)
        : id(0), nombre((char*)_nombre) { }
        Usuario(int _id, const char* _nombre)
        : id(_id), nombre((char*)_nombre) { }
    };
    struct Pedido {
        int id;
        Usuario usuario;
        List<Producto> productos;
        double costo_total;

        Pedido(Usuario _usuario, List<Producto> _productos) 
        : id(0), usuario(_usuario), productos(_productos) { 
            this->costo_total = 0;
            this->productos.forEach(
                [&](int _, Producto& product) -> void {
                    this->costo_total += product.costo;
                }
            );
        }
    };
}

namespace Data {
    struct Tables {
        static List<Models::Producto> Productos;
        static List<Models::Usuario> Usuarios;
        static List<Models::Pedido> Pedidos;
    };
    List<Models::Producto> Tables::Productos = List<Models::Producto>();
    List<Models::Usuario> Tables::Usuarios = List<Models::Usuario>();
    List<Models::Pedido> Tables::Pedidos = List<Models::Pedido>();

    void Fill_data () {
        Tables::Productos.push_back(Models::Producto(0, "Langley", 144.883));           
        Tables::Productos.push_back(Models::Producto(1, "Hinton", 84.0902));        
        Tables::Productos.push_back(Models::Producto(2, "Patel", 15.8934));         
        Tables::Productos.push_back(Models::Producto(3, "Henson", 161.877));        
        Tables::Productos.push_back(Models::Producto(4, "Cash", 132.913));       
        Tables::Productos.push_back(Models::Producto(5, "Decker", 1.382));   
        Tables::Productos.push_back(Models::Producto(6, "Acevedo", 127.1603));       
        Tables::Productos.push_back(Models::Producto(7, "Rose", 56.0588));      
        Tables::Productos.push_back(Models::Producto(8, "Gonzales", 133.542));       
        Tables::Productos.push_back(Models::Producto(9, "Burks", 190.891));
        Tables::Productos.push_back(Models::Producto(10, "Cooke", 34.524));      
        Tables::Productos.push_back(Models::Producto(11, "Fry", 163.2334));       
        Tables::Productos.push_back(Models::Producto(12, "Frank", 169.893));    
        Tables::Productos.push_back(Models::Producto(13, "Alston", 25.646));         
        Tables::Productos.push_back(Models::Producto(14, "Morton", 165.848));      
        Tables::Productos.push_back(Models::Producto(15, "Yang", 45.149));     
        Tables::Productos.push_back(Models::Producto(16, "Mccullough", 63.969));          
        Tables::Productos.push_back(Models::Producto(17, "Green", 105.474));        
        Tables::Productos.push_back(Models::Producto(18, "Montgomery", 84.478));    
        Tables::Productos.push_back(Models::Producto(19, "Dickerson", 75.172));
    }
}

int main() {
    Data::Fill_data();
    printf("\n -------------------------------------- \n");
    printf("  %-5s| %-20s| %7s\n", "ID", "PERSONA", "CREDITO");
    printf(" --------------------------------------\n");
    Data::Tables::Productos.forEach([](int _, Models::Producto &product) -> void {
        printf("  %-5i| %-20s| $ %-7.2lf\n", product.id, product.nombre, product.costo);
    });
    printf(" --------------------------------------\n");
    return 0;
}