import os
from Models.Varilla import Varilla
from Models.Questions import form_template
from Models.KindOperation import KindOperation


def calcualte_effort(n_elements: int, same_charge: bool):
    print(" ")
    output_type = "N/m^2"
    template_output = "{:27}{:>10} {}".format("{} del elemento {}", ": {}", output_type)
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
        template_questions = [' Diametro(m):']
        if not same_charge:
            template_questions.append(' Carga(N): ')
        varilla_data = form_template(template_questions)

        varilla.diametro = float(varilla_data[0])
        varilla.carga = global_charge \
            if same_charge else \
            sum((v.carga for v in varillas), float(varilla_data[1]))
        print(" ")
        varillas.append(varilla)

    for index, item in enumerate(varillas):
        print(template_output.format(KindOperation.CALCULATE_DEFORMATION,
                index + 1, "{0:.4E}".format(item.calculate_effort()).replace('E', ' E')))
