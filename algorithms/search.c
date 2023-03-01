/**
 * \file            search.c
 * \brief           source file containing the definition of search algorithms implemented in this library.
 */

#include <stdio.h>
#include "search.h"
#include "data_structures/memalloc.h"
#include "data_structures/exitcodes.h"

/**
 * \brief           Constructs a new graph traverser.
 * \param[in]       graph: pointer to the graph object to be traversed. `NULL` is not considered a valid input and will cause an early exit
 *                  with INVALID_INPUT status code.
 * \param[in]       process_vertex_early: pointer to a function that processes a vertex before its adjacent edges.
 * \param[in]       process_vertex_late: pointer to a function that processes a vertex after its adjacent edges.
 * \param[in]       process_edge: pointer to a function that processes an edge.
 * \param[in]       type: type of search that this traverser will be used on.
 * \return          a pointer to the newly created graph traverser object.
 * \relates         graph_t
 */
graph_traverser_t*
graph_traverser_construct(graph_t* graph, process_vertex_fn process_vertex_early, process_vertex_fn process_vertex_late,
                          process_edge_fn process_edge, enum search_type type) {
    graph_traverser_t* new_traverser;

    if (graph == NULL) {
        fprintf(stderr,
                "[graph_traverser_construct] Invalid input. Faulty traverse creation request with NULL graph.\n");
        exit(INVALID_INPUT);
    }

    new_traverser = malloc_s(sizeof(graph_traverser_t));
    new_traverser->discovered = calloc_s(graph->nvertices, sizeof(bool));
    new_traverser->processed = calloc_s(graph->nvertices, sizeof(bool));
    new_traverser->parent = malloc_s(sizeof(size_t) * graph->nvertices);
    for (size_t i = 0; i < graph->nvertices; i++) {
        new_traverser->parent[i] = GRAPH_PARENT_UNDEFINED;
    }

    new_traverser->process_edge = process_edge;
    new_traverser->process_vertex_early = process_vertex_early;
    new_traverser->process_vertex_late = process_vertex_late;

    if (type == DEPTH_FIRST) {
        new_traverser->time = 1;
        new_traverser->entry_time = calloc_s(graph->nvertices, sizeof(size_t));
        new_traverser->exit_time = calloc_s(graph->nvertices, sizeof(size_t));
        new_traverser->terminate = false;
    } else {
        new_traverser->entry_time = NULL;
        new_traverser->exit_time = NULL;
    }

    return new_traverser;
}

/**
 * \brief           free the given graph.
 * \param[in]       traverser: pointer to graph pointer.
 * \note            this function will free the memory used by the traverser. The input pointer itself will be set to `NULL`.
 * \relates         graph_t
 */
void
graph_traverser_clear(graph_traverser_t** traverser) {
    if (traverser == NULL || *traverser == NULL) {
        return;
    }

    free((*traverser)->discovered);
    free((*traverser)->parent);
    free((*traverser)->processed);
    free((*traverser)->entry_time);
    free((*traverser)->exit_time);

    free_s(*traverser);
}

/**
 * \brief           constructs a new vertices queue.
 * \param[in]       size: The maximum number of vertices that can be stored in the queue.
 * \return          pointer to the newly created vertices queue object.
 */
static vertices_queue_t*
vqueue_construct(size_t size) {
    vertices_queue_t* new_queue;

    new_queue = malloc_s(sizeof(vertices_queue_t));
    new_queue->vertices = malloc_s(sizeof(size_t) * size);
    new_queue->end = 0;
    new_queue->start = 0;

    return new_queue;
}

/**
 * \brief           frees the memory allocated for a vertices queue.
 * \param[in]       queue: a pointer to the vertices queue to be freed.
 */
static void
vqueue_free(vertices_queue_t* queue) {
    free(queue->vertices);
    free(queue);
}

/**
 * \brief           adds a vertex to the end of a vertices queue.
 * \param[in]       queue: A pointer to the vertices queue where the vertex will be added.
 * \param[in]       vertex: The vertex to be added to the queue.
 * \hideinitializer
 */
#define enqueue(queue, vertex) (queue->vertices[queue->end++] = vertex)

