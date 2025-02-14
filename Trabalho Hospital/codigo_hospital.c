#include <stdio.h>
#include <string.h>

#define MAX_PACIENTES 50
#define MAX_MEDICOS 20
#define MAX_CONSULTAS 100

typedef struct {
    int id;
    char nome[50];
    char especialidade[50];
} Medico;

typedef struct {
    int id;
    char nome[50];
    char identidade[20];
    char endereco[100];
    char telefone[15];
    char sexo;
} Paciente;

typedef struct {
    int numero;
    int medico_id;
    int paciente_id;
    char horario[10];
    int duracao;
    char data[11];
} Consulta;

void adicionarMedico(Medico medicos[], int *quantidade) {
    if (*quantidade >= MAX_MEDICOS) {
        printf("Limite de médicos atingido!\n");
        return;
    }

    Medico novo;
    novo.id = *quantidade + 1;
    printf("Nome do médico: ");
    scanf(" %[^\n]", novo.nome);
    printf("Especialidade: ");
    scanf(" %[^\n]", novo.especialidade);

    medicos[*quantidade] = novo;
    (*quantidade)++;
    printf("Médico cadastrado com sucesso!\n");
}

void adicionarPaciente(Paciente pacientes[], int *quantidade) {
    if (*quantidade >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido!\n");
        return;
    }

    Paciente novo;
    novo.id = *quantidade + 1;
    printf("Nome do paciente: ");
    scanf(" %[^\n]", novo.nome);
    printf("Identidade: ");
    scanf(" %[^\n]", novo.identidade);
    printf("Endereço: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", novo.telefone);
    printf("Sexo (M/F): ");
    scanf(" %c", &novo.sexo);

    pacientes[*quantidade] = novo;
    (*quantidade)++;
    printf("Paciente cadastrado com sucesso!\n");
}

void adicionarConsulta(Consulta consultas[], int *quantidade, int qtd_medicos, int qtd_pacientes) {
    if (*quantidade >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido!\n");
        return;
    }

    Consulta nova;
    nova.numero = *quantidade + 1;
    
    printf("ID do médico: ");
    scanf("%d", &nova.medico_id);
    if (nova.medico_id < 1 || nova.medico_id > qtd_medicos) {
        printf("Médico não encontrado!\n");
        return;
    }

    printf("ID do paciente: ");
    scanf("%d", &nova.paciente_id);
    if (nova.paciente_id < 1 || nova.paciente_id > qtd_pacientes) {
        printf("Paciente não encontrado!\n");
        return;
    }

    printf("Horário: ");
    scanf(" %[^\n]", nova.horario);
    printf("Duração (minutos): ");
    scanf("%d", &nova.duracao);
    printf("Data (DD/MM/AAAA): ");
    scanf(" %[^\n]", nova.data);

    consultas[*quantidade] = nova;
    (*quantidade)++;
    printf("Consulta cadastrada com sucesso!\n");
}

void listarConsultasPaciente(Consulta consultas[], int quantidade, int paciente_id) {
    printf("Consultas do Paciente %d:\n", paciente_id);
    for (int i = 0; i < quantidade; i++) {
        if (consultas[i].paciente_id == paciente_id) {
            printf("Consulta %d - Médico ID: %d, Data: %s, Horário: %s\n", 
                   consultas[i].numero, consultas[i].medico_id, consultas[i].data, consultas[i].horario);
        }
    }
}

void listarConsultasMedico(Consulta consultas[], int quantidade, int medico_id) {
    printf("Consultas do Médico %d:\n", medico_id);
    for (int i = 0; i < quantidade; i++) {
        if (consultas[i].medico_id == medico_id) {
            printf("Consulta %d - Paciente ID: %d, Data: %s, Horário: %s\n", 
                   consultas[i].numero, consultas[i].paciente_id, consultas[i].data, consultas[i].horario);
        }
    }
}

void excluirMedico(Medico medicos[], int *qtd_medicos, Consulta consultas[], int *qtd_consultas, int id) {
    for (int i = 0; i < *qtd_medicos; i++) {
        if (medicos[i].id == id) {
            for (int j = i; j < *qtd_medicos - 1; j++) {
                medicos[j] = medicos[j + 1];
            }
            (*qtd_medicos)--;

            for (int k = 0; k < *qtd_consultas; k++) {
                if (consultas[k].medico_id == id) {
                    for (int l = k; l < *qtd_consultas - 1; l++) {
                        consultas[l] = consultas[l + 1];
                    }
                    (*qtd_consultas)--;
                    k--;
                }
            }
            printf("Médico e suas consultas foram excluídos!\n");
            return;
        }
    }
    printf("Médico não encontrado!\n");
}

void excluirPaciente(Paciente pacientes[], int *qtd_pacientes, Consulta consultas[], int *qtd_consultas, int id) {
    for (int i = 0; i < *qtd_pacientes; i++) {
        if (pacientes[i].id == id) {
            for (int j = i; j < *qtd_pacientes - 1; j++) {
                pacientes[j] = pacientes[j + 1];
            }
            (*qtd_pacientes)--;

            for (int k = 0; k < *qtd_consultas; k++) {
                if (consultas[k].paciente_id == id) {
                    for (int l = k; l < *qtd_consultas - 1; l++) {
                        consultas[l] = consultas[l + 1];
                    }
                    (*qtd_consultas)--;
                    k--;
                }
            }
            printf("Paciente e suas consultas foram excluídos!\n");
            return;
        }
    }
    printf("Paciente não encontrado!\n");
}

int main() {
    Medico medicos[MAX_MEDICOS];
    Paciente pacientes[MAX_PACIENTES];
    Consulta consultas[MAX_CONSULTAS];

    int qtd_medicos = 0, qtd_pacientes = 0, qtd_consultas = 0;
    int opcao, id;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1 - Adicionar Médico\n");
        printf("2 - Adicionar Paciente\n");
        printf("3 - Adicionar Consulta\n");
        printf("4 - Listar Consultas de um Paciente\n");
        printf("5 - Listar Consultas de um Médico\n");
        printf("6 - Excluir Médico\n");
        printf("7 - Excluir Paciente\n");
        printf("8 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarMedico(medicos, &qtd_medicos);
                break;
            case 2:
                adicionarPaciente(pacientes, &qtd_pacientes);
                break;
            case 3:
                adicionarConsulta(consultas, &qtd_consultas, qtd_medicos, qtd_pacientes);
                break;
            case 4:
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                listarConsultasPaciente(consultas, qtd_consultas, id);
                break;
            case 5:
                printf("Digite o ID do médico: ");
                scanf("%d", &id);
                listarConsultasMedico(consultas, qtd_consultas, id);
                break;
            case 6:
                printf("Digite o ID do médico: ");
                scanf("%d", &id);
                excluirMedico(medicos, &qtd_medicos, consultas, &qtd_consultas, id);
                break;
            case 7:
                printf("Digite o ID do paciente: ");
                scanf("%d", &id);
                excluirPaciente(pacientes, &qtd_pacientes, consultas, &qtd_consultas, id);
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 8);

    return 0;
}
