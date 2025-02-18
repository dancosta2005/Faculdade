#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#define MAX_MEDICOS 20
#define MAX_PACIENTES 50
#define MAX_CONSULTAS 100

// Estruturas
typedef struct {
    int id;
    char nome[100];
    char especialidade[50];
} Medico;

typedef struct {
    int id;
    char nome[100];
    char identidade[20];
    char endereco[200];
    char telefone[20];
    char sexo[10];
} Paciente;

typedef struct {
    int numero;
    int idMedico;
    int idPaciente;
    char horario[20];
    int duracao; // duração em minutos
    char data[20];
} Consulta;

// Declarações de protótipo das funções
Medico* pesquisarMedico(int id);
Paciente* pesquisarPaciente(int id);
int verificarConflitoHorario(int idMedico, int idPaciente, const char* horario, const char* data, int numeroConsulta);
void alterarPaciente();
void alterarMedico();

// Variáveis globais para armazenar os registros
Medico medicos[MAX_MEDICOS];
Paciente pacientes[MAX_PACIENTES];
Consulta consultas[MAX_CONSULTAS];

// Contadores para os registros
int numMedicos = 0;
int numPacientes = 0;
int numConsultas = 0;

// Funções auxiliares para exibir um médico, paciente ou consulta
void exibirMedico(Medico m) {
    printf("ID: %d, Nome: %s, Especialidade: %s\n", m.id, m.nome, m.especialidade);
}

void exibirPaciente(Paciente p) {
    printf("ID: %d, Nome: %s, Identidade: %s, Endereço: %s, Telefone: %s, Sexo: %s\n", 
            p.id, p.nome, p.identidade, p.endereco, p.telefone, p.sexo);
}

void exibirConsulta(Consulta c) {
    printf("Número: %d, Médico ID: %d, Paciente ID: %d, Horário: %s, Duração: %d minutos, Data: %s\n", 
            c.numero, c.idMedico, c.idPaciente, c.horario, c.duracao, c.data);
}

// Função para verificar conflitos de horário
int verificarConflitoHorario(int idMedico, int idPaciente, const char* horario, const char* data, int numeroConsulta) {
    for (int i = 0; i < numConsultas; i++) {
        // Ignora a consulta que está sendo alterada
        if (consultas[i].numero == numeroConsulta) {
            continue;
        }
        if (strcmp(consultas[i].data, data) == 0 && strcmp(consultas[i].horario, horario) == 0) {
            if (consultas[i].idMedico == idMedico) {
                printf("Erro: O médico já possui uma consulta marcada neste horário e data.\n");
                return 1; // Conflito encontrado
            }
            if (consultas[i].idPaciente == idPaciente) {
                printf("Erro: O paciente já possui uma consulta marcada neste horário e data.\n");
                return 1; // Conflito encontrado
            }
        }
    }
    return 0; // Sem conflitos
}

// Funções de cadastro
void cadastrarMedico() {
    if (numMedicos >= MAX_MEDICOS) {
        printf("Limite de médicos atingido.\n");
        return;
    }

    Medico m;
    printf("Digite o ID do médico: ");
    scanf("%d", &m.id);
    getchar(); // Limpa o buffer

    // Verifica se o ID já existe
    for (int i = 0; i < numMedicos; i++) {
        if (medicos[i].id == m.id) {
            printf("Erro: ID já existe.\n");
            return;
        }
    }

    printf("Digite o nome do médico: ");
    fgets(m.nome, 100, stdin);
    m.nome[strcspn(m.nome, "\n")] = 0;
    printf("Digite a especialidade: ");
    fgets(m.especialidade, 50, stdin);
    m.especialidade[strcspn(m.especialidade, "\n")] = 0;
    medicos[numMedicos++] = m;
    printf("Médico cadastrado com sucesso!\n");
}

