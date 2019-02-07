# Es clase es el objeto para el manejo de las varillas, tiene las funciones para
# calcular su propia area, deformacion y alargamiento
#   calculate_area        -> Calcula el area de la varilla
#   calculate_deformation -> Calcula la deformacion de la varilla
#   calculate_effort      -> Calcula el esfuerzo de la varilla
class Varilla:
    __PI = 3.14159265359

    def __init__(self):
        self.diametro = 0
        self.elasticidad = 0
        self.longitud = 0
        self.carga = 0

    def calculate_area(self) -> float:
        return (self.__PI*(self.diametro ** 2)) / 4

    def calculate_deformation(self) -> float:
        return (self.carga * self.longitud) / (self.calculate_area() * self.elasticidad)

    def calculate_effort(self) -> float:
        return self.carga / self.calculate_area()