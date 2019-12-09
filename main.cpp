#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

class Person {
  private:
    // >0: infected;
    // 0: helathy;
    // -1: recovered;
    // -2: vaccinated;
    int state;
  public:
    Person() {
      state = 0;
    }

    string status_string() {
      if (state == 0) {
        return "healthy";
      } else if (state == -1) {
        return "recovered";
      } else if (state == -2) {
        return "vaccinated";
      } else {
        return "sick";
      }
    }

    void update() {
      // If sick, reduce days of sickness remaining
      if (state > 1) {
        state--;
      } else if (state == 1) {
        state = -1;
      }
    }

    void infect(int nDays) {
      // Only 'healthy' persons can be infected
      if (state == 0) {
        state = nDays;
      } else {
        cout << "Already infected, cannot reinfect" << endl;
      }
    }

    void vaccinate() {
      // change status to vaccinated
      state = -2;
    }

    bool is_stable() {
      // true if person is 'recovered', else false
      if (state == -1) {
        return true;
      } else {
        return false;
      }
    }
};

class Population {
  private:
    vector<Person> people;
    int n;
    float p;
    int step;

  public:
    // Default Constructor
    Population(int nPeople) {
      n = nPeople;
      p = 0.0;
      step = 0;
      // Build vector of People, length n
      for (int i = 0; i < n; i++) {
        people.push_back(Person());
      }
    }

    // Constructor with addition parameter for p
    Population(int nPeople, float probabilityOfInfection) {
      n = nPeople;
      p = probabilityOfInfection;
      step = 0;
      // Build vector of People, length n
      for (int i = 0; i < n; i++) {
        people.push_back(Person());
      }
    }

    int count_infected() {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        if (people[i].status_string() == "sick") {
          cnt++;
        }
      }
      return cnt;
    }

    void status_string() {
      cout << "In step " << step << "   # sick: " << count_infected() << ": ";
      for (int i = 0; i < n; i++) {
        cout << people[i].status_string() << ", ";
      }
      cout << endl;
    }

    void random_infection() {
      // pick a random number between 0 and n
      int ind = rand() % n;
      cout << "random choice: " << ind << endl;
      people[ind].infect(5);
    }

    void set_probability_of_transfer(float probability) {
      p = probability;
    }

    void vaccinate_randomly(int nVaccinate) {
      // pick n random people to vaccinate
      int ind;
      int vaccinated = 0;
      while (vaccinated <= nVaccinate) {
        ind = rand() % n;
        // Only vaccinate people that are "healthy"
        if (people[ind].status_string() == "healthy") {
          people[ind].vaccinate();
          vaccinated++;
        }
      }
    }

    void update() {
      step++;
      int r;
      for (int i = 0; i < n; i++) {
        //if healthy and next to an infected Person, probability p of infection
        if (people[i].status_string() == "healthy") {
          if ((i < n - 1 && people[i+1].status_string() == "sick") || (i > 0 && people[i-1].status_string() == "sick")) {
            r = rand() % 100;
            if (r < p * 100) {
              people[i].infect(5);
            }
          }
        }
        people[i].update();
      }
    }


};

int main() {
  srand(time(NULL));
  ofstream outputFile;
  // Person joe;
  // int step = 1;
  // for (; ; step++) {
  //   joe.update();
  //   float bad_luck = (float) rand()/(float)RAND_MAX;
  //   if (bad_luck>.95) {
  //     joe.infect(5);
  //   }
  //   cout << "On day " << step << ", Joe is " << joe.status_string() << endl;
  //   if (joe.is_stable()) {
  //     break;
  //   }
  // }

  // Population pop(20);
  // srand (time(NULL));
  // pop.random_infection();
  // while (pop.count_infected() != 0) {
  //   pop.status_string();
  //   pop.update();
  // }


  // output sick population timeseries
  outputFile.open("output.txt");
  for (float p = .1; p < 1; p = p +.4) {
    Population pop(1000);
    pop.set_probability_of_transfer(p);
    pop.random_infection();
    while (pop.count_infected() != 0) {
      outputFile << pop.count_infected() << " ";
      pop.update();
    }
    outputFile << pop.count_infected() << endl;
  }

  outputFile.close();


  // output sick population timeseries
  outputFile.open("outputWithVaccination.txt");
  for (int v = 0; v <= 200; v = v + 50) {
    Population pop2(1000);
    pop2.set_probability_of_transfer(.5);
    pop2.random_infection();
    pop2.vaccinate_randomly(v);
    while (pop2.count_infected() != 0) {
      outputFile << pop2.count_infected() << " ";
      pop2.update();
    }
    outputFile << pop2.count_infected() << endl;
  }
  
  outputFile.close();
};
