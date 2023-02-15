/**
 * \file            graph.h
 * \brief           header file containing the declaration of the graph data structure and operations.
 */

#ifndef GRAPH
#define GRAPH

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "datatype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           structure representing a single edge of the graph.
 * \note            each edge is considered a segment between vertices x and y. We can store only the y vertex inside the edge as the x vertex is used as
 *                  index in the edges array of the graph structure.
 *                  This is not an hypergraph, edges connecting more than 2 vertices are not supported.
 */
typedef struct edgenode_t {
    size_t y;              /* adjacency info */
    int32_t weight;        /* edge weight, if any */
    char* label;           /* label, if any */
    struct edgenode* next; /* next edge in list */
} edgenode_t;

/**
 * \brief           graph data structure.
 * \note            This implementation uses an adjacency list to store  the neighbors of each vertex.
 *                  This is not an hypergraph, edges connecting more than 2 vertices are not supported.
 */
typedef struct {
    edgenode_t** edges; /* adjacency info */
    size_t nvertices;   /* number of vertices in the graph */
    size_t nedges;      /* number of edges in the graph */
    bool is_directed;   /* flag indicating whether the graph is directed or not */
} graph_t;

__declspec(dllexport) graph_t* graph_construct(size_t vertices_size, bool directed);
__declspec(dllexport) void graph_insert_edge(graph_t* graph, size_t x, size_t y, int32_t weight, char* label);
__declspec(dllexport) void graph_remove_edge(graph_t* graph, size_t x, size_t y);
__declspec(dllexport) void graph_clear(graph_t** graph);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !GRAPH