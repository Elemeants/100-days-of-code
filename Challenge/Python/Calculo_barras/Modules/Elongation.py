import os
from Models.Varilla import Varilla
from Models.Questions import form_template


def calcualte_elongation(n_elements: int, same_charge: bool):
    print(" ")
    output_type = "mts"
    template_output = "El alargamiento es: {:>10} {}".format(": {}", output_type)
    if (same_charge and n_elements == 1) or (n_elements <= 0):
        print(" Error de opcion...")
        return
    os.system("cls")
    global_charge = 0
    varillas = []
    if same_charge:
        print(" ")
        global_charge = float(input(" Carga aplicada(N): "))
        print(" ")

    for index in range(0, n_elements):
        varilla = Varilla()
        print(f"Datos de la varilla n{index + 1}.")
        template_questions = [' Diametro(m):', ' Módulo de elasticidad(Pa): ', ' Longitud(m): ']
        if not same_charge:
            template_questions.append(' Carga(N): ')
        varilla_data = form_template(template_questions)

        varilla.diametro = float(varilla_data[0])
        varilla.elasticidad = float(varilla_data[1])
        varilla.longitud = float(varilla_data[2])
        varilla.carga = global_charge \
            if same_charge else \
            sum((v.carga for v in varillas), float(varilla_data[3]))
        print(" ")
        varillas.append(varilla)

    total_elongation = float(0)
    for _, item in enumerate(varillas):
        total_elongation += item.calculate_deformation()

    print(template_output.format("{0:.4E}".format(total_elongation).replace('E', ' E')))
