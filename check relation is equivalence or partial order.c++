// C++ Program for checking
// Equivalence relation
#include <bits/stdc++.h>
using namespace std;

class Relation {
public:
bool checkPartialOrder(set<int> A,set<pair<int, int> > R)
    {
        bool transitive = checkTransitive(R);
        bool antisymmetric = checkAntiSymmetric(R);
        bool reflexive = checkReflexive(A, R);
        return (transitive && antisymmetric && reflexive);
    }
	bool checkEquivalence(set<int> A, set<pair<int, int> > R) {
		bool transitive = checkTransitive(R);
		bool symmetric = checkSymmetric(R);
		bool reflexive = checkReflexive(A, R);
		return (transitive && symmetric && reflexive);
	}

	bool checkTransitive(set<pair<int, int> > R) {
		// Empty relation is always transitive
		if (R.size() == 0) {
			return true;
		}

		// Create a dictionary to store tuple as key value
		// pair
		map<int, set<int> > tup;

		// Creating dictionary of relation where (a) is key
		// and (b) is value
		for (auto i = R.begin(); i != R.end(); i++) {
			if (tup.find(i->first) == tup.end()) {
				set<int> temp;
				temp.insert(i->second);
				tup.insert(
					pair<int, set<int> >(i->first, temp));
			}
			else {
				tup.at(i->first).insert(i->second);
			}
		}

		for (auto a = tup.begin(); a != tup.end(); a++) {

			// Set of all b's related with a
			set<int> all_b_in_aRb = tup.at(a->first);

			// Taking all c's from each b one by one
			for (int b : all_b_in_aRb) {
				if (tup.find(b) != tup.end()
					&& a->first != b) {

					// Set of all c's related with b
					set<int> all_c_in_bRc = tup.at(b);

					// All c's related with each b must be
					// subset of all b's related with a
					for (int c : all_c_in_bRc) {
						if (all_b_in_aRb.find(c)
							== all_b_in_aRb.end()) {
							return false;
						}
					}
				}
			}
		}

		// For all aRb and bRc there exist aRc in relation R
		return true;
	}
	bool checkAntiSymmetric(set<pair<int, int> > R)
    {
        // Empty relation is always anti-symmetric
        if (R.size() == 0) {
            return true;
        }
 
        for (auto i = R.begin(); i != R.end(); i++) {
            if (i->second != i->first) {
 
                // Not a aRa tuple
                // making a mirror tuple
                auto temp = make_pair(i->second, i->first);
 
                if (R.find(temp) != R.end()) {
                    // If bRa tuple exists
                    // in relation R
                    return false;
                }
            }
        }
 
        // bRa tuples does not exist
        // for all aRb in relation R
        return true;
    }

	bool checkSymmetric(set<pair<int, int> > R) {
		// Empty relation is always symmetric
		if (R.size() == 0) {
			return true;
		}

		for (auto i = R.begin(); i != R.end(); i++) {

			// Making a mirror tuple
			auto temp = make_pair(i->second, i->first);

			if (R.find(temp) == R.end()) {

				// If bRa tuple does not exists in relation
				// R
				return false;
			}
		}

		// bRa tuples exists for all aRb in relation R
		return true;
	}

	bool checkReflexive(set<int> A, set<pair<int, int> > R) {
		// Empty relation on a non-empty relation set is never reflexive.
		if (A.size() > 0 && R.size() == 0) {
			return false;
		}
		// Relation defined on an empty set is always reflexive.
		else if (A.size() == 0) {
			return true;
		}

		for (auto i = A.begin(); i != A.end(); i++) {

			// Making a tuple of same element
			auto temp = make_pair(*i, *i);

			if (R.find(temp) == R.end()) {

				// If aRa tuple not exists in relation R
				return false;
			}
		}

		// All aRa tuples exists in relation R
		return true;
	}
};

int main()
{
	// Creating a set A
	set<int> A{ 1, 2, 3, 4 };

	set<pair<int, int> > R;


	R.insert(make_pair(1, 1));
	R.insert(make_pair(1, 3));
	R.insert(make_pair(2, 2));
	R.insert(make_pair(3, 3));
	R.insert(make_pair(3, 1));
	R.insert(make_pair(3, 4));
	R.insert(make_pair(4, 4));
	R.insert(make_pair(4, 3));

	Relation obj;

	
	if (obj.checkEquivalence(A, R)) {
		cout << "Equivalence Relation" << endl;
	}
	else if(obj.checkPartialOrder(A,R)) {
		cout << "Partial order relation " << endl;
	}else{
	    cout<<"Not a equivalence nor partial order"<<endl;
	}

	return 0;
}
