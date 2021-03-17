#include <iostream>
#include <fstream>
#include <memory>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

uint64_t number_of_individuals = 0;
uint64_t number_of_queries = 0;

int main(int argc, char **argv)
{
	auto start = chrono::high_resolution_clock::now();
    uint64_t* node_to_label;
    ifstream file(argv[1]);
    ofstream out_file;
    out_file.open(argv[2]);
    std::vector<vector<uint64_t> > level_grid;
    std::vector<uint64_t> level_finder;
    std::vector<uint64_t> level_index_finder;
    uint64_t level1 = 0;
    uint64_t index1 = 0;
    uint64_t the_parent = 0;

    if (file.is_open())
    {
        file >> number_of_individuals;

        if ( 0 == number_of_individuals)
        {
            out_file << "Cannot parse number_of_individuals" << endl;
        }
        else
        {
            node_to_label = new uint64_t[number_of_individuals];
            //int64_t* temp = new int64_t[number_of_individuals * number_of_individuals];
            level_grid = std::vector<vector<uint64_t> >(number_of_individuals);
            level_finder = std::vector<uint64_t>(number_of_individuals);
            level_index_finder = std::vector<uint64_t>(number_of_individuals);

            for (size_t c = 0; c < number_of_individuals; c++)
            {
                int64_t parent_id;

                file >> parent_id;
                node_to_label[c] = (uint64_t)parent_id;
            }

            for (size_t c = 0; c < number_of_individuals; c++)
            {
                uint64_t level = 0;
                for ( size_t i = c; node_to_label[i] != (uint64_t)-1 ; i = node_to_label[i])
                {
                    ++level;
                }
                level_finder[c] = level;
                level_index_finder[c] = level_grid[level].size();
                level_grid[level].push_back(node_to_label[c]);
            }

            /*out_file << "HASH TABLE ??" << endl;
            for (size_t c = 0; c < number_of_individuals; c++)
            {
                out_file << "Child: " << c  << " parent: " << node_to_label[c] << endl;
            }
            out_file << "level grid:" << endl;
            for (uint64_t i = 0; i < level_grid.size(); i++) {
            	out_file << i << ": " ;
                for (uint64_t j = 0; j < level_grid[i].size(); j++)
                    out_file << level_grid[i][j] << " ";
                out_file << endl;
            }*/

            file >> number_of_queries;

            for (size_t i = 0; i < number_of_queries; i++)
            {
                uint64_t v, query_depth, label, s, v_depth;

                file >> v >> query_depth;

                label = v;

                the_parent = v;
                /*search depth for v */
                for (size_t j = 0; j < query_depth; j++)
                {
                    level1 = level_finder[the_parent] ;
                    index1 = level_index_finder[the_parent];
                    the_parent = level_grid[level1][index1];
                    if(the_parent == (uint64_t)-1)
                    	break;
                }

                out_file << (int64_t)the_parent << endl;

            }
        }
    	auto stop = high_resolution_clock::now();
    	auto duration = duration_cast<seconds>(stop - start);
    	cout << duration.count() << endl;
    }
    else
    {
    	out_file << "Error on reading input file " << endl;
    }

    file.close();
}
