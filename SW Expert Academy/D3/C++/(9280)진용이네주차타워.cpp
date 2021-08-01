#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int park_costs_per_weight[101];
int car_weights[2001];
int parked[2001];

int main(void)
{
	int TC;
	cin >> TC;
	
	// N: Parking spaces
	// M: Number of cars
	// CAR: Current car
	int N, M, CAR;
	int parking_space;

	// priority_queue<T, container, comparing>
	priority_queue<int, vector<int>, greater<int>> parking_spaces;

	// waiting queue
	queue<int> waiting_queue;

	// answer
	int total_costs = 0;

	for (int test_case = 1; test_case <= TC; test_case++)
	{
		cin >> N >> M;

		for (int i = 1; i <= N; i++) cin >> park_costs_per_weight[i];
		for (int i = 1; i <= M; i++) cin >> car_weights[i];
		
		// parking spaces
		for (int i = 1; i <= N; i++) parking_spaces.push(i);

		for (int i = 0; i < 2 * M; i++)
		{
			// input current car
			cin >> CAR;

			// check in / out
			if (CAR > 0)
			{
				// check possible parking space
				if (parking_spaces.empty()) waiting_queue.push(CAR);
				else
				{
					parking_space = parking_spaces.top();
					parking_spaces.pop();

					// check and sum cost
					parked[CAR] = parking_space;
					total_costs += car_weights[CAR] * park_costs_per_weight[parking_space];
				}
			}
			else
			{
				// park out
				CAR = abs(CAR);
				parking_space = parked[CAR];
				parking_spaces.push(parking_space);

				// until waiting nothing or parking spaces full
				while (waiting_queue.empty() == false && parking_spaces.empty() == false)
				{
					CAR = waiting_queue.front();
					waiting_queue.pop();

					parking_space = parking_spaces.top();
					parking_spaces.pop();

					parked[CAR] = parking_space;
					total_costs += car_weights[CAR] * park_costs_per_weight[parking_space];
				}
			}
		}

		cout << '#' << test_case << ' ' << total_costs << '\n';
		
		// initialize
		while (!parking_spaces.empty()) parking_spaces.pop();
		total_costs = 0;
	}

	return 0;
}