void cadastrarPaciente() {
    if (numPacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }

    Paciente p;
    printf("Digite o ID do paciente: ");
    scanf("%d", &p.id);
    getchar(); // Limpa o buffer

    // Verifica se o ID já existe
    for (int i = 0; i < numPacientes; i++) {
        if (pacientes[i].id == p.id) {
            printf("Erro: ID já existe.\n");
            return;
        }
    }

    printf("Digite o nome do paciente: ");
    fgets(p.nome, 100, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;
    printf("Digite a identidade do paciente: ");
    fgets(p.identidade, 20, stdin);
    p.identidade[strcspn(p.identidade, "\n")] = 0;
    printf("Digite o endereço do paciente: ");
    fgets(p.endereco, 200, stdin);
    p.endereco[strcspn(p.endereco, "\n")] = 0;
    printf("Digite o telefone do paciente: ");
    fgets(p.telefone, 20, stdin);
    p.telefone[strcspn(p.telefone, "\n")] = 0;
    printf("Digite o sexo do paciente: ");
    fgets(p.sexo, 10, stdin);
    p.sexo[strcspn(p.sexo, "\n")] = 0;
    pacientes[numPacientes++] = p;
    printf("Paciente cadastrado com sucesso!\n");
}

void cadastrarConsulta() {
    if (numConsultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    Consulta c;
    printf("Digite o número da consulta: ");
    scanf("%d", &c.numero);
    getchar(); // Limpa o buffer

    // Verifica se o número da consulta já existe
    for (int i = 0; i < numConsultas; i++) {
        if (consultas[i].numero == c.numero) {
            printf("Erro: Número de consulta já existe.\n");
            return;
        }
    }

    printf("Digite o ID do médico: ");
    scanf("%d", &c.idMedico);
    // Verifica se o médico existe
    if (pesquisarMedico(c.idMedico) == NULL) {
        printf("Erro: Médico não encontrado.\n");
        return;
    }

    printf("Digite o ID do paciente: ");
    scanf("%d", &c.idPaciente);
    // Verifica se o paciente existe
    if (pesquisarPaciente(c.idPaciente) == NULL) {
        printf("Erro: Paciente não encontrado.\n");
        return;
    }

    getchar(); // Limpa o buffer
    printf("Digite o horário da consulta: ");
    fgets(c.horario, 20, stdin);
    c.horario[strcspn(c.horario, "\n")] = 0;
    printf("Digite a duração da consulta (em minutos): ");
    scanf("%d", &c.duracao);
    getchar(); // Limpa o buffer
    printf("Digite a data da consulta: ");
    fgets(c.data, 20, stdin);
    c.data[strcspn(c.data, "\n")] = 0;

    // Verifica conflitos de horário e data
    if (verificarConflitoHorario(c.idMedico, c.idPaciente, c.horario, c.data, -1)) {
        printf("Erro: Conflito de horário e data detectado.\n");
        return;
    }

    consultas[numConsultas++] = c;
    printf("Consulta cadastrada com sucesso!\n");
}

// Funções de pesquisa por ID
Medico* pesquisarMedico(int id) {
    for (int i = 0; i < numMedicos; i++) {
        if (medicos[i].id == id) {
            return &medicos[i];
        }
    }
    return NULL;
}

Paciente* pesquisarPaciente(int id) {
    for (int i = 0; i < numPacientes; i++) {
        if (pacientes[i].id == id) {
            return &pacientes[i];
        }
    }
    return NULL;
}

Consulta* pesquisarConsulta(int numero) {
    for (int i = 0; i < numConsultas; i++) {
        if (consultas[i].numero == numero) {
            return &consultas[i];
        }
    }
    return NULL;
}

// Funções de alteração
void alterarPaciente() {
    int id;
    printf("Digite o ID do paciente a ser alterado: ");
    scanf("%d", &id);
    Paciente* p = pesquisarPaciente(id);
    if (p != NULL) {
        printf("Paciente encontrado! Dados atuais:\n");
        exibirPaciente(*p);
        getchar(); // Limpa o buffer
        printf("Digite o novo nome do paciente: ");
        fgets(p->nome, 100, stdin);
        p->nome[strcspn(p->nome, "\n")] = 0;
        printf("Digite a nova identidade: ");
        fgets(p->identidade, 20, stdin);
        p->identidade[strcspn(p->identidade, "\n")] = 0;
        printf("Digite o novo endereço: ");
        fgets(p->endereco, 200, stdin);
        p->endereco[strcspn(p->endereco, "\n")] = 0;
        printf("Digite o novo telefone: ");
        fgets(p->telefone, 20, stdin);
        p->telefone[strcspn(p->telefone, "\n")] = 0;
        printf("Digite o novo sexo: ");
        fgets(p->sexo, 10, stdin);
        p->sexo[strcspn(p->sexo, "\n")] = 0;
        printf("Dados do paciente alterados com sucesso!\n");
    } else {
        printf("Paciente não encontrado!\n");
    }
}

void alterarMedico() {
    int id;
    printf("Digite o ID do médico a ser alterado: ");
    scanf("%d", &id);
    Medico* m = pesquisarMedico(id);
    if (m != NULL) {
        printf("Médico encontrado! Dados atuais:\n");
        exibirMedico(*m);
        getchar(); // Limpa o buffer
        printf("Digite o novo nome do médico: ");
        fgets(m->nome, 100, stdin);
        m->nome[strcspn(m->nome, "\n")] = 0;
        printf("Digite a nova especialidade: ");
        fgets(m->especialidade, 50, stdin);
        m->especialidade[strcspn(m->especialidade, "\n")] = 0;
        printf("Dados do médico alterados com sucesso!\n");
    } else {
        printf("Médico não encontrado!\n");
    }
}

void alterarConsulta() {
    int numero;
    printf("Digite o número da consulta a ser alterada: ");
    scanf("%d", &numero);
    Consulta* c = pesquisarConsulta(numero);
    if (c != NULL) {
        printf("Consulta encontrada! Dados atuais:\n");
        exibirConsulta(*c);
        getchar(); // Limpa o buffer

        // Alterar número da consulta
        printf("Digite o novo número da consulta (ou pressione Enter para manter o atual): ");
        char input[20];
        fgets(input, 20, stdin);
        if (strlen(input) > 1) { // Se o usuário digitou algo
            int novoNumero = atoi(input);
            // Verifica se o novo número já existe
            if (pesquisarConsulta(novoNumero) != NULL) {
                printf("Erro: Número de consulta já existe.\n");
                return;
            }
            c->numero = novoNumero;
        }

        // Alterar ID do médico
        printf("Digite o novo ID do médico (ou pressione Enter para manter o atual): ");
        fgets(input, 20, stdin);
        if (strlen(input) > 1) {
            int novoIdMedico = atoi(input);
            if (pesquisarMedico(novoIdMedico) == NULL) {
                printf("Erro: Médico não encontrado.\n");
                return;
            }
            c->idMedico = novoIdMedico;
        }

        // Alterar ID do paciente
        printf("Digite o novo ID do paciente (ou pressione Enter para manter o atual): ");
        fgets(input, 20, stdin);
        if (strlen(input) > 1) {
            int novoIdPaciente = atoi(input);
            if (pesquisarPaciente(novoIdPaciente) == NULL) {
                printf("Erro: Paciente não encontrado.\n");
                return;
            }
            c->idPaciente = novoIdPaciente;
        }

        // Alterar horário
        printf("Digite o novo horário da consulta (ou pressione Enter para manter o atual): ");
        fgets(input, 20, stdin);
        if (strlen(input) > 1) {
            strcpy(c->horario, input);
            c->horario[strcspn(c->horario, "\n")] = 0;
        }

        // Alterar duração
        printf("Digite a nova duração (em minutos) (ou pressione Enter para manter a atual): ");
        fgets(input, 20, stdin);
        if (strlen(input) > 1) {
            c->duracao = atoi(input);
        }

        // Alterar data
        printf("Digite a nova data da consulta (ou pressione Enter para manter a atual): ");
        fgets(input, 20, stdin);
        if (strlen(input) > 1) {
            strcpy(c->data, input);
            c->data[strcspn(c->data, "\n")] = 0;
        }

        // Verifica conflitos de horário e data após alteração
        if (verificarConflitoHorario(c->idMedico, c->idPaciente, c->horario, c->data, c->numero)) {
            printf("Erro: Conflito de horário e data detectado após alteração.\n");
            return;
        }

        printf("Dados da consulta alterados com sucesso!\n");
    } else {
        printf("Consulta não encontrada!\n");
    }
}

// Funções de exclusão
void excluirMedico() {
    int id;
    printf("Digite o ID do médico a ser excluído: ");
    scanf("%d", &id);
    Medico* m = pesquisarMedico(id);
    if (m != NULL) {
        // Excluir todas as consultas associadas ao médico
        for (int i = 0; i < numConsultas; i++) {
            if (consultas[i].idMedico == id) {
                printf("Consulta excluída: ");
                exibirConsulta(consultas[i]);
                for (int j = i; j < numConsultas - 1; j++) {
                    consultas[j] = consultas[j + 1];
                }
                numConsultas--;
                i--; // Verificar novamente a posição após a remoção
            }
        }
        printf("Médico excluído: ");
        exibirMedico(*m);
        // Remover médico
        for (int i = 0; i < numMedicos; i++) {
            if (medicos[i].id == id) {
                for (int j = i; j < numMedicos - 1; j++) {
                    medicos[j] = medicos[j + 1];
                }
                numMedicos--;
                break;
            }
        }
    } else {
        printf("Médico não encontrado!\n");
    }
}

void excluirPaciente() {
    int id;
    printf("Digite o ID do paciente a ser excluído: ");
    scanf("%d", &id);
    Paciente* p = pesquisarPaciente(id);
    if (p != NULL) {
        // Excluir todas as consultas associadas ao paciente
        for (int i = 0; i < numConsultas; i++) {
            if (consultas[i].idPaciente == id) {
                printf("Consulta excluída: ");
                exibirConsulta(consultas[i]);
                for (int j = i; j < numConsultas - 1; j++) {
                    consultas[j] = consultas[j + 1];
                }
                numConsultas--;
                i--; // Verificar novamente a posição após a remoção
            }
        }
        printf("Paciente excluído: ");
        exibirPaciente(*p);
        // Remover paciente
        for (int i = 0; i < numPacientes; i++) {
            if (pacientes[i].id == id) {
                for (int j = i; j < numPacientes - 1; j++) {
                    pacientes[j] = pacientes[j + 1];
                }
                numPacientes--;
                break;
            }
        }
    } else {
        printf("Paciente não encontrado!\n");
    }
}

void excluirConsulta() {
    int numero;
    printf("Digite o número da consulta a ser excluída: ");
    scanf("%d", &numero);
    Consulta* c = pesquisarConsulta(numero);
    if (c != NULL) {
        printf("Consulta excluída: ");
        exibirConsulta(*c);
        // Remover consulta
        for (int i = 0; i < numConsultas; i++) {
            if (consultas[i].numero == numero) {
                for (int j = i; j < numConsultas - 1; j++) {
                    consultas[j] = consultas[j + 1];
                }
                numConsultas--;
                break;
            }
        }
    } else {
        printf("Consulta não encontrada!\n");
    }
}

// Funções de relatórios
void relatorioConsultasPaciente() {
    int id;
    printf("Digite o ID do paciente para exibir as consultas: ");
    scanf("%d", &id);
    printf("Consultas agendadas para o paciente ID %d:\n", id);
    for (int i = 0; i < numConsultas; i++) {
        if (consultas[i].idPaciente == id) {
            exibirConsulta(consultas[i]);
        }
    }
}

void relatorioConsultasMedico() {
    int id;
    printf("Digite o ID do médico para exibir as consultas: ");
    scanf("%d", &id);
    printf("Consultas agendadas para o médico ID %d:\n", id);
    for (int i = 0; i < numConsultas; i++) {
        if (consultas[i].idMedico == id) {
            exibirConsulta(consultas[i]);
        }
    }
}

void relatorioPacientesPorEspecialidade() {
    char especialidade[50];
    printf("Digite a especialidade para exibir os pacientes: ");
    getchar(); // Limpa o buffer
    fgets(especialidade, 50, stdin);
    especialidade[strcspn(especialidade, "\n")] = 0;

    printf("Pacientes associados à especialidade %s:\n", especialidade);
    for (int i = 0; i < numMedicos; i++) {
        if (strcmp(medicos[i].especialidade, especialidade) == 0) {
            printf("Médico: %s\n", medicos[i].nome);
            for (int j = 0; j < numConsultas; j++) {
                if (consultas[j].idMedico == medicos[i].id) {
                    Paciente* p = pesquisarPaciente(consultas[j].idPaciente);
                    if (p != NULL) {
                        exibirPaciente(*p);
                    }
                }
            }
        }
    }
}

// Funções para listar todos os registros
void listarTodosMedicos() {
    printf("Lista de todos os médicos cadastrados:\n");
    for (int i = 0; i < numMedicos; i++) {
        exibirMedico(medicos[i]);
    }
}

void listarTodosPacientes() {
    printf("Lista de todos os pacientes cadastrados:\n");
    for (int i = 0; i < numPacientes; i++) {
        exibirPaciente(pacientes[i]);
    }
}

void listarTodasConsultas() {
    printf("Lista de todas as consultas cadastradas:\n");
    for (int i = 0; i < numConsultas; i++) {
        exibirConsulta(consultas[i]);
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura a localização

    int opcao;

    do {
        printf("\n1 – Consulta\n");
        printf("2 – Paciente\n");
        printf("3 – Médico\n");
        printf("4 – Relatórios\n");
        printf("5 – Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\n1 – Cadastrar Consulta\n");
                printf("2 – Alterar Consulta\n");
                printf("3 – Excluir Consulta\n");
                printf("Escolha uma opção: ");
                int opConsulta;
                scanf("%d", &opConsulta);
                if (opConsulta == 1) {
                    cadastrarConsulta();
                } else if (opConsulta == 2) {
                    alterarConsulta();
                } else if (opConsulta == 3) {
                    excluirConsulta();
                }
                break;
            case 2:
                printf("\n1 – Cadastrar Paciente\n");
                printf("2 – Alterar Paciente\n");
                printf("3 – Excluir Paciente\n");
                printf("Escolha uma opção: ");
                int opPaciente;
                scanf("%d", &opPaciente);
                if (opPaciente == 1) {
                    cadastrarPaciente();
                } else if (opPaciente == 2) {
                    alterarPaciente();
                } else if (opPaciente == 3) {
                    excluirPaciente();
                }
                break;
            case 3:
                printf("\n1 – Cadastrar Médico\n");
                printf("2 – Alterar Médico\n");
                printf("3 – Excluir Médico\n");
                printf("Escolha uma opção: ");
                int opMedico;
                scanf("%d", &opMedico);
                if (opMedico == 1) {
                    cadastrarMedico();
                } else if (opMedico == 2) {
                    alterarMedico();
                } else if (opMedico == 3) {
                    excluirMedico();
                }
                break;
            case 4:
                printf("\n1 – Lista de Consultas Agendadas para o Paciente\n");
                printf("2 – Lista de Consultas Agendadas para o Médico\n");
                printf("3 – Lista de Pacientes por Especialidade\n");
                printf("4 – Listar Todos os Médicos\n");
                printf("5 – Listar Todos os Pacientes\n");
                printf("6 – Listar Todas as Consultas\n");
                printf("Escolha uma opção: ");
                int opRelatorio;
                scanf("%d", &opRelatorio);
                if (opRelatorio == 1) {
                    relatorioConsultasPaciente();
                } else if (opRelatorio == 2) {
                    relatorioConsultasMedico();
                } else if (opRelatorio == 3) {
                    relatorioPacientesPorEspecialidade();
                } else if (opRelatorio == 4) {
                    listarTodosMedicos();
                } else if (opRelatorio == 5) {
                    listarTodosPacientes();
                } else if (opRelatorio == 6) {
                    listarTodasConsultas();
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
