#include <assert.h>
#include "algorithms/search.h"
#include "search_test.h"
#include "testvalues.h"

graph_t* graph; /* TODO test on undirected graph. */
graph_traverser_t* trv;
data_type sum;

size_t index_early;
size_t v_early[6];
size_t index_late;
size_t v_late[6];

void
pv_early(size_t v) {
    v_early[index_early++] = v;
}

void
pv_late(size_t v) {
    v_late[index_late++] = v;
}

void
pe(size_t x, edgenode_t* edge) {
    assert(edge->weight == edge->y - x); // slight violation of the AAA test pattern
    sum += edge->weight;
}

void
pe_early_exit(size_t x, edgenode_t* edge) {
    sum += edge->weight;
    if (sum == 5) {
        trv->terminate = true;
    }
}

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
    * 
    * the weight of each edge is given by the formula: destination edge - source edge
    */
    graph = graph_construct(7, true);
    graph_insert_edge(graph, 0, 2, 2);
    graph_insert_edge(graph, 0, 1, 1);
    graph_insert_edge(graph, 1, 4, 3);
    graph_insert_edge(graph, 1, 3, 2);
    graph_insert_edge(graph, 1, 2, 1);
    graph_insert_edge(graph, 2, 5, 3);
    graph_insert_edge(graph, 5, 4, -1);
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
    assert(traverser->time == 1);
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

    sum = 0;
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
    assert(sum == 11);

    /* check that we are respecting the correct early/late processing order */
    assert(v_early[0] == 0);
    assert(v_early[1] == 1);
    assert(v_early[2] == 2);
    assert(v_early[3] == 3);
    assert(v_early[4] == 4);
    assert(v_early[5] == 5);
    assert(v_late[0] == 0);
    assert(v_late[1] == 1);
    assert(v_late[2] == 2);
    assert(v_late[3] == 3);
    assert(v_late[4] == 4);
    assert(v_late[5] == 5);

    graph_traverser_clear(&traverser);
}

void
graph_depth_first_search_test(void) {
    graph_traverser_t* traverser;

    traverser = graph_traverser_construct(graph, pv_early, pv_late, pe, DEPTH_FIRST);

    index_early = 0;
    index_late = 0;
    sum = 0;
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
    assert(sum == 11);

    /* check that we are respecting the correct early/late processing order */
    assert(v_early[0] == 0);
    assert(v_early[1] == 1);
    assert(v_early[2] == 2);
    assert(v_early[3] == 5);
    assert(v_early[4] == 4);
    assert(v_early[5] == 3);
    assert(v_late[0] == 4);
    assert(v_late[1] == 5);
    assert(v_late[2] == 2);
    assert(v_late[3] == 3);
    assert(v_late[4] == 1);
    assert(v_late[5] == 0);

    assert(traverser->entry_time[0] == 1);
    assert(traverser->exit_time[0] == 12);
    assert(traverser->entry_time[1] == 2);
    assert(traverser->exit_time[1] == 11);
    assert(traverser->entry_time[2] == 3);
    assert(traverser->exit_time[2] == 8);
    assert(traverser->entry_time[3] == 9);
    assert(traverser->exit_time[3] == 10);
    assert(traverser->entry_time[4] == 5);
    assert(traverser->exit_time[4] == 6);
    assert(traverser->entry_time[5] == 4);
    assert(traverser->exit_time[5] == 7);
    assert(traverser->entry_time[6] == 0);
    assert(traverser->exit_time[6] == 0);

    graph_traverser_clear(&traverser);
}

void
graph_depth_first_search_early_exit_test(void) {
    trv = graph_traverser_construct(graph, NULL, NULL, pe_early_exit, DEPTH_FIRST);

    sum = 0;
    graph_depth_first_search(graph, trv, 0);

    assert(trv->discovered[0]);
    assert(trv->parent[0] == GRAPH_PARENT_UNDEFINED);
    assert(trv->parent[1] == 0);
    assert(trv->parent[2] == 1);
    assert(trv->parent[5] == 2);
    assert(!trv->discovered[3]);
    assert(!trv->discovered[4]);
    assert(!trv->discovered[6]);
    assert(sum == 5);

    graph_traverser_clear(&trv);
}

void
search_testall(void) {
    setup();
    graph_traverser_construct_test();
    graph_traverser_clear_test();
    graph_breadth_first_search_test();
    graph_depth_first_search_test();
    graph_depth_first_search_early_exit_test();
    tear_down();
}