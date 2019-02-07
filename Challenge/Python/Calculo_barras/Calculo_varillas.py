# ---------------------------------------------------------------------------------------
#    Calculo_varillas.py
#        - Este codigo permite calcular la deformacion, alargamiento y esfuerzo de
#          N cantidad de varillas con la misma o diferente carga
#    v.1.0 - 05/02/2019
# ---------------------------------------------------------------------------------------

# Se importa Os para limpiar la consola
import os
from Models.Questions import form_template
from Models.KindOperation import KindOperation
from Modules.Deformation import calcualte_deformation
from Modules.Effort import calcualte_effort
from Modules.Elongation import calcualte_elongation
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
    option_selected = int(input(" -> "))
    # Mapeo de la opcions seleccionada al resultado
    result = int(-1)
    if option_selected == 1:
        result = KindOperation.CALCULATE_DEFORMATION
    if option_selected == 2:
        result = KindOperation.CALCULATE_EFFORT
    if option_selected == 3:
        result = KindOperation.CALCULATE_ELONGATION
    if option_selected == 4:
        print("\n Terminando el programa")
        return
    if result == -1:
        print("\n Opcion no valida")
        return

    # Limpia la pantalla de la consola, para hacer mas claro el programa
    os.system("cls")
    print(result.replace('', ' '))
    # Mostramos las preguntas y obtenemos la respuesta de cada una
    output_values = form_template([
        "De cuántos elementos esta formada la varilla?",
        "Tiene mas de una carga aplicada(y, n)?"
    ])
    # Llamamos a la funcion que obtendra los datos y calculara el resultado
    # de la operacion seleccionada
    is_same_charge = not output_values[1] == 'y'

    if result == KindOperation.CALCULATE_DEFORMATION:
        calcualte_deformation(int(output_values[0]), is_same_charge)
    if result == KindOperation.CALCULATE_ELONGATION:
        calcualte_elongation(int(output_values[0]), is_same_charge)
    if result == KindOperation.CALCULATE_EFFORT:
        calcualte_effort(int(output_values[0]), is_same_charge)
    # Se le da al usuario la opcion de regresar al menu principal o terminar
    # el programa
    if input(" Desea regresar al menu principal? (y/n) ") == 'y':
        os.system("cls")
        main_menu()
# ---------------------------------------------------------------------------------------


# ---------------------------------------------------------------------------------------
#                                      EJECUCION
# ---------------------------------------------------------------------------------------
# Llama al menu principal
main_menu()
