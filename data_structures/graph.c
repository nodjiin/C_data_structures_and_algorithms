/**
 * \file            graph.c
 * \brief           source file containing the definition of graph operations.
 */

#include <stdio.h>;
#include <stdlib.h>;
#include "memalloc.h";
#include "exitcodes.h";
#include "graph.h";

/**
 * \brief           construct a new graph.
 * \param[in]       vertices_size: number of vertices that the graph will be able to contain after initialization. 0 is not considered a valid input, 
 *                  and will result in a program early exit with INVALID_INPUT code.
 * \param[in]       directed: parameter indicating whether the graph should be directed, or not.
 * \return          a pointer the newly constructed graph.
 * \relates         graph_t
 */
graph_t*
graph_construct(size_t vertices_size, bool directed) {
    graph_t* new_graph;

    if (vertices_size == 0) {
        fprintf(stderr, "[graph_construct] Invalid input. Faulty construct request with vertices size 0.\n");
        exit(INVALID_INPUT);
    }

    new_graph = malloc_s(sizeof(graph_t));
    new_graph->edges = calloc_s(vertices_size, sizeof(edgenode_t*));
    new_graph->is_directed = directed;
    new_graph->nvertices = vertices_size;
    new_graph->nedges = 0;

    return new_graph;
}

/**
 * \brief           insert x->y in graph, if the graph is undirected insert also the y->x edge.
 * \param[in]       graph: graph pointer.
 * \param[in]       x: vertex from which the edge starts.
 * \param[in]       y: vertex towards which the edge is directed.
 * \param[in]       weight: weight of the edge.
 * \param[in]       directed: value indicating if the edge is directed or not.
 */
static void
insert_edge(graph_t* graph, size_t x, size_t y, data_type weight, bool directed) {
    edgenode_t* edge;

    edge = malloc_s(sizeof(edgenode_t));
    edge->weight = weight;
    edge->y = y;
    edge->next = graph->edges[x];
    graph->edges[x] = edge; /* insert the edge at the head of the list */

    if (!directed) { /* if the edge is not directed insert a copy at index y */
        insert_edge(graph, y, x, weight, true);
    }
}

/**
 * \brief           insert a new edge between vertices x and y in graph.
 * \param[in]       graph: graph pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       x: vertex from which the edge starts. Trying to insert an edge with index greater than vertices size will result in an early 
 *                  exit with invalid input status code.
 * \param[in]       y: vertex towards which the edge is directed. Trying to insert an edge with index greater than vertices size will result in an early 
 *                  exit with invalid input status code.
 * \param[in]       weight: weight of the edge.
 * \relates         graph_t
 */
void
graph_insert_edge(graph_t* graph, size_t x, size_t y, data_type weight) {
    if (graph == NULL) {
        fprintf(stderr, "[graph_insert_edge] Invalid input. Faulty edge insert request on NULL graph.\n");
        exit(INVALID_INPUT);
    }

    if (x >= graph->nvertices) {
        fprintf(stderr,
                "[graph_insert_edge] Invalid input. Faulty edge insert request with x vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                x, graph->nvertices);
        exit(INVALID_INPUT);
    }

    if (y >= graph->nvertices) {
        fprintf(stderr,
                "[graph_insert_edge] Invalid input. Faulty edge insert request with y vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                y, graph->nvertices);
        exit(INVALID_INPUT);
    }

    insert_edge(graph, x, y, weight, graph->is_directed);
    graph->nedges++;
}

/**
 * \brief           remove an edge from the graph.
 * \param[in]       graph: graph pointer.
 * \param[in]       x: vertex from which the edge starts. 
 * \param[in]       y: vertex towards which the edge is directed.
 * \param[in]       directed: value indicating if the edge is directed or not.
 */
static void
remove_edge(graph_t* graph, size_t x, size_t y, bool directed) {
    edgenode_t *edge, *to_free;

    edge = graph->edges[x];
    if (edge == NULL) {
        return;
    }

    if (edge->y == y) { /* if the edge is the first element of the list, we can remove it directly */
        graph->edges[x] = edge->next;
        free(edge);
    } else { /* otherwise we iterate the list to find it */
        while (edge->next != NULL && edge->next->y != y) {
            edge = edge->next;
        }

        if (edge->next != NULL) { /* safety check in case we didn't find it */
            to_free = edge->next;
            edge->next = edge->next->next;
            free(to_free);
        }
    }

    if (!directed) { /* if the edge is not directed remove its copy at index y */
        remove_edge(graph, y, x, true);
    }
}

/**
 * \brief           remove an edge from the graph.
 * \param[in]       graph: graph pointer. `NULL` is not considered a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param[in]       x: vertex from which the edge starts. Trying to insert an edge with index greater than vertices size will result in an early 
 *                  exit with invalid input status code.
 * \param[in]       y: vertex towards which the edge is directed. Trying to insert an edge with index greater than vertices size will result in an early 
 *                  exit with invalid input status code.
 * \note            trying to remove an edge not present in the graph, but whose coordinates respect its maximum size will not result in an error.
 * \relates         graph_t
 */
void
graph_remove_edge(graph_t* graph, size_t x, size_t y) {
    if (graph == NULL) {
        fprintf(stderr, "[graph_remove_edge] Invalid input. Faulty edge remove request on NULL graph.\n");
        exit(INVALID_INPUT);
    }

    if (x >= graph->nvertices) {
        fprintf(stderr,
                "[graph_remove_edge] Invalid input. Faulty edge remove request with x vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                x, graph->nvertices);
        exit(INVALID_INPUT);
    }

    if (y >= graph->nvertices) {
        fprintf(stderr,
                "[graph_remove_edge] Invalid input. Faulty edge remove request with y vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                y, graph->nvertices);
        exit(INVALID_INPUT);
    }

    remove_edge(graph, x, y, graph->is_directed);
    graph->nedges--;
}

/**
 * \brief           free the given graph.
 * \param[in]       graph: pointer to graph pointer.
 * \note            this function will free the memory used by the graph. The input pointer itself will be set to `NULL`.
 * \relates         graph_t
 */
void
graph_clear(graph_t** graph) {
    if (graph == NULL || *graph == NULL) {
        return;
    }

    for (size_t i = 0; i < (*graph)->nvertices; i++) {
        edgenode_t *edge, *to_free;

        edge = (*graph)->edges[i];
        while (edge != NULL) {
            to_free = edge;
            edge = edge->next;
            free(to_free);
        }
    }

    free_s(*graph);
}