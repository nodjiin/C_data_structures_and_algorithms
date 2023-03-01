/**
 * \file            search.h
 * \brief           header file containing the declaration of search algorithms implemented in this library.
 */

#ifndef SEARCH
#define SEARCH

#include <stdlib.h>
#include <limits.h>
#include "data_structures/graph.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GRAPH_PARENT_UNDEFINED SIZE_MAX

/**
 * \brief           structure that represents a queue of vertices.
 * \note            this structure is used to store the vertices that need to be visited during graph traversal.
 */
typedef struct {
    size_t* vertices; /*!< array of vertices. */
    size_t start;     /*!< index of the first element in the queue */
    size_t end;       /*!< index of the last element in the queue */
} vertices_queue_t;

/**
* \brief            function pointer type that defines a callback for processing a vertex.
* \param[in]        vertex: vertex to process.
* \note             this type is used to pass a function that performs some action on a vertex during graph traversal.
*                   The function takes a size_t parameter that represents the vertex number, and returns void
*/
typedef void (*process_vertex_fn)(size_t vertex);

/**
* \brief            function pointer type that defines a callback for processing an edge.
* \param[in]        vertex_x: first vertex defining an edge. Source vertex in a directed graph.
* \param[in]        edge: data structure containing the edge data.
* \note             this type is used to pass a function that performs some action on an edge during graph traversal.
*/
typedef void (*process_edge_fn)(size_t vertex_x, edgenode_t* edge);

/**
* \brief            structure that represents a graph traverser object.
* \note             this structure is used to store the state and callbacks for graph traversal algorithms such as breadth-first search or depth-first search.
*/
typedef struct graph_traverser_t {
    bool* processed;    /*!< array that indicate whether a vertex has been processed. */
    bool* discovered;   /*!< array that indicate whether a vertex has been discovered*/
    bool terminate;     /*!< boolean flag used to terminate the search early. (used only on depth-first search) */
    size_t* parent;     /*!< array containing the number of the parent of each vertex */
    size_t time;        /*!< value representing how many node have been elaborated so far. (used only on depth-first) */
    size_t* entry_time; /*!< array containing the search entry time on each vertex. (used only on depth-first) */
    size_t* exit_time;  /*!< array containing the search exit time from each vertex. (used only on depth-first) */
    process_vertex_fn process_vertex_early; /*!< function pointer used to process a vertex before its adjacent edges */
    process_vertex_fn process_vertex_late;  /*!< function pointer used to process a vertex after its adjacent edges */
    process_edge_fn process_edge;           /*!< function pointer used to process an edge */
} graph_traverser_t;

enum search_type { BREADTH_FIRST, DEPTH_FIRST };

__declspec(dllexport) graph_traverser_t* graph_traverser_construct(graph_t* graph,
                                                                   process_vertex_fn process_vertex_early,
                                                                   process_vertex_fn process_vertex_late,
                                                                   process_edge_fn process_edge, enum search_type);
__declspec(dllexport) void graph_traverser_clear(graph_traverser_t** traverser);
__declspec(dllexport) void graph_breadth_first_search(graph_t* graph, graph_traverser_t* traverser,
                                                      size_t starting_vertex);
__declspec(dllexport) void graph_depth_first_search(graph_t* graph, graph_traverser_t* traverser,
                                                    size_t starting_vertex);
__declspec(dllexport) int binary_search(data_type array[], data_type key, data_type_compare_fn compare, int low,
                                        int high);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !SEARCH