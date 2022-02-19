#include "./includes/whole_includes.h"
#include "./includes/flags.h"

using namespace std;

/// params used
// size : chromosome size -> private simulator
// num_parent: number of individuals per generation -> private simulator
// num_generation : number of iterating generation -> private simulator
// gene_encode : type of gene encode ex> simple int , 4-triplet



int main(int argc, char *argv[])
{
	int **parent;
	int **child;
	int size = 1;
	int num_parent = 1;
	int generation_num = 1;
	//int size = atoi(argv[1]);
	//int num_parent = atoi(argv[2]);
	
	//int generation_num = atoi(argv[3]);


	const flags::args args(argc, argv);

	const auto size_parsed = args.get<int>("size");
	if (size_parsed){
		size = *size_parsed;
		cout << "size: " << size << endl;
	}
	else
		cout << "size: " << size << "(default)" << endl;

	const auto num_parent_parsed = args.get<int>("num_parent");
	if (num_parent_parsed){
		num_parent = *num_parent_parsed;
		cout << "num_parent: " << num_parent << endl;
	}
	else
		cout << "num_parent: " << num_parent << "(defalut)" << endl;

	const auto generation_parsed = args.get<int>("num_generation");
	if (generation_parsed){
		generation_num = *generation_parsed;
		cout << "genertion_num: " << generation_num << endl;
	}
	else 
		cout << "genertion_num: " << generation_num << "(default)" << endl;

	int *fitness_arr = new int[num_parent];

	// file out
	ofstream fout;
	fout.open("a.txt");

	
	// first generation
	parent = new int*[num_parent];
	for(int i=0; i<num_parent; i++)
		parent[i] = int_fixed_size_generation(size, 0, 9);
	// for(int i=0; i<num_parent; i++){
	//     cout << "chromosome" << i << ":" ;
	//     for(int j=0; j<size; j++){
	//         cout <<  parent[i][j];
	//     }
	//     cout << "\n";
	// // }
	
	for(int i=0; i<generation_num; i++){


		//calculate fitness
		for(int i=0; i<num_parent; i++){
			fitness_arr[i] = fitness_sum2Value(parent[i], size, 40);
			//cout << "fitness" << i << ":" << fitness_arr[i] << "\n";
		}

		// make child
		child = new int*[num_parent];
		for (int i=0; i<num_parent; i++){
			child[i] = cross_simple_percent(selection_roulette(parent, fitness_arr, num_parent),selection_roulette(parent, fitness_arr, num_parent), size);
		}
		// for (int i=0; i<num_parent; i++){
		//     cout << "child:";
		//     for (int j=0; j<size; j++)
		//         cout << child[i][j];
		//     cout << "\n";
		// }

		// child mutation
		for (int i=0; i<num_parent; i++){
			child[i] = mutation_simple(child[i], size, 0.001);
		}
		// for (int i=0; i<num_parent; i++){
		//     cout << "mutated_child:";
		//     for (int j=0; j<size; j++)
		//         cout << child[i][j];
		//     cout << "\n";
		// }

		//succeeding generation
		for (int i=0; i< num_parent; i++){
			parent[i] = child[i];
		}
	

	// for(int i=0; i<num_parent; i++){
	//     cout << "final chromosome" << i << ":" ;
	//         for(int j=0; j<size; j++){
	//             cout <<  parent[i][j];
	//         }
	//     cout << "\n";
	// }

	cout << "Generation " << i << " Report::\n";
	int sum_fit = 0;
	for (int i=0; i<num_parent; i++){
		sum_fit += fitness_arr[i];
	}
	double avg_fit = (double)sum_fit/num_parent;
	cout << "Fitness average: " << avg_fit << "\n";
	fout << i << " " << avg_fit << "\n";
	
	int *best_final = end_flag_sum2Value(parent, fitness_arr, num_parent, size, 40);

	cout << "best chromosome: ";
	int sum1 = 0;
	for (int i=0; i<size; i++){
		cout << parent[best_final[0]][i];
		sum1 += parent[best_final[0]][i];
	}
	cout << " with value " << best_final[1] << "sum: " << sum1 << "\n\n" ;

	}
	fout.close();

	return 0;
}
