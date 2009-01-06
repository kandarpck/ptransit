
// File: check_data.cpp
// Description: Contains functions to check input data for errors 
// and inconsistencies.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cassert>
#include "route.h"

using namespace std;

extern RouteContainer RoutesList;
extern ofstream ferr;

// Check input data for errors and inconsistencies.
void check_data()
{
	Route * route = NULL;	
	int error_cnt = 0, total_cnt = 0;
	RouteIterator iter;

	// For each object in RoutesList.
	cout<<"Sort start times ... ";
	iter = RoutesList.begin();
	for(; iter != RoutesList.end(); iter++) {
		route = (*iter);
		route->sort_start_times();
	}
	cout<<"Done."<<endl;

	cout<<"Checking routes data for inconsistencies ...";
	ferr<<endl<<endl;
	ferr<<"Routes data inconsistency errors"<<endl<<endl;

	// For each object in RoutesList.
	iter = RoutesList.begin();
	for(; iter != RoutesList.end(); iter++) {
		route = (*iter);

		int master_cnt = route->stop_list.size();
		int depot_cnt =  route->stop_count;

		// TODO: why?
		if(route->stop_count == 0)
			continue;

		if(route->stop_count != (int)route->stop_list.size()) {
			// Data mismatch
			ferr<<"Route = "<<setw(6)<<route->short_name;
			ferr<<", Bus id = "<<setw(4)<<route->bus_id; 
			ferr<<", master = "<<setw(4)<<route->stop_list.size();
			ferr<<", depot = "<<setw(4)<<route->stop_count;
			ferr<<", diff = "<<setw(4)<<(master_cnt-depot_cnt)<<endl;
			error_cnt++;
		}
		total_cnt++;
	}
	ferr << endl;
	ferr << "# Total routes = " << total_cnt << endl;
	ferr << "# Mismatch count = " << error_cnt << endl;
	ferr<<endl<<endl;

	// Check for unused routes
	// For each object in RoutesList.
	iter = RoutesList.begin();
	int unused_count = 0;
	for(; iter != RoutesList.end(); iter++) {
		route = (*iter);

		int depot_cnt =  route->stop_count;

		// TODO: why?
		if((depot_cnt == 0) || (route->start_time_list.size() == 0)) {
			ferr<<"Unused Route = "<<setw(6)<<route->short_name;
			ferr<<", Bus id = "<<setw(4)<<route->bus_id << endl; 
			unused_count++;
			continue;
		}
	}

	ferr << endl;
	ferr << "# Unused routes = " << unused_count << endl;
	cout << " Done."<<endl;
}