/**
 * \brief           returns the first vertex of the queue and move its head to the next item in line.
 * \param[in]       queue: pointer to the vertices queue where the vertex will be removed from.
 * \return          the vertex that was the first item in the queue.
 * \hideinitializer
 */
#define dequeue(queue)         (queue->vertices[queue->start++])

/**
 * \brief           checks if a vertices queue is not empty.
 * \param[in]       queue: pointer to the vertices queue to be checked.
 * \return          true if there are still elements in the queue, false otherwise.
 * \hideinitializer
 */
#define is_not_empty(queue)    (queue->end > queue->start)

/**
 * \brief           calls process_vertex_early if it has been defined.
 * \param[in]       traverser: traverser object.
 * \param[in]       vertex: vertex to process.
 * \hideinitializer
 */
#define process_vertex_early(traverser, vertex)                                                                        \
    if (traverser->process_vertex_early != NULL)                                                                       \
        traverser->process_vertex_early(vertex);

/**
 * \brief           calls process_vertex_late if it has been defined.
 * \param[in]       traverser: traverser object.
 * \param[in]       vertex: vertex to process.
 * \hideinitializer
 */
#define process_vertex_late(traverser, vertex)                                                                         \
    if (traverser->process_vertex_late != NULL)                                                                        \
        traverser->process_vertex_late(vertex);

/**
 * \brief           calls process_edge if it has been defined.
 * \param[in]       traverser: traverser object.
 * \param[in]       source_vertex: source vertex of the edge to process.
 * \param[in]       edge: edge to process.
 * \hideinitializer
 */
#define process_edge(traverser, source_vertex, edge)                                                                   \
    if (traverser->process_edge != NULL)                                                                               \
        traverser->process_edge(source_vertex, edge);

/**
 * \brief           performs a breadth-first search on a graph object, starting from a given vertex.
 * \param           graph: pointer to the graph to be searched. `NULL` is not considered a valid input and will cause an early exit
 *                  with INVALID_INPUT status code.
 * \param           traverser: pointer to the graph traverser that contains the functions and arrays for processing vertices and edges. `NULL` is not considered
 *                  a valid input and will cause an early exit with INVALID_INPUT status code.
 * \param           starting_vertex: index of the vertex where the search will begin. The given value must be a valid index in the graph object.
 * \note            the graph traverser object is updated with the information gathered during the search, such as parent vertices and processed edges. 
 *                  The functions provided by the traverser are called at appropriate times during the search.
 */
