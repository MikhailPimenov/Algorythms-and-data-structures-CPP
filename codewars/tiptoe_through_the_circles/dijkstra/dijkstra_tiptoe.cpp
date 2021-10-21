#include "dijkstra_tiptoe.h"

static double get_unreachable_maximum(const Graph_t& graph) {
	double maximum = 0.0;
	for (const auto& [vertex, neighbors] : graph)
		for (const auto& [neighbor, distance] : neighbors)
			maximum += distance;
	
	return maximum * 10.0;
}

double dijkstra_tiptoe(const Graph_t& graph, const Vertex_t& start, const Vertex_t& finish) {
	if (graph.find(start) == graph.cend() || graph.find(finish) == graph.cend())
		return -1.0;
	
	const double maximum = get_unreachable_maximum(graph);

	Distances_t distances;
	for (const auto& [vertex, _] : graph)
		distances.insert(std::pair<Vertex_t, double>(vertex, maximum));

	distances.at(start) = 0.0;

	Queue_t queue;
	queue.push_back(start);
	
	while (! queue.empty()) {
		const auto vertex = queue.front();
		queue.pop_front();

		for (const auto& [neighbor, edge_weight] : graph.at(vertex)) {
			if (distances.at(vertex) + edge_weight < distances.at(neighbor)) {
				distances.at(neighbor) = distances.at(vertex) + edge_weight;
				queue.push_back(neighbor);
			}
		}
	}
	return are_equal(distances.at(finish), maximum) ? -1.0 : distances.at(finish);
}
