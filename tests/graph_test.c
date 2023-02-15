#include <assert.h>
#include "data_structures/graph.h"
#include "graph_test.h"
#include "testvalues.h"

void
graph_construct_directed_test(bool directed) {
    graph_t* graph;

    graph = graph_construct(3, directed);

    assert(graph != NULL);
    assert(graph->edges != NULL);
    assert(graph->nvertices = 3);
    assert(graph->nedges == 0);
    assert(graph->is_directed == directed);
}

void
graph_construct_test(void) {
    graph_construct_directed_test(true);
    graph_construct_directed_test(false);
}

undirected_graph_insert_edge_test(void) {
    graph_t* graph;

    graph = graph_construct(3, false);

    graph_insert_edge(graph, 0, 1, TESTVAL1); /* edge between vertex 0 and 1 */
    graph_insert_edge(graph, 0, 2, TESTVAL2); /* edge between vertex 0 and 2 */
    graph_insert_edge(graph, 1, 2, TESTVAL3); /* edge between vertex 1 and 2 */

    assert(graph->edges[0]->y == 2);
    assert(graph->edges[0]->weight == TESTVAL2);
    assert(graph->edges[0]->next->y == 1);
    assert(graph->edges[0]->next->weight == TESTVAL1);
    assert(graph->edges[0]->next->next == NULL);
    assert(graph->edges[1]->y == 2);
    assert(graph->edges[1]->weight == TESTVAL3);
    assert(graph->edges[1]->next->y == 0);
    assert(graph->edges[1]->next->weight == TESTVAL1);
    assert(graph->edges[1]->next->next == NULL);
    assert(graph->edges[2]->y == 1);
    assert(graph->edges[2]->weight == TESTVAL3);
    assert(graph->edges[2]->next->y == 0);
    assert(graph->edges[2]->next->weight == TESTVAL2);
    assert(graph->edges[2]->next->next == NULL);
    assert(graph->nedges == 3);
}

directed_graph_insert_edge_test(void) {
    graph_t* graph;

    graph = graph_construct(3, true);

    graph_insert_edge(graph, 0, 1, TESTVAL1); /* edge between vertex 0 and 1 */
    graph_insert_edge(graph, 0, 2, TESTVAL2); /* edge between vertex 0 and 2 */
    graph_insert_edge(graph, 1, 2, TESTVAL3); /* edge between vertex 1 and 2 */

    assert(graph->edges[0]->y == 2);
    assert(graph->edges[0]->weight == TESTVAL2);
    assert(graph->edges[0]->next->y == 1);
    assert(graph->edges[0]->next->weight == TESTVAL1);
    assert(graph->edges[0]->next->next == NULL);
    assert(graph->edges[1]->y == 2);
    assert(graph->edges[1]->weight == TESTVAL3);
    assert(graph->edges[1]->next == NULL);
    assert(graph->edges[2] == NULL);
    assert(graph->nedges == 3);
}

undirected_graph_remove_edge_test(void) {
    graph_t* graph;

    graph = graph_construct(3, false);
    graph_insert_edge(graph, 0, 1, TESTVAL1); /* edge between vertex 0 and 1 */
    graph_insert_edge(graph, 0, 2, TESTVAL2); /* edge between vertex 0 and 2 */
    graph_insert_edge(graph, 1, 2, TESTVAL3); /* edge between vertex 1 and 2 */

    graph_remove_edge(graph, 0, 2);
    graph_remove_edge(graph, 1, 2);

    assert(graph->edges[0]->y == 1);
    assert(graph->edges[0]->weight == TESTVAL1);
    assert(graph->edges[0]->next == NULL);
    assert(graph->edges[1]->y == 0);
    assert(graph->edges[1]->weight == TESTVAL1);
    assert(graph->edges[1]->next == NULL);
    assert(graph->edges[2] == NULL);
    assert(graph->nedges == 1);
}

directed_graph_remove_edge_test(void) {
    graph_t* graph;

    graph = graph_construct(3, true);
    graph_insert_edge(graph, 0, 1, TESTVAL1); /* edge between vertex 0 and 1 */
    graph_insert_edge(graph, 0, 2, TESTVAL2); /* edge between vertex 0 and 2 */
    graph_insert_edge(graph, 1, 2, TESTVAL3); /* edge between vertex 1 and 2 */

    graph_remove_edge(graph, 0, 2);
    graph_remove_edge(graph, 1, 2);

    assert(graph->edges[0]->y == 1);
    assert(graph->edges[0]->weight == TESTVAL1);
    assert(graph->edges[1] == NULL);
    assert(graph->edges[2] == NULL);
    assert(graph->nedges == 1);
}

void
graph_insert_edge_test(void) {
    undirected_graph_insert_edge_test();
    directed_graph_insert_edge_test();
}

void
graph_remove_edge_test(void) {
    undirected_graph_remove_edge_test();
    directed_graph_remove_edge_test();
}

void
graph_clear_test(void) {
    graph_t* graph;

    graph = graph_construct(3, true);
    graph_insert_edge(graph, 0, 1, TESTVAL1); /* edge between vertex 0 and 1 */
    graph_insert_edge(graph, 0, 2, TESTVAL2); /* edge between vertex 0 and 2 */
    graph_insert_edge(graph, 1, 2, TESTVAL3); /* edge between vertex 1 and 2 */

    graph_clear(&graph);

    assert(graph == NULL);
}

void
graph_testall() {
    graph_construct_test();
    graph_insert_edge_test();
    graph_remove_edge_test();
    graph_clear_test();
}