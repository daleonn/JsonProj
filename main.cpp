#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

path main_path_get(){
	path p;
	string s;
	//cin >> p;
	getline(cin, s);
	p = s;
	while (!is_directory(p)){
		cout << "ERROR  " << p << " is not valid path"<< endl
			<<"Enter valid path" << endl ;
		//cin >> p;
		getline(cin, s);
		p = s;
	}
	return p;
} 

void dir_runner(path main_p, ptree &pt){
	for (directory_iterator dir_itr(main_p);
		dir_itr != directory_iterator();
		++dir_itr)
	{
		if (is_directory(*dir_itr)) dir_runner(*dir_itr,pt);
		if (is_regular_file(*dir_itr)){
				path p = *dir_itr;
				/*cout << p.string() << " size : " << file_size(*dir_itr)
				<< " FILENAME : "<< p.filename() << endl;*/
				ptree current_file;
				current_file.put("FILENAME", p.filename().string());
				current_file.put("File Size (Bytes)  ", file_size(*dir_itr) );
				current_file.put("File Path", p.string());
				pt.push_back(make_pair("", current_file));
				}
	}
}

ptree path_reader(){
	cout << "Enter your path" << endl;
	ptree pt;
	ptree files_array;
	path main_path = main_path_get();
	dir_runner(main_path, files_array);
	pt.add_child( "Path ( " + main_path.string() + " )  Files " , files_array);
	return pt;
}


int main(){
	write_json("Directory_Files_output.json", path_reader()); 
	return 0;
}