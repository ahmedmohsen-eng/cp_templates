# Clean Templates Manifest

This manifest lists the files copied into clean_templates/, their original paths, and short topic tags. I will update this file when new templates are added or modified.

Format: path -> original_path : topics

files:
- clean_templates/lambda_functions.cpp -> lambda_functions.cpp : lambdas, captures
- clean_templates/algorithms/greedy/kadane's_algorithm_with_indices.cpp -> algorithms/greedy/kadane's_algorithm_with_indices.cpp : greedy, kadane, max-subarray
- clean_templates/combinatorics/combinatorics_1.cpp -> combinatorics/combinatorics_1.cpp : combinatorics, permutations, combinations
- clean_templates/implemenations/other_people_solutions_and_templates/UVA12148_and_template_of_one_day_difference_check_between_two_days.cpp -> implemenations/other_people_solutions_and_templates/UVA12148_and_template_of_one_day_difference_check_between_two_days.cpp : implementation, date-difference
- clean_templates/graph_theory/bfs/bfs.cpp -> graph_theory/bfs/bfs.cpp : graph, bfs, shortest-path, bipartite, topo
- clean_templates/graph_theory/dfs/connected_components_and_DAG(by_ai).cpp -> graph_theory/dfs/connected_components_and_DAG(by_ai).cpp : dfs, components, topo
- clean_templates/graph_theory/dfs/iterative_dfs.cpp -> graph_theory/dfs/iterative_dfs.cpp : dfs, iterative
- clean_templates/graph_theory/dfs/recursive_dfs.cpp -> graph_theory/dfs/recursive_dfs.cpp : dfs, recursive
- clean_templates/graph_theory/dijkstra/learning_dijkstra.cpp -> graph_theory/dijkstra/learning_dijkstra.cpp : dijkstra, shortest-path, pq
- clean_templates/graph_theory/dijkstra/learning_dikjstra_building_path.cpp -> graph_theory/dijkstra/learning_dikjstra_building_path.cpp : dijkstra, path-reconstruction
- clean_templates/graph_theory/dsu/learning_dsu.cpp -> graph_theory/dsu/learning_dsu.cpp : dsu, union-find
- clean_templates/graph_theory/dsu/applications_for_example_mst/kruksal_algorithm_for_mst_____mst_minimum_spanning_tree.cpp -> graph_theory/dsu/applications_for_example_mst/kruksal_algorithm_for_mst_____mst_minimum_spanning_tree.cpp : kruskal, mst
- clean_templates/graph_theory/dsu/applications_for_example_mst/mst_to_target_from_x_to_y_(kruskal_implemnetation_also).cpp -> graph_theory/dsu/applications_for_example_mst/mst_to_target_from_x_to_y_(kruskal_implemnetation_also).cpp : mst, kruskal, path
- clean_templates/math/number_theory/fast_pow.cpp -> math/number_theory/fast_pow.cpp : modular-exponentiation
- clean_templates/math/number_theory/number_theory1.cpp -> math/number_theory/number_theory1.cpp : number-theory, assorted
- clean_templates/math/number_theory/number_theroy_advanced_algorithms.cpp -> math/number_theory/number_theroy_advanced_algorithms.cpp : number-theory, advanced
- clean_templates/math/number_theory/number_thoery_2_with_fact_and_nPr_and_nCr.cpp -> math/number_theory/number_thoery_2_with_fact_and_nPr_and_nCr.cpp : factorials, nPr, nCr

Notes:
- Comments were cleaned: only high-level, complexity, I/O and critical DSA notes are kept. Error/debug comments were grouped as a block at the end of each file.
- Files were formatted using Google-style clang-format.

