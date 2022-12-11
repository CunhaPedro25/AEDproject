# AEDproject

Projeto desenvolvido por:
- [Pedro Cunha](https://github.com/CunhaPedro25)
- [Miguel Alves](https://github.com/Spectralpt/)

## Enunciado:

O Departamento de Informática da ESTG - IPVC, pretende manter um registo organizado do parque
informático. Para tal necessita de um “software” que corresponda aos seguintes requisitos:
- O registo de equipamentos (Computadores e/ou Servidores):
  - **Equipment**
    - Data de aquisição
    - Departamento
    - Garantia (duração em meses)
    - CPU
    - Disco duro
    - Memória RAM
    - Sistema Operativo
    - Aplicações Instaladas
      - Designação
      - Versão
      - License da licença
    - Uma ou mais networkCard de rede
      - Endereço IP
      - Máscara de rede
      - Endereço de broadcast
  - **Efetuar as seguintes operações:**
    - Inserir, mostrar, alterar, eliminar equipamentos.
    - Inserir, mostrar, alterar, eliminar aplicações instaladas.
    - Inserir, mostrar, alterar, eliminar networkCard de rede.
  - **Pesquisar:**
    - Todos os equipamentos:
      - com um dado operatingSystem operativo (e.g. Linux);
      - que pertençam a uma dada rede;
      - com uma dada aplicação.
    - **Listar:**
      - Totais por equipment ou departamento:
      - de MIPS (million instructions per second, considere 1250 MIPS por cada
        GHz);
      - de memória;
      - capacidade dos disk duros.
      - Equipamentos com menos de determinado valor em memória RAM.
      - Equipamentos pertencentes a determinado departamento ou rede.
      - Equipamentos cuja warranty expirou.
      - Equipamentos com aplicações cuja license da licença expirou.
    - **Detetar possíveis problemas:**
      - Dois equipamentos com o mesmo endereço IP.
    - **Outras funcionalidades:**
      - Determinar se dois equipamentos podem comunicar, ou seja, se estão na mesma
        rede

## Objetivos:

Minimo:
- [x] Estrutura de dados dos equipamentos
- [x] Criar menus
- [ ] Funções para inserir equipamentos, aplicações, e networkCard de rede
- [ ] Listar equipamentos e aplicações

Maior Dificuldade:
- [ ] Pesquisar Equipamentos
- [ ] Determinar se dois equipamentos estão na mesma rede