void
graph_breadth_first_search(graph_t* graph, graph_traverser_t* traverser, size_t starting_vertex) {
    vertices_queue_t* queue;
    size_t source_vertex, destination_vertex;
    edgenode_t* edge;

    if (graph == NULL) {
        fprintf(stderr, "[graph_breadth_first_search] Invalid input. Faulty breadth first search on NULL graph.\n");
        exit(INVALID_INPUT);
    }

    if (traverser == NULL) {
        fprintf(stderr,
                "[graph_breadth_first_search] Invalid input. Faulty breadth first search with NULL traverser.\n");
        exit(INVALID_INPUT);
    }

    if (starting_vertex >= graph->nvertices) {
        fprintf(stderr,
                "[graph_breadth_first_search] Invalid input. Faulty breadth first search with starting vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                starting_vertex, graph->nvertices);
        exit(INVALID_INPUT);
    }

    queue = vqueue_construct(graph->nvertices);
    enqueue(queue, starting_vertex);
    traverser->discovered[starting_vertex] = true;

    while (is_not_empty(queue)) {
        source_vertex = dequeue(queue);

        process_vertex_early(traverser, source_vertex);
        traverser->processed[source_vertex] = true;
        edge = graph->edges[source_vertex];

        while (edge != NULL) {
            destination_vertex = edge->y;

            if ((!traverser->processed[destination_vertex]) || graph->is_directed) {
                process_edge(traverser, source_vertex, edge);
            }

            if (!traverser->discovered[destination_vertex]) {
                enqueue(queue, destination_vertex);
                traverser->discovered[destination_vertex] = true;
                traverser->parent[destination_vertex] = source_vertex;
            }

            edge = edge->next;
        }

        process_vertex_late(traverser, source_vertex);
    }

    vqueue_free(queue);
}

/**
 * \brief           check the early termination flag and return if it's true.
 * \param[in]       traverser: traverser object.
 * \hideinitializer
 */
#define check_early_termination(traverser)                                                                             \
    if (traverser->terminate)                                                                                          \
        return;

/**
 * \brief           check if the edge has not been processed yet.
 * \param[in]       graph: graph object.
 * \param[in]       trv: traverser object.
 * \param[in]       source: source vertex of the edge.
 * \param[in]       destination: destination vertex of the edge.
 * \returns         true if the edge has not been processed yet (e.g. this is the first time we <re encountering it), false otherwise.
 * \hideinitializer
 */
#define is_edge_yet_to_process(graph, trv, source, destination)                                                        \
    (graph->is_directed || (!trv->processed[destination] && trv->parent[source] != destination))

/**
 * \brief           performs a recursive depth-first search on a graph, using as source the given vertex.
 * \param[in]       graph: A pointer to the graph_t object representing the graph to be traversed.
 * \param[in]       traverser: A pointer to the graph_traverser_t that stores the traversal state and callbacks.
 * \param[in]       source_vertex: The index of the vertex where the traversal starts.
 */
static void
graph_depth_first_search_recursive(graph_t* graph, graph_traverser_t* traverser, size_t source_vertex) {
    edgenode_t* edge;
    size_t destination_vertex;

    check_early_termination(traverser);
    traverser->discovered[source_vertex] = true;
    traverser->entry_time[source_vertex] = traverser->time++;
    process_vertex_early(traverser, source_vertex);

    edge = graph->edges[source_vertex];
    while (edge != NULL) {
        destination_vertex = edge->y;

        if (!traverser->discovered[destination_vertex]) { /* we found a new vertex, keep recursing */
            traverser->parent[destination_vertex] = source_vertex;
            process_edge(traverser, source_vertex, edge);
            graph_depth_first_search_recursive(graph, traverser, destination_vertex);

        } else if (is_edge_yet_to_process(graph, traverser, source_vertex, destination_vertex)) {
            process_edge(traverser, source_vertex, edge);
        }

        check_early_termination(traverser);
        edge = edge->next;
    }

    process_vertex_late(traverser, source_vertex);
    traverser->exit_time[source_vertex] = traverser->time++;
    traverser->processed[source_vertex] = true;
}

/**
 * \brief           performs a depth-first search on a graph, starting from a given vertex.
 * \param[in]       graph: A pointer to the graph_t object representing the graph to be traversed.`NULL` is not considered a valid input and will cause an early exit
 *                  with INVALID_INPUT status code.
 * \param[in]       traverser: A pointer to the graph_traverser_t that stores the traversal state and callbacks. `NULL` is not considered a valid input and will
 *                  cause an early exit with INVALID_INPUT status code.
 * \param[in]       starting_vertex: The index of the vertex where the traversal starts, must be less than graph->nvertices.
 *                  This function traverses a graph in depth-first order, using graph_traverser_t to store the visited vertices and edges. 
 *                  It also invokes callbacks for pre-visit, post-visit,and edge processing events. 
 *                  The traversal can be terminated early by setting graph_traverser_t->terminate to true in any of the callbacks. 
 */
void
graph_depth_first_search(graph_t* graph, graph_traverser_t* traverser, size_t starting_vertex) {
    if (graph == NULL) {
        fprintf(stderr, "[graph_depth_first_search] Invalid input. Faulty depth first search on NULL graph.\n");
        exit(INVALID_INPUT);
    }

    if (traverser == NULL) {
        fprintf(stderr, "[graph_depth_first_search] Invalid input. Faulty depth first search with NULL traverser.\n");
        exit(INVALID_INPUT);
    }

    if (starting_vertex >= graph->nvertices) {
        fprintf(stderr,
                "[graph_depth_first_search] Invalid input. Faulty depth first search with starting vertex '%zu' "
                "exceeding vertices size '%zu'.\n",
                starting_vertex, graph->nvertices);
        exit(INVALID_INPUT);
    }

    graph_depth_first_search_recursive(graph, traverser, starting_vertex);
}