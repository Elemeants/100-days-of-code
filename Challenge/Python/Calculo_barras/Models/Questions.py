
def form_template(questions: []) -> []:
    output_values = []
    for index, question in enumerate(questions):
        output_values.append(input(f" {index + 1} -> {question} "))
    return output_values
