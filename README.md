# Notas Aulas Sobre Projeto AED 2

## Objetivos

### Criar Grafo a partir dos ficheiros dados (2 opções):

- Criar um único grafo mais completo para todas as tarefas pedidas.

-Criar vários grafos com caraterísticas diferentes, feitos de forma especializada para uma tarefa específica.

### Interface / Menu

- Menu simples com listagem das funcionalidades que o utilizador pode usar.
- Deve ser "amigável", tornando explícito ao utilizador o que faz cada funcionalidade.

### Diferentes tipos de "Local"

- Uma paragem específica
- Um par de coordenadas, através dos quais se indicam paragens próximas

### "Melhor Percurso"

O programa deve verificar o Melhor Percurso segundo vários critérios diferentes como (exemplos):

- O que passa em menos paragens
- O que percorre menor distância
- O que implica menos mudanças de autocarro/linha
- O que passa muda menos vezes de zona
(...)

### Mudar de Autocarro

Ao mudar de linha, também deve ser possível mudar de paragem para uma paragem vizinha (a menos de uma certa distância da paragem em que saiu).

### Usar Pelo Menos Uma Vez:

- Pesquisa em Largura (BFS) para grafos não pesados

- Algoritmo de Dijkstra para grafos pesados

### Calcular Distâncias com Longitude e Latitude

- Fórmula de Haversine e Implementação no Enunciado

### Documentação Doxygen

Comentar complexidade temporal de métodos mais algorítmicos

## Extras (Opcionais)

- Permitir selecionar viagens diurnas ou noturnas (Prefixo M)

- Cálculo de Minimum Spanning Trees

- Possibilitar fecho de paragens ou linhas (o utilizador ser capaz de definir paragens/linhas por onde não quer passar)

- Adicionar outros meios de transporte (metro/comboio)

## Sugestões de Implementação

### Acrescentar atributos ao Node

- Estação
- Zona

**Nota:** Talvez acrescentar Linha às edges também?

Se quisermos referir-nos aos nodes com ids inteiros, fazer um map que converta cada inteiro numa string correspondente ao código dessa estação.


### Algoritmo de Dijkstra

#### Pseudo-Código

**Cálculo da Menor Distância:** Determina apenas a menor distância entre os dois pontos

```
Dijkstra (G,s) --> sendo G um grafo e s o nó onde começamos
  Para todos os nós v de G fazer:
    v-dist <- infinito
    v-visited <- false
  s.dist <- 0
  Enquanto houver nós não visitados fazer:
    Escolher nó não visitado u com a menor distância //caminho mais curto (podemos usar Heaps ou BSTs, por exemplo - demonstradas na aula teórica 2 da última semana)
    Para cada aresta (u,v) de G fazer:
      Se v.visited = false e u.dist + weight(u,v) < v.dist então:
        v.dist <- u.dist + weight(u,v)
```
**Cálculo do Menor Caminho:** Adiciona-se um int pred ao nó que guarda o nó que lhe precede no caminho

```
Dijkstra (G,s) --> sendo G um grafo e s o nó onde começamos
  Para todos os nós v de G fazer:
    v-dist <- infinito
    v-visited <- false
  s.dist <- 0
  s.pred <- s
  Enquanto houver nós não visitados fazer:
    Escolher nó não visitado u com a menor distância //caminho mais curto
    Para cada aresta (u,v) de G fazer:
      Se v.visited = false e u.dist + weight(u,v) < v.dist então:
        v.dist <- u.dist + weight(u,v)
        v.pred <- u
```
