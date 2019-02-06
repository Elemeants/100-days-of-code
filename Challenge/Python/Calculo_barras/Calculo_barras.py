# ---------------------------------------------------------------------------------------
#    Calculo_varillas.py
#        - Este codigo permite calcular la deformacion, alargamiento y esfuerzo de
#          N cantidad de varillas con la misma o diferente carga
#    v.1.0 - 05/02/2019
# ---------------------------------------------------------------------------------------

# Se importa Os para limpiar la consola
import os


# ---------------------------------------------------------------------------------------
#                                       CLASES
# ---------------------------------------------------------------------------------------
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


# Esta clase guarda las constantes para el codigo para un mejor
# entendimiento del mismo
class Constants:
    EXIT = -1


# Esta clase guarda las constantes de tipos de operacion y su nombre
# normalizado para mostrarlos
class KindOperation:
    CALCULATE_DEFORMATION = 'Deformacion'
    CALCULATE_EFFORT = 'Esfuerzo'
    CALCULATE_ELONGATION = 'Alargamiento'
# ---------------------------------------------------------------------------------------


# ---------------------------------------------------------------------------------------
#                                      FUNCIONES
# ---------------------------------------------------------------------------------------
# Funcion principal la cual es la funcion principal del codigo
# la que hace es generar el menu de opciones, posteriormente mapea
# la seleccion a un tipo de operacion, y ejecuta la funcion con
# los parametros especificados en el menu
def main_menu():
    # Opciones del menu principal
    options = [
        "Calcular la deformación de cada elemento de la varilla.",
        "Calcular el esfuerzo de cada elemento.",
        "Calcular el alargamiento total de la varilla.",
        "Salir del programa."
    ]
    for index, option in enumerate(options):
        print(f" {index + 1}) {option}")
    option_selected = int(input(" -> ")) - 1
    # Mapeo de la opcions seleccionada al resultado
    try:
        result = [
            KindOperation.CALCULATE_DEFORMATION,
            KindOperation.CALCULATE_EFFORT,
            KindOperation.CALCULATE_ELONGATION,
            Constants.EXIT
        ][option_selected]
        if result == Constants.EXIT:
            return
    except IndexError:
        # Si seleccionaste una opcion no valida detiene el programa
        # y muestra un mensaje de error
        print("\n Opcion no valida")
        return

    # Limpia la pantalla de la consola, para hacer mas claro el programa
    os.system("cls")
    # Mostramos las preguntas y obtenemos la respuesta de cada una
    print(f"  {result.replace('', ' ')}")
    output_values = []
    for index, question in enumerate([
        "De cuántos elementos esta formada la varilla?",
        "Tiene mas de una carga aplicada(y, n)?"
    ]):
        # Agregamos las respuestas a un arreglo con los valores
        output_values.append(input(f" {index + 1} -> {question} "))

    # Llamamos a la funcion que obtendra los datos y calculara el resultado
    # de la operacion seleccionada
    get_data(n_elements=int(output_values[0]),
             same_charge=not(output_values[1] == 'y'),
             operation_kind=result)
    # Se le da al usuario la opcion de regresar al menu principal o terminar
    # el programa
    if input(" Desea regresar al menu principal? (y/n) ") == 'y':
        os.system("cls")
        main_menu()


# Esta funcion obtiene los datos para los parametros pasados por los argumentos
#   n_elements  -> Es el numero de elementos que se calcularan
#   same_charge -> Variable que dice si los elementos tienen la misma carga o
#                  es una carga diferente
#   operation_kind -> Esta variable es mapeada de las opciones
def get_data(n_elements: int, same_charge: bool, operation_kind: str):
    print(" ")
    # Esta es la forma predeterminada para mostrar los datos
    template_output = "{:27}{:>10}".format("{} del elemento {}", ": {}")
    # Si el questionario es erroneo, como por ejemplo:
    #   + 1 varilla y diferentes cargas, es una operacion invalida por lo que
    #     retorna un error
    if (same_charge and n_elements == 1) or (n_elements <= 0):
        print(" Error de opcion...")
        return

    # Limpia la pantalla de la consola, para hacer mas claro el programa
    os.system("cls")
    # Variables que nos ayudaran a calcular los datos de las operaciones
    global_charge = 0
    varillas = []
    # Si todas tienen la misma carga, la pregunta antes de pedir los demas
    # datos de las varillas
    if same_charge:
        print(" ")
        global_charge = float(input(" Carga aplicada(N): "))
        print(" ")

    # Genera un ciclo donde pedira todos los datos de cada varilla
    for index in range(0, n_elements):
        varilla = Varilla()
        # Muestra la varilla donde se esta guardando
        print(f"Datos de la varilla n{index + 1}.")
        # Pide el diametro
        varilla.diametro = float(input(' Diametro(m): '))
        # Si la operacion no es de tipo esfuerzo pide el modulo y la longitud
        # de la varilla
        if not (operation_kind == KindOperation.CALCULATE_EFFORT):
            varilla.elasticidad = float(input(' Módulo de elasticidad(Pa): '))
            varilla.longitud = float(input(' Longitud(m): '))
        # Si todas tiene la misma carga, la carga va a ser igual a la carga global
        # pero en caso de que sean diferentes cargas, pide la carga de la varilla y
        # la suma a las otras cargas ya guardadas y la asigna
        varilla.carga = global_charge \
            if same_charge else \
            sum((v.carga for v in varillas), float(input(' Carga(N): ')))
        print(" ")
        varillas.append(varilla)

    # Si la operacion no es de alargamiento muestra con un ciclo cada una de las
    # varillas y su resultado correspondiente si no, simplemente muestra el resultado
    # de la suma total de las deformaciones(alargamiento)
    if not (operation_kind == KindOperation.CALCULATE_ELONGATION):
        for index, item in enumerate(varillas):
            value = calculate(operation_kind, item)
            print(template_output.format(operation_kind, index + 1, "{0:.6f}".format(value)))
    else:
        value = 0
        for _, item in enumerate(varillas):
            value += calculate(operation_kind, item)
        print(template_output.format(operation_kind, '', "{0:.6f}".format(value)))


# Funcion que apartir de una varilla y el tipo de operacion retorna el
# resultado de la operacion
def calculate(operation_kind: str, varilla: Varilla) -> float:
    value = float(0)
    if operation_kind == KindOperation.CALCULATE_DEFORMATION \
            or operation_kind == KindOperation.CALCULATE_ELONGATION:
        value = varilla.calculate_deformation()
    if operation_kind == KindOperation.CALCULATE_EFFORT:
        value = varilla.calculate_effort()
    return value
# ---------------------------------------------------------------------------------------


# ---------------------------------------------------------------------------------------
#                                      EJECUCION
# ---------------------------------------------------------------------------------------
# Llama al menu principal
main_menu()
