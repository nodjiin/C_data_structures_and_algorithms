#include <assert.h>
#include "algorithms/search.h"
#include "search_test.h"
#include "testvalues.h"

graph_t* graph;

void
pv_early(size_t v) {}

void
pv_late(size_t v) {}

void
pe(size_t v, edgenode_t* edge) {}

void
setup() {
    /**
    *  graph structure:
    *  
    *   3  4 <---- 5  6
    *   ^  ^       ^   
    *    \ |       |  
    *      1 ----> 2
    *       ^     ^
    *        \   /
    *          0 
    */
    graph = graph_construct(7, true);
    graph_insert_edge(graph, 0, 2, 0);
    graph_insert_edge(graph, 0, 1, 0);
    graph_insert_edge(graph, 1, 4, 0);
    graph_insert_edge(graph, 1, 3, 0);
    graph_insert_edge(graph, 1, 2, 0);
    graph_insert_edge(graph, 2, 5, 0);
    graph_insert_edge(graph, 5, 4, 0);
}

void
tear_down() {
    graph_clear(&graph);
}

void
bfs_graph_traverser_construct_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, BREADTH_FIRST);

    assert(traverser->discovered != NULL);
    assert(traverser->processed != NULL);
    assert(traverser->parent != NULL);
    assert(traverser->entry_time == NULL);
    assert(traverser->exit_time == NULL);
    assert(traverser->process_vertex_early == pv_early);
    assert(traverser->process_vertex_late == pv_late);
    assert(traverser->process_edge == pe);

    graph_traverser_clear(&traverser);
}

void
dfs_graph_traverser_construct_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, DEPTH_FIRST);

    assert(traverser->discovered != NULL);
    assert(traverser->processed != NULL);
    assert(traverser->parent != NULL);
    assert(traverser->entry_time != NULL);
    assert(traverser->exit_time != NULL);
    assert(traverser->terminate == false);
    assert(traverser->process_vertex_early == pv_early);
    assert(traverser->process_vertex_late == pv_late);
    assert(traverser->process_edge == pe);

    graph_traverser_clear(&traverser);
}

void
graph_traverser_construct_test(void) {
    bfs_graph_traverser_construct_test();
    dfs_graph_traverser_construct_test();
}

void
graph_traverser_clear_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, BREADTH_FIRST);

    graph_traverser_clear(&traverser);

    assert(traverser == NULL);
}

void
graph_breadth_first_search_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, BREADTH_FIRST);

    graph_breadth_first_search(graph, traverser, 0);

    assert(traverser->discovered[0]);
    assert(traverser->parent[0] == GRAPH_PARENT_UNDEFINED);
    assert(traverser->parent[1] == 0);
    assert(traverser->parent[2] == 0);
    assert(traverser->parent[3] == 1);
    assert(traverser->parent[4] == 1);
    assert(traverser->parent[5] == 2);
    assert(traverser->parent[6] == GRAPH_PARENT_UNDEFINED);
    assert(!traverser->discovered[6]);

    graph_traverser_clear(&traverser);
}

void
graph_depth_first_search_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, DEPTH_FIRST);

    graph_depth_first_search(graph, traverser, 0);

    assert(traverser->discovered[0]);
    assert(traverser->parent[0] == GRAPH_PARENT_UNDEFINED);
    assert(traverser->parent[1] == 0);
    assert(traverser->parent[2] == 1);
    assert(traverser->parent[5] == 2);
    assert(traverser->parent[4] == 5);
    assert(traverser->parent[3] == 1);
    assert(traverser->parent[6] == GRAPH_PARENT_UNDEFINED);
    assert(!traverser->discovered[6]);

    graph_traverser_clear(&traverser);
}

void
search_testall(void) {
    setup();
    graph_traverser_construct_test();
    graph_traverser_clear_test();
    graph_breadth_first_search_test();
    graph_depth_first_search_test();
    tear_down();
